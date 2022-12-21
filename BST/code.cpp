//DS1101ex5_��27��_10833230�����t_10844149�©y�x
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
    string sname; // �ǮզW��school name
    string dname; // ��t�W��department name
    string type; // �鶡�A�i�קOeither day or night
    string level; // ���ŧOgraduate or undergraduate
    int nstud; // �ǥͼ�number of students
    int nprof; // �Юv��number of professors
    int ngrad; // �W�Ǧ~�ײ��~�ͼ�number of graduates
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
      fNo = 0; // �ثe����ĴX�� number of fields read so far
      pre = 0; // �ثe����ĴX��char  locate one field of input record
      buf.assign(cstr); // copy c-string into C++ string
      do{ // scan the buffer from left to right
        pos = buf.find_first_of('\t', pre); // locate the next field by '\t' (tab)
        cut = buf.substr(pre, pos - pre); //����tab len = pos - pre // retrieve a field
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
        pre = ++pos; // ���Ltab //move to the next field
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
    int key;                       // ��� [�W�Ǧ~�ײ��~�ͼ�]
    string stringkey;              // ��� [�ǮզW��]
	SchoolList::schoolType value;  // DATA
  public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),stringkey(NULL),value(){};
    TreeNode(int a,string b, schoolType input):leftchild(0),rightchild(0),parent(0),key(a),stringkey(b),value(input){};

    int GetKey(){return key;}                     // ��� [�W�Ǧ~�ײ��~�ͼ�]
    string GetstringKey(){return stringkey;}      // ��� [�ǮզW��]
    string GetSname(){return this->value.sname;}  
	string GetDname(){return this->value.dname;} 
	string GetType(){return this->value.type;} 
	string GetLevel(){return this->value.level;} 
	int GetNstud(){return this->value.nstud;} 
	int GetNprof(){return this->value.nprof;} 
	int GetNgrad(){return this->value.ngrad;}  
    friend class BST;   // �i�H��b private �� public  
};

