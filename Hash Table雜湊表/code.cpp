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

using namespace std;

struct Data {  // 放資料
    char id[10] ;       // 學生id
    char name[10] ;     // 學生名字
    unsigned char grade[6] ;  // 成績(僅在txt轉bin需要)
    float aveGrade ;          // 平均成績
    int index;                // 序號
	int hashkey;              // 限用函數：hash(key) =（學號每個字母對應的 ASCII 編碼相乘）除以雜湊表大小取餘數
};

struct DData {  // 放資料
    char id[10] ;       // 學生id
    char name[10] ;     // 學生名字
    int hvalue ;
    float aveGrade ;          // 平均成績
};

class dataList {

    private :


    public :
        string fileName ;
        int length ;  // 資料數
        vector<Data> bank;

        void checkBinfileline() { // 確認資料數(bin)
            length = 0 ;
            FILE * fp = NULL;
            // int c ;

            char out1[10] ;
            char out2[2] ;
            char out3[10] ;
            char out5[20] ;
            float out4 ;

            fp = fopen(fileName.c_str(), "rb");

            while( fread( out1 ,sizeof( char ), 8 , fp ) != 0 ) {

              fread( out2 ,sizeof( char ), 2 , fp );
              fread( out3 ,sizeof( char ), 6 , fp );
              fread( out5 ,sizeof( char ), 12 , fp );
              fread(  (void*)(&out4) ,sizeof( out4 ), 1 , fp );
              length ++;

            } //while

            fclose(fp);

        } // checkBinfileline ()

        void arrayClean( unsigned char grade[6] , char name[10]   ) { // 清空陣列
            for ( int j = 0 ; j < 6 ; j++ ) {
                grade[j] = '\0' ;

            } // for()

            for ( int j = 0 ; j < 10 ; j++ ) {
              name[j] = '\0' ;
            } // for()

        } // arrayClean()

        bool isBin ( string input ) { // 處理bin檔
          fileName = "input"+input+".bin" ;
          FILE * infile = NULL;
          infile = fopen(fileName.c_str(),"rb") ;

          if(infile == NULL ) {          // bin檔不存在，尋找text建立
            if ( readandcreatefile( input ) ) {
              output( input ) ;             // 輸出bin檔
              deleteBank() ;
              isBin ( input ) ;
              return true ;
            } // if ()
            else {
              return false ;
            } // else

          } // if ()

          //----------------------------------建立資料庫
          checkBinfileline();
          Data now ;
          for ( int x = 0 ; x < length  ; x++ ) {
            char out[100] ;
            bank.push_back(now) ;

            arrayClean( bank[x].grade, bank[x].name ) ;
            fread( bank[x].id ,sizeof( char ), 8 , infile );
            fread( out ,sizeof( char ), 2 , infile );
            char in[10] ;
            int y = 0 ;
            fread( in ,sizeof( char ), 1 , infile );
            for (  ; y<5 || strcmp( in ,"\0") != 0 ; y++ ) {
              strcat( bank[x].name, in ) ;
              fread( in ,sizeof( char ), 1 , infile );

            } // for()


            if ( y == 5 )
                y = 12 ;
            else
                y = 11 ;
            fread( out ,sizeof( char ), y , infile );
            fread( (void*)(&bank[x].aveGrade) ,sizeof( bank[x].aveGrade ), 1 , infile );


          } // for()

          fclose(infile);
          //printBank() ;   // ------------------------------------------bin檔內容讀入測試處(<--)
          return true ;
        } // isBin ()

        void checkfileline() {  // 確認資料數(text)
          length = 0 ;
          FILE * fp = NULL;
          int c, lc=0;
          fp = fopen(fileName.c_str(), "r");
          while((c = fgetc(fp)) != EOF) {
            if(c == '\n') length ++;
              lc = c;
          } // while
          fclose(fp);
          if(lc != '\n') length ++;
        } // checkfileline ()

