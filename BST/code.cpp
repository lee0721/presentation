//DS1101ex5_第27組_10833230李郁含_10844149謝宜庭
#include<iostream>    // cin,cout,endl
#include<fstream> // open, is_open
#include<vector>
#include<new> // new
#include<string>      // c_str,length
#include<string.h> 
#include<stdio.h> 
#include<cstdlib> // system, atoi
#include<iomanip> // setw, setprecision
#include<typeinfo>
using namespace std;

class SchoolList {
	public:
  typedef struct sT{ 
    string sname; // 學校名稱school name
    string dname; // 科系名稱department name
    string type; // 日間∕進修別either day or night
    string level; // 等級別graduate or undergraduate
    int nstud; // 學生數number of students
    int nprof; // 教師數number of professors
    int ngrad; // 上學年度畢業生數number of graduates
  } schoolType; // structure of school data
  
  vector<schoolType> allR; // list of all records with 7 columns
  string fileID; // file identifier 501 502 503 504
  void reset(); // declaration: initial set up
  
  public:
    SchoolList() { reset(); } // constructor for initialization
    ~SchoolList() { reset(); } // destructor for initialization   
    bool readFile(); // declaration: read all from a file
    void print();
    void Delete(string Snametemp, string Dnametemp, int Nstudtemp, int Nproftemp, int Ngradtemp);
}; //end SchoolList

void SchoolList::reset(){ // definition: initial set up
  this->allR.clear(); // clean up the job list
  this->fileID.clear(); // clean up the file identifier
} //end reset

bool SchoolList::readFile(){ // definition: read all from a file
  fstream inFile; // file handle
  string fileName; // file name
  this->reset(); // call: initial set up
  cout << endl << "Input a file number: ";
  cin >> this->fileID; // get the file identifier
  fileName = "input" + fileID + ".txt";
  inFile.open(fileName.c_str(), fstream::in); // open file to read
  if (!inFile.is_open()){ // unable to open file
    cout << endl << "### " << fileName << " does not exist! ###" << endl;
    cout << endl << "There is no data!" << endl;
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
          case 2: oneR.sname = cut; // get the school name
            break;
          case 4: oneR.dname = cut; // get the department name
            break;
          case 5: oneR.type = cut; // get either day or night
            break;
          case 6: oneR.level = cut; // get graduate or undergraduate
            break;
          case 7: oneR.nstud = atoi(cut.c_str()); // get the number of students
            break;
          case 8: oneR.nprof = atoi(cut.c_str()); // get the number of professors
            break;
          case 9: oneR.ngrad = atoi(cut.c_str()); // get the number of graduates
            break;
          default: break;
        } //end switch
        pre = ++pos; // 跳過tab //move to the next field
      } while ((pos > 0) && (fNo < 10)); // continue if there are still fields to be read
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

void SchoolList::print(){ // test
  for ( int i = 0 ; i < this->allR.size() ; i++ ){
  	cout << this->allR[i].sname << " " << this->allR[i].dname << " " 
	     << this->allR[i].type << " " << this->allR[i].level << " " 
		 << this->allR[i].nstud << " " << this->allR[i].nprof << " " << this->allR[i].ngrad << endl ; // test
  } // for 
} //end print

void SchoolList::Delete(string Snametemp, string Dnametemp, int Nstudtemp, int Nproftemp, int Ngradtemp){ 
  for ( int i = 0 ; i < this->allR.size() ; i++ ){
  	if ( this->allR[i].sname == Snametemp && this->allR[i].dname == Dnametemp && this->allR[i].nstud == Nstudtemp 
  	  && this->allR[i].nprof == Nproftemp && this->allR[i].ngrad == Ngradtemp )
  	  this->allR.erase(allR.begin()+i);
  } // for 
} // Delete

