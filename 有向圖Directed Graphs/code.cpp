// 10920110 王柏甯 10833230 李郁含
#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include <stack>
#include<iomanip> // setw, setprecision
#include <queue>

using namespace std;

struct Data {  // 放資料
    char putID[10] ;       // 學生id
    char getID[10] ;     // 學生id
    float weight ;       // 權重
};

struct adData {  // 放資料
    char ID[10] ;       // 學生id
    float weight ;       // 權重 (發訊者為-1)
    adData* get;      // 收訊者
    adData* next;     // 下一個發訊者(收訊者無)
    bool visited;   // 讓後面走訪時用的
};

struct bfsData {  // 放資料
    char ID[10] ;       // 學生id
    int bfs_influence_num; // 發訊者的影響力 (收訊者為-1)
    bfsData* get;      // 收訊者
    bfsData* next;     // 下一個發訊者(收訊者無)
};

class DataList {
    public :
        string fileName ;
        int length ;  // 資料數
        vector<Data> bank;

        DataList() {
          length = 0 ;
        } // dataList

        void checkBinfileline() { // 確認資料數(bin)
            if ( length != 0 )
              deleteBank() ;

            length = 0 ;
            FILE * fp = NULL;
            // int c ;

            char out1[10] ;
            char out2[2] ;
            char out3[10] ;
            float out4 ;

            fp = fopen(fileName.c_str(), "rb");

            while( fread( out1 ,sizeof( char ), 8 , fp ) != 0 ) {

              fread( out2 ,sizeof( char ), 2 , fp );
              fread( out3 ,sizeof( char ), 10 , fp );
              fread(  (void*)(&out4) ,sizeof( out4 ), 1 , fp );
              length ++;

            } //while

            fclose(fp);

        } // checkBinfileline ()

        bool empty() {

          if ( length == 0 )
            return true ;
          else
            return false ;

        } // empty()

        void arrayClean( char id1[10] , char id2[10]   ) { // 清空陣列
            for ( int j = 0 ; j < 10 ; j++ ) {
                id1[j] = '\0' ;

            } // for()

            for ( int j = 0 ; j < 10 ; j++ ) {
              id2[j] = '\0' ;
            } // for()

        } // arrayClean()

        bool isBin ( string input ) { // 處理bin檔
          fileName = "pairs"+input+".bin" ;
          FILE * infile = NULL;
          infile = fopen(fileName.c_str(),"r") ;

          if(infile == NULL ) {          // bin檔不存在
            cout<<endl<<fileName<<" does not exist!" << endl ;
            return false ;

          } // if ()

          //----------------------------------建立資料庫
          checkBinfileline();
          Data now ;
          for ( int x = 0 ; x < length  ; x++ ) {
            char out[100] ;
            bank.push_back(now) ;
            char in[10] ;
            arrayClean( bank[x].getID, bank[x].putID ) ;
            int y = 0 ;
            fread( in ,sizeof( char ), 1 , infile );
            for (  ; y<8 && strcmp( in ,"\0") != 0 ; y++ ) {
              strcat( bank[x].putID, in ) ;
              fread( in ,sizeof( char ), 1 , infile );

            } // for()

            if ( y == 8 )
                y = 1 ;
            else
                y = 2 ;

            fread( out ,sizeof( char ), y , infile );
            y = 0 ;

            fread( in ,sizeof( char ), 1 , infile );
            for (  ; y<8 && strcmp( in ,"\0") != 0 ; y++ ) {
              strcat( bank[x].getID, in ) ;
              fread( in ,sizeof( char ), 1 , infile );

            } // for()

            if ( y == 8 )
                y = 1 ;
            else
                y = 2 ;

            fread( out ,sizeof( char ), y , infile );

            fread( (void*)(&bank[x].weight) ,sizeof( bank[x].weight ), 1 , infile );


          } // for()

          fclose(infile);
          printBank() ;   // ------------------------------------------bin檔內容讀入測試處(<--)
          return true ;
        } // isBin ()

        void printBank() {                    // 測試用印出
          for ( int x = 0 ; x < length ; x++ ) {

            for ( int y = 0 ; ( y < 8 ) && ( bank[x].getID[y] != '\0' ) ; y++ ) {
              cout << bank[x].putID[y] ;

            } // for()

            cout << "-------" ;
            for ( int y = 0 ;  ( y < 8 ) && ( bank[x].putID[y] != '\0' ) ; y++ ) {
              cout << bank[x].getID[y] ;
            } // for()

            cout << "\t" ;

            cout << bank[x].weight << endl ;

          } // for()

        } // printBank()