         bool readandcreatefile( string input ) { // 處理text檔
            FILE *infile = NULL ;
            Data now ;
            char temp = '\0' ;
            int intTemp ;
            float aveTemp ;
            fileName = "input"+input+".txt" ;

            infile = fopen(fileName.c_str(),"r") ;
            checkfileline();
            if(infile == NULL ) {
                cout<<endl<<fileName<<" does not exist!" << endl ;
                return false ;
            }
            else{

                for ( int x = 0 ; x < length  ; x++ ) {
                  bank.push_back(now) ;
                  arrayClean( bank[x].grade, bank[x].name ) ;

                  fscanf(infile,"%c",&temp) ;
                  while ( temp == '\n' ) {
                    fscanf(infile,"%c",&temp) ;
                  } // while()

                  for ( int y = 0 ; temp != '\t' ; y++ ) {
                    bank[x].id[y] = temp;
                    fscanf(infile,"%c",&temp) ;
                  } // for()

                  fscanf(infile,"%c",&temp) ;
                  for ( int y = 0 ; temp != '\t' ; y++ ) {

                    bank[x].name[y] = temp;
                    fscanf(infile,"%c",&temp) ;
                  } // for()


                  fscanf(infile,"%d",&intTemp) ;
                  int stop = 0 ;

                  for ( int j = 0 ; stop<6 ; j++ ) {
                      bank[x].grade[j] = (unsigned char) intTemp;
                      if ( stop < 5 )
                        fscanf(infile,"%d",&intTemp) ;


                    if ( stop == 5 )
                      fscanf(infile,"%c",&temp) ;

                    stop++ ;


                  } // for()

                  fscanf(infile,"%f",&aveTemp) ;
                  bank[x].aveGrade = aveTemp ;
                  // cout << endl << bank[x].aveGrade << "_____" << x << "-" << length ;

                } // for()

            } // else
            fclose(infile);

            return true ;
        } // readandcreatefile()

        void output( string name ) {   // 建立bin檔

            FILE * fp = NULL;
            fileName = "input"+name+".bin" ;
            // ofstream out("ex2.txt", ios::binary);
            fp = fopen(fileName.c_str(), "wb");
            if(!fp) {
              perror("目標檔案建立失敗");
              return ;
            } // if()
          for ( int x = 0 ; x < length ; x++ ) {

            // for ( int y = 0 ; y < 8 ; y++ ) {
              // fwrite(&bank[x].id[y], sizeof(char), 1, pf);
            // } // for()
            fwrite( bank[x].id, sizeof(char), 8, fp );
            fwrite("\0", sizeof(char), 1, fp);
            char sp = (char)166 ;
            fwrite( &sp, sizeof(char), 1, fp);

            // fwrite("|", sizeof(char), 1, fp);
            int longer = 0 ;
            for ( int y = 0 ;  ( y < 10 ) && ( bank[x].name[y] != '\0' ) ; y++ ) {
              fwrite( &bank[x].name[y], sizeof(char), 1, fp );
              longer = y+1 ;
            } // for()

            fwrite("\0", sizeof(char), 1, fp);
            if ( longer == 5 ) {

              sp = (char)19 ;
              fwrite( &sp, sizeof(char), 1, fp);
            } // if ()
            else if (longer == 4) {
              fwrite("\0", sizeof(char), 1, fp);
              sp = (char)19 ;
              fwrite( &sp, sizeof(char), 1, fp);
            } // else if

            fwrite("\0\0\0", sizeof(char), 3, fp);
            for ( int i = 0 ; i < 6 ; i++ ) 
              fwrite( &bank[x].grade[i], sizeof(unsigned char), 1, fp );

            fwrite("\0\0", sizeof(char), 2, fp);
            fwrite( &bank[x].aveGrade, sizeof(float), 1, fp ) ;
          } // for()

            fclose(fp);
        } // outPut()

