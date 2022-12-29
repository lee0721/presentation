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
#define BUFFER_SIZE  200

using namespace std;

struct Offset{
   float weight ;
   int off ;
};

struct Data {  // 放資料
    char putID[10] ;       // 學生id
    char getID[10] ;     // 學生id
    float weight ;       // 權重
};

struct Data2 {  // 放資料

    Offset w[5] ;       // 權重
    Data2* p1 ;
    Data2* p2 ;
    Data2* p3 ;
    Data2* p4 ;
    Data2* p5 ;
    Data2* p6 ;
    Data2* next ;
};

class externalSort {
    public :
    	float internal_time; // 讀檔和內部排序(氣泡排序)執行時間 
    	float external_time; // 寫檔和外部排序(合併排序)執行時間
        string inputname;
        int length ;  // 資料數
        int num_ways;  //  資料數/200
        int remain;    //是否整除200
        vector<Data> buffer; //只能放200筆
        vector< vector<Data> > bank;

        externalSort() {
          internal_time = 0;
          external_time = 0;
          inputname.clear();
          length = 0 ;
          num_ways = 0 ;
          remain = 0 ;
          buffer.clear(); 
          bank.clear();
        } // externalSort()

        void bubbleSort(vector<Data> &buffer) {


          for (int i = 0; i < buffer.size() - 1; i++) {
            for (int j = 0; j < ( buffer.size() - i - 1 ) ; j++) {
              if ( buffer.at(j).weight < buffer.at(j+1).weight ) {
                std::swap(buffer.at(j), buffer.at(j+1));

              } // if ()
            } // for()
          } // for()

        } // bubbleSort()
        
        void timeshow(){
        	cout << endl << "The execution time ..." << endl << "Internal Sort = " << internal_time << " ms" << endl;
        	cout << "External Sort = " << external_time << " ms" << endl << "Total Execution Time = " << internal_time+external_time << " ms" << endl;
		} //timeshow

        void input( string input ){
        	inputname = input;
        	clock_t start,end;  // 測量執行時間 
        	start = clock();
        	string fileName = "pairs"+input+".bin" ;
            ifstream infile;
            buffer.resize(BUFFER_SIZE); //限制只能200筆
            infile.open(fileName.c_str(), ios::in | ios::binary); //binary 開檔
            infile.seekg (0, ios::end);
            length = infile.tellg()/sizeof(Data); // 取得檔案大小
            infile.seekg (0, ios::beg);
            num_ways = length / BUFFER_SIZE;  //  資料數/200
            int i = 0;
            while ( i < num_ways ){
            	infile.read( (char *) &buffer[0], BUFFER_SIZE*sizeof(Data));
            	bubbleSort(buffer);
            	bank.push_back(buffer);
            	i++;
			} // while
			remain = length-(num_ways*BUFFER_SIZE);
			if ( remain > 0 ){ //如果總資料數無法整除200會有餘數 剩下的自成一檔
                buffer.resize(remain);
				infile.read( (char *) &buffer[0], remain*sizeof(Data));
				bubbleSort(buffer);
				bank.push_back(buffer);
				num_ways++;
			} // if
            infile.close();
            end = clock();
            internal_time = end - start;
		} // input