        void deleteBank() {
          bank.clear() ;
        } // ()

} ;

class adjaceLists{
  private :
    int IDnum ;
    int nodes ;

  public :
    adData* adList;

	adData* getadList(){
  	  return adList;
	} // getIDnum

	adjaceLists () {
      IDnum = 0 ;
      nodes = 0 ;
	} // adjaceLists

  	bool empty(){
  		if ( IDnum == 0 )
  		  return true;
  	    return false;
	} //empty
    void creatList( int length, vector<Data> bank ) {
      IDnum = 0 ;
      nodes = 0 ;
      adData* temp = NULL ;
      adList = NULL ;
      for( int i = 0 ; i < length ; i++ ) {

        temp = findID ( bank[i].putID ) ; //確認好發訊者學號 不管是找不到而新增的還是找到的
        putList( temp, bank[i] ) ;

      } // for()

      //printList() ;
      cout << endl << "<<< There are "<< IDnum << " IDs in total. >>>" << endl ;
      cout << endl << "<<< There are " << nodes << " nodes in total. >>>" << endl ;

    } // creatList()

    adData* findID ( char in[] ) {
        adData* temp = adList ;
        if (adList == NULL) {
          adList = new adData ;
          adList->next = NULL ;
          adList->get = NULL ;
          strcpy( adList->ID, in ) ;
          adList->weight = -1 ;
          IDnum++ ;
          return adList ;
        } // if()
        adData* last = temp ;                                          //主陣列必須依照學號字串由小到大排序
        while ( (strcmp( temp->ID, in ) != 0 ) &&  strcmp( temp->ID, in ) < 0 && ( temp->next != NULL )  ) {
            last = temp ;
            temp = temp->next ;
        } // while ()
                        //新的發訊者的get肯定是NULL                        //  strcmp( temp->ID, in ) < 0 && ( temp->next != NULL )
        if (  strcmp( temp->ID, in ) != 0 )  {  // 新的發訊者  代表是因為找不到才停下來( 可能在中間            可能到底都還找不到 )
          if ( temp->next == NULL && strcmp( temp->ID, in ) < 0 ) {  // 增加尾
            temp->next = new adData ;
            temp = temp->next ;
            temp->next = NULL ;
            temp->get = NULL ;
          } // if ()
          else if ( last == temp && strcmp( temp->ID, in ) > 0 ) { // 替換頭
            adList = new adData ;
            adList->next =temp ;
            adList->get = NULL ;
            temp = adList ;
          } // else if ()
          else {
            last->next = new adData ;
            last = last->next ;
            last->next = temp ;
            last->get = NULL ;
            temp = last ;
          } // else
          strcpy( temp->ID, in ) ;
          temp->weight = -1 ;
          IDnum++ ;
        } // if
        return temp ;
    } // findID

    void putList( adData* input, Data target ) {  // 放入收訊者
      if (input->get == NULL) {
        input->get = new adData ;
        input->get->get = NULL ;
        strcpy( input->get->ID, target.getID ) ;
        input->get->weight = target.weight ;
        nodes++ ;
        return ;
      } // if ()

      adData* temp = input->get ;
      adData* last = temp ;
      while( ( temp->weight >= target.weight ) && temp->get != NULL ) { // 【量化權重】由大到小排序
        last = temp ;
        temp = temp->get ;

      } // while

      if ( temp->get == NULL && ( temp->weight >= target.weight ) ) { // 增加尾
        temp->get = new adData ;
        temp = temp->get ;
        temp->get = NULL ;
        strcpy( temp->ID, target.getID ) ;
        temp->weight = target.weight ;
      } // if ()
      else if ( last == temp && ( temp->weight < target.weight ) ) {  // 替換頭
        input->get = new adData ;
        input->get->get = temp ;
        temp = input->get ;
        strcpy( temp->ID, target.getID ) ;
        temp->weight = target.weight ;
      } // else if ()
      else {
        last->get = new adData ;
        last = last->get ;
        last->get = temp ;
        temp = last ;
        strcpy( temp->ID, target.getID ) ;
        temp->weight = target.weight ;
      } // else

      nodes++ ;
      findID ( target.getID ) ;

    } // putList()

    void printList() {
      adData* tempList = adList ;
      adData* tempGet = NULL ;
      while ( tempList != NULL ) {
        cout << endl << "*" << tempList->ID ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          cout << " --- " << tempGet->ID  ;
          tempGet = tempGet->get ;
        } // while

        tempList = tempList->next ;

      } // while