        void printBank() {                    // 測試用印出
          for ( int x = 0 ; x < length ; x++ ) {

            for ( int y = 0 ; y < 8 ; y++ ) {
              cout << bank[x].id[y] ;

            } // for()

            cout << "\t" ;
            for ( int y = 0 ;  ( y < 10 ) && ( bank[x].name[y] != '\0' ) ; y++ ) {
              cout << bank[x].name[y] ;
            } // for()

            cout << "\t" ;
            for ( int y = 0 ; y < 6 ; y++ ) {
                cout << bank[x].grade[y] ;

              // } // for()

              cout << "\t" ;
            } // for()

            cout << bank[x].aveGrade << endl ;

          } // for()

        } // printBank()

        void deleteBank() {
          bank.clear() ;
        } // ()

} ;

//---------------------------------------------case one---------------------------------------------------------------------------

bool isNumber( string isnum ){ // check whether the character is a number
    if ( ( isnum[0] <= '9' ) && ( isnum[0] >= '0' ))
       return true;
    else
        return false;
} // isNumber

bool is_prime_num(int N){
  if (N == 1) 
        return false;
  else {
    if (N <= 3)  
        return true;
    else {
      for (int i=3; i <= N/2; i++) {
        if (N % i == 0) 
            return false;
      } // for
      return true;
    } // else
  } // else
} // is_prime_num

unsigned __int64 id_to_asciinum( char id[] ){
	unsigned __int64 total = 1;
	int i = 0;
	while ( ( id[i]!='\0' )&&(i< 8) ){
		total = total*int( id[i] );
		i++;
	} // while
	return total;
} //id_to_asciinum

class LinearHash{
private :
  	string filename;
  	float unsuccess; 
  	int success; 
  	int hash_size;
  	float data_length;
  	vector<Data> linear;
public :
  	bool search_hastable(int temp, Data &d){ // 找找裡面是不是已經放了 
  		for ( int i = 0 ; i < linear.size() ; i++ ) 
  		  if ( linear[i].index == temp ){
  		  	d = linear[i];
  		  	return true;
		  } // if
  	    return false;
	} // search_hastable
  	
        void arrayClean( unsigned char grade[6] , char name[10]   ) { // 清空陣列
            for ( int j = 0 ; j < 6 ; j++ ) {
                grade[j] = '\0' ;

            } // for()

            for ( int j = 0 ; j < 10 ; j++ ) {
              name[j] = '\0' ;
            } // for()

        } // arrayClean()
  	
  	void createhash( dataList dataBank ){
  		unsuccess = 0;
  		success = 0;
  		filename = dataBank.fileName;
  		data_length = dataBank.length;
  		remove_nonnumber( filename ); //移除不是數字的部分 
  		int temp = ceil(dataBank.length*1.2);
  		while ( !is_prime_num(temp) )
		  temp++; 
  		hash_size = temp;
  		Data tempdata; // 借用而已 

        for( int i = 0 ; i < hash_size ; i++ ) {
          linear.push_back(tempdata) ;
          arrayClean( linear[i].grade, linear[i].name ) ;
          linear[i].hashkey = -1 ;
        }// for()
      
	    for( int i = 0 ; i < dataBank.length ; i++ ) {
        	success++;
            int hash_key = id_to_asciinum( dataBank.bank[i].id ) % hash_size;
            int temp_index = hash_key;

              while( linear[temp_index].hashkey != -1 ) {
                success++;
  		    	if ( temp_index == hash_size-1 )
  		  	      temp_index  = 0;
  		  	    else
			      temp_index++;
              } // while()
              strcpy( linear[temp_index].id, dataBank.bank[i].id ) ;
              strcpy( linear[temp_index].name, dataBank.bank[i].name ) ;
              linear[temp_index].aveGrade = dataBank.bank[i].aveGrade ;
              linear[temp_index].hashkey = hash_key ;



        } // for()
        
	    //cout << endl << "out" ;
	} // createhash( dataList dataBank )
  
