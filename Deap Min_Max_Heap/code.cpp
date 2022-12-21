//DS1102ex01_10833230_李郁含 
#include<iostream>    // cin,cout,endl
#include<fstream> // open, is_open
#include<string>      // c_str,length
#include<vector>
#include<cstdlib>     //strtoul,system
#include<cmath>       //sqrt
#include <math.h>     //次方 
using namespace std;

class SchoolList {
  public:
    typedef struct sT{ 
      int nstud; // 學生數number of students
      int num;   // 序號 
    } schoolType; // structure of school data
  
  vector<schoolType> allR; 
  string fileID;
  void reset(); // declaration: initial set up
  
  public:
    SchoolList() { reset(); } // constructor for initialization
    ~SchoolList() { reset(); } // destructor for initialization   
    bool readFile(); // declaration: read all from a file
}; //end SchoolList

void SchoolList::reset(){ // definition: initial set up
  this->allR.clear(); // clean up the job list
  this->fileID.clear(); // clean up the file identifier
} //end reset

bool isNumber( string isnum ){ // 第一個字元是否是數字 
  if ( ( isnum[0] <= '9' ) && ( isnum[0] >= '0' ))
    return true;
  else
    return false;
} // isNumber

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

bool SchoolList::readFile(){ // definition: read all from a file
  int n = 0; //序號 
  fstream inFile; // file handle
  string fileName; // file name
  this->reset(); // call: initial set up
  cout << endl << "Input a file number ([0] Quit): ";
  cin >> this->fileID; // get the file identifier
  fileName = "input" + fileID + ".txt";
  inFile.open(fileName.c_str(), fstream::in); // open file to read
  if (!inFile.is_open()){ // unable to open file
    cout << endl << "### " << fileName << " does not exist! ###" << endl;
    return false;
  } //end if
  else{
    char cstr[255]; // input buffer of one line as c-string
    int fNo, pre, pos;
    inFile.getline(cstr, 255, '\n'); // skip the 1st header line
    inFile.getline(cstr, 255, '\n'); // skip the 2nd header line
    inFile.getline(cstr, 255, '\n'); // skip the list of column names
    while (inFile.getline(cstr, 255, '\n')){ // get all records line by line
      schoolType oneR; // one data record
      string buf, cut; // transform c-string into C++ string
      fNo = 0; // 目前切到第幾個 number of fields read so far
      pre = 0; // 目前切到第幾個char  locate one field of input record
      buf.assign(cstr); // copy c-string into C++ string
      do{ // scan the buffer from left to right
        pos = buf.find_first_of('\t', pre); // locate the next field by '\t' (tab)
        cut = buf.substr(pre, pos - pre); //扣掉tab len = pos - pre // retrieve a field
        switch (++fNo){
          case 7: remove_nonnumber( cut );
		    oneR.nstud = atoi(cut.c_str()); // get the number of students
            break;
          default: break;
        } //end switch
        pre = ++pos; // 跳過tab //move to the next field
      } while ((pos > 0) && (fNo < 10)); // continue if there are still fields to be read
      n = n + 1;
      oneR.num = n;
      this->allR.push_back(oneR); // save one record into the school list
    } //end outer-while
    inFile.close(); // close file
  } // end else
  if (!this->allR.size()){
    cout << endl << "### Get nothing from the file " << fileName << " ! ### " << endl;
    return false;
  } // end if
  return true;
} // end readFil

class Heap{  //以『學生數』建立一棵最大堆積 
  private:
    vector<SchoolList::schoolType> myHeap; //最大堆積 
  public:
	void reset(); // declaration: initial set up
	Heap() { reset(); } // constructor for initialization
    ~Heap() { reset(); } // destructor for initialization   
	bool empty(){ if ( myHeap.size() == 0 )  return true; else  return false; } // empty
    void reHeap();// construct
    void maxheap(vector<SchoolList::schoolType> allR);
    
    void printLeftMost(); //print LeftMost
    void printBottom(){; // printBottom
      int i = myHeap.size()-1; //直接取得heap中最後一個元素
      cout << "bottom:" << " [" << myHeap[i].num << "] " <<  myHeap[i].nstud << endl; //印index 印學生數number of students 
    } // printBottom
    void printOR(){
    	cout << "root:" << " [" << myHeap[0].num << "] " <<  myHeap[0].nstud << endl; //印index 印學生數number of students
    } // printOR
};

void Heap::reset(){ // definition: initial set up
  this->myHeap.clear(); // clean up the job list
} //end reset