class BST{
  private:
    TreeNode *root;
    TreeNode* SearchRightest(TreeNode *current);  //�̥��� 
    TreeNode* Successor(TreeNode *current);
  public:
  	bool hasfind = false; //�O�_����� 
    BST():root(0){};
    void deletebst();
    void InsertBST(int key, string stringkey, SchoolList::schoolType data);               //��[�W�Ǧ~�ײ��~�ͼ�]���G���� 
    void Insert_SchoolName_BST(int key, string stringkey, SchoolList::schoolType data);   //��[�ǮզW��]���G����     
    int maxDepth(TreeNode *current);     //�H���j��� 
	int GetmaxDepth();       
	void PreorderPrint_recur( TreeNode *current, int &n, int num );       //��case2�h���j�H��Ȥ���h�j�M��ϥΪ̿�J���Ʀr�j�ε��󪺸�� 
	void SearchGreaterNumPreorderPrint( int &n, int num );
	void PreorderPrint_recur( TreeNode *current, int &n, string name );   //��case3�h���j�H��Ȥ���h�j�M�P�ϥΪ̿�J���W�ٲŦX���Ҧ����  
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

void BST::InsertBST(int key, string stringkey, SchoolList::schoolType data){     //��[�W�Ǧ~�ײ��~�ͼ�]���G����  

    TreeNode *b = 0;        
    TreeNode *a = 0;        
    TreeNode *insert_node = new TreeNode(key, stringkey, data); 

    a = root;
    while (a != NULL) {                // �M��A����m  insert     
        b = a;                                
        if (insert_node->key < a->key) //���� 
            a = a->leftchild;
        else                           //���k 
            a = a->rightchild;
    }  //while                         // ���X�j��Y��� a��NULL
    insert_node->parent = b;           //���s�`�I��n���� 

    if (b == NULL)                     //����`�I��n�s�p�� 
        this->root = insert_node;
    else if (insert_node->key < b->key)
        b->leftchild = insert_node;
    else
        b->rightchild = insert_node;
} // InsertBST
  
void BST::Insert_SchoolName_BST(int key, string stringkey, SchoolList::schoolType data){  //��[�ǮզW��]���G���� 

    TreeNode *b = 0;        
    TreeNode *a = 0;        
    TreeNode *insert_node = new TreeNode(key, stringkey, data); 

    a = root;
    while (a != NULL) {                // �M��A����m  insert     
        b = a;                                
        if (insert_node->stringkey.compare(a->stringkey) < 0) //���� 
            a = a->leftchild;
        else                           //���k 
            a = a->rightchild;
    }  //while                         // ���X�j��Y��� a��NULL
    insert_node->parent = b;           //���s�`�I��n���� 

    if (b == NULL)                     //����`�I��n�s�p�� 
        this->root = insert_node;
    else if (insert_node->stringkey.compare(b->stringkey) < 0)
        b->leftchild = insert_node;
    else
        b->rightchild = insert_node;
} // Insert_SchoolName_BST

int BST::maxDepth(TreeNode *current){  //�H���j��� 
    if (current == NULL)
        return 0;
    else
    {
        //�p��C�@�Ӥl�`�I���� 
        int lDepth = maxDepth(current->leftchild);
        int rDepth = maxDepth(current->rightchild);
     
        //return������ 
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    } // else
} // maxDepth

int BST::GetmaxDepth(){
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    return maxDepth(current);      //�H���j��� 
} // GetmaxDepth

int GetIntLength(int i){ //��X�Ʀr������ 
  int len=1;
  while ( i/10 > 0 ){
  	len++;
  	i /= 10;
  }
  return len;
} // GetIntLength

void BST::PreorderPrint_recur( TreeNode *current, int &n, int num ){  //��case2�h���j�H��Ȥ���h�j�M��ϥΪ̿�J���Ʀr�j�ε��󪺸�� 
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
	//�j�M��ƸT��ϥιM���C�Ӹ`�I���ɤO�k�A�����ǥѤ����Ȩ��קK���X�L�Ҧ��`�I�C
	if ( current->GetKey() < num )   //��Ȥ�num�p�N���k�������� 
	  PreorderPrint_recur( current->rightchild, n, num );
	else{
	  PreorderPrint_recur( current->leftchild, n, num );
      PreorderPrint_recur( current->rightchild, n, num );
	} // else
} // PreorderPrint_recur

void BST::SearchGreaterNumPreorderPrint( int &n, int num){  
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    PreorderPrint_recur( current, n, num );
} // SearchGreaterNumPreorderPrint

void BST::PreorderPrint_recur( TreeNode *current, int &n, string name ){  //��case3�h���j�H��Ȥ���h�j�M�P�ϥΪ̿�J���W�ٲŦX���Ҧ���� 
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
	//�j�M��ƸT��ϥιM���C�Ӹ`�I���ɤO�k�A�����ǥѤ����Ȩ��קK���X�L�Ҧ��`�I�C
	if ( current->GetstringKey().compare(name) < 0 )    
	  PreorderPrint_recur( current->rightchild, n, name );
	else{
	  PreorderPrint_recur( current->leftchild, n, name );
      PreorderPrint_recur( current->rightchild, n, name );
	} // else
} // PreorderPrint_recur

void BST::SearchMatchNamePreorderPrint( int &n, string name){  
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    PreorderPrint_recur( current, n, name );
} // SearchMatchNamePreorderPrint


void BST::DeleteBST(TreeNode *delete_node){              
    TreeNode *b = 0;      // �u���n�Q�R�����`�I 
    TreeNode *a = 0;      // �ȩ�n�Q�R�����`�I���p�� 

    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL) //1.�n�R���`�I�Oleaf 2.�n�R���`�I�u���@�Ӥp��
        b = delete_node;
    else                                   //3.�n�R�����`�I����Ӥp�� 
        b = Successor(delete_node);        // �����   �Nb�]��delete_node��Successor  
	//b�ثe���i��O  1.�n�R���`�I�Oleaf 2.�n�R���`�I�u���@�Ӥp��            
    if (b->leftchild != NULL)
        a = b->leftchild;                  // �Na�]��b���p�Ħ��i��ONULL���i�ण�ONULL 
    else
        a = b->rightchild;
    // �bb�Q�R�����e��a���^BST
    if (a != NULL)                        
        a->parent = b->parent;        
	// ���ۧ�n�Q�R�����`�I���������V�s�p�� 
    if (b->parent == NULL)                  // �p�G�n�R�����Oroot, �N��a���s��root 
        this->root = a;
    else if (b == b->parent->leftchild)     // �Yb�O���p�ĴN��a���Nb 
        b->parent->leftchild = a;           
    else                                    // �Yb�O�k�p�ĴN��a���Nb
        b->parent->rightchild = a;        
                                       