    void remove_nonnumber( string &str ){ //移除不是數字的部分
      string token; //接著放判斷過的token(去除不是數字的token)
      while ( !str.empty() ){
    	if ( isNumber( str ) ){
  	      token.append(1, str[0]);
  		  str.erase(str.begin());
	    } // if
	    else
	      str.erase(str.begin());
      } // while
      str = token;
    } // remove_nonnumber
  
    void printlinear() {                    // test
        for ( int x = 0 ; x < linear.size() ; x++ ) {
            cout << x << "[" << linear[x].index<< "]" << "\t" << linear[x].hashkey << ",\t";
            for ( int y = 0 ; y < 8 ; y++ ) 
              cout << linear[x].id[y] ;

            cout << "\t" ;
            for ( int y = 0 ;  ( y < 10 ) && ( linear[x].name[y] != '\0' ) ; y++ ) 
              cout << linear[x].name[y] ;
            cout << "\t" ;
            cout << linear[x].aveGrade << endl ;
        } // for()
    } // printlinear
  
    void writelinear( dataList dataBank ){

      FILE * fp = NULL;
      filename = "linear"+filename+".txt" ;
      fp = fopen(filename.c_str(), "w+");		
      if(!fp) {
        perror("目標檔案建立失敗");
        return ;
      } // if()

      fprintf(fp," --- Hash Table X --- (linear probing)\n");
      for ( int x = 0 ; x < hash_size ; x++ ) {
        if( linear[x].hashkey != -1 ) {
          fprintf(fp, "[  %d]\t\t%d,\t", x, linear[x].hashkey );

          for ( int y = 0 ; ( linear[x].id[y]!='\0' )&& (y < 8 ) ; y++ ) {
            fprintf(fp, "%c", linear[x].id[y] );
          } // for()
          fprintf(fp, ",\t" );
          fprintf(fp, "%s", linear[x].name );

          fprintf(fp, ",\t\t" );

          fprintf(fp, "%6g\n", linear[x].aveGrade );

        } // if()
        else {
          fprintf(fp, "[  %d] \n", x );
        } // else

      } // for()

      fclose(fp);
		
	} // writelinear
	
	void probs_unsuccess(){
		unsuccess = 0;
		Data d; // 只是暫放 
		for( int i = 0 ; i < hash_size ; i++ ){
			int step = 0;
			int n = i;
			while ( linear[n].hashkey != -1 ){   // search_hastable(n, d)
				step++;
				n = i + step;
				if ( n > hash_size-1 ) //到底惹!! 
				  n = n % hash_size;
			} // while
			unsuccess = unsuccess + step;
		} // for
		
	} // probs_unsuccess
	
	void print_unsuccess_success(){
	  probs_unsuccess();
	  float unsu;
	  unsu = (float)unsuccess/(float)hash_size;
	  float su;
	  su = (float)success/(float)data_length;
	  cout << "unsuccessful search: " << fixed <<  setprecision(4) << unsu << " comparisons on average" << endl;
	  cout << "successful search: " << fixed <<  setprecision(4) << su << " comparisons on average" << endl;
	} // print_unsuccess_success
	
	void deleteData() {
      filename.clear();
  	  unsuccess = 0; 
  	  success = 0; 
  	  hash_size = 0;
  	  data_length = 0;
  	  linear.clear();
    } // deleteData()
	
}; // LinearHash

//---------------------------------------------case one---------------------------------------------------------------------------
//---------------------------------------------case two---------------------------------------------------------------------------