void Heap::reHeap(){ 
    int len = myHeap.size(); // get length
    for(int i = len/2-1; i >= 0; i--){  // int i = len/2-1 先從最底下擁有子節點的父節點開始判斷 類似 call heapRebuild(i), i = 2, 1, 0 從2開始 
        int index = i; // 設定本次移動的位置
        while(1){
            int swapPos; //要交換的位置
            int childMax = -1; //children比較大的數值
            if(index*2+1 < len){ //如果有leftChild
                if(myHeap[index*2+1].nstud > childMax){ //如果大於childMax,就設定childMax數值,並設定為要交換的位置
                    childMax = myHeap[index*2+1].nstud;
                    swapPos = index*2+1;
                } // if 
            } // if 
            if(index*2+2 < len){ //如果有rightChild
                if(myHeap[index*2+2].nstud > childMax){ //如果大於childMax,就設定childMax數值,並設定為要交換的位置
                    childMax = myHeap[index*2+2].nstud;
                    swapPos = index*2+2;
                } // if 
            } // if 

            if(childMax > myHeap[index].nstud){ //如果最後發現有child大於自己
                swap(myHeap[index],myHeap[swapPos]); //就進行交換
                index = swapPos; //設定新的位置
            } // if 
            else //沒有的話代表結束
                break;
        } // while
    } // for
} // reHeap()

void Heap::maxheap(vector<SchoolList::schoolType> allR){ //以『學生數』建立一棵最大堆積，依照序號由小到大一筆一筆新增至原有的堆積結構中
  //schoolType oneR;
  for ( int i = 0 ; i < allR.size() ; i++ ){
  	myHeap.push_back(allR[i]); //將資料一個一個推進heap 
  	reHeap();                  //再去重整heap 
  } // for 
} // maxheap

void Heap::printLeftMost(){ //輸出最左邊的
    cout << "leftmost bottom:";
    int i = 0; 
    int len = myHeap.size(); //取得長度
    while(true) {//設立無限迴圈
        if(i*2+1 < len) //如果有left child,就繼續往左邊走
            i = i*2+1;
        else//沒有的話就break
            break;
    } // while
    cout << " [" << myHeap[i].num << "] " <<  myHeap[i].nstud << endl ; //印index 印學生數number of students
} // printLeftMost

class Deap{ // 以『學生數』建立一棵雙堆積
private:
    vector<SchoolList::schoolType> myDeap; // 雙堆積
public:
	void reset(){ this->myDeap.clear(); } // reset declaration: initial set up
	Deap() { reset(); } // constructor for initialization
    ~Deap() { reset(); } // destructor for initialization 
    
	bool empty(){ if ( myDeap.size() == 0 ) return true;   else  return false; } // empty
	int height( int N ) { return ceil(log2(N+2)); }// height 輸出目前level
	int parent( int i ){ i--; return i/2; } // parent 輸出目前節點的父節點
	
	void max_heap_redeap( int j ); // 將目前資料與該父節點比較並調整
	void min_heap_redeap( int i );
	bool is_min( int i, int temp ); //判斷剛新增的節點是在min-heap還是max-heap 
    void reDeap( int index );// construct
    void deap(vector<SchoolList::schoolType> allR);
    
    void printVal(); // print Val of deap
    void printLeftMost(); //print LeftMost
    void printBottom(){; // printBottom
      int i = myDeap.size()-1; //直接取得heap中最後一個元素
      cout << "bottom:" << " [" << myDeap[i].num << "] " <<  myDeap[i].nstud << endl; //印index 印學生數number of students 
    } // printBottom
};

void Deap::printVal(){//輸出heap的內容
    int len = myDeap.size(); //取得heap長度
    for(int i = 0; i < len; i++){
        cout << "[" << myDeap[i].num << "]" ; //印index
        cout <<  myDeap[i].nstud ;     // 印學生數number of students (5)
        cout << endl ;
    } // for
} // printVal

void Deap::max_heap_redeap( int j ){  // 將目前資料與該父節點比較並調整
    int p = parent(j);
    while ( p != 0 ){
      if( myDeap[j].nstud > myDeap[p].nstud )
	    swap(myDeap[j],myDeap[p]);
	  else
	    break;
	  j = p;
	  p = parent(j);
	} // while
} // max_heap_redeap

void Deap::min_heap_redeap( int i ){  // 將目前資料與該父節點比較並調整
    int p = parent(i);
    while ( p != 0 ){
      if( myDeap[i].nstud < myDeap[p].nstud )
	    swap(myDeap[i],myDeap[p]);
	  else
	    break;
	  i = p;
	  p = parent(i);
	} // while
} // min_heap_redeap

bool Deap::is_min( int i, int temp ){  //判斷剛新增的節點是在min-heap還是max-heap 
    int check = 3*temp - 1; //算出(check) 每level的第一個max
    if ( i < check )        //如果小於check代表在min 
      return true;
    else                    //如果大於等於check代表在max 
      return false;
} // is_min