    // 3.�n�R�����`�I����Ӥp�Ī��᭱�B�J 
    if (b != delete_node) {                 // �Yb�Odelete_node������, �̫�n�A�Nb����Ʃ�^delete_node���O�����m
        delete_node->key = b->key;          //�N�O��b�o��delete_node���p�Ī���ƨ��Ndelete_node����� 
        delete_node->value = b->value;  
    }

    delete b;                               // �Nb���O�����m����
    b = 0;
} // DeleteBST

void BST::SearchMatchNameBST( TreeNode *current, string Sname, string Dname, int Nstud, int Nprof, int Ngrad ){  //�h���j�H��Ȥ���h�j�M�P�n�Q�R������Ƨ����ŦX���Ҧ���� 
    bool check = false;
	if (current == NULL)
      return;
    if ( current->GetSname().compare(Sname) == 0 ){
      if ( current->GetDname().compare(Dname) == 0 && current->GetNstud() == Nstud && current->GetNprof() == Nprof && current->GetNgrad() == Ngrad ){
      	DeleteBST(current);
	    return;
	  } // if
	} // if
	//�j�M��ƸT��ϥιM���C�Ӹ`�I���ɤO�k�A�����ǥѤ����Ȩ��קK���X�L�Ҧ��`�I�C
	if ( current->GetstringKey().compare(Sname) < 0 ) {   
      SearchMatchNameBST( current->rightchild, Sname, Dname, Nstud, Nprof, Ngrad );
    } // if 
	else{
	  SearchMatchNameBST( current->leftchild, Sname, Dname, Nstud, Nprof, Ngrad );
	  SearchMatchNameBST( current->rightchild, Sname, Dname, Nstud, Nprof, Ngrad );
	}
} // SearchMatchNameBST

void BST::DeleteMatchNameBST(string Sname, string Dname, int Nstud, int Nprof, int Ngrad){  
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    SearchMatchNameBST( current, Sname, Dname, Nstud, Nprof, Ngrad );
} // DeleteMatchNameBST

void BST::SearchSmallerNumBST( TreeNode *current, int &n, int num, BST &bstname, SchoolList &list ){  //�h���j�H��Ȥ���h�j�M��ϥΪ̿�J���Ʀr�p�ε��󪺸�� 
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
	  //cout << Snametemp << "�o��" <<endl; // test 
	  DeleteBST(current);
	  bstname.DeleteMatchNameBST(Snametemp, Dnametemp, Nstudtemp, Nproftemp, Ngradtemp);
	  list.Delete(Snametemp, Dnametemp, Nstudtemp, Nproftemp, Ngradtemp);
	  n++;
	} // if
	//�j�M��ƸT��ϥιM���C�Ӹ`�I���ɤO�k�A�����ǥѤ����Ȩ��קK���X�L�Ҧ��`�I�C
	if ( current->GetKey() <= num ){   //��Ȥ�num�j�N�����������k 
	  SearchSmallerNumBST( current->rightchild, n, num, bstname, list );
	  SearchSmallerNumBST( current->leftchild, n, num, bstname, list );
	  if ( current->GetKey() <= num && check )
	    SearchSmallerNumBST( current, n, num, bstname, list );
    } // if
	else
	  SearchSmallerNumBST( current->leftchild, n, num, bstname, list );
} // SearchSmallerNumBST

void BST::DeleteSmallerNumBST( int &n, int num, BST &bstname, SchoolList &list){  
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    SearchSmallerNumBST( current, n, num, bstname, list );
} // DeleteSmallerNumBST