class DoubleHash {
private:
    int one ;
    int two ;
    int probes ; // 碰撞次數
    vector<DData> DoubleBank;
public:
    void MaxDouble( int num ) {
      //one = num * 1.2 ;                // 雜湊表大小
      one = ceil(num*1.2);

      bool isPrime = false ;
      while( isPrime == false ) {
        bool out = false ;
        for( int i = 2 ; ( out == false ) && (i*i <= one ) ; i++ ) {
            if (one%i==0) {
                out = true ;
            } // if ()

        } // for()

        if (out==false)
          isPrime = true ;
        else
          one++ ;

      } // while()

      // ---------------------------------------------------

      // 最高步階
      //float ansF = (float)num / 3.0  ;
      
      two = num / 3 + 1 ;
     // if ( num % 3 == 0 )
      //  two ++ ;
        
      isPrime = false ;
      while( isPrime == false ) {
        bool out = false ;
        for( int i = 2 ; ( out == false ) && (i*i <= two ) ; i++ ) {
            if (two%i==0) {
                out = true ;
            } // if ()

        } // for()

        if (out==false)
          isPrime = true ;
        else
          two++ ;

      } // while()

      DData now ;
      for( int i = 0 ; i < one ; i++ ) {
        DoubleBank.push_back(now) ;
        arrayClean( DoubleBank[i].name, DoubleBank[i].id ) ;
        DoubleBank[i].hvalue = -1 ;
      }// for()

      probes = 0 ;

    } // MaxDouble()

    void arrayClean( char name[10], char id[10] ) {
      for ( int j = 0 ; j < 10 ; j++ ) {
        name[j] = '\0' ;
      } // for()

      for ( int j = 0 ; j < 10 ; j++ ) {
        id[j] = '\0' ;
      } // for()

    } // arrayClean()

    int multiplyID( char id[10], int Max ) {
        int ans = 1 ;
        int in = 0 ;
        int i = 0 ;
        for( ; ( id[i]!='\0' )&&(i< 8) ; i++ ) {
            in = (int) id[i] ;
            ans = ans * in ;
            if( i!=0 && (i-1)%2==0 ){
                ans = ans % Max ;
                cout << "[" << ans << "]" ;
                if ( ans==0 && i!=7 )
                  ans = 1 ;
            } // if
 
        } // for()

        if ( i == 7 ) {
          ans = ans % Max ;
          if ( ans==0 )
            ans = 1 ;
        } // if()

         cout << "---" << ans ; 
        return ans ;

    } // multiplyID()

    int outOfRange( int now ){  // 檢查是否超出範圍
      if( now >= one ){
        now = now - one ;
        return now ;
      } // if()
      else {
        return now ;
      }//else

    } // outOfRange()

    void creatDouble( vector<Data> bank, int len ){
        MaxDouble( len ) ;
        int now = 0 ; // 要放進去的位置
        int hva = 0 ; // 目前計算出的雜湊值
        int cal = 0 ; // 第二次要加的數
        for( int i = 0 ; i < len ; i++ ) {
        	//cout << endl << i ;
        	hva = id_to_asciinum( bank[i].id ) % one;
            // hva = multiplyID( bank[i].id, one ) ;
            now = hva ;
            probes++;
            if( DoubleBank[now].hvalue == -1 ) {
           //	cout << endl << i << "--" <<  bank[i].id <<  "---" << hva ;
              strcpy( DoubleBank[now].id, bank[i].id ) ;
              strcpy( DoubleBank[now].name, bank[i].name ) ;
              DoubleBank[now].aveGrade = bank[i].aveGrade ;
              DoubleBank[now].hvalue = hva ;
            } // if()
            else{
              cal = two - id_to_asciinum( bank[i].id ) % two;
              now = now + cal ;
              now = outOfRange( now ) ;
              probes++;
              //cout << endl << i << "--" <<  bank[i].id << "[" << two << "-" << cal << "]" << "---" << hva ;
              while( DoubleBank[now].hvalue != -1 ) {
                now = now + cal ;
                now = outOfRange( now ) ;
                probes++;
              } // while()
                strcpy( DoubleBank[now].id, bank[i].id ) ;
                strcpy( DoubleBank[now].name, bank[i].name ) ;
                DoubleBank[now].aveGrade = bank[i].aveGrade ;
                DoubleBank[now].hvalue = hva ;
               // cout << " <" << now << ">" ;

            } // else


        } // for()

        // printBank() ;
    } // creatDouble()