class BST;
class TreeNode: public SchoolList{
  private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;                       // 鍵值 [上學年度畢業生數]
    string stringkey;              // 鍵值 [學校名稱]
	SchoolList::schoolType value;  // DATA
  public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),stringkey(NULL),value(){};
    TreeNode(int a,string b, schoolType input):leftchild(0),rightchild(0),parent(0),key(a),stringkey(b),value(input){};

    int GetKey(){return key;}                     // 鍵值 [上學年度畢業生數]
    string GetstringKey(){return stringkey;}      // 鍵值 [學校名稱]
    string GetSname(){return this->value.sname;}  
	string GetDname(){return this->value.dname;} 
	string GetType(){return this->value.type;} 
	string GetLevel(){return this->value.level;} 
	int GetNstud(){return this->value.nstud;} 
	int GetNprof(){return this->value.nprof;} 
	int GetNgrad(){return this->value.ngrad;}  
    friend class BST;   // 可以放在 private 或 public  
};

class BST{
  private:
    TreeNode *root;
    TreeNode* SearchRightest(TreeNode *current);  //最左邊 
    TreeNode* Successor(TreeNode *current);
  public:
  	bool hasfind = false; //是否有找到 
    BST():root(0){};
    void deletebst();
    void InsertBST(int key, string stringkey, SchoolList::schoolType data);               //建[上學年度畢業生數]的二元樹 
    void Insert_SchoolName_BST(int key, string stringkey, SchoolList::schoolType data);   //建[學校名稱]的二元樹     
    int maxDepth(TreeNode *current);     //以遞迴找樹高 
	int GetmaxDepth();       
	void PreorderPrint_recur( TreeNode *current, int &n, int num );       //讓case2去遞迴以鍵值比較去搜尋比使用者輸入的數字大或等於的資料 
	void SearchGreaterNumPreorderPrint( int &n, int num );
	void PreorderPrint_recur( TreeNode *current, int &n, string name );   //讓case3去遞迴以鍵值比較去搜尋與使用者輸入的名稱符合的所有資料  
	void SearchMatchNamePreorderPrint( int &n, string name);
	void DeleteBST(TreeNode *delete_node);
	void SearchMatchNameBST( TreeNode *current, string Sname, string Dname, int Nstud, int Nprof, int Ngrad );    //recur
	void DeleteMatchNameBST( string Sname, string Dname, int Nstud, int Nprof, int Ngrad );
	void SearchSmallerNumBST( TreeNode *current, int &n, int num, BST &bstname, SchoolList &list );       //recur
	void DeleteSmallerNumBST( int &n, int num, BST &bstname, SchoolList &list);
};

TreeNode* BST::SearchRightest(TreeNode *current){
    while (current->rightchild != NULL)
        current = current->rightchild;
    return current;
} // SearchRightest

TreeNode* BST::Successor(TreeNode *current){
    if (current->leftchild != NULL)
        return SearchRightest(current->leftchild);
} // Successor

void BST::deletebst(){  
	root = NULL;
	delete root;
} // deletebst

void BST::InsertBST(int key, string stringkey, SchoolList::schoolType data){     //建[上學年度畢業生數]的二元樹  

    TreeNode *b = 0;        
    TreeNode *a = 0;        
    TreeNode *insert_node = new TreeNode(key, stringkey, data); 

    a = root;
    while (a != NULL) {                // 尋找適當的位置  insert     
        b = a;                                
        if (insert_node->key < a->key) //往左 
            a = a->leftchild;
        else                           //往右 
            a = a->rightchild;
    }  //while                         // 跳出迴圈即表示 a為NULL
    insert_node->parent = b;           //讓新節點找好父母 

    if (b == NULL)                     //讓原節點找好新小孩 
        this->root = insert_node;
    else if (insert_node->key < b->key)
        b->leftchild = insert_node;
    else
        b->rightchild = insert_node;
} // InsertBST
  