       //deleteList()  ;
    } // printList

    void deleteList() {
      adData* tempList = adList ;
      adData* tempGet = NULL ;
      adData* del = NULL ;
      adList = NULL ;
      while ( tempList != NULL ) {
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          del = tempGet ;
          tempGet = tempGet->get ;
          delete del ;
        } // while

        del = tempList ;
        tempList = tempList->next ;
        delete del ;

      } // while
    } // deleteList()

    void output( string name ) {   // 建立adj檔
      FILE * fp = NULL;
      string fileName = "pairs"+name+".adj" ;
      fp = fopen(fileName.c_str(), "w+");
      if(!fp) {
        perror("目標檔案建立失敗");
        return ;
      } // if()
      adData* tempList = adList ;
      adData* tempGet = NULL ;
      fprintf( fp,"<<< There are %d IDs in total. >>>\n", IDnum ) ;
      int i = 1 ;
      int j = 1 ;
      while ( tempList != NULL ) {
        fprintf( fp,"[%3d] %s: \n", i, tempList->ID ) ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          fprintf( fp,"\t(%2d) %s,", j, tempGet->ID ) ;
          fprintf( fp,"%6g", tempGet->weight ) ;
          if ( j % 10 == 0 )
            fprintf( fp,"\n" ) ;
          j++ ;
          tempGet = tempGet->get ;
        } // while

        fprintf( fp,"\n" ) ;
        i++ ;
        j = 1 ;
        tempList = tempList->next ;
      } // while
      fprintf( fp,"<<< There are %d nodes in total. >>>\n", nodes ) ;
      fclose(fp);
    } // outPut()
};

class BFS{
  private :
    int bfsnum ;
    bfsData* bfsList;
    adData* askList ;
    int asknum ;
    int testnum ;
  public :

    BFS() {
      bfsnum = 0 ;
      bfsList = NULL ;
    } // BFS()

