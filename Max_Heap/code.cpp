//DS1101ex6_第27組_10833230李郁含_10844149謝宜庭
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
        int no; // 編號# pokemon number (1)
        string name; // 名稱 pokemon name (2)
        string tp1; // 類型 1 1st type (3)
        //int tot; // 總和 total sum
        int hp; // 生命值 health point (4)
        int atk; // 攻擊 attack (5)
        int def; // 防禦 defense (6)
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
            fNo = 0; // 目前切到第幾個 number of fields read so far
            pre = 0; // 目前切到第幾個char  locate one field of input record
            buf.assign(cstr); // copy c-string into C++ string
            do { // scan the buffer from left to right
                pos = buf.find_first_of('\t', pre); // locate the next field by '\t' (tab)
                cut = buf.substr(pre, pos - pre); //扣掉tab len = pos - pre // retrieve a field
                switch (++fNo){
                case 1:
                    oneR.no = atoi(cut.c_str()); // get the 編號# pokemon number (1)
                    break;
                case 2:
                    oneR.name = cut; // get the 名稱 pokemon name (2)
                    break;
                case 3:
                    oneR.tp1 = cut; // get 類型 1 1st type (3)
                    break;
                case 6:
                    oneR.hp = atoi(cut.c_str()); // get 生命值 health point (4)
                    break;
                case 7:
                    oneR.atk = atoi(cut.c_str()); // get 攻擊 attack (5)
                    break;
                case 8:
                    oneR.def = atoi(cut.c_str()); // get 防禦 defense (6)
                    break;
                default:
                    break;
                } //end switch
                pre = ++pos; // 跳過tab //move to the next field
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

int GetIntLength(int i){  //算出數字的長度
    int len=1;
    while ( i/10 > 0 ){
        len++;
        i /= 10;
    } //while 
    return len;
} // GetIntLength

void pokemonList::showAll(){
    for ( int i = 0 ; i < this->pSet.size() ; i++ ){
        if ( i == 0 ) //印第一行
            cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
        cout << "[" << i+1 << "]" ; //印index
        this->pSet[i].rawR = i+1;
        for ( int a = GetIntLength(i+1)+2 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].no ;     // 印編號# pokemon number (1)
        for ( int a = GetIntLength(this->pSet[i].no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].name ;     // 印名稱 pokemon name (2)
        for ( int a = this->pSet[i].name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].tp1 ;     // 印類型 1 1st type (3)
        for ( int a = this->pSet[i].tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].hp ;     // 印生命值 health point (4)
        for ( int a = GetIntLength(this->pSet[i].hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->pSet[i].atk ;     // 印攻擊 attack (5)
        for ( int a = GetIntLength(this->pSet[i].atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  this->pSet[i].def ;     // 印防禦 defense (6)
        cout << endl ;
    } // for
} //end showAll()

class TreeNode: public pokemonList{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;                         // 鍵值 [生命值 HP]
    pokemonList::pokemonType value;  // DATA
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),value() {};
    TreeNode(int a, pokemonType input):leftchild(0),rightchild(0),parent(0),key(a),value(input) {};

    int rawR = 0; // raw data of one record
    int no; // 編號# pokemon number (1)
    string name; // 名稱 pokemon name (2)
    string tp1; // 類型 1 1st type (3)
    //int tot; // 總和 total sum
    int hp; // 生命值 health point (4)
    int atk; // 攻擊 attack (5)
    int def; // 防禦 defense (6)

    int GetKey(){ return key; }  // 鍵值 [生命值 HP]
    void printOR(){
        cout << "[" << this->value.rawR << "]" ; //印index
        for ( int a = GetIntLength(this->value.rawR)+2 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  this->value.no ;     // 印編號# pokemon number (1)
        for ( int a = GetIntLength(this->value.no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->value.name ;     // 印名稱 pokemon name (2)
        for ( int a = this->value.name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  this->value.tp1 ;     // 印類型 1 1st type (3)
        for ( int a = this->value.tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  this->value.hp ;     // 印生命值 health point (4)
        for ( int a = GetIntLength(this->value.hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  this->value.atk ;     // 印攻擊 attack (5)
        for ( int a = GetIntLength(this->value.atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  this->value.def ;     // 印防禦 defense (6)
        cout << endl ;
    } // printOR
    friend class BST;   // 可以放在 private 或 public
};

class BST{
private:
    TreeNode *root;
    TreeNode* SearchRightest(TreeNode *current);
    TreeNode* SearchLeftest(TreeNode *current);
public:
    bool hasfind = false; //是否有找到
    BST():root(0) {};
    void deletebst();
    void InsertBST(int key, pokemonList::pokemonType data);               //建[生命值 HP]的二元樹
    int maxDepth(TreeNode *current);     //以遞迴找樹高
    int GetmaxDepth();
    void SearchAndPrint_Leftmost();   //找出最左側節點對應的資料
    void SearchAndPrint_Rightmost();  //找出最右側節點對應的資料
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

void BST::InsertBST(int key, pokemonList::pokemonType data){      //建[生命值 HP]的二元樹
    TreeNode *b = 0;
    TreeNode *a = 0;
    TreeNode *insert_node = new TreeNode(key, data);

    a = root;
    while (a != NULL){                  // 尋找適當的位置  insert
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

int BST::maxDepth(TreeNode *current){   //以遞迴找樹高
    if (current == NULL)
        return 0;
    else{
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

void BST::SearchAndPrint_Leftmost(){
    TreeNode *current = root;      // 將current指向root作為traversal起點
    TreeNode *result = SearchLeftest(current);
    if ( result != NULL ){
        cout << "Leftmost node:" << endl;
        cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
        result->printOR();
    } // if
} // SearchAndPrint_Leftmost

void BST::SearchAndPrint_Rightmost(){
    TreeNode *current = root;      // 將current指向root作為traversal起點
    TreeNode *result = SearchRightest(current);
    if ( result != NULL ){
        cout << "Rightmost node:" << endl;
        cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
        result->printOR();
    } // if
} // SearchAndPrint_Rightmost


class Heap{
private:
    vector<pokemonList::pokemonType> myHeap;//宣告heap<vector>型態
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
        cout <<  myHeap[0].no ;     // 印編號# pokemon number (1)
        for ( int a = GetIntLength(myHeap[0].no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].name ;     // 印名稱 pokemon name (2)
        for ( int a = myHeap[0].name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].tp1 ;     // 印類型 1 1st type (3)
        for ( int a = myHeap[0].tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].hp ;     // 印生命值 health point (4)
        for ( int a = GetIntLength(myHeap[0].hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[0].atk ;     // 印攻擊 attack (5)
        for ( int a = GetIntLength(myHeap[0].atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  myHeap[0].def ;     // 印防禦 defense (6)
        cout << endl << endl ;
    } // printOR
};


void Heap::constructHeap(vector<pokemonList::pokemonType> pSet){ //根據第一個功能的動態陣列來建構
    myHeap = pSet; // let heap = pSet
    int len = myHeap.size(); // get length
    for(int i = len/2-1; i >= 0; i--){  // int i = len/2-1 先從最底下擁有子節點的父節點開始判斷 類似 call heapRebuild(i), i = 2, 1, 0 從2開始 
        int index = i; // 設定本次移動的位置
        while(1){
            int swapPos; //要交換的位置
            int childMax = -1; //children比較大的數值
            if(index*2+1 < len){ //如果有leftChild
                if(myHeap[index*2+1].hp > childMax){ //如果大於childMax,就設定childMax數值,並設定為要交換的位置
                    childMax = myHeap[index*2+1].hp;
                    swapPos = index*2+1;
                } // if 
            } // if 
            if(index*2+2 < len){ //如果有rightChild
                if(myHeap[index*2+2].hp > childMax){ //如果大於childMax,就設定childMax數值,並設定為要交換的位置
                    childMax = myHeap[index*2+2].hp;
                    swapPos = index*2+2;
                } // if 
            } // if 

            if(childMax > myHeap[index].hp){ //如果最後發現有child大於自己
                swap(myHeap[index],myHeap[swapPos]); //就進行交換
                index = swapPos; //設定新的位置
            } // if 
            else //沒有的話代表結束
                break;
        } // while
    } // for
} // constructHeap

void Heap::printVal(){//輸出heap的內容
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    int len = myHeap.size(); //取得heap長度
    for(int i = 0; i < len; i++){
        cout << "[" << i << "]" ; //印index
        for ( int a = GetIntLength(i)+2 ; a < 8 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].no ;     // 印編號# pokemon number (1)
        for ( int a = GetIntLength(myHeap[i].no)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].name ;     // 印名稱 pokemon name (2)
        for ( int a = myHeap[i].name.length()+1 ; a < 33 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].tp1 ;     // 印類型 1 1st type (3)
        for ( int a = myHeap[i].tp1.length()+1 ; a < 17 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].hp ;     // 印生命值 health point (4)
        for ( int a = GetIntLength(myHeap[i].hp)+1 ; a < 9 ; a++ )
            cout << " " ;
        cout <<  myHeap[i].atk ;     // 印攻擊 attack (5)
        for ( int a = GetIntLength(myHeap[i].atk)+1 ; a < 9; a++ )
            cout << " " ;
        cout <<  myHeap[i].def ;     // 印防禦 defense (6)
        cout << endl ;
    } // for
} // printVal
void Heap::printheight(){//輸出heap的高度
    int N = myHeap.size();
    cout << "HP heap height = " << ceil(log2(N + 1)) << endl;  // ceil()向上取整函數 
} // printheight

void Heap::printLeftMost(){ //輸出最左邊的
    cout << "Leftmost node:" << endl;
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    int i = 0; //迭代變數
    int len = myHeap.size(); //取得長度
    while(true) {//設立無限迴圈
        if(i*2+1 < len) //如果有left child,就繼續往左邊走
            i = i*2+1;
        else//沒有的話就break
            break;
    } // while
    cout << "[" << i << "]" ; //印index
    for ( int a = GetIntLength(i)+2 ; a < 8 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].no ;     // 印編號# pokemon number (1)
    for ( int a = GetIntLength(myHeap[i].no)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].name ;     // 印名稱 pokemon name (2)
    for ( int a = myHeap[i].name.length()+1 ; a < 33 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].tp1 ;     // 印類型 1 1st type (3)
    for ( int a = myHeap[i].tp1.length()+1 ; a < 17 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].hp ;     // 印生命值 health point (4)
    for ( int a = GetIntLength(myHeap[i].hp)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].atk ;     // 印攻擊 attack (5)
    for ( int a = GetIntLength(myHeap[i].atk)+1 ; a < 9; a++ )
        cout << " " ;
    cout <<  myHeap[i].def ;     // 印防禦 defense (6)
    cout << endl ;
} // printLeftMost

void Heap::printBottom(){//輸出最後一個
    cout << "Bottom:" << endl;
    cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
    int i = myHeap.size()-1; //直接取得heap中最後一個元素
    cout << "[" << i << "]" ; //印index
    for ( int a = GetIntLength(i)+2 ; a < 8 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].no ;     // 印編號# pokemon number (1)
    for ( int a = GetIntLength(myHeap[i].no)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].name ;     // 印名稱 pokemon name (2)
    for ( int a = myHeap[i].name.length()+1 ; a < 33 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].tp1 ;     // 印類型 1 1st type (3)
    for ( int a = myHeap[i].tp1.length()+1 ; a < 17 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].hp ;     // 印生命值 health point (4)
    for ( int a = GetIntLength(myHeap[i].hp)+1 ; a < 9 ; a++ )
        cout << " " ;
    cout <<  myHeap[i].atk ;     // 印攻擊 attack (5)
    for ( int a = GetIntLength(myHeap[i].atk)+1 ; a < 9; a++ )
        cout << " " ;
    cout <<  myHeap[i].def ;     // 印防禦 defense (6)
    cout << endl ;
} // printBottom

void Heap::deleteMax(){ //刪除最大鍵值 
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
  	constructHeap(myHeap); //因為刪掉max肯定會變semi-heap 因此做heap rebuild讓他重新整理變成 maxheap 
  } // else
} //  deleteMax

int main(){
    int command = 0; //第一個input(0, 1, 2)
    bool hascommand1 = false; //判斷有沒有command1過
    pokemonList list;
    BST bst; // 生命值 HP
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
        cin >> command;  //cin第一個input(0, 1, 2, 3)
        switch(command){
        case 0 :
            break;
        case 1 :
            if ( hascommand1 )  // 如果先前已經建過二元樹要先刪除
                bst.deletebst();
            hascommand1 = true;
            list.readF();
            list.showAll();

            //以「生命值 HP」為鍵值建立二元搜尋樹
            for ( int i = 0 ; i < list.pSet.size() ; i++ )
                bst.InsertBST( list.pSet[i].hp, list.pSet[i] );

            //印出「生命值 HP」為鍵值的二元搜尋樹的樹高
            cout << "HP tree height = " << bst.GetmaxDepth() << endl ; // test

            bst.SearchAndPrint_Leftmost();  //找出最左側節點對應的資料
            bst.SearchAndPrint_Rightmost(); //找出最右側節點對應的資料
            break;
        case 2 :
            if(hascommand1){ //如果有執行第一個功能,就開始執行第二個
                heap.constructHeap(list.pSet);
                heap.printVal();
                heap.printheight();
                heap.printLeftMost();
                heap.printBottom();
            } // if
            else //如果沒有執行第一個功能
                cout << "\n----- Execute Mission 1 first! -----\n\n";
            break;
        case 3 :
            if(hascommand1){ //如果有執行第一個功能,就開始執行第二個
                heap.deleteMax();
                if ( !heap.empty() ){
                  heap.printVal();
                  heap.printheight();
                  heap.printLeftMost();
                  heap.printBottom();
				} // if
            } // if
            else //如果沒有執行第一個功能
                cout << "\n----- Execute Mission 1 first! -----\n\n";
            break;
        default :
            cout << endl << "Command does not exist!" << endl; //input 0,1以外的
        } // end switch
    }
    while ( command != 0 );    //'0':stop the program
    system ( "pause" );        // pause the display
    return 0;
} // end main