void BST::Insert_SchoolName_BST(int key, string stringkey, SchoolList::schoolType data){  //建[學校名稱]的二元樹 

    TreeNode *b = 0;        
    TreeNode *a = 0;        
    TreeNode *insert_node = new TreeNode(key, stringkey, data); 

    a = root;
    while (a != NULL) {                // 尋找適當的位置  insert     
        b = a;                                
        if (insert_node->stringkey.compare(a->stringkey) < 0) //往左 
            a = a->leftchild;
        else                           //往右 
            a = a->rightchild;
    }  //while                         // 跳出迴圈即表示 a為NULL
    insert_node->parent = b;           //讓新節點找好父母 

    if (b == NULL)                     //讓原節點找好新小孩 
        this->root = insert_node;
    else if (insert_node->stringkey.compare(b->stringkey) < 0)
        b->leftchild = insert_node;
    else
        b->rightchild = insert_node;
} // Insert_SchoolName_BST

int BST::maxDepth(TreeNode *current){  //以遞迴找樹高 
    if (current == NULL)
        return 0;
    else
    {
        //計算每一個子節點的樹高 
        int lDepth = maxDepth(current->leftchild);
        int rDepth = maxDepth(current->rightchild);
     
        //return較長的 
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    } // else
} // maxDepth

int BST::GetmaxDepth(){
    TreeNode *current = root;      // 將current指向root作為traversal起點
    return maxDepth(current);      //以遞迴找樹高 
} // GetmaxDepth

int GetIntLength(int i){ //算出數字的長度 
  int len=1;
  while ( i/10 > 0 ){
  	len++;
  	i /= 10;
  }
  return len;
} // GetIntLength

void BST::PreorderPrint_recur( TreeNode *current, int &n, int num ){  //讓case2去遞迴以鍵值比較去搜尋比使用者輸入的數字大或等於的資料 
    if (current == NULL)
      return;
    if ( current->GetKey() >= num ){
      hasfind = true;
      if ( n == 1 )
        cout << "Search results: " << endl;
      cout << "[" << n << "]" ;
      for ( int i = GetIntLength(n)+3 ; i < 8 ; i++ )
        cout << " " ;
	  cout <<  current->GetSname() ;
	  for ( int i = current->GetSname().length()+1 ; i < 30 ; i++ )
        cout << " " ;
	  cout << current->GetDname() ;
	  for ( int i = current->GetDname().length()+1 ; i < 50 ; i++ )
        cout << " " ;
	  cout << current->GetType() << " "
	  << current->GetLevel() << " " << current->GetNstud() << " " << current->GetNprof() << " " 
	  << current->GetNgrad() << endl ;
	  n++;
	} // if
	//搜尋資料禁止使用遍歷每個節點的暴力法，必須藉由比較鍵值來避免走訪過所有節點。
	if ( current->GetKey() < num )   //鍵值比num小就往右走不往左 
	  PreorderPrint_recur( current->rightchild, n, num );
	else{
	  PreorderPrint_recur( current->leftchild, n, num );
      PreorderPrint_recur( current->rightchild, n, num );
	} // else
} // PreorderPrint_recur

void BST::SearchGreaterNumPreorderPrint( int &n, int num){  
    TreeNode *current = root;      // 將current指向root作為traversal起點
    PreorderPrint_recur( current, n, num );
} // SearchGreaterNumPreorderPrint

void BST::PreorderPrint_recur( TreeNode *current, int &n, string name ){  //讓case3去遞迴以鍵值比較去搜尋與使用者輸入的名稱符合的所有資料 
    if (current == NULL)
      return;
    if ( current->GetstringKey().compare(name) == 0 ){
      hasfind = true;
      if ( n == 1 )
        cout << "Search results: " << endl; 
      cout << "[" << n << "]" ;
      for ( int i = GetIntLength(n)+3 ; i < 9 ; i++ )
        cout << " " ;
	  cout <<  current->GetSname() ;
	  for ( int i = current->GetSname().length()+1 ; i < 30 ; i++ )
        cout << " " ;
	  cout << current->GetDname() ;
	  for ( int i = current->GetDname().length()+1 ; i < 50 ; i++ )
        cout << " " ;
	  cout << current->GetType() << " "
	  << current->GetLevel() << " " << current->GetNstud() << " " << current->GetNprof() << " " 
	  << current->GetNgrad() << endl ;
	  n++;
	} // if
	//搜尋資料禁止使用遍歷每個節點的暴力法，必須藉由比較鍵值來避免走訪過所有節點。
	if ( current->GetstringKey().compare(name) < 0 )    
	  PreorderPrint_recur( current->rightchild, n, name );
	else{
	  PreorderPrint_recur( current->leftchild, n, name );
      PreorderPrint_recur( current->rightchild, n, name );
	} // else
} // PreorderPrint_recur