        void external_sort(){
            clock_t start,end;  // 測量執行時間 
        	start = clock();
            
        	int num = num_ways;
        	int buffer_size = BUFFER_SIZE;
        	int two = 2;
        	int two_pow = 1;
        	while ( num > 1 ){
              vector< vector<Data> > temp_bank ;
              temp_bank.assign(bank.begin(), bank.end());

              bank.clear();
              int workNum = 0 ; // 還未合併的資料庫量
              if ( num%2 == 1 )
                workNum = num - 1 ; // 奇數個，最後再處理落單的
              else
                workNum = num ;

              int now = 0 ; // 進入比較的資料庫1，資料庫2為now+1

              while ( now < workNum ) {
                vector<Data> in1 ;
                vector<Data> in2 ;
                vector<Data> all ;
                int left1 = 0 ;
                int left2 = 0 ;

                  while( left1 < temp_bank[now].size() &&  left2 < temp_bank[now+1].size()  ) {
                    for( int i = left1 ; ( (i-left1) < BUFFER_SIZE ) && ( i < temp_bank[now].size()  ) ; i++ ) {
                      in1.push_back(temp_bank[now][i]) ;
                    } // for

                    for( int i = left2 ; ( (i-left2) < BUFFER_SIZE ) && ( i < temp_bank[now+1].size() ) ; i++ ) {
                      in2.push_back(temp_bank[now+1][i]) ;
                    } // for

                    in1 = newMergeLeft( in1, in2, left1 , left2 ) ;

                    if ( !all.empty() )
                      all.insert(all.end(),in1.begin(),in1.end());
                    else
                      all.assign(in1.begin(), in1.end());


                    in1.clear() ;
                    in2.clear() ;
                  } // while()

                  while ( left1 < temp_bank[now].size() ) {
                    all.push_back(temp_bank[now][left1]) ;
                    left1++ ;
                  } // while()

                  while ( left2 < temp_bank[now+1].size() ) {
                    all.push_back(temp_bank[now+1][left2]) ;
                    left2++ ;
                  } // while()



                bank.push_back( all ) ;
                all.clear() ;

                now = now + 2 ;
              } // while()

              if ( num%2 == 1 ) {

                bank.push_back( temp_bank[num-1] ) ;
                num = ( num - 1 ) / 2 + 1 ; // 奇數個，落單加回去
                temp_bank.clear() ;
              } // if ()
              else {
                num = num/2 ;
                temp_bank.clear() ;
              } // else
              cout << endl << "Now there are " << num  << " runs." << endl ; // test
			}// while
			
			output();
			end = clock();
            external_time = end - start;
            timeshow();
		} // external_sort


		vector<Data> newMergeLeft( vector<Data> one, vector<Data>& two, int& left1 , int& left2 ) {

          vector<Data> ans ;

          int now1 = 0 ;
          int now2 = 0 ;
          int long1 = one.size() ;
          int long2 = two.size() ;

          int use = 0 ;

          while( now1 < long1 && now2 < long2 ) {


              if ( one[now1].weight > two[now2].weight ) {
                ans.push_back( one[now1] ) ;
                now1++ ;
                left1++ ;
              } // if ()
              else if ( one[now1].weight < two[now2].weight  ) {
                ans.push_back( two[now2] ) ;
                left2++ ;
                now2++ ;
              } // else if ()
              else {
                  ans.push_back( one[now1] ) ;
                  now1++ ;
                  left1++ ;
              } // else



            use++ ;

          } // while()

          return ans ;

		} // newMergeLeft()


        void output(){
        	ofstream outfile;
            string output = "sorted"+inputname+".bin" ;
            outfile.open(output.c_str(), ios::out | ios::binary | ios_base::trunc);
            int i = 0;
            int now = 0 ;
            while ( i < num_ways ){
                if ( i < num_ways-1 ) {
            	  outfile.write( (char *) &bank[0][now], BUFFER_SIZE* sizeof(Data));
            	  now = now + BUFFER_SIZE ;
                } // if ()
                else{
                  outfile.write( (char *) &bank[0][now], (length-now)* sizeof(Data));

                } // else

            	i++;
			} // while

			bank.clear() ;
			outfile.close();
		} // output

		void printbuffer(int size) {                    // 測試用印出
          for ( int x = 0 ; x < size ; x++ )
            cout << buffer[x].putID << "-------" << buffer[x].getID << "\t" << buffer[x].weight << endl;
        } // printbuffer()

} ; // externalSort


class DataList {
    public :
        string fileName ;
        int length ;  // 資料數
        int largerNum ;
        Data2* bank;

        int getLength() {
          return length ;
        } // getLength()

        Data2* getBank() {
          return bank ;
        } // getBank()

        DataList() {
          length = 0 ;
          largerNum = 0 ;
          bank = NULL ;
        } // dataList

