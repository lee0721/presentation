//DS1101ex6_��27��_10833230�����t_10844149�©y�x
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
#include<math.h> //use ceil
using namespace std;

class pokemonList{

public:
    typedef struct pT{
        int rawR ; // raw data of one record
        int no; // �s��# pokemon number (1)
        string name; // �W�� pokemon name (2)
        string tp1; // ���� 1 1st type (3)
        //int tot; // �`�M total sum
        int hp; // �ͩR�� health point (4)
        int atk; // ���� attack (5)
        int def; // ���m defense (6)
    } pokemonType;
    vector<pokemonType> pSet; // set of data records
    string fileNO; // number to form a file name
    //*******************************************************************/
    // the above are private data members
    //*******************************************************************/
public:
    pokemonList(): fileNO("") { } // constructor: do nothing
    bool readF(); // read records from a file
    void showAll(); // display all the records on screen
    void clearUp(){  // erase the object content
        pSet.clear();
        fileNO.clear();
    } // end clearUp
    ~pokemonList(){ clearUp(); }   // destructor: destroy the object
}; // class pokemonList


bool pokemonList::readF(){  // definition: read all from a file
    fstream inFile; // file handle
    string fileName; // file name
    this->clearUp(); // call: initial set up
    cout << endl << "Input a file number [0: quit]: ";
    cin >> this->fileNO; // get the file identifier
    fileName = "input" + fileNO + ".txt";
    inFile.open(fileName.c_str(), fstream::in); // open file to read
    if (!inFile.is_open()){  // unable to open file
        cout << endl << "### " << fileName << " does not exist! ###" << endl;
        cout << endl << "There is no data!" << endl;
        return false;
    } //end if
    else{
        char cstr[255]; // input buffer of one line as c-string
        int fNo, pre, pos;
        inFile.getline(cstr, 255, '\n'); // skip the list of column names
        while (inFile.getline(cstr, 255, '\n')){  // get all records line by line
            pokemonType oneR; // one data record
            string buf, cut; // transform c-string into C++ string
            fNo = 0; // �ثe����ĴX�� number of fields read so far
            pre = 0; // �ثe����ĴX��char  locate one field of input record
            buf.assign(cstr); // copy c-string into C++ string
            do { // scan the buffer from left to right
                pos = buf.find_first_of('\t', pre); // locate the next field by '\t' (tab)
                cut = buf.substr(pre, pos - pre); //����tab len = pos - pre // retrieve a field
                switch (++fNo){
                case 1:
                    oneR.no = atoi(cut.c_str()); // get the �s��# pokemon number (1)
                    break;
                case 2:
                    oneR.name = cut; // get the �W�� pokemon name (2)
                    break;
                case 3:
                    oneR.tp1 = cut; // get ���� 1 1st type (3)
                    break;
                case 6:
                    oneR.hp = atoi(cut.c_str()); // get �ͩR�� health point (4)
                    break;
                case 7:
                    oneR.atk = atoi(cut.c_str()); // get ���� attack (5)
                    break;
                case 8:
                    oneR.def = atoi(cut.c_str()); // get ���m defense (6)
                    break;
                default:
                    break;
                } //end switch
                pre = ++pos; // ���Ltab //move to the next field
            }
            while ((pos > 0) && (fNo < 10));   // continue if there are still fields to be read
            this->pSet.push_back(oneR); // save one record into the school list
        } //end outer-while
        inFile.close(); // close file
    } // end else
    if (!this->pSet.size()){
        cout << endl << "### Get nothing from the file " << fileName << " ! ### " << endl;
        return false;
    } // end if
    return true;
} // end pokemonList

int GetIntLength(int i){  //��X�Ʀr������
    int len=1;
    while ( i/10 > 0 ){
        len++;
        i /= 10;
    } //while 
    return len;
} // GetIntLength

