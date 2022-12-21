//DS1102ex01_10833230_�����t 
#include<iostream>    // cin,cout,endl
#include<fstream> // open, is_open
#include<string>      // c_str,length
#include<vector>
#include<cstdlib>     //strtoul,system
#include<cmath>       //sqrt
#include <math.h>     //���� 
using namespace std;

class SchoolList {
  public:
    typedef struct sT{ 
      int nstud; // �ǥͼ�number of students
      int num;   // �Ǹ� 
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

bool isNumber( string isnum ){ // �Ĥ@�Ӧr���O�_�O�Ʀr 
  if ( ( isnum[0] <= '9' ) && ( isnum[0] >= '0' ))
    return true;
  else
    return false;
} // isNumber

void remove_nonnumber( string &str ){ //�������O�Ʀr������ 
  string token; //���۩�P�_�L��token(�h�����O�Ʀr��token) 
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
  int n = 0; //�Ǹ� 
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
      fNo = 0; // �ثe����ĴX�� number of fields read so far
      pre = 0; // �ثe����ĴX��char  locate one field of input record
      buf.assign(cstr); // copy c-string into C++ string
      do{ // scan the buffer from left to right
        pos = buf.find_first_of('\t', pre); // locate the next field by '\t' (tab)
        cut = buf.substr(pre, pos - pre); //����tab len = pos - pre // retrieve a field
        switch (++fNo){
          case 7: remove_nonnumber( cut );
		    oneR.nstud = atoi(cut.c_str()); // get the number of students
            break;
          default: break;
        } //end switch
        pre = ++pos; // ���Ltab //move to the next field
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

class Heap{  //�H�y�ǥͼơz�إߤ@�ʳ̤j��n 
  private:
    vector<SchoolList::schoolType> myHeap; //�̤j��n 
  public:
	void reset(); // declaration: initial set up
	Heap() { reset(); } // constructor for initialization
    ~Heap() { reset(); } // destructor for initialization   
	bool empty(){ if ( myHeap.size() == 0 )  return true; else  return false; } // empty
    void reHeap();// construct
    void maxheap(vector<SchoolList::schoolType> allR);
    
    void printLeftMost(); //print LeftMost
    void printBottom(){; // printBottom
      int i = myHeap.size()-1; //�������oheap���̫�@�Ӥ���
      cout << "bottom:" << " [" << myHeap[i].num << "] " <<  myHeap[i].nstud << endl; //�Lindex �L�ǥͼ�number of students 
    } // printBottom
    void printOR(){
    	cout << "root:" << " [" << myHeap[0].num << "] " <<  myHeap[0].nstud << endl; //�Lindex �L�ǥͼ�number of students
    } // printOR
};

void Heap::reset(){ // definition: initial set up
  this->myHeap.clear(); // clean up the job list
} //end reset

void Heap::reHeap(){ 
    int len = myHeap.size(); // get length
    for(int i = len/2-1; i >= 0; i--){  // int i = len/2-1 ���q�̩��U�֦��l�`�I�����`�I�}�l�P�_ ���� call heapRebuild(i), i = 2, 1, 0 �q2�}�l 
        int index = i; // �]�w�������ʪ���m
        while(1){
            int swapPos; //�n�洫����m
            int childMax = -1; //children����j���ƭ�
            if(index*2+1 < len){ //�p�G��leftChild
                if(myHeap[index*2+1].nstud > childMax){ //�p�G�j��childMax,�N�]�wchildMax�ƭ�,�ó]�w���n�洫����m
                    childMax = myHeap[index*2+1].nstud;
                    swapPos = index*2+1;
                } // if 
            } // if 
            if(index*2+2 < len){ //�p�G��rightChild
                if(myHeap[index*2+2].nstud > childMax){ //�p�G�j��childMax,�N�]�wchildMax�ƭ�,�ó]�w���n�洫����m
                    childMax = myHeap[index*2+2].nstud;
                    swapPos = index*2+2;
                } // if 
            } // if 

            if(childMax > myHeap[index].nstud){ //�p�G�̫�o�{��child�j��ۤv
                swap(myHeap[index],myHeap[swapPos]); //�N�i��洫
                index = swapPos; //�]�w�s����m
            } // if 
            else //�S�����ܥN����
                break;
        } // while
    } // for
} // reHeap()

void Heap::maxheap(vector<SchoolList::schoolType> allR){ //�H�y�ǥͼơz�إߤ@�ʳ̤j��n�A�̷ӧǸ��Ѥp��j�@���@���s�W�ܭ즳����n���c��
  //schoolType oneR;
  for ( int i = 0 ; i < allR.size() ; i++ ){
  	myHeap.push_back(allR[i]); //�N��Ƥ@�Ӥ@�ӱ��iheap 
  	reHeap();                  //�A�h����heap 
  } // for 
} // maxheap

void Heap::printLeftMost(){ //��X�̥��䪺
    cout << "leftmost bottom:";
    int i = 0; 
    int len = myHeap.size(); //���o����
    while(true) {//�]�ߵL���j��
        if(i*2+1 < len) //�p�G��left child,�N�~�򩹥��䨫
            i = i*2+1;
        else//�S�����ܴNbreak
            break;
    } // while
    cout << " [" << myHeap[i].num << "] " <<  myHeap[i].nstud << endl ; //�Lindex �L�ǥͼ�number of students
} // printLeftMost

class Deap{ // �H�y�ǥͼơz�إߤ@������n
private:
    vector<SchoolList::schoolType> myDeap; // ����n
public:
	void reset(){ this->myDeap.clear(); } // reset declaration: initial set up
	Deap() { reset(); } // constructor for initialization
    ~Deap() { reset(); } // destructor for initialization 
    
	bool empty(){ if ( myDeap.size() == 0 ) return true;   else  return false; } // empty
	int height( int N ) { return ceil(log2(N+2)); }// height ��X�ثelevel
	int parent( int i ){ i--; return i/2; } // parent ��X�ثe�`�I�����`�I
	
	void max_heap_redeap( int j ); // �N�ثe��ƻP�Ӥ��`�I����ýվ�
	void min_heap_redeap( int i );
	bool is_min( int i, int temp ); //�P�_��s�W���`�I�O�bmin-heap�٬Omax-heap 
    void reDeap( int index );// construct
    void deap(vector<SchoolList::schoolType> allR);
    
    void printVal(); // print Val of deap
    void printLeftMost(); //print LeftMost
    void printBottom(){; // printBottom
      int i = myDeap.size()-1; //�������oheap���̫�@�Ӥ���
      cout << "bottom:" << " [" << myDeap[i].num << "] " <<  myDeap[i].nstud << endl; //�Lindex �L�ǥͼ�number of students 
    } // printBottom
};

void Deap::printVal(){//��Xheap�����e
    int len = myDeap.size(); //���oheap����
    for(int i = 0; i < len; i++){
        cout << "[" << myDeap[i].num << "]" ; //�Lindex
        cout <<  myDeap[i].nstud ;     // �L�ǥͼ�number of students (5)
        cout << endl ;
    } // for
} // printVal

void Deap::max_heap_redeap( int j ){  // �N�ثe��ƻP�Ӥ��`�I����ýվ�
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

void Deap::min_heap_redeap( int i ){  // �N�ثe��ƻP�Ӥ��`�I����ýվ�
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

bool Deap::is_min( int i, int temp ){  //�P�_��s�W���`�I�O�bmin-heap�٬Omax-heap 
    int check = 3*temp - 1; //��X(check) �Clevel���Ĥ@��max
    if ( i < check )        //�p�G�p��check�N��bmin 
      return true;
    else                    //�p�G�j�󵥩�check�N��bmax 
      return false;
} // is_min

void Deap::reDeap( int index ){ 
    int j = 0;
	int i = index; //index�O�ثe�� 
    int depth = height(i);  // ��X�ثelevel
    int temp = pow(2,depth-2); //min�������max�������t�Z 
    
    if ( i == 1 )
      return;
    if ( is_min( i, temp ) ){ // min-heap
      j = i + temp;
      
      if ( j > myDeap.size() )  //������max�O�Ū� s    //�p�G���O�Ū� 
      	j = parent(j);          //�N��j�����`�I��     //�N������j�� 
	  
      if( myDeap[i].nstud > myDeap[j].nstud ){
      	swap(myDeap[i],myDeap[j]);
        max_heap_redeap(j);    //max_heap_redeap(�}�C��m) �N�ثe��ƻP�Ӥ��`�I����ýվ�
      } // if
	  else 
        min_heap_redeap(i);    //min_heap_redeap(�}�C��m);      
    } // if 
    else if ( !is_min( i, temp ) ){ // max-heap
      j = i ;
      i = i - temp;
      
      if ( i > myDeap.size() )  //������min�O�Ū�      //�p�G���O�Ū�
        i = parent(i);          //�N��i�����`�I��     //�N������i��
      
      if( myDeap[j].nstud < myDeap[i].nstud ) {
        swap(myDeap[i],myDeap[j]);
        min_heap_redeap(i);   //min_heap_redeap(�}�C��m)  
      }  // if 
	  else 
        max_heap_redeap(j);   //max_heap_redeap(�}�C��m);      
    } // else if
} // reDeap()

void Deap::deap(vector<SchoolList::schoolType> allR){ //�H�y�ǥͼơz�إߤ@�ʳ̤j��n�A�̷ӧǸ��Ѥp��j�@���@���s�W�ܭ즳����n���c��
  SchoolList::schoolType oneR; 
  oneR.nstud = 0;
  oneR.num = 0;
  myDeap.push_back(oneR);  //���i�Ū� �إߤ@�ӵ������`�I(0) 
  for ( int i = 0 ; i < allR.size() ; i++ ){
  	myDeap.push_back(allR[i]); //�N��Ƥ@�Ӥ@�ӱ��ideap 
  	reDeap( i+1 );             //�A����deap 
  	printVal();
  	cout << endl ;
  } // for 
} // maxheap

void Deap::printLeftMost(){ //��X�̥��䪺
    cout << "leftmost bottom:";
    int i = 0; //���N�ܼ�
    int len = myDeap.size(); //���o����
    while(true) {//�]�ߵL���j��
        if(i*2+1 < len) //�p�G��left child,�N�~�򩹥��䨫
            i = i*2+1;
        else//�S�����ܴNbreak
            break;
    } // while
    cout << " [" << myDeap[i].num << "] " ; //�Lindex
    cout <<  myDeap[i].nstud ;     // �L�ǥͼ�number of students 
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
	int height( int N ) { return ceil(log2(N+2)); }// height ��X�ثelevel
	int parent( int i ){ i--; return i/2; } // parent ��X�ثe�`�I�����`�I
	int grandparent( int i ){ i = (i - 3)/4;  return i; } // grandparent ��X�ثe�`�I�������`�I
	bool is_even( int N );
	
	void theMax( int i );
	void theMin( int i );
    void reMMHeap( int index );// construct
    void MinMaxHeap(vector<SchoolList::schoolType> allR);
    void printOR(){
    	cout << "root:" << " [" << myMMH[0].num << "] " <<  myMMH[0].nstud << endl; //�Lindex �L�ǥͼ�number of students 
    } // printOR
    void printBottom(){; // printBottom
      int i = myMMH.size()-1; //�������oheap���̫�@�Ӥ���
      cout << "bottom:" << " [" << myMMH[i].num << "] " <<  myMMH[i].nstud << endl; //�Lindex �L�ǥͼ�number of students 
    } // printBottom
    void printLeftMost(); //print LeftMost
};

bool Min_MaxHeap::is_even( int N ){ //�O����? 
	if ( N % 2 == 0 )
	  return true;
	else
	  return false;
} // is_even

void Min_MaxHeap::theMax( int i ){  // �N���j�����W�� 
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

void Min_MaxHeap::theMin( int i ){  // �N���p�����W��
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
    if ( !is_even( depth ) ){  //�O�_��->�N��Omin
      if(myMMH[index].nstud > myMMH[p].nstud) {
        swap(myMMH[index],myMMH[p]);
        theMax(p);      //�N���`�I�P�����`�I��� �N���j�����W��
      } // if
      else
        theMin(index);  //�N�ثe�`�I�`�I�P�����`�I��� �N���p�����W��
    } // if
    else {                    //�O����->�N��Omax
      if(myMMH[index].nstud < myMMH[p].nstud) {
        swap(myMMH[index],myMMH[p]);
        theMin(p);  //�N���`�I�P�����`�I��� �N���p�����W�� 
      } // if
      else
        theMax(index);	//�N�ثe�`�I�P�����`�I��� �N���j�����W�� 
	} // else
	 
} // reMMHeap

void Min_MaxHeap::MinMaxHeap(vector<SchoolList::schoolType> allR){ //�H�y�ǥͼơz�إߤ@�ʳ̤p�̤j��n�A�̷ӧǸ��Ѥp��j�@���@���s�W�ܭ즳����n���c��
  for ( int i = 0 ; i < allR.size() ; i++ ){
  	myMMH.push_back(allR[i]);   //�N��Ƥ@�Ӥ@�ӱ��iMin-maxheap  
  	if ( i != 0 )               //�p�G�O�Ĥ@�ӴN���έ��� 
  	  reMMHeap( i );            //�A����Min-maxheap  
  } // for 
} // maxheap

void Min_MaxHeap::printLeftMost(){ //��X�̥��䪺
    cout << "leftmost bottom:";
    int i = 0; 
    int len = myMMH.size(); //���o����
    while(true) {//�]�ߵL���j��
        if(i*2+1 < len) //�p�G��left child,�N�~�򩹥��䨫
            i = i*2+1;
        else//�S�����ܴNbreak
            break;
    } // while
    cout << " [" << myMMH[i].num << "] " ; //�Lindex
    cout <<  myMMH[i].nstud ;     // �L�ǥͼ�number of students
    cout << endl ;
} // printLeftMost

int main(){
    int command = 0; //�Ĥ@��input(0, 1, 2)
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
        cin >> command;  //cin�Ĥ@��input(0, 1, 2, 3)
        switch(command){
        case 0 :
            break;
        case 1 :
            while ( !list.readFile() ) //Ū�ɨñN�C����ƪ��W�ߤ@�Ǹ��� 
              list.reset();
            if(!heap.empty())
        	  heap.reset();
            heap.maxheap(list.allR); //�H�y�ǥͼơz�إߤ@�ʳ̤j��n 
            cout << "<max heap>" << endl;
            heap.printOR(); // ���̤j��n����ڨæL�X 
            heap.printBottom(); // ���]�k�U���^�����`�I�æL�X 
            heap.printLeftMost(); // ���̥��U�������`�I�æL�X	
            break;
        case 2 :
        	while ( !list.readFile() ) //Ū�ɨñN�C����ƪ��W�ߤ@�Ǹ��� 
        	  list.reset();
        	if(!deap.empty())
        	  deap.reset();
            deap.deap(list.allR); // �H�y�ǥͼơz�إߤ@������n 
            cout << "<DEAP>" << endl;
            deap.printBottom(); // ���]�k�U���^�����`�I�æL�X
            deap.printLeftMost(); // ���̥��U�������`�I�æL�X
            break;
        case 3 :
        	while ( !list.readFile() ) //Ū�ɨñN�C����ƪ��W�ߤ@�Ǹ��� 
        	  list.reset();
        	if(!MMHeap.empty())
        	  MMHeap.reset();
            MMHeap.MinMaxHeap(list.allR); // �H�y�ǥͼơz�إߤ@�ʳ̤p-�̤j��n
            cout << "<min-max heap>" << endl;
            MMHeap.printOR();             // ���̤j��n����ڨæL�X  
            MMHeap.printBottom();         // ���]�k�U���^�����`�I�æL�X 
            MMHeap.printLeftMost();       // ���̥��U�������`�I�æL�X 
            break;
        default :
            cout << endl << "Command does not exist!" << endl; //input 0,1�H�~��
        } // end switch
    }
    while ( command != 0 );    //'0':stop the program
    system ( "pause" );        // pause the display
    return 0;
} // end main