        Data2* HeadIsLeaf( Data2* temp, float now ) {

           // 本身是葉子
          Data2* newHead = new Data2 ;
          newHead->w[0].weight = now ;
          newHead->w[0].off = 1 ;
          newHead->w[1].off = 0 ;
          newHead->w[2].off = 0 ;
          newHead->w[3].off = 0 ;
          newHead->w[4].off = 0 ;

          newHead->p2 = new Data2 ;
          newHead->p2->w[0].weight = now ;
          newHead->p2->w[0].off = largerNum ;
          largerNum++ ;
          temp->w[3].off = 0 ;


          newHead->p1 = temp ;
          newHead->p2 = newLeaf( newHead->p2, now ) ;
          newHead->p3 = NULL ;
          newHead->p4 = NULL ;
          newHead->p5 = NULL ;
          newHead->p6 = NULL ;

          temp->next =  newHead->p2 ;

          newHead->p2->p1 = temp->p4 ;
          newHead->p2->p2 = temp->p5 ;
          newHead->p2->p3 = temp->p6 ;
          temp->p4 = NULL ;
          temp->p5 = NULL ;
          temp->p6 = NULL ;

          return newHead ;

        } // HeadIsLeaf()

        Data2* newLeaf( Data2* temp, float now ) {
          temp->w[1].off = 0 ;
          temp->w[2].off = 0 ;
          temp->w[3].off = 0 ;
          temp->w[4].off = 0 ;
          temp->p1 = NULL ;
          temp->p2 = NULL ;
          temp->p3 = NULL ;
          temp->p4 = NULL ;
          temp->p5 = NULL ;
          temp->p6 = NULL ;
          temp->next = NULL ;
          return temp ;
        } // newLeaf()

        Data2* divideHead( Data2* temp ) {

          Data2* newHead = new Data2 ;
          newHead->p2 = new Data2 ;

          newHead->w[0].weight = temp->w[2].weight ;
          newHead->w[0].off = 1 ;
          exchange( temp, newHead->p2 ) ;
          newHead->p1 = temp ;
          newHead->p3 = NULL ;
          newHead->p4 = NULL ;
          newHead->p5 = NULL ;
          newHead->p6 = NULL ;

          return newHead ;

        } // divideHead()

        void checkBinfileline( string input ) { // 確認資料數(bin)

            if ( !isEmpty() )
              bank = deleteBank( bank ) ;

            length = 0 ;
            largerNum = 0 ;
            bank = NULL ;

            float weight ;

            Data inp ;
            ifstream infile;
            infile.open(fileName.c_str(), ios::in | ios::binary); //binary 開檔

            infile.seekg (0, ios::end);
            int lengthAll = infile.tellg()/sizeof(Data); // 取得檔案大小
            length = lengthAll ;
            infile.seekg (0, ios::beg);

            int num_ways = lengthAll / BUFFER_SIZE ;  //  資料數/200
            int remain = 0 ;

            int divide = 0 ; // 1,分資料到新葉 2.分節點
            vector<Data> buffer; //只能放200筆
            buffer.resize(BUFFER_SIZE);

            int i = 0;
            while ( i < num_ways ) {

              infile.read( (char *) &buffer[0], BUFFER_SIZE*sizeof(Data));

              for ( int j = 0 ; j < BUFFER_SIZE ; j++ ) {

                weight = buffer[j].weight ;



                bank = inputData( bank , weight, divide ) ;
                if ( divide == 1 ) { // 第一次分裂
                  bank = HeadIsLeaf( bank, weight ) ;

                  divide = 0 ;
                } // if ()
                else if ( divide == 2 ) { // 第一次分裂

                  bank = divideHead( bank ) ;
                  divide = 0 ;
                } // else if ()

             } // for()


              i++;
			} // while

			remain = lengthAll-(num_ways*200);
			if ( remain > 0 ){ //如果總資料數無法整除200會有餘數 剩下的自成一檔
              buffer.resize(remain);
			  infile.read( (char *) &buffer[0], remain*sizeof(Data));

              for ( int j = 0 ; j < remain ; j++ ) {
                weight = buffer[j].weight ;


                bank = inputData( bank , weight, divide ) ;
                if ( divide == 1 ) { // 頭分裂
                  bank = HeadIsLeaf( bank, weight ) ;

                  divide = 0 ;
                } // if ()
                else if ( divide == 2 ) { // 頭分裂

                  bank = divideHead( bank ) ;
                  divide = 0 ;
                } // else if ()

             } // for()


			} // if

			infile.close();



        } // checkBinfileline ()