void Deap::reDeap( int index ){ 
    int j = 0;
	int i = index; //index是目前的 
    int depth = height(i);  // 輸出目前level
    int temp = pow(2,depth-2); //min跟對應的max之間的差距 
    
    if ( i == 1 )
      return;
    if ( is_min( i, temp ) ){ // min-heap
      j = i + temp;
      
      if ( j > myDeap.size() )  //對應的max是空的 s    //如果不是空的 
      	j = parent(j);          //就跟j的父節點比     //就直接跟j比 
	  
      if( myDeap[i].nstud > myDeap[j].nstud ){
      	swap(myDeap[i],myDeap[j]);
        max_heap_redeap(j);    //max_heap_redeap(陣列位置) 將目前資料與該父節點比較並調整
      } // if
	  else 
        min_heap_redeap(i);    //min_heap_redeap(陣列位置);      
    } // if 
    else if ( !is_min( i, temp ) ){ // max-heap
      j = i ;
      i = i - temp;
      
      if ( i > myDeap.size() )  //對應的min是空的      //如果不是空的
        i = parent(i);          //就跟i的父節點比     //就直接跟i比
      
      if( myDeap[j].nstud < myDeap[i].nstud ) {
        swap(myDeap[i],myDeap[j]);
        min_heap_redeap(i);   //min_heap_redeap(陣列位置)  
      }  // if 
	  else 
        max_heap_redeap(j);   //max_heap_redeap(陣列位置);      
    } // else if
} // reDeap()

void Deap::deap(vector<SchoolList::schoolType> allR){ //以『學生數』建立一棵最大堆積，依照序號由小到大一筆一筆新增至原有的堆積結構中
  SchoolList::schoolType oneR; 
  oneR.nstud = 0;
  oneR.num = 0;
  myDeap.push_back(oneR);  //推進空的 建立一個虛擬的節點(0) 
  for ( int i = 0 ; i < allR.size() ; i++ ){
  	myDeap.push_back(allR[i]); //將資料一個一個推進deap 
  	reDeap( i+1 );             //再重整deap 
  	printVal();
  	cout << endl ;
  } // for 
} // maxheap

void Deap::printLeftMost(){ //輸出最左邊的
    cout << "leftmost bottom:";
    int i = 0; //迭代變數
    int len = myDeap.size(); //取得長度
    while(true) {//設立無限迴圈
        if(i*2+1 < len) //如果有left child,就繼續往左邊走
            i = i*2+1;
        else//沒有的話就break
            break;
    } // while
    cout << " [" << myDeap[i].num << "] " ; //印index
    cout <<  myDeap[i].nstud ;     // 印學生數number of students 
    cout << endl ;
} // printLeftMost

class Min_MaxHeap{
private:
    vector<SchoolList::schoolType> myMMH;
public:
	void reset(){ this->myMMH.clear(); } // reset declaration: initial set up
	Min_MaxHeap() { reset(); } // constructor for initialization
    ~Min_MaxHeap() { reset(); } // destructor for initialization 
	  
	bool empty(){ if ( myMMH.size() == 0 ) return true;   else  return false; } // empty
	int height( int N ) { return ceil(log2(N+2)); }// height 輸出目前level
	int parent( int i ){ i--; return i/2; } // parent 輸出目前節點的父節點
	int grandparent( int i ){ i = (i - 3)/4;  return i; } // grandparent 輸出目前節點的祖父節點
	bool is_even( int N );
	
	void theMax( int i );
	void theMin( int i );
    void reMMHeap( int index );// construct
    void MinMaxHeap(vector<SchoolList::schoolType> allR);
    void printOR(){
    	cout << "root:" << " [" << myMMH[0].num << "] " <<  myMMH[0].nstud << endl; //印index 印學生數number of students 
    } // printOR
    void printBottom(){; // printBottom
      int i = myMMH.size()-1; //直接取得heap中最後一個元素
      cout << "bottom:" << " [" << myMMH[i].num << "] " <<  myMMH[i].nstud << endl; //印index 印學生數number of students 
    } // printBottom
    void printLeftMost(); //print LeftMost
};

bool Min_MaxHeap::is_even( int N ){ //是偶數? 
	if ( N % 2 == 0 )
	  return true;
	else
	  return false;
} // is_even

void Min_MaxHeap::theMax( int i ){  // 將較大的往上推 
    if ( i == 0 || i == 1 || i == 2 )
      return;
    int gp = grandparent(i);
    while ( gp >= 0 ){
      if( myMMH[i].nstud > myMMH[gp].nstud )
	    swap(myMMH[i],myMMH[gp]);
	  else
	    break;
	  if ( gp == 0 || gp == 1 || gp == 2 )
        return;
	  i = gp;
	  gp = grandparent(i);
	} // while
} // theMax