void BST::SearchMatchNamePreorderPrint( int &n, string name){  
    TreeNode *current = root;      // 將current指向root作為traversal起點
    PreorderPrint_recur( current, n, name );
} // SearchMatchNamePreorderPrint


void BST::DeleteBST(TreeNode *delete_node){              
    TreeNode *b = 0;      // 真正要被刪除的節點 
    TreeNode *a = 0;      // 暫放要被刪除的節點的小孩 

    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL) //1.要刪的節點是leaf 2.要刪的節點只有一個小孩
        b = delete_node;
    else                                   //3.要刪掉的節點有兩個小孩 
        b = Successor(delete_node);        // 找替身   將b設成delete_node的Successor  
	//b目前有可能是  1.要刪的節點是leaf 2.要刪的節點只有一個小孩            
    if (b->leftchild != NULL)
        a = b->leftchild;                  // 將a設成b的小孩有可能是NULL有可能不是NULL 
    else
        a = b->rightchild;
    // 在b被刪除之前把a接回BST
    if (a != NULL)                        
        a->parent = b->parent;        
	// 接著把要被刪除的節點的父母指向新小孩 
    if (b->parent == NULL)                  // 如果要刪除的是root, 就把a當成新的root 
        this->root = a;
    else if (b == b->parent->leftchild)     // 若b是左小孩就讓a取代b 
        b->parent->leftchild = a;           
    else                                    // 若b是右小孩就讓a取代b
        b->parent->rightchild = a;        
                                       
    // 3.要刪掉的節點有兩個小孩的後面步驟 
    if (b != delete_node) {                 // 若b是delete_node的替身, 最後要再將b的資料放回delete_node的記憶體位置
        delete_node->key = b->key;          //就是讓b這個delete_node的小孩的資料取代delete_node的資料 
        delete_node->value = b->value;  
    }

    delete b;                               // 將b的記憶體位置釋放
    b = 0;
} // DeleteBST

void BST::SearchMatchNameBST( TreeNode *current, string Sname, string Dname, int Nstud, int Nprof, int Ngrad ){  //去遞迴以鍵值比較去搜尋與要被刪除的資料完全符合的所有資料 
    bool check = false;
	if (current == NULL)
      return;
    if ( current->GetSname().compare(Sname) == 0 ){
      if ( current->GetDname().compare(Dname) == 0 && current->GetNstud() == Nstud && current->GetNprof() == Nprof && current->GetNgrad() == Ngrad ){
      	DeleteBST(current);
	    return;
	  } // if
	} // if
	//搜尋資料禁止使用遍歷每個節點的暴力法，必須藉由比較鍵值來避免走訪過所有節點。
	if ( current->GetstringKey().compare(Sname) < 0 ) {   
      SearchMatchNameBST( current->rightchild, Sname, Dname, Nstud, Nprof, Ngrad );
    } // if 
	else{
	  SearchMatchNameBST( current->leftchild, Sname, Dname, Nstud, Nprof, Ngrad );
	  SearchMatchNameBST( current->rightchild, Sname, Dname, Nstud, Nprof, Ngrad );
	}
} // SearchMatchNameBST