    void printBank() {                    // 測試用印出
      for ( int x = 0 ; x < one ; x++ ) {
        if( DoubleBank[x].hvalue != 0 ) {
          cout << x << "\t" << DoubleBank[x].hvalue << "\t" ;
          for ( int y = 0 ; y < 8 ; y++ ) {
            cout << DoubleBank[x].id[y] ;

          } // for()

          cout << "\t" ;
          for ( int y = 0 ;  ( y < 10 ) && ( DoubleBank[x].name[y] != '\0' ) ; y++ ) {
            cout << DoubleBank[x].name[y] ;
          } // for()

          cout << "\t" ;
          cout << DoubleBank[x].aveGrade << endl ;

        } // if()
        else
          cout << x << endl ;

      } // for()

    } // printBank()

    void output( string name ) {

      FILE * fp = NULL;
      string fileName = "double"+name+".txt" ;
      fp = fopen(fileName.c_str(), "w+");
      if(!fp) {
        perror("目標檔案建立失敗");
        return ;
      } // if()

      fprintf(fp," --- Hash Table Y --- (double hashing)\n");
      for ( int x = 0 ; x < one ; x++ ) {
        if( DoubleBank[x].hvalue != -1 ) {
          fprintf(fp, "[  %d]\t\t%d,\t", x, DoubleBank[x].hvalue );

          for ( int y = 0 ; ( DoubleBank[x].id[y]!='\0' )&& (y < 8 ) ; y++ ) {
            fprintf(fp, "%c", DoubleBank[x].id[y] );
          } // for()
          fprintf(fp, ",\t" );
          fprintf(fp, "%s", DoubleBank[x].name );

          fprintf(fp, ",\t\t" );

          fprintf(fp, "%6g\n", DoubleBank[x].aveGrade );

        } // if()
        else {
          fprintf(fp, "[  %d] \n", x );
        } // else

      } // for()

      fclose(fp);
    } // output()

    void countPro( int len ) {
      float ans = 0.0 ;
      ans = (float) probes / (float) len ;
      printf("\nsuccessful search: %.4f comparisons on average\n", ans );
    } //  countPro()


    void deleteData() {
      DoubleBank.clear() ;
      one = 0 ;
      two = 0 ;
      probes = 0 ;
    } // deleteData()
}; // DoubleHash

//---------------------------------------------case two---------------------------------------------------------------------------
//---------------------------------------------case three-------------------------------------------------------------------------

void remove_nonnumber( string &str ){ //移除不是數字的部分
    string token; //接著放判斷過的token(去除不是數字的token)
    while ( !str.empty() ){
      if ( isNumber( str ) ){
  	    token.append(1, str[0]);
  		str.erase(str.begin());
	  } // if
	  else
	    str.erase(str.begin());
    } // while
    str = token;
} // remove_nonnumber

class Quadratic{
private :
	  string filename;
	  int success;
	  int unsuccess;
	  int pass_unsu; // test
  	  int hash_size;
      double data_length;
  	  vector<Data> quadra;
public:
  	bool search_hastable(int temp, Data &d){ // 找找裡面是不是已經放了 
  		for ( int i = 0 ; i < quadra.size() ; i++ ) 
  		  if ( quadra[i].index == temp ){
  		  	d = quadra[i];
  		  	return true;
		  } // if
  	    return false;
	} // search_hastable
        void arrayClean( unsigned char grade[6] , char name[10]   ) { // 清空陣列
            for ( int j = 0 ; j < 6 ; j++ ) {
                grade[j] = '\0' ;

            } // for()

            for ( int j = 0 ; j < 10 ; j++ ) {
              name[j] = '\0' ;
            } // for()

        } // arrayClean()
        