int main() {
	int command = 0; //�Ĥ@��input(0, 1, 2)
	bool hascommand1 = false; //�P�_���S��command1�L 
	SchoolList list;
	BST bstNum; // �W�Ǧ~�ײ��~�ͼ�
	BST bstSchoolName; // �ǮզW��
	do {  
	  cout << endl << "*** University Graduate Information System ***";
	  cout << endl << "* 0. Quit                                    *";
	  cout << endl << "* 1. Create Two Binary Search Trees          *"; 
	  cout << endl << "* 2. Search by Number of Graduates           *";
	  cout << endl << "* 3. Search by School Name                   *";
	  cout << endl << "* 4. Removal by Number of Graduates          *";
	  cout << endl << "**********************************************"; 
	  cout << endl << "Input a command(0, 1-4): "; 
	  cin >> command;  //cin�Ĥ@��input(0, 1, 2, 3, 4)
	  switch(command){	
	  	case 0 : break;
	  	case 1 :   
	  	  if ( hascommand1 ){ // �p�G���e�w�g�عL�G����n���R�� 
	  	    bstNum.deletebst();
	  	    bstSchoolName.deletebst();
	  	  } // if 
	  	  hascommand1 = true; 
	  	  list.readFile();
	  	  //list.print();   //�Ѯv�����D�ؤW���n��ܩ�ù��W�A�H�T�w���e�������T ��demo�S��ܦ]�����ѱ� 
	  	  
	  	  //�H�u�W�Ǧ~�ײ��~�ͼơv����ȫإߤG���j�M�� 
	  	  for ( int i = 0 ; i < list.allR.size() ; i++ ){ 
  	        bstNum.InsertBST( list.allR[i].ngrad, list.allR[i].sname, list.allR[i] );
          } // for 
          
          //�H�u�ǮզW�١v����ȫإߤG���j�M�� 
	  	  for ( int i = 0 ; i < list.allR.size() ; i++ ){ 
  	        bstSchoolName.Insert_SchoolName_BST( list.allR[i].ngrad, list.allR[i].sname, list.allR[i] );
          } // for 
          
          //�L�X�u�ǮզW�١v����Ȫ��G���j�M�𪺾� 
          cout << "Tree height {School name} = " << bstSchoolName.GetmaxDepth() << endl ; // test
          
          //�L�X�u�W�Ǧ~�ײ��~�ͼơv����Ȫ��G���j�M�𪺾� 
          cout << "Tree height {Number of graduates} = " << bstNum.GetmaxDepth() << endl ; // test
		  break;
		case 2 :   
	  	  if ( hascommand1 ){
	  	  	int n = 1;
	  	  	int num = 0;
	  	  	cout << "Input the number of graduates: "; 
	  	  	bstNum.hasfind = false;
	  	  	cin >> num;  //cin�@�ӫD�t��� �b�u�W�Ǧ~�ײ��~�ͼơv�G���j�M���X��Ȥ��C��Ӿ�ƪ��Ҧ���� 
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
	  	  	cin >> name;  //cin�@�ӦW�٦r�� �b�u�ǮզW�١v�G���j�M���X��X�����ۦP(exact match)���Ҧ����
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
	  	  	cin >> num;  //cin�@�ӫD�t��� �b�u�W�Ǧ~�ײ��~�ͼơv�G���j�M���X�çR����Ȥ��W�L�Ӿ�ƪ��Ҧ���� 
	  	  	bstNum.DeleteSmallerNumBST( n, num, bstSchoolName, list );
	  	  	if ( !bstNum.hasfind )
	  	  	  cout << "There is no match!" << endl ;
		  	
	  	  	//�L�X�u�ǮզW�١v����Ȫ��G���j�M�𪺾� 
            cout << "Tree height {School name} = " << bstSchoolName.GetmaxDepth() << endl ; // test
          
            //�L�X�u�W�Ǧ~�ײ��~�ͼơv����Ȫ��G���j�M�𪺾� 
            cout << "Tree height {Number of graduates} = " << bstNum.GetmaxDepth() << endl ; // test
		  } // if
	  	  else
	  	    cout << endl << "Please choose command 1 first!" << endl;
		  break;
	    default : cout << endl << "Command does not exist!" << endl; //input 0,1�H�~�� 
	  } // end switch
	} while ( command != 0 );  //'0':stop the program
	system ( "pause" );        // pause the display
	return 0;
} // end main