        Data2* inputData( Data2* temp ,float now, int& divide ) {

          if ( temp == NULL ) {
            temp = new Data2 ;
            temp->w[0].weight = now ;
            if ( largerNum == 0 )
              temp->w[0].off = -1 ; //第一個，沒有比它大的
            else
              temp->w[0].off = largerNum ;

            temp->w[1].off = 0 ;
            temp->w[2].off = 0 ;
            temp->w[3].off = 0 ;
            temp->w[4].off = 0 ;
            temp->p1 = NULL ;
            temp->p2 = NULL ;
            temp->p3 = NULL ;
            temp->p4 = NULL ;
            temp->p5 = NULL ;
            temp->p6 = NULL ;
            temp->next = NULL ;
            largerNum++ ;

            return temp ;

          } // if ()


          if ( temp->p1 == NULL ) { // 已經是葉子
            if ( temp->w[2].off == 0 ) {  // 未滿
              roomInput( temp, now ) ;

            } // if ()
            else if ( temp->w[2].weight == now ) {

              largerNum++ ;
            } // else if ()
            else {  // 分裂
              divide = 1 ;
              return temp ;
            } // else

          } // if ()
          else if ( temp->p3 == NULL ) {  // 兩節點
            temp->p2 = inputData( temp->p2 , now, divide ) ;
            if ( divide == 1 ) {
              temp->p3 = inputData( temp->p3 , now, divide ) ;
              temp->p2->next = temp->p3 ;
              temp->w[1].weight = now ;
              temp->w[1].off = 1 ;
              divide = 0 ;
            } // if ()
            else if ( divide == 2 ) {

              temp->p3 = new Data2 ;
              temp->w[1].weight = temp->p2->w[2].weight ;
              temp->w[1].off = 1 ;
              exchange( temp->p2, temp->p3 ) ;
              divide = 0 ;
            } // else if ()



          } // else if ()
          else if ( temp->p4 == NULL ) {   // 三節點
            temp->p3 = inputData( temp->p3 , now, divide ) ;

            if ( divide == 1 ) {
              temp->p4 = inputData( temp->p4 , now, divide ) ;
              temp->p3->next = temp->p4 ;
              temp->w[2].weight = now ;
              temp->w[2].off = 1 ;
              divide = 0 ;
            } // if ()
            else if ( divide == 2 ) {

              temp->p4 = new Data2 ;
              temp->w[2].weight = temp->p3->w[2].weight ;
              temp->w[2].off = 1 ;
              exchange( temp->p3, temp->p4 ) ;

              divide = 0 ;
            } // else if ()


          } // else if ()
          else if ( temp->p5 == NULL ) {  // 四節點
            temp->p4 = inputData( temp->p4 , now, divide ) ;
            if ( divide == 1 ) {
              temp->p5 = inputData( temp->p5 , now, divide ) ;
              temp->p4->next = temp->p5 ;
              temp->w[3].weight = now ;
              temp->w[3].off = 1 ;
              divide = 0 ;
            } // if ()
            else if ( divide == 2 ) {

              temp->p5 = new Data2 ;
              temp->w[3].weight = temp->p2->w[2].weight ;
              temp->w[3].off = 1 ;
              exchange( temp->p4, temp->p5 ) ;
              divide = 0 ;
            } // else if ()


          } // else if ()
          else if ( temp->p6 == NULL ) {  // 五節點
            temp->p5 = inputData( temp->p5 , now, divide ) ;
            if ( divide == 1 ) {
              temp->p6 = inputData( temp->p6 , now, divide ) ;
              temp->p5->next = temp->p6 ;
              temp->w[4].weight = now ;
              temp->w[4].off = 1 ;
              divide = 2 ;
            } // if ()
            else if ( divide == 2 ) {

              temp->p6 = new Data2 ;
              temp->w[4].weight = temp->p2->w[2].weight ;
              temp->w[4].off = 1 ;
              exchange( temp->p5, temp->p6 ) ;
              divide = 2 ;
            } // else if ()


          } // else if ()

          return temp ;

        } // inputData()