    int multiplyID( char id[10], int Max ) {
        int ans = 1 ;
        int in = 0 ;
        int i = 0 ;
        for( ; ( id[i]!='\0' )&&(i< 8) ; i++ ) {
            in = (int) id[i] ;
            ans = ans * in ;
            if( i!=0 && (i-1)%2==0 ){
                ans = ans % Max ;

                if ( ans==0 && i!=7 )
                  ans = 1 ;
            } // if


        } // for()

        if ( i == 7 ) {
          ans = ans % Max ;
          if ( ans==0 )
            ans = 1 ;
        } // if()

        return ans ;

    } // multiplyID()
        
  	void createhash( dataList dataBank ){
  		success = 0;
  		filename = dataBank.fileName;
  		data_length = dataBank.length;
  		remove_nonnumber( filename ); //移除不是數字的部分 
  		int temp = ceil(dataBank.length*1.2);
  		while ( !is_prime_num(temp) )
		  temp++; 
  		hash_size = temp;
  		Data tempdata; // 借用而已 

        for( int i = 0 ; i < hash_size ; i++ ) {
          quadra.push_back(tempdata) ;
          arrayClean( quadra[i].grade, quadra[i].name ) ;
          quadra[i].hashkey = -1 ;
        }// for()
      
	    for( int i = 0 ; i < dataBank.length ; i++ ) {
        	success++;
  		    int dataprob = 1;
  		    int step = 1;
  		    bool out = false ;
            //int hash_key = id_to_asciinum( dataBank.bank[i].id ) % hash_size;
            int hash_key = multiplyID( dataBank.bank[i].id, hash_size ) ;
			long long int temp_index = hash_key;

              while( out == false && quadra[temp_index].hashkey != -1 ) {
                success++;
                dataprob++;
                long long int temp = pow( step, 2 );
  		    	temp_index = hash_key + temp;
                step++;
  		     	if ( temp_index > hash_size-1 )
  		  	      temp_index  = temp_index % hash_size;
  		     	if ( dataprob > hash_size ) {
  		  	    	cout << "### Failed at [" << i <<  "]. ###" << endl;
  		  		    out = true ;
		    	} // if
		    	
              } // while()
              if ( out != true ) {
                strcpy( quadra[temp_index].id, dataBank.bank[i].id ) ;
                strcpy( quadra[temp_index].name, dataBank.bank[i].name ) ;
                quadra[temp_index].aveGrade = dataBank.bank[i].aveGrade ;
                quadra[temp_index].hashkey = hash_key ;
			  } // if ()


        } // for()
	    
	} // createhash( dataList dataBank )
	
	void writequadratic( dataList dataBank ){
    	filename = "quadratic"+filename+".txt" ;
      FILE * fp = NULL;
      fp = fopen(filename.c_str(), "w+");		
      if(!fp) {
        perror("目標檔案建立失敗");
        return ;
      } // if()

      fprintf(fp," --- Hash Table Z --- (quadratic probing)\n");
      for ( int x = 0 ; x < hash_size ; x++ ) {
        if( quadra[x].hashkey != -1 ) {
          fprintf(fp, "[  %d]\t\t%d,\t", x, quadra[x].hashkey );

          for ( int y = 0 ; ( quadra[x].id[y]!='\0' )&& (y < 8 ) ; y++ ) {
            fprintf(fp, "%c", quadra[x].id[y] );
          } // for()
          fprintf(fp, ",\t" );
          fprintf(fp, "%s", quadra[x].name );

          fprintf(fp, ",\t\t" );

          fprintf(fp, "%6g\n", quadra[x].aveGrade );

        } // if()
        else {
          fprintf(fp, "[  %d] \n", x );
        } // else

      } // for()

      fclose(fp);
	} // writelinear
	