  	bool empty(){
  		if ( bfsnum == 0 )
  		  return true;
  	    return false;
	} //empty
	void deletebfs() {
      bfsData* tempList = bfsList ;
      bfsData* tempGet = NULL ;
      bfsData* del = NULL ;
      bfsList = NULL ;
      while ( tempList != NULL ) {
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          del = tempGet ;
          tempGet = tempGet->get ;
          delete del ;
        } // while

        del = tempList ;
        tempList = tempList->next ;
        delete del ;

      } // while
    } // deletebfs
  	void initial_visited( adData* list ) {
      adData* tempList = list ;
      adData* tempGet = NULL ;
      while ( tempList != NULL ) {
        tempList->visited = false ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          tempGet->visited = false ;
          tempGet = tempGet->get ;
        } // while
        tempList = tempList->next ;
      } // while
    } // initial_visited

    adData* find_putID( adData* list, adData* tempGet ) {
      adData* tempList = list ;
      while ( tempList != NULL ) {
        if ( strcmp( tempList->ID, tempGet->ID ) == 0  )
          return tempList;
        tempList = tempList->next ;
      } // while
      return NULL;
    } // find_putID

  	bfsData* add_getIDlist( bfsData* getIDlist, int &temp_bfs_influence_num, adData* target ) {  // 放入收訊者
      if (getIDlist == NULL) {
        getIDlist = new bfsData ;
        getIDlist->get = NULL ;
        getIDlist->bfs_influence_num = -1;
        strcpy( getIDlist->ID, target->ID ) ;
        temp_bfs_influence_num++ ;
        return getIDlist;
      } // if ()

      bfsData* temp = getIDlist ;
      bfsData* last = temp ;                            // 依照學號字串由小到大排序
      while ( (strcmp( temp->ID, target->ID ) != 0 ) &&  strcmp( temp->ID, target->ID ) < 0 && ( temp->get != NULL )  ) {
            last = temp ;
            temp = temp->get ;
      } // while ()
      if ( strcmp( temp->ID, target->ID ) != 0 ){
      	if ( temp->get == NULL && strcmp( temp->ID, target->ID ) < 0 ) { // 增加尾
          temp->get = new bfsData ;
          temp = temp->get ;
          temp->get = NULL ;
          temp->bfs_influence_num = -1;
          strcpy( temp->ID, target->ID ) ;
        } // if ()
        else if ( last == temp && strcmp( temp->ID, target->ID ) > 0 ) {  // 替換頭
          getIDlist = new bfsData ;
          getIDlist->get = temp ;
          temp = getIDlist ;
          temp->bfs_influence_num = -1;
          strcpy( temp->ID, target->ID ) ;
        } // else if ()
        else {
          last->get = new bfsData ;
          last = last->get ;
          last->get = temp ;
          temp = last ;
          temp->bfs_influence_num = -1;
          strcpy( temp->ID, target->ID ) ;
        } // else
      	temp_bfs_influence_num++ ;
	  } // if
	  return getIDlist;
    } // add_getID

  	void add_putIDlist( bfsData* smallest_getID, int temp_bfs_influence_num, adData* target ){
  	    bfsData* temp = bfsList ;
        if (bfsList == NULL) {
          bfsList = new bfsData ;
          bfsList->next = NULL ;
          bfsList->get = smallest_getID ;
          bfsList->bfs_influence_num = temp_bfs_influence_num;
          strcpy( bfsList->ID, target->ID ) ;
          bfsnum++ ;
          return ;
        } // if()
        bfsData* last = temp ;                                          //主陣列必須依照影響力由大到小排序
        while ( ( temp->bfs_influence_num >= temp_bfs_influence_num ) && temp->next != NULL ) {
            last = temp ;
            temp = temp->next ;
        } // while ()
        if ( temp->next == NULL && ( temp->bfs_influence_num >= temp_bfs_influence_num ) ) {  // 增加尾
          temp->next = new bfsData ;
          temp = temp->next ;
          temp->next = NULL ;
        } // if ()
        else if ( last == temp && ( temp->bfs_influence_num < temp_bfs_influence_num ) ) { // 替換頭
          bfsList = new bfsData ;
          bfsList->next =temp ;
          temp = bfsList ;
        } // else if ()
        else {
          last->next = new bfsData ;
          last = last->next ;
          last->next = temp ;
          temp = last ;
        } // else
        temp->get = smallest_getID ;
        strcpy( temp->ID, target->ID ) ;
        temp->bfs_influence_num = temp_bfs_influence_num;
        bfsnum++ ;
	} // add_putID
  	void bfs_traversals_create(adjaceLists dataList) {
      bfsnum = 0 ;
      adData* tempList = dataList.getadList() ;
      adData* tempGet = NULL ;
      adData* target_putID = NULL ;
      bfsList = NULL ;
      while ( tempList != NULL ) {
      	initial_visited(dataList.getadList());
      	queue<adData* > q;
      	tempList->visited = true;
        q.push(tempList);
        int temp_bfs_influence_num = 0; // 發訊者的影響力 (收訊者為-1)
        bfsData* smallest_getID = NULL ;
        while( !q.empty() ){
        	adData* temp = q.front();
        	q.pop();
        	tempGet = temp->get;
        	while ( tempGet != NULL ){
			    target_putID = find_putID( dataList.getadList(), tempGet );
			    if ( target_putID != NULL ){
			      if ( !target_putID->visited ){
			      	smallest_getID = add_getIDlist( smallest_getID, temp_bfs_influence_num, tempGet );
			      	target_putID->visited = true;
			      	q.push(target_putID);
				  } // if
				} //if
				else
				  smallest_getID = add_getIDlist( smallest_getID, temp_bfs_influence_num, tempGet );
			    tempGet = tempGet->get;
			} // while
		} // while
		add_putIDlist( smallest_getID, temp_bfs_influence_num, tempList ); // 將第一個getID接回發訊者(增加發訊者)
        tempList = tempList->next ;
      } // while
      //printbfs() ;
      cout << endl << "<<< There are "<< bfsnum << " IDs in total. >>>" << endl ;
    } // creatList()

  	void bfs_traversals_create2(adjaceLists dataList) {
      bfsnum = 0 ;
      bool out = false ;
      askList = copyList( dataList.getadList() ) ;
      adData* tempList = dataList.getadList() ;
      adData* tempGet = NULL ;
      adData* target_putID = NULL ;
      bfsList = NULL ;
      while ( tempList != NULL ) {
      	initial_visited(dataList.getadList());
      	queue<adData* > q;
      	tempList->visited = true;
        q.push(tempList);
        out = checkList( dataList.getadList(), tempList ) ;
        int temp_bfs_influence_num = 0; // 發訊者的影響力 (收訊者為-1)
        bfsData* smallest_getID = NULL ;
        while( !q.empty() ){
        	adData* temp = q.front();
        	q.pop();
        	tempGet = temp->get;
        	while ( tempGet != NULL ){
			    target_putID = find_putID( dataList.getadList(), tempGet );
			    if ( target_putID != NULL ){
			      if ( !target_putID->visited ){
			      	smallest_getID = add_getIDlist( smallest_getID, temp_bfs_influence_num, tempGet );
			      	target_putID->visited = true;
			      	if (out==false)
			      	  q.push(target_putID);

			      	out = checkList( dataList.getadList(), target_putID ) ;

				  } // if
				} //if
				else
				  smallest_getID = add_getIDlist( smallest_getID, temp_bfs_influence_num, tempGet );
			    tempGet = tempGet->get;
			} // while
		} // while
		add_putIDlist( smallest_getID, temp_bfs_influence_num, tempList ); // 將第一個getID接回發訊者(增加發訊者)
        tempList = tempList->next ;
      } // while
      //printbfs() ;
      cout << endl << "<<< There are "<< bfsnum << " IDs in total. >>>" << endl ;
    } // creatList2()

    bool checkList( adData* inList, adData* in ) {
        while( inList != NULL && strcmp( inList->ID , in->ID ) != 0 ) {
          inList = inList->next ;
        } // while
        adData* temp = inList ;
        adData* check = askList ;
        bool out = false ;
        while( temp != NULL ) {
          check = askList ;
          out = false ;
          while ( check != NULL && out == false  ) {
            if ( strcmp( check->ID , temp->ID ) == 0 ) {
              if ( check->visited == false ) {
                check->visited = true ;
                testnum++ ;
              } // if ()

              out = true ;
            } // if ()

            check = check->next ;
          } // while ()

          temp = temp->get ;
        } // while()

        if ( asknum == testnum )
          return true ;
        else
          return false ;

    } // checkList()

    adData* copyList( adData* inList ) {
      adData* temp ;
      askList = new adData ;
      strcpy( askList->ID, inList->ID ) ;
      askList->visited = false ;
      askList->next = NULL ;
      inList = inList->next ;
      temp = askList ;
      asknum = 1 ;
      while( inList != NULL ) {
        temp->next = new adData ;
        temp = temp->next ;
        strcpy( temp->ID, inList->ID ) ;
        temp->visited = false ;
        temp->next = NULL ;
        asknum++ ;
        inList = inList ->next ;
      } // while()

      testnum = 0 ;

      return askList ;

    } // copyList()

    void printbfs() { // test
      bfsData* tempList = bfsList ;
      bfsData* tempGet = NULL ;
      while ( tempList != NULL ) {
        cout << endl << "*" << tempList->ID ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          cout << " --- " << tempGet->ID  ;
          tempGet = tempGet->get ;
        } // while

        tempList = tempList->next ;

      } // while
    } // printbfs
    void write( string name ) {   // 建立cnt檔
      FILE * fp = NULL;
      string fileName = "pairs"+name+".cnt" ;
      fp = fopen(fileName.c_str(), "w+");
      if(!fp) {
        perror("目標檔案建立失敗");
        return ;
      } // if()
      bfsData* tempList = bfsList ;
      bfsData* tempGet = NULL ;
      fprintf( fp,"<<< There are %d IDs in total. >>>\n", bfsnum ) ;
      int i = 1 ;
      int j = 1 ;
      while ( tempList != NULL ) {
        fprintf( fp,"[%3d] %s(%d): \n", i, tempList->ID, tempList->bfs_influence_num ) ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          fprintf( fp,"\t(%2d) %s", j, tempGet->ID ) ;
          if ( j % 10 == 0 )
            fprintf( fp,"\n" ) ;
          j++ ;
          tempGet = tempGet->get ;
        } // while

        fprintf( fp,"\n" ) ;
        i++ ;
        j = 1 ;
        tempList = tempList->next ;
      } // while
      fclose(fp);
    } // write()
};