        void exchange( Data2* old, Data2* nw ) {
          nw->w[0].weight = old->w[3].weight ;
          nw->w[1].weight = old->w[4].weight ;
          nw->w[0].off = 1 ;
          nw->w[1].off = 1 ;
          nw->w[2].off = 0 ;
          nw->w[3].off = 0 ;
          nw->w[4].off = 0 ;

          old->w[2].off = 0 ;
          old->w[3].off = 0 ;
          old->w[4].off = 0 ;
          nw->p1 = old->p4 ;
          nw->p2 = old->p5 ;
          nw->p3 = old->p6 ;
          nw->p4 = NULL ;
          nw->p5 = NULL ;
          nw->p6 = NULL ;
          old->p4 = NULL ;
          old->p5 = NULL ;
          old->p6 = NULL ;
        } // exchange()

        void roomInput( Data2* temp, float now ) {
          for ( int i = 0 ; i < 4 ; i++ ) {
            if ( temp->w[i].weight == now ) {
              largerNum++ ;
              return ;
            }  // if ()
            else if ( temp->w[i].off == 0 ) {
              temp->w[i].weight = now ;
              temp->w[i].off = largerNum ;
              largerNum++ ;
              return ;
            } // else if ()

          } // for

        } // roomInput()

        bool isEmpty() {

          if ( largerNum == 0 )
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
          fileName = "sorted"+input+".bin" ;
          FILE * infile = NULL;
          infile = fopen(fileName.c_str(),"rb") ;
          if(infile == NULL ) {          // bin檔不存在
              cout<<endl<<fileName<<" does not exist!" << endl ;
              return false ;

          } // if ()
          fclose(infile);
          //----------------------------------建立資料庫
          checkBinfileline( fileName );

          return true ;

          //printBank() ;   // ------------------------------------------bin檔內容讀入測試處(<--)

        } // isBin ()

        void printBank() {                    // 測試用印出
          Data2* temp = bank ;
          int i = 1 ;
          while ( temp != NULL && temp->p1 != NULL ) {
            temp = temp->p1 ;

          } // for()

          while ( temp != NULL ) {
            cout << endl << "[" << i << "] (" << temp->w[0].weight << ", " ;
            if ( temp->w[0].off == -1)
              cout << "0)"  ;
            else
              cout << temp->w[0].off << ")"  ;

            i++ ;
            if ( temp->w[1].off != 0 ) {
              cout << endl << "[" << i << "] (" << temp->w[1].weight << ", " << temp->w[1].off << ")"  ;
              i++ ;
            } // if ()
            if ( temp->w[2].off != 0 ) {
              cout << endl << "[" << i << "] (" << temp->w[2].weight << ", " << temp->w[2].off << ")"  ;
              i++ ;
            } // if()

            temp = temp->next ;
          } // while

        } // printBank()


        Data2* deleteBank( Data2* temp ) {

          if ( temp->p6 != NULL ) {
            temp->p6 = deleteBank( temp->p6 ) ;
          } // if ()
          if ( temp->p5 != NULL ) {
            temp->p5 = deleteBank( temp->p5 ) ;
          } // if ()
          if ( temp->p4 != NULL ) {
            temp->p4 = deleteBank( temp->p4 ) ;
          } // if ()
          if ( temp->p3 != NULL ) {
            temp->p3 = deleteBank( temp->p3 ) ;
          } // if ()
          if ( temp->p2 != NULL ) {
            temp->p2 = deleteBank( temp->p2 ) ;
          } // if ()
          if ( temp->p1 != NULL ) {
            temp->p1 = deleteBank( temp->p1 ) ;
          } // if ()

          delete temp ;
          temp = NULL ;

          return temp ;

        } // ()


} ;

class searchData {
private:
    int start ;
    int stop ;

public:

    void findRange( Data2* tree, int length ) {
       Data2* temp = tree ;
       Data2* target = NULL ;
       start = 0 ;
       stop = 0 ;
       float num ;
       cout << endl << "Please input a threshold in the range [0,1]: " ;
       cin >> num ;

       runTree( temp, num ) ;

       if ( start == -1 )
          start = 0 ;

       if ( stop == -1 )
         stop = length ;


    } // findRange()