	void probs_unsuccess(){
		unsuccess = 0;
		Data d; // 只是暫放 
		for( int i = 0 ; i < hash_size ; i++ ){ //hash_size
			int step = 0;
			int temp = pow( step, 2 );
			int n = i + temp;
			bool out = false;
			while ( !out && quadra[n].hashkey != -1 ){
				step++;
				temp = pow( step, 2 );
				n = i + temp;
				if ( n > hash_size-1 )  //到底惹!! 
				  n = n % hash_size;
				if ( step > hash_size )
				  out = true;
			} // while
			unsuccess = unsuccess + step;
		} // for
	} // probs_unsuccess
	
	void print_unsuccess_success(){
	  probs_unsuccess();
	  float unsu;
	  unsu = (float)unsuccess/(float)hash_size;
	  float su;
	  su = (float)success/(float)data_length;
	  cout << "unsuccessful search: " << fixed <<  setprecision(4) << unsu << " comparisons on average" << endl;
	  cout << "successful search: " << fixed <<  setprecision(4) << su << " comparisons on average" << endl;
	} // print_unsuccess_success
	
	void deleteData() {
      filename.clear();
  	  unsuccess = 0; 
  	  success = 0; 
  	  hash_size = 0;
  	  data_length = 0;
  	  quadra.clear();
    } // deleteData()
	
}; // Quadratic
//---------------------------------------------case three-------------------------------------------------------------------------

int main()
{
    int command = -1 ;
    dataList dataBank ;
    string fileName ;
    do{
        printf("\n*** Hash Table Builder **\n* 0. QUIT              *\n* 1. Linear probing    *\n* 2. Double hashing    *\n* 3. Quadratic probing *\n") ;
        printf("************************") ;
        printf("\nInput a choice(0, 1, 2, 3): ") ;
        cin >> command ;
        while ( command > 3 || command < 0 ) {
            printf("請輸入正確的數 :") ;
            cin >> command ;
        } // while

        if ( command == 1 ) {
          cout << "\nInput a file number ([0] Quit): " ;
          cin >> fileName ;
          if ( fileName != "0" ) {
            if (!dataBank.bank.empty())
              dataBank.deleteBank() ;
            dataBank.isBin(fileName) ;
            LinearHash one;
            one.createhash( dataBank );

          	cout << "Hash Table X has been created." << endl;
          	one.writelinear( dataBank );
          	one.print_unsuccess_success();
          	one.deleteData() ;
          } // if ()
		  else{
		  	cout << "Please input again!" << endl;
		  } // else
        } // if ()


        if ( command == 2 ) {
          cout << "\nInput a file number ([0] Quit): " ;
          cin >> fileName ;
          if ( fileName != "0" ) {
            if (!dataBank.bank.empty())
              dataBank.deleteBank() ;
            dataBank.isBin(fileName) ;
            DoubleHash dBank ;
            dBank.creatDouble( dataBank.bank, dataBank.length ) ;
            cout << "Hash Table Y has been created." << endl;
            dBank.output( fileName ) ;
            dBank.countPro( dataBank.length ) ;
            dBank.deleteData() ;
          } // if ()

        } // if ()

        if ( command == 3 ) { //挑戰備用
          cout << "\nInput a file number ([0] Quit): " ;
          cin >> fileName ;
          if ( fileName != "0" ) {
            if (!dataBank.bank.empty())
              dataBank.deleteBank() ;
            dataBank.isBin(fileName) ;
            Quadratic q;
            q.createhash( dataBank );
            cout << "Hash Table Z has been created." << endl;
          	q.writequadratic( dataBank );
          	q.print_unsuccess_success();
          	q.deleteData() ;
          } // if ()
		  else{
		  	cout << "Please input again!" << endl;
		  } // else

        } // if()


    }while( command != 0 ) ;
    system ( "pause" );        // pause the display
    return 0;
}