void BST::DeleteMatchNameBST(string Sname, string Dname, int Nstud, int Nprof, int Ngrad){  
    TreeNode *current = root;      // 將current指向root作為traversal起點
    SearchMatchNameBST( current, Sname, Dname, Nstud, Nprof, Ngrad );
} // DeleteMatchNameBST

void BST::SearchSmallerNumBST( TreeNode *current, int &n, int num, BST &bstname, SchoolList &list ){  //去遞迴以鍵值比較去搜尋比使用者輸入的數字小或等於的資料 
    bool check = false;  
    if (current == NULL)
      return;
    if ( current->GetKey() <= num ){
      hasfind = true;
      if ( n == 1 )
        cout << "Deleted records: " << endl;
      cout << "[" << n << "]" ;
      for ( int i = GetIntLength(n)+3 ; i < 8 ; i++ )
        cout << " " ;
	  cout <<  current->GetSname() ;
	  for ( int i = current->GetSname().length()+1 ; i < 30 ; i++ )
        cout << " " ;
	  cout << current->GetDname() ;
	  for ( int i = current->GetDname().length()+1 ; i < 50 ; i++ )
        cout << " " ;
	  cout << current->GetType() << " "
	  << current->GetLevel() << " " << current->GetNstud() << " " << current->GetNprof() << " " 
	  << current->GetNgrad() << endl ;
	  if (current->leftchild != NULL && current->rightchild != NULL) 
        check = true;
      string Snametemp = current->GetSname();
	  string Dnametemp = current->GetDname();
	  int Nstudtemp = current->GetNstud();
	  int Nproftemp = current->GetNprof();
	  int Ngradtemp = current->GetNgrad();
	  //cout << Snametemp << "這裡" <<endl; // test 
	  DeleteBST(current);
	  bstname.DeleteMatchNameBST(Snametemp, Dnametemp, Nstudtemp, Nproftemp, Ngradtemp);
	  list.Delete(Snametemp, Dnametemp, Nstudtemp, Nproftemp, Ngradtemp);
	  n++;
	} // if
	//搜尋資料禁止使用遍歷每個節點的暴力法，必須藉由比較鍵值來避免走訪過所有節點。
	if ( current->GetKey() <= num ){   //鍵值比num大就往佐走不往右 
	  SearchSmallerNumBST( current->rightchild, n, num, bstname, list );
	  SearchSmallerNumBST( current->leftchild, n, num, bstname, list );
	  if ( current->GetKey() <= num && check )
	    SearchSmallerNumBST( current, n, num, bstname, list );
    } // if
	else
	  SearchSmallerNumBST( current->leftchild, n, num, bstname, list );
} // SearchSmallerNumBST

void BST::DeleteSmallerNumBST( int &n, int num, BST &bstname, SchoolList &list){  
    TreeNode *current = root;      // 將current指向root作為traversal起點
    SearchSmallerNumBST( current, n, num, bstname, list );
} // DeleteSmallerNumBST