class Influence{
  private :
    int bfsnum ;
    bfsData* bfsList;
    adData* askList ;
    float threshold ;
    int asknum ;
    int testnum ;
  public :

    Influence() {
      bfsnum = 0 ;
      threshold = 0.0 ;
      bfsList = NULL ;
    } // BFS()

  	bool empty(){
  		if ( bfsnum == 0 )
  		  return true;
  	    return false;
	} //empty
	void deletebfs() {
      bfsData* tempList = bfsList ;
      bfsData* tempGet = NULL ;
      bfsData* del = NULL ;
      bfsList = NULL ;
      while ( tempList != NULL ) {
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          del = tempGet ;
          tempGet = tempGet->get ;
          delete del ;
        } // while

        del = tempList ;
        tempList = tempList->next ;
        delete del ;

      } // while
    } // deletebfs
  	void initial_visited( adData* list ) {
      adData* tempList = list ;
      adData* tempGet = NULL ;
      while ( tempList != NULL ) {
        tempList->visited = false ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          tempGet->visited = false ;
          tempGet = tempGet->get ;
        } // while
        tempList = tempList->next ;
      } // while
    } // initial_visited

    adData* find_putID( adData* list, adData* tempGet ) {
      adData* tempList = list ;
      while ( tempList != NULL ) {
        if ( strcmp( tempList->ID, tempGet->ID ) == 0  )
          return tempList;
        tempList = tempList->next ;
      } // while
      return NULL;
    } // find_putID

  	bfsData* add_getIDlist( bfsData* getIDlist, int &temp_bfs_influence_num, adData* target ) {  // 放入收訊者
      if (getIDlist == NULL) {
        getIDlist = new bfsData ;
        getIDlist->get = NULL ;
        getIDlist->bfs_influence_num = -1;
        strcpy( getIDlist->ID, target->ID ) ;
        temp_bfs_influence_num++ ;
        return getIDlist;
      } // if ()

      bfsData* temp = getIDlist ;
      bfsData* last = temp ;                            // 依照學號字串由小到大排序
      while ( (strcmp( temp->ID, target->ID ) != 0 ) &&  strcmp( temp->ID, target->ID ) < 0 && ( temp->get != NULL )  ) {
            last = temp ;
            temp = temp->get ;
      } // while ()
      if ( strcmp( temp->ID, target->ID ) != 0 ){
      	if ( temp->get == NULL && strcmp( temp->ID, target->ID ) < 0 ) { // 增加尾
          temp->get = new bfsData ;
          temp = temp->get ;
          temp->get = NULL ;
          temp->bfs_influence_num = -1;
          strcpy( temp->ID, target->ID ) ;
        } // if ()
        else if ( last == temp && strcmp( temp->ID, target->ID ) > 0 ) {  // 替換頭
          getIDlist = new bfsData ;
          getIDlist->get = temp ;
          temp = getIDlist ;
          temp->bfs_influence_num = -1;
          strcpy( temp->ID, target->ID ) ;
        } // else if ()
        else {
          last->get = new bfsData ;
          last = last->get ;
          last->get = temp ;
          temp = last ;
          temp->bfs_influence_num = -1;
          strcpy( temp->ID, target->ID ) ;
        } // else
      	temp_bfs_influence_num++ ;
	  } // if
	  return getIDlist;
    } // add_getID

  	void add_putIDlist( bfsData* smallest_getID, int temp_bfs_influence_num, adData* target ){
  	    bfsData* temp = bfsList ;
        if (bfsList == NULL) {
          bfsList = new bfsData ;
          bfsList->next = NULL ;
          bfsList->get = smallest_getID ;
          bfsList->bfs_influence_num = temp_bfs_influence_num;
          strcpy( bfsList->ID, target->ID ) ;
          bfsnum++ ;
          return ;
        } // if()
        bfsData* last = temp ;                                          //主陣列必須依照影響力由大到小排序
        while ( ( temp->bfs_influence_num >= temp_bfs_influence_num ) && temp->next != NULL ) {
            last = temp ;
            temp = temp->next ;
        } // while ()
        if ( temp->next == NULL && ( temp->bfs_influence_num >= temp_bfs_influence_num ) ) {  // 增加尾
          temp->next = new bfsData ;
          temp = temp->next ;
          temp->next = NULL ;
        } // if ()
        else if ( last == temp && ( temp->bfs_influence_num < temp_bfs_influence_num ) ) { // 替換頭
          bfsList = new bfsData ;
          bfsList->next =temp ;
          temp = bfsList ;
        } // else if ()
        else {
          last->next = new bfsData ;
          last = last->next ;
          last->next = temp ;
          temp = last ;
        } // else
        temp->get = smallest_getID ;
        strcpy( temp->ID, target->ID ) ;
        temp->bfs_influence_num = temp_bfs_influence_num;
        bfsnum++ ;
	} // add_putID
  	void bfs_traversals_create(adjaceLists dataList) {
      bfsnum = 0 ;
      askList = copyList( dataList.getadList() ) ;
      adData* tempList = dataList.getadList() ;
      adData* tempGet = NULL ;
      adData* target_putID = NULL ;
      bfsList = NULL ;
      bool out = false ;
      cout << endl << "Input a real number in [0,1]: " ;
      cin >> threshold ;
      while ( tempList != NULL ) {
        // cout << endl ;
      	initial_visited(dataList.getadList());
      	queue<adData* > qGet;
      	stack<adData* > q;
      	tempList->visited = true;
        q.push(tempList);
        out = checkList( dataList.getadList(), tempList ) ;
        int temp_bfs_influence_num = 0; // 發訊者的影響力 (收訊者為-1)
        bfsData* smallest_getID = NULL ;
        adData* nextGet = tempList->get ;
        while( nextGet != NULL ) {
          if ( nextGet->weight >= threshold )
            qGet.push( nextGet );
          nextGet = nextGet->get ;
        } // while
        while( !qGet.empty() ) {
          q.push( qGet.front() );
          qGet.pop();
        } // while

        while( !q.empty() ){
        	adData* temp = q.top();
        	q.pop();
        	tempGet = temp->get;
        	  while ( tempGet != NULL ){
			    target_putID = find_putID( dataList.getadList(), tempGet );
			    // cout << "-->" << target_putID->ID ;
			    if ( target_putID != NULL ){
			      if ( !target_putID->visited ){
			      	smallest_getID = add_getIDlist( smallest_getID, temp_bfs_influence_num, tempGet );
			      	target_putID->visited = true;

			      	adData* isList = dataList.getadList() ;
			      	if ( out == false ) {
			      	  while( strcmp( isList->ID, tempGet->ID ) != 0 ) {
                        isList = isList->next ;
			      	  } // while
                      nextGet = isList->get ;
                      while( nextGet != NULL ) {
                        if ( nextGet->weight >= threshold )
                          qGet.push( nextGet );
                        nextGet = nextGet->get ;
                      } // while
                      while( !qGet.empty() ) {
                        q.push( qGet.front() );
                        qGet.pop();
                      } // while
			      	} // if ()
			      	out = checkList( dataList.getadList(), target_putID ) ;
				  } // if
				  else {
                    target_putID = NULL ;
				  } // else
				} //if
				else {
				  smallest_getID = add_getIDlist( smallest_getID, temp_bfs_influence_num, tempGet );
				} // else
				if ( target_putID != NULL ) {
			      tempGet = target_putID->get;
				} // if ()
                else {
                  tempGet = NULL ;
                } // else
			  } // while
		} // while
		add_putIDlist( smallest_getID, temp_bfs_influence_num, tempList ); // 將第一個getID接回發訊者(增加發訊者)
        tempList = tempList->next ;
      } // while
      //printbfs() ;
      cout << endl << "<<< There are "<< bfsnum << " IDs in total. >>>" << endl ;
    } // creatList()

    bool checkList( adData* inList, adData* in ) {
        adData* now = inList ;
        while( now != NULL && strcmp( now->ID , in->ID ) != 0 ) {
          now = now->next ;
        } // while
        adData* temp = now ;
        adData* check = askList ;
        bool out = false ;
        bool stop = false ;
        while( ( now != NULL ) && ( stop == false ) ) {
          check = askList ;
          out = false ;
          while ( check != NULL && out == false  ) {
            if ( strcmp( check->ID , now->ID ) == 0 ) {
              if ( ( check->weight >= threshold ) && ( check->visited == false ) ) {
                check->visited = true ;
                testnum++ ;
              } // if ()
              else {
                stop = true ;
              } // else

              out = true ;
            } // if ()

            check = check->next ;
          } // while ()

          if ( stop == false ) {
            temp = now->get ; // 下一個的名稱
            now = inList ; // 尋找此名稱真正的位置
            while( temp != NULL && now != NULL && strcmp( temp->ID , now->ID ) != 0 ) {
              now = now->next ;
            } // while()
          } // if ()



        } // while()

        if ( asknum == testnum )
          return true ;
        else
          return false ;

    } // checkList()

    adData* copyList( adData* inList ) {
      adData* temp ;
      askList = new adData ;
      strcpy( askList->ID, inList->ID ) ;
      askList->weight = inList->weight ;
      askList->visited = false ;
      askList->next = NULL ;
      inList = inList->next ;
      temp = askList ;
      asknum = 1 ;
      while( inList != NULL ) {
        temp->next = new adData ;
        temp = temp->next ;
        strcpy( temp->ID, inList->ID ) ;
        temp->visited = false ;
        temp->next = NULL ;
        asknum++ ;
        inList = inList ->next ;
      } // while()

      testnum = 0 ;

      return askList ;

    } // copyList()

    void printbfs() { // test
      bfsData* tempList = bfsList ;
      bfsData* tempGet = NULL ;
      while ( tempList != NULL ) {
        cout << endl << "*" << tempList->ID ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          cout << " --- " << tempGet->ID  ;
          tempGet = tempGet->get ;
        } // while

        tempList = tempList->next ;

      } // while
    } // printbfs
    void write( string name ) {   // 建立cnt檔
      FILE * fp = NULL;
      string fileName = "pairs"+name+".inf" ;
      fp = fopen(fileName.c_str(), "w+");
      if(!fp) {
        perror("目標檔案建立失敗");
        return ;
      } // if()
      bfsData* tempList = bfsList ;
      bfsData* tempGet = NULL ;
      fprintf( fp,"<<< There are %d IDs in total. >>>\n", bfsnum ) ;
      int i = 1 ;
      int j = 1 ;
      while ( tempList != NULL ) {
        fprintf( fp,"[%3d] %s(%d): \n", i, tempList->ID, tempList->bfs_influence_num ) ;
        tempGet = tempList->get ;
        while(tempGet != NULL) {
          fprintf( fp,"\t(%2d) %s", j, tempGet->ID ) ;
          if ( j % 10 == 0 )
            fprintf( fp,"\n" ) ;
          j++ ;
          tempGet = tempGet->get ;
        } // while

        fprintf( fp,"\n" ) ;
        i++ ;
        j = 1 ;
        tempList = tempList->next ;
      } // while
      fclose(fp);
    } // write()
};