     void runTree( Data2* temp, float num ) {


        if ( temp->w[0].off != 1 ) {

          if ( temp->w[0].weight == num ) {

            start = temp->w[0].off ;
            if ( temp->w[1].off != 0 )
              stop = temp->w[1].off ;
            else
              stop = -1 ;
          } // if()
          else if ( temp->w[1].weight == num ) {
            start = temp->w[1].off ;
            if ( temp->w[2].off != 0 )
              stop = temp->w[2].off ;
            else
              stop = -1 ;
          } // else if ()
          else if ( temp->w[2].weight == num ) {
            start = temp->w[2].off ;
            temp = temp->next ;
            if ( temp != NULL )
              stop = temp->w[0].off ;
            else
              stop = -1 ;
          } // else if ()

          return ;
        } // if ()

        if ( temp->w[3].off != 0 &&  temp->w[3].weight >= num ) {

          runTree( temp->p5, num ) ;
        } // if ()
        else if ( temp->w[2].off != 0 &&  temp->w[2].weight >= num ) {

          runTree( temp->p4, num ) ;
        } // else if ()
        else if ( temp->w[1].off != 0 &&  temp->w[1].weight >= num ) {

          runTree( temp->p3, num ) ;
        } // else if ()
        else if ( temp->w[0].off != 0 &&  temp->w[0].weight >= num ) {
            cout << endl << temp->w[0].weight ;
          runTree( temp->p2, num ) ;
        } // else if ()
        else{

          runTree( temp->p1, num ) ;
        } // else

     } // runTree()

        void checkBinfileline( string input ) { // 確認資料數(bin)

            string fileName = "sorted"+input+".bin" ;


            ifstream infile;
            infile.open(fileName.c_str(), ios::in | ios::binary); //binary 開檔

            infile.seekg (0, ios::end);
            infile.seekg (0, ios::beg);



            int remain = 0 ;
            int i = 0 ;
            int code = 1 ;

            vector<Data> buffer; //只能放200筆
            buffer.resize(BUFFER_SIZE);
            while ( i < stop ) {

              if ( stop-i >= 200 ) {
                infile.read( (char *) &buffer[0], BUFFER_SIZE*sizeof(Data));

                for ( int j = 0 ; j < BUFFER_SIZE ; j++ ) {
                  cout << endl << "[" << code << "]" << setw(12) << buffer[j].putID << setw(12) << buffer[j].getID << setw(12) << buffer[j].weight ;
                  code++ ;
                } // for()

                i = i + 200 ;
              } // if ()
              else {
                buffer.resize(stop-i);
                infile.read( (char *) &buffer[0], (stop-i)*sizeof(Data));

                for ( int j = 0 ; j < (stop-i) ; j++ ) {
                  cout << endl << "[" << code << "]" << setw(12) << buffer[j].putID << setw(12) << buffer[j].getID << setw(12) << buffer[j].weight ;
                  code++ ;
                } // for()

                i = stop ;
              } // else



			} // while

			cout << endl ;
			infile.close();



        } // checkBinfileline ()

};

int main(){
    int command = -1 ;
    DataList dataBank ;
    externalSort mission_one ;
    searchData sData ;
    string fileName ;
    do{
        printf("\n***********************************************\n On-machine Exercise 05                       *\n Mission 1: External Merge Sort on a Big File *\n Mission 2: Construction of Primary Index     *\n") ;
        printf( " Mission 3: Range Search by Primary Index     *\n" ) ;
        printf("***********************************************") ;
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
          	mission_one.input( fileName ) ;
          	cout << endl << "The internal sort is completed. Check the initial sorted runs!" << endl;
          	mission_one.external_sort();
          } // if ()
		  else
		  	cout << "Please input again!" << endl;
        } // if ()
        else if ( command == 2 ) {
          cout << "\nInput a file number ([0] Quit): " ;
          cin >> fileName ;
          if ( fileName != "0" ) {

            if ( dataBank.isBin ( fileName )) {

              dataBank.printBank() ;

            } // if ()

          } // if ()
		  else
		  	cout << "Please input again!" << endl;

        } // if ()
        else if ( command == 3 ) { //挑戰備用
          if ( dataBank.getLength() != 0 ) {
            sData.findRange( dataBank.getBank(), dataBank.getLength() ) ;
            sData.checkBinfileline( fileName ) ;
          } // if()
          else {
            cout << endl << "### Choose 1 first. ###" ;
          } // else

        } // else if()
        else if ( command == 4 ) {


        } // if ()
    }while( command != 0 ) ;
    system ( "pause" );        // pause the display
    return 0;
}