int main() {
	int command = 0; //第一個input(0, 1, 2)
	bool hascommand1 = false; //判斷有沒有command1過 
	SchoolList list;
	BST bstNum; // 上學年度畢業生數
	BST bstSchoolName; // 學校名稱
	do {  
	  cout << endl << "*** University Graduate Information System ***";
	  cout << endl << "* 0. Quit                                    *";
	  cout << endl << "* 1. Create Two Binary Search Trees          *"; 
	  cout << endl << "* 2. Search by Number of Graduates           *";
	  cout << endl << "* 3. Search by School Name                   *";
	  cout << endl << "* 4. Removal by Number of Graduates          *";
	  cout << endl << "**********************************************"; 
	  cout << endl << "Input a command(0, 1-4): "; 
	  cin >> command;  //cin第一個input(0, 1, 2, 3, 4)
	  switch(command){	
	  	case 0 : break;
	  	case 1 :   
	  	  if ( hascommand1 ){ // 如果先前已經建過二元樹要先刪除 
	  	    bstNum.deletebst();
	  	    bstSchoolName.deletebst();
	  	  } // if 
	  	  hascommand1 = true; 
	  	  list.readFile();
	  	  //list.print();   //老師給的題目上說要顯示於螢幕上，以確定內容完全正確 但demo沒顯示因此註解掉 
	  	  
	  	  //以「上學年度畢業生數」為鍵值建立二元搜尋樹 
	  	  for ( int i = 0 ; i < list.allR.size() ; i++ ){ 
  	        bstNum.InsertBST( list.allR[i].ngrad, list.allR[i].sname, list.allR[i] );
          } // for 
          
          //以「學校名稱」為鍵值建立二元搜尋樹 
	  	  for ( int i = 0 ; i < list.allR.size() ; i++ ){ 
  	        bstSchoolName.Insert_SchoolName_BST( list.allR[i].ngrad, list.allR[i].sname, list.allR[i] );
          } // for 
          
          //印出「學校名稱」為鍵值的二元搜尋樹的樹高 
          cout << "Tree height {School name} = " << bstSchoolName.GetmaxDepth() << endl ; // test
          
          //印出「上學年度畢業生數」為鍵值的二元搜尋樹的樹高 
          cout << "Tree height {Number of graduates} = " << bstNum.GetmaxDepth() << endl ; // test
		  break;
		case 2 :   
	  	  if ( hascommand1 ){
	  	  	int n = 1;
	  	  	int num = 0;
	  	  	cout << "Input the number of graduates: "; 
	  	  	bstNum.hasfind = false;
	  	  	cin >> num;  //cin一個非負整數 在「上學年度畢業生數」二元搜尋樹找出鍵值不低於該整數的所有資料 
	  	  	bstNum.SearchGreaterNumPreorderPrint( n, num );
	  	  	if ( !bstNum.hasfind )
	  	  	  cout << "There is no match!" << endl ;
		  } // if
	  	  else
	  	    cout << endl << "Please choose command 1 first!" << endl; 
		  break;
		case 3 :   
	  	  if ( hascommand1 ){
	  	  	int n = 1;
	  	  	string name;
	  	  	cout << "Input a school name: "; 
	  	  	bstSchoolName.hasfind = false;
	  	  	cin >> name;  //cin一個名稱字串 在「學校名稱」二元搜尋樹找出找出完全相同(exact match)的所有資料
	  	  	bstSchoolName.SearchMatchNamePreorderPrint( n, name );
	  	  	if ( !bstSchoolName.hasfind )
	  	  	  cout << "There is no match!" << endl ; 
		  } // if
	  	  else
	  	    cout << endl << "Please choose command 1 first!" << endl;
		  break;
		case 4 :   
		  if ( hascommand1 ){
		  	int n = 1;
	  	  	int num = 0;
	  	  	cout << "Input the number of graduates: "; 
	  	  	bstNum.hasfind = false;
	  	  	cin >> num;  //cin一個非負整數 在「上學年度畢業生數」二元搜尋樹找出並刪除鍵值不超過該整數的所有資料 
	  	  	bstNum.DeleteSmallerNumBST( n, num, bstSchoolName, list );
	  	  	if ( !bstNum.hasfind )
	  	  	  cout << "There is no match!" << endl ;
		  	
	  	  	//印出「學校名稱」為鍵值的二元搜尋樹的樹高 
            cout << "Tree height {School name} = " << bstSchoolName.GetmaxDepth() << endl ; // test
          
            //印出「上學年度畢業生數」為鍵值的二元搜尋樹的樹高 
            cout << "Tree height {Number of graduates} = " << bstNum.GetmaxDepth() << endl ; // test
		  } // if
	  	  else
	  	    cout << endl << "Please choose command 1 first!" << endl;
		  break;
	    default : cout << endl << "Command does not exist!" << endl; //input 0,1以外的 
	  } // end switch
	} while ( command != 0 );  //'0':stop the program
	system ( "pause" );        // pause the display
	return 0;
} // end main