int main(){
    int command = -1 ;
    DataList dataBank ;
    adjaceLists dataList ;
    BFS bfslist;
    Influence FluList ;
    string fileName ;
    do{
        printf("\n***** Influence on a graph  ****\n* 0. QUIT                      *\n* 1. Build adjacency lists     *\n* 2. Compute influence values  *\n") ;
        printf( "* 3. Estimate influence values *\n" ) ;
        printf("*************************************") ;
        printf("\nInput a choice(0, 1, 2, 3): ") ;
        cin >> command ;
        while ( command > 4 || command < 0 ) {
            printf("請輸入正確的數 :") ;
            cin >> command ;
        } // while
        if ( command == 1 ) {
          cout << "\nInput a file number ([0] Quit): " ;
          cin >> fileName ;
          if ( fileName != "0" ) {
            if ( !dataList.empty() )
              dataList.deleteList() ;
            if ( dataBank.isBin ( fileName )) {

              //dataBank.printBank() ;
              dataList.creatList( dataBank.length, dataBank.bank ) ;
              dataList.output( fileName ) ;
            } // if ()

          } // if ()
		  else
		  	cout << "Please input again!" << endl;
        } // if ()
        else if ( command == 2 ) {
          if ( !dataBank.empty() ) {

            if ( !bfslist.empty() )
              bfslist.deletebfs();

            bfslist.bfs_traversals_create2(dataList);

            bfslist.write( fileName );
          } // if ()
          else{
            cout << "### There is no graph and choose 1 first. ###" << endl;
          } // else

        } // if ()
        else if ( command == 3 ) { //挑戰備用
          if ( !dataBank.empty() ) {

            if ( !FluList.empty() )
              FluList.deletebfs();

            FluList.bfs_traversals_create(dataList);

            FluList.write( fileName );
          } // if ()
          else{
            cout << "### There is no graph and choose 1 first. ###" << endl;
          } // else

        } // else if()
        else if ( command == 4 ) {
          float test[2][3] ;
          int i = 0;
          int j = 0 ;
          clock_t a,b;
          // if ( !dataBank.empty() ) {

            // if ( !bfslist.empty() )
              bfslist.deletebfs();

            while( j < 3 ) {
            cout << "\nInput a file number ([0] Quit): " ;
            cin >> fileName ;

              if ( !dataList.empty() )
                dataList.deleteList() ;
              if ( dataBank.isBin ( fileName )) {

              //dataBank.printBank() ;
                dataList.creatList( dataBank.length, dataBank.bank ) ;
                dataList.output( fileName ) ;
              } // if ()
              a = clock();
              bfslist.bfs_traversals_create(dataList);
              b = clock();
              bfslist.deletebfs();
              test[i][j] = (float)(b-a) ;
              i++ ;
              a = clock();
              bfslist.bfs_traversals_create2(dataList);
              b = clock();
              bfslist.deletebfs();
              test[i][j] = (float)(b-a) ;
              i = 0 ;
              j++ ;
            } // while

		    cout << endl << "實驗比較 資料檔1 資料檔2 資料檔3" ;
		    cout << endl << "修改前 " << test[0][0] << "(ms) " << test[0][1] << "(ms) " << test[0][2] << "(ms) "  ;
		    cout << endl << "修改後 " << test[1][0] << "(ms) " << test[1][1] << "(ms) " << test[1][2] << "(ms) " ;
            // bfslist.write( fileName );
          // } // if ()
          // else{
           // cout << "### There is no graph and choose 1 first. ###" << endl;
          // } // else

        } // if ()
    }while( command != 0 ) ;
    system ( "pause" );        // pause the display
    return 0;
}