void Min_MaxHeap::theMin( int i ){  // 將較小的往上推
    if ( i == 0 || i == 1 || i == 2 )
      return;
    int gp = grandparent(i);
    while ( gp >= 0 ){
      if( myMMH[i].nstud < myMMH[gp].nstud )
      	swap(myMMH[i],myMMH[gp]);
	  else
	    break;
	  if ( gp == 0 || gp == 1 || gp == 2 )
        return;
	  i = gp;
	  gp = grandparent(i);
	} // while
} // theMin


void Min_MaxHeap::reMMHeap( int index ){ 
    int depth = height(index);
    int p = parent(index);
    if ( !is_even( depth ) ){  //是奇數->代表是min
      if(myMMH[index].nstud > myMMH[p].nstud) {
        swap(myMMH[index],myMMH[p]);
        theMax(p);      //將父節點與祖父節點比較 將較大的往上推
      } // if
      else
        theMin(index);  //將目前節點節點與祖父節點比較 將較小的往上推
    } // if
    else {                    //是偶數->代表是max
      if(myMMH[index].nstud < myMMH[p].nstud) {
        swap(myMMH[index],myMMH[p]);
        theMin(p);  //將父節點與祖父節點比較 將較小的往上推 
      } // if
      else
        theMax(index);	//將目前節點與祖父節點比較 將較大的往上推 
	} // else
	 
} // reMMHeap

void Min_MaxHeap::MinMaxHeap(vector<SchoolList::schoolType> allR){ //以『學生數』建立一棵最小最大堆積，依照序號由小到大一筆一筆新增至原有的堆積結構中
  for ( int i = 0 ; i < allR.size() ; i++ ){
  	myMMH.push_back(allR[i]);   //將資料一個一個推進Min-maxheap  
  	if ( i != 0 )               //如果是第一個就不用重整 
  	  reMMHeap( i );            //再重整Min-maxheap  
  } // for 
} // maxheap

void Min_MaxHeap::printLeftMost(){ //輸出最左邊的
    cout << "leftmost bottom:";
    int i = 0; 
    int len = myMMH.size(); //取得長度
    while(true) {//設立無限迴圈
        if(i*2+1 < len) //如果有left child,就繼續往左邊走
            i = i*2+1;
        else//沒有的話就break
            break;
    } // while
    cout << " [" << myMMH[i].num << "] " ; //印index
    cout <<  myMMH[i].nstud ;     // 印學生數number of students
    cout << endl ;
} // printLeftMost

int main(){
    int command = 0; //第一個input(0, 1, 2)
    SchoolList list;
    Heap heap;
    Deap deap;
    Min_MaxHeap MMHeap;
    do{
        cout << endl << "**** Heap Construction *****";
        cout << endl << "* 0. QUIT                  *";
        cout << endl << "* 1. Build a max heap      *";
        cout << endl << "* 2. Build a DEAP          *";
        cout << endl << "* 3. Build a min-max heap  *";
        cout << endl << "****************************";
        cout << endl << "Input a choice(0, 1, 2, 3): ";
        cin >> command;  //cin第一個input(0, 1, 2, 3)
        switch(command){
        case 0 :
            break;
        case 1 :
            while ( !list.readFile() ) //讀檔並將每筆資料附上唯一序號後 
              list.reset();
            if(!heap.empty())
        	  heap.reset();
            heap.maxheap(list.allR); //以『學生數』建立一棵最大堆積 
            cout << "<max heap>" << endl;
            heap.printOR(); // 找到最大堆積的樹根並印出 
            heap.printBottom(); // 找到（右下角）底部節點並印出 
            heap.printLeftMost(); // 找到最左下角落的節點並印出	
            break;
        case 2 :
        	while ( !list.readFile() ) //讀檔並將每筆資料附上唯一序號後 
        	  list.reset();
        	if(!deap.empty())
        	  deap.reset();
            deap.deap(list.allR); // 以『學生數』建立一棵雙堆積 
            cout << "<DEAP>" << endl;
            deap.printBottom(); // 找到（右下角）底部節點並印出
            deap.printLeftMost(); // 找到最左下角落的節點並印出
            break;
        case 3 :
        	while ( !list.readFile() ) //讀檔並將每筆資料附上唯一序號後 
        	  list.reset();
        	if(!MMHeap.empty())
        	  MMHeap.reset();
            MMHeap.MinMaxHeap(list.allR); // 以『學生數』建立一棵最小-最大堆積
            cout << "<min-max heap>" << endl;
            MMHeap.printOR();             // 找到最大堆積的樹根並印出  
            MMHeap.printBottom();         // 找到（右下角）底部節點並印出 
            MMHeap.printLeftMost();       // 找到最左下角落的節點並印出 
            break;
        default :
            cout << endl << "Command does not exist!" << endl; //input 0,1以外的
        } // end switch
    }
    while ( command != 0 );    //'0':stop the program
    system ( "pause" );        // pause the display
    return 0;
} // end main