void pokemonList::showAll(){
    for ( int i = 0 ; i < this->pSet.size() ; i++ ){
        if ( i == 0 ) //�L�Ĥ@��
            cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
        cout << "[" << i+1 << "]" ; //�Lindex
        this->pSet[i].rawR = i+1;
        for ( int a = GetIntLength(i+1)+2 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].no ;     // �L�s��# pokemon number (1)
        for ( int a = GetIntLength(this->pSet[i].no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].name ;     // �L�W�� pokemon name (2)
        for ( int a = this->pSet[i].name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].tp1 ;     // �L���� 1 1st type (3)
        for ( int a = this->pSet[i].tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].hp ;     // �L�ͩR�� health point (4)
        for ( int a = GetIntLength(this->pSet[i].hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].atk ;     // �L���� attack (5)
        for ( int a = GetIntLength(this->pSet[i].atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  this->pSet[i].def ;     // �L���m defense (6)
        cout << endl ;
    } // for
} //end showAll()

class TreeNode: public pokemonList{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;                         // ��� [�ͩR�� HP]
    pokemonList::pokemonType value;  // DATA
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),value() {};
    TreeNode(int a, pokemonType input):leftchild(0),rightchild(0),parent(0),key(a),value(input) {};

    int rawR = 0; // raw data of one record
    int no; // �s��# pokemon number (1)
    string name; // �W�� pokemon name (2)
    string tp1; // ���� 1 1st type (3)
    //int tot; // �`�M total sum
    int hp; // �ͩR�� health point (4)
    int atk; // ���� attack (5)
    int def; // ���m defense (6)

    int GetKey(){ return key; }  // ��� [�ͩR�� HP]
    void printOR(){
        cout << "[" << this->value.rawR << "]" ; //�Lindex
        for ( int a = GetIntLength(this->value.rawR)+2 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  this->value.no ;     // �L�s��# pokemon number (1)
        for ( int a = GetIntLength(this->value.no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->value.name ;     // �L�W�� pokemon name (2)
        for ( int a = this->value.name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  this->value.tp1 ;     // �L���� 1 1st type (3)
        for ( int a = this->value.tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  this->value.hp ;     // �L�ͩR�� health point (4)
        for ( int a = GetIntLength(this->value.hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->value.atk ;     // �L���� attack (5)
        for ( int a = GetIntLength(this->value.atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  this->value.def ;     // �L���m defense (6)
        cout << endl ;
    } // printOR
    friend class BST;   // �i�H��b private �� public
};

class BST{
private:
    TreeNode *root;
    TreeNode* SearchRightest(TreeNode *current);
    TreeNode* SearchLeftest(TreeNode *current);
public:
    bool hasfind = false; //�O�_�����
    BST():root(0) {};
    void deletebst();
    void InsertBST(int key, pokemonList::pokemonType data);               //��[�ͩR�� HP]���G����
    int maxDepth(TreeNode *current);     //�H���j���
    int GetmaxDepth();
    void SearchAndPrint_Leftmost();   //��X�̥����`�I���������
    void SearchAndPrint_Rightmost();  //��X�̥k���`�I���������
};

TreeNode* BST::SearchRightest(TreeNode *current){
    while (current->rightchild != NULL)
        current = current->rightchild;
    return current;
} // SearchRightest

TreeNode* BST::SearchLeftest(TreeNode *current){
    while (current->leftchild != NULL)
        current = current->leftchild;
    return current;
} // SearchLefttest

void BST::deletebst(){
    root = NULL;
    delete root;
} // deletebst

void BST::InsertBST(int key, pokemonList::pokemonType data){      //��[�ͩR�� HP]���G����
    TreeNode *b = 0;
    TreeNode *a = 0;
    TreeNode *insert_node = new TreeNode(key, data);

    a = root;
    while (a != NULL){                  // �M��A����m  insert
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

int BST::maxDepth(TreeNode *current){   //�H���j���
    if (current == NULL)
        return 0;
    else{
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

void BST::SearchAndPrint_Leftmost(){
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    TreeNode *result = SearchLeftest(current);
    if ( result != NULL ){
        cout << "Leftmost node:" << endl;
        cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
        result->printOR();
    } // if
} // SearchAndPrint_Leftmost

void BST::SearchAndPrint_Rightmost(){
    TreeNode *current = root;      // �Ncurrent���Vroot�@��traversal�_�I
    TreeNode *result = SearchRightest(current);
    if ( result != NULL ){
        cout << "Rightmost node:" << endl;
        cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
        result->printOR();
    } // if
} // SearchAndPrint_Rightmost


class Heap{
private:
    vector<pokemonList::pokemonType> myHeap;//�ŧiheap<vector>���A
public:
	bool empty(){
		if ( myHeap.size() == 0 )
		  return true;
		else
		  return false;
	} // empty
    void constructHeap(vector<pokemonList::pokemonType> pSet);// construct
    void printVal(); // print Val of heap
    void printheight(); //print height of heap
    void printLeftMost(); //print LeftMost
    void printBottom(); // printBottom
    void deleteMax();
    void printOR(){
        for ( int a = 0 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].no ;     // �L�s��# pokemon number (1)
        for ( int a = GetIntLength(myHeap[0].no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].name ;     // �L�W�� pokemon name (2)
        for ( int a = myHeap[0].name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].tp1 ;     // �L���� 1 1st type (3)
        for ( int a = myHeap[0].tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].hp ;     // �L�ͩR�� health point (4)
        for ( int a = GetIntLength(myHeap[0].hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].atk ;     // �L���� attack (5)
        for ( int a = GetIntLength(myHeap[0].atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  myHeap[0].def ;     // �L���m defense (6)
        cout << endl << endl ;
    } // printOR
};


void Heap::constructHeap(vector<pokemonList::pokemonType> pSet){ //�ھڲĤ@�ӥ\�઺�ʺA�}�C�ӫغc
    myHeap = pSet; // let heap = pSet
    int len = myHeap.size(); // get length
    for(int i = len/2-1; i >= 0; i--){  // int i = len/2-1 ���q�̩��U�֦��l�`�I�����`�I�}�l�P�_ ���� call heapRebuild(i), i = 2, 1, 0 �q2�}�l 
        int index = i; // �]�w�������ʪ���m
        while(1){
            int swapPos; //�n�洫����m
            int childMax = -1; //children����j���ƭ�
            if(index*2+1 < len){ //�p�G��leftChild
                if(myHeap[index*2+1].hp > childMax){ //�p�G�j��childMax,�N�]�wchildMax�ƭ�,�ó]�w���n�洫����m
                    childMax = myHeap[index*2+1].hp;
                    swapPos = index*2+1;
                } // if 
            } // if 
            if(index*2+2 < len){ //�p�G��rightChild
                if(myHeap[index*2+2].hp > childMax){ //�p�G�j��childMax,�N�]�wchildMax�ƭ�,�ó]�w���n�洫����m
                    childMax = myHeap[index*2+2].hp;
                    swapPos = index*2+2;
                } // if 
            } // if 

            if(childMax > myHeap[index].hp){ //�p�G�̫�o�{��child�j��ۤv
                swap(myHeap[index],myHeap[swapPos]); //�N�i��洫
                index = swapPos; //�]�w�s����m
            } // if 
            else //�S�����ܥN����
                break;
        } // while
    } // for
} // constructHeap

void Heap::printVal(){//��Xheap�����e
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    int len = myHeap.size(); //���oheap����
    for(int i = 0; i < len; i++){
        cout << "[" << i << "]" ; //�Lindex
        for ( int a = GetIntLength(i)+2 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].no ;     // �L�s��# pokemon number (1)
        for ( int a = GetIntLength(myHeap[i].no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].name ;     // �L�W�� pokemon name (2)
        for ( int a = myHeap[i].name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].tp1 ;     // �L���� 1 1st type (3)
        for ( int a = myHeap[i].tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].hp ;     // �L�ͩR�� health point (4)
        for ( int a = GetIntLength(myHeap[i].hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].atk ;     // �L���� attack (5)
        for ( int a = GetIntLength(myHeap[i].atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  myHeap[i].def ;     // �L���m defense (6)
        cout << endl ;
    } // for
} // printVal
void Heap::printheight(){//��Xheap������
    int N = myHeap.size();
    cout << "HP heap height = " << ceil(log2(N + 1)) << endl;  // ceil()�V�W������ 
} // printheight

void Heap::printLeftMost(){ //��X�̥��䪺
    cout << "Leftmost node:" << endl;
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    int i = 0; //���N�ܼ�
    int len = myHeap.size(); //���o����
    while(true) {//�]�ߵL���j��
        if(i*2+1 < len) //�p�G��left child,�N�~�򩹥��䨫
            i = i*2+1;
        else//�S�����ܴNbreak
            break;
    } // while
    cout << "[" << i << "]" ; //�Lindex
    for ( int a = GetIntLength(i)+2 ; a < 8 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].no ;     // �L�s��# pokemon number (1)
    for ( int a = GetIntLength(myHeap[i].no)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].name ;     // �L�W�� pokemon name (2)
    for ( int a = myHeap[i].name.length()+1 ; a < 33 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].tp1 ;     // �L���� 1 1st type (3)
    for ( int a = myHeap[i].tp1.length()+1 ; a < 17 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].hp ;     // �L�ͩR�� health point (4)
    for ( int a = GetIntLength(myHeap[i].hp)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].atk ;     // �L���� attack (5)
    for ( int a = GetIntLength(myHeap[i].atk)+1 ; a < 9; a++ )
        cout << " " ;
    cout <<  myHeap[i].def ;     // �L���m defense (6)
    cout << endl ;
} // printLeftMost

void Heap::printBottom(){//��X�̫�@��
    cout << "Bottom:" << endl;
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    int i = myHeap.size()-1; //�������oheap���̫�@�Ӥ���
    cout << "[" << i << "]" ; //�Lindex
    for ( int a = GetIntLength(i)+2 ; a < 8 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].no ;     // �L�s��# pokemon number (1)
    for ( int a = GetIntLength(myHeap[i].no)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].name ;     // �L�W�� pokemon name (2)
    for ( int a = myHeap[i].name.length()+1 ; a < 33 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].tp1 ;     // �L���� 1 1st type (3)
    for ( int a = myHeap[i].tp1.length()+1 ; a < 17 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].hp ;     // �L�ͩR�� health point (4)
    for ( int a = GetIntLength(myHeap[i].hp)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].atk ;     // �L���� attack (5)
    for ( int a = GetIntLength(myHeap[i].atk)+1 ; a < 9; a++ )
        cout << " " ;
    cout <<  myHeap[i].def ;     // �L���m defense (6)
    cout << endl ;
} // printBottom

void Heap::deleteMax(){ //�R���̤j��� 
  if ( myHeap.size() == 0 )
    cout << endl << "----- Execute Mission 2 first! -----" << endl;
  else if ( myHeap.size() == 1 ){
  	cout << "The removed root:" << endl;
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    printOR();
    myHeap.pop_back();
  } // if
  else{
  	cout << "The removed root:" << endl;
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    printOR();
  	myHeap[0] = myHeap[myHeap.size()-1];
  	myHeap.pop_back();
  	constructHeap(myHeap); //�]���R��max�֩w�|��semi-heap �]����heap rebuild���L���s��z�ܦ� maxheap 
  } // else
} //  deleteMax

int main(){
    int command = 0; //�Ĥ@��input(0, 1, 2)
    bool hascommand1 = false; //�P�_���S��command1�L
    pokemonList list;
    BST bst; // �ͩR�� HP
    Heap heap;
    do{
        cout << endl << "****** Pokemon Tree and Heap ******";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1. Read a file to build BST     *";
        cout << endl << "* 2. Transform it into Max Heap   *";
        cout << endl << "***********************************";
        cout << endl << "* 3. Delete max from Max Heap     *";
        cout << endl << "***********************************";
        cout << endl << "Input a choice(0, 1, 2, 3): ";
        cin >> command;  //cin�Ĥ@��input(0, 1, 2, 3)
        switch(command){
        case 0 :
            break;
        case 1 :
            if ( hascommand1 )  // �p�G���e�w�g�عL�G����n���R��
                bst.deletebst();
            hascommand1 = true;
            list.readF();
            list.showAll();

            //�H�u�ͩR�� HP�v����ȫإߤG���j�M��
            for ( int i = 0 ; i < list.pSet.size() ; i++ )
                bst.InsertBST( list.pSet[i].hp, list.pSet[i] );

            //�L�X�u�ͩR�� HP�v����Ȫ��G���j�M�𪺾�
            cout << "HP tree height = " << bst.GetmaxDepth() << endl ; // test

            bst.SearchAndPrint_Leftmost();  //��X�̥����`�I���������
            bst.SearchAndPrint_Rightmost(); //��X�̥k���`�I���������
            break;
        case 2 :
            if(hascommand1){ //�p�G������Ĥ@�ӥ\��,�N�}�l����ĤG��
                heap.constructHeap(list.pSet);
                heap.printVal();
                heap.printheight();
                heap.printLeftMost();
                heap.printBottom();
            } // if
            else //�p�G�S������Ĥ@�ӥ\��
                cout << "\n----- Execute Mission 1 first! -----\n\n";
            break;
        case 3 :
            if(hascommand1){ //�p�G������Ĥ@�ӥ\��,�N�}�l����ĤG��
                heap.deleteMax();
                if ( !heap.empty() ){
                  heap.printVal();
                  heap.printheight();
                  heap.printLeftMost();
                  heap.printBottom();
				} // if
            } // if
            else //�p�G�S������Ĥ@�ӥ\��
                cout << "\n----- Execute Mission 1 first! -----\n\n";
            break;
        default :
            cout << endl << "Command does not exist!" << endl; //input 0,1�H�~��
        } // end switch
    }
    while ( command != 0 );    //'0':stop the program
    system ( "pause" );        // pause the display
    return 0;
} // end main


