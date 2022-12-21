// 10920110 王柏甯 10833230 李郁含
#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<fstream> // open, is_open
#include<vector>
#include<cstdlib>     //strtoul,system
#include<cmath>       //sqrt
#include <stack> // push, pop, top
#define PTR_NUM 3
#define KEY_NUM PTR_NUM - 1
#define item  16
#define wanted 10
using namespace std;



struct listing{

    int sameData[1000] ;  // 同樣的名稱放進一陣列
    int number ;     // 同樣的名稱數
    string name ;    // 名稱

};

struct node {
    int nodeNum ;
    listing nameSmall ;
    listing nameMiddle ;
    listing nameBig ;
    node* parent ;
    node* left ;
    node* middle ;
    node* right ;

};

//------------------------讀檔-------------------------------

class SchoolList { //讀檔的部分
  public:
    typedef struct sT{
      int num;   // 序號
      string sname; // 學校名稱school name
      string dname; // 科系名稱department name
      string type; // 日間∕進修別either day or night
      string level; // 等級別graduate or undergraduate
      int nstud; // 學生數number of students
    } schoolType; // structure of school data

  vector<schoolType> allR;
  string fileID;
  void reset(); // declaration: initial set up

  public:
    SchoolList() { reset(); } // constructor for initialization
    ~SchoolList() { reset(); } // destructor for initialization
    bool readFile( string inName ); // declaration: read all from a file
    bool empty(){ if ( allR.size() == 0 )  return true; else  return false; } // empty
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

bool SchoolList::readFile( string inName ){ // definition: read all from a file
  int n = 0; //序號
  fstream inFile; // file handle
  string fileName; // file name
  this->reset(); // call: initial set up
  //cout << endl << "Input a file number ([0] Quit): ";
  //cin >> this->fileID; // get the file identifier
  this->fileID = inName ;
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
          case 2: oneR.sname = cut; // get the school name
            break;
          case 4: oneR.dname = cut; // get the department name
            break;
          case 5: oneR.type = cut; // get either day or night
            break;
          case 6: oneR.level = cut; // get graduate or undergraduate
            break;
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

//------------------------讀檔-------------------------------

class TreeNode {
  public:
  	vector<SchoolList::schoolType> data; //每個節點仍是資料庫
    string key;
    string color ;
    int num;
    TreeNode * parent ;
    TreeNode * left;
    TreeNode * right;

    TreeNode() {
      data.clear();
      key = "";
      color = "" ;
      num = 0;
      parent = NULL ;
      left = NULL;
      right = NULL;
    } // TreeNode
    TreeNode(SchoolList::schoolType newdata) {
      data.push_back(newdata);
      key = newdata.dname;
      color = "" ;
      num = 1;
      parent = NULL ;
      left = NULL;
      right = NULL;
    } // TreeNode
};

class TwoThreeTree {

    private :
        int length = 0 ;  // 儲存區長
        string filenum ;
        string fileName ;
        node* tree ;     // 樹，裡面只放資料位置
        string** data ;  // 資料儲存區
        int height = 0 ;
        int allnum = 0 ;


    public :

        node* getRoot () {
            return tree ;
        } // getRoot ()

        void getfileName( string input) {
            filenum = input ;
            fileName = "input"+input+".txt" ;
        }


        void checkfileline() {
            length = 0 ;
            FILE * fp = NULL;
            int c, lc=0;
            fp = fopen(fileName.c_str(), "r");
            while((c = fgetc(fp)) != EOF) {
                if(c == '\n') length ++;
                lc = c;
            }
            fclose(fp);
            if(lc != '\n') length ++;
            length = length - 3 ;
        }


         bool readandcreatefile() {
             tree = NULL ;
            FILE *infile = NULL ;
            char temp[50] ;

            infile = fopen(fileName.c_str(),"r") ;
            if(infile == NULL ) {
                cout<<endl<<fileName<<"does not exist!" << endl ;
                return false ;
            }
            else{
                for ( int i = 0 ; i < 15 ; i++ ) fscanf(infile,"%s",&temp) ;
                data = new string*[10] ;  // 建立動態陣列
                for ( int i = 0 ; i < 10 ; i++ ) data[i] = new string[length+1] ;
                for ( int x = 1 ; fscanf(infile,"%s",&temp) != EOF ; x++ ) {
                    data[0][x] = to_string(x) ;  // 0 是原始順序
                    fscanf(infile,"%s",&temp) ;  // 忽略文本序號
                    data[1][x] = temp ;         // 學校名
                    fscanf(infile,"%s",&temp) ;
                    for ( int i = 2 ; i < 8 ; i++ ) {
                        fscanf(infile,"%s",&temp) ;
                        if( i == 3 &&  strcmp( temp, "D" ) != 0 && strcmp( temp, "N" ) != 0  && strcmp( temp, "P" ) != 0 ) {
                            //cout << endl << data[0][x] << " " << temp ;
                            data[3][x] = '\0' ;
                            data[4][x] = '\t' ;
                            data[5][x] = '\0' ;
                            data[6][x] = '\t' ;
                            i = 7 ;
                        }
                        else if( i == 5 &&  strcmp( temp, "D" ) != 0 && strcmp( temp, "M" ) != 0 && strcmp( temp, "B" ) != 0
                                && strcmp( temp, "X" ) != 0 && strcmp( temp, "C" ) != 0 && strcmp( temp, "5" ) != 0 && strcmp( temp, "2" ) != 0)  {
                            //cout << endl << data[0][x] << " " << temp ;
                            data[5][x] = '\0' ;
                            data[6][x] = '\t' ;
                            i = 7 ;
                        }
                        data[i][x] = temp ;
                    }

                    for ( int i = 0 ; i < 6 ; i++ ) {
                            fscanf(infile,"%s",&temp) ; // 讀掉沒用的
                    }
                }
            }
            fclose(infile);
            return true ;
        }

        void printfile() {
            cout << "\n學校代碼\t學校名稱\t科系代碼\t科系名稱\t日間∕進修別\t等級別\t學生數\t教師數\t上學年度畢業生數\t縣市名稱\t體系別\n" ;
            for ( int x = 0 ; x < length ; x++ ) {
                for ( int y = 1 ; y < 8 ; y++ ) {
                    cout << data[y][x] << "\t";
                }
                cout << "\n" ;
            }
        }


        void deletefile() {  //釋放記憶體
            delete [] data ;
            length = 0 ;
            height = 0 ;
            deleteTree ( tree ) ;

        } // deletefile()

        void deleteTree ( node* temp ) {
            if (temp!=NULL) {
                 deleteTree ( temp->right ) ;
                 deleteTree (temp->left) ;
                 deleteTree(temp->middle) ;
                 deleteNode( temp ) ;
                 temp = NULL ;
            } // if ()

        } //deleteTree()


        void printListing( listing temp, int num ) {
          for (int i = 0 ; i < 8 ; i++ ) {
            if ( i == 0 ) {
              cout << " [" << temp.sameData[num] << "] " ;
            }
             else {
               if (i>1&&i!=4&&i!=6)
                 cout << ", " ;
               if (i==4||i==6)
                 cout << " " ;
               cout << data[i][temp.sameData[num]] ;
             }
           }
        } // printListing()

         void printData( listing temp, int& num ) {  // 印出特定位置的資料
             for (int j = 1 ; j <= temp.number ; j++ ) {
                 cout << endl << num++ << ":" ;
                 for (int i = 0 ; i < 8 ; i++ ) {
                     if ( i == 0 ) {
                        cout << " [" << temp.sameData[j-1] << "] " ;
                     }
                     else {
                        if (i>1&&i!=4&&i!=6)
                            cout << ", " ;
                        if (i==4||i==6)
                            cout << " " ;
                        cout << data[i][temp.sameData[j-1]] ;
                     }
                 }
             }
         } // printData()

         void printNode( node* target ) {
             int num = 1 ;
             if (target->nameBig.number!=0) {
                printData( target->nameBig, num ) ;
             }
             if (target->nameMiddle.number!=0) {
                printData( target->nameMiddle, num ) ;
             }
             if (target->nameSmall.number!=0) {
                printData( target->nameSmall, num ) ;
             }

         } // printNode()

         int getLength() {  //給予陣列長
           return length ;
         } // getLength()

         void printTree () {
             node* temp = tree ;
             cout << "Tree height = " << height ;
             printNode( tree ) ;
             cout << endl ;
         } // printTree ()

         void printAll() {
             int num = 1 ;

            for ( int x = 1 ; x <= length ; x++ ) {
                cout << endl << num++ << ":" ;
                for ( int y = 0 ; y < 8 ; y++ ) {
                    if ( y == 0 ) {
                        cout << " [" << data[y][x] << "] " ;
                     }
                     else {
                        if (y>1&&y!=4&&y!=6)
                            cout << ", " ;
                        if (y==4||y==6)
                            cout << " " ;
                        cout << data[y][x] ;
                     }
                }
            }

         } // printAll()

         void checkDepartment(TreeNode * target, listing temp ) {
             if (target==NULL || temp.number == 0 ) {
                return ;
             } // if()

             int out = 1 ;
             for ( int i = 0 ; i < temp.number ; i++ ) {
                //cout << endl << data[2][temp.sameData[i]] << "  " << target->key ;
               if(data[2][temp.sameData[i]] == target->key){
                    cout << endl << out++ << ":" ;
                    printListing(temp, i) ;
               }

             }

         } // checkDepartment()

         listing searchSchool ( node* temp , string name) {

             listing target ;
             target.number = 0 ;

             if ( temp->nameMiddle.name == name ) {        // 等於中間值
                return temp->nameMiddle ;

             } // if
             else if ( temp->nameBig.number!=0 && temp->nameBig.name == name ) {  // 等於較大值
                return temp->nameBig ;
             } // else if
             else if (temp->nameSmall.number!=0 && temp->nameSmall.name == name ) {  // 等於較小值
                return temp->nameSmall ;
             }

             // ----------------------------繼續找-----------------------------------------------------------------

            if ( temp->nameMiddle.name > name ) {
               if ( (temp->middle!=NULL) && (temp->nameSmall.number!=0) && (temp->nameSmall.name < name) ) {   //中間存在，比最小還大
                        target = searchSchool( temp->middle , name) ;
               }
               else if (temp->left!=NULL){          // 繼續往左走
                        //cout << endl <<"to left:   " << data[1][location] ;
                  target = searchSchool( temp->left , name) ;
               }
                    // ------------------------------------------------------------- 已經走到最底
              else {
                  return target;
              }
            } // if()

            else if ( temp->nameMiddle.name < name ) {
              if ( (temp->middle!=NULL) && (temp->nameBig.number!=0) && (temp->nameBig.name > name) ) {   //中間存在，比最大還小
                 target = searchSchool( temp->middle , name) ;
              }
              else if (temp->right!=NULL){          // 繼續往右走
                 target = searchSchool( temp->right , name) ;
              }
                    // ------------------------------------------------------------- 已經走到最底
              else {
                 return target ;
              }
            } // else if()

            return target ;

         } // searchSchool()

         // -----------------------------------------------------------------------------------------------製作2_3樹主程式

         listing increaseListing( listing nameList, int i ) {  // 新增節點內增加的學校代碼

             nameList.sameData[nameList.number] = i ;
             nameList.number++ ;
             return nameList ;

         }  // increaseListing()

         node* creatNode( listing school ) {
                node* temp = new node ;
                temp->left = NULL ;
                temp->middle = NULL ;
                temp->right = NULL;
                temp->parent = NULL;
                temp->nameMiddle = school ;
                temp->nameBig.number = 0 ;
                temp->nameSmall.number = 0 ;

                return temp ;
         } // creatNode()


         listing creatListing( int i ) {

             listing temp ;
             temp.name = data[1][i] ;                              // 名字
             temp.number = 1 ;                                     // 有幾個同樣的(目前只有一個)
             temp.sameData[temp.number-1] = i ;                   // 同樣名字的資料列表(目前只有一個)
             return temp ;
         } // creatListing

         void exchangeListing( listing& from, listing& to ) {    // 交換List資料

             listing temp ;
             temp.number = from.number ;
             if (temp.number!=0) {
                 temp.name = from.name ;

                 for (int j=0 ; j<temp.number ; j++) {
                    temp.sameData[j] = from.sameData[j] ;
                    from.sameData[j] = 0 ;
                 } // for
             }
             from.number = to.number ;
             if (from.number!=0) {
                 from.name = to.name ;

                 //from.sameData = new int[to.number] ;
                 for (int j=0 ; j<from.number ; j++) {
                    from.sameData[j] = to.sameData[j] ;
                    to.sameData[j] = 0 ;
                 } // for
             }
             to.number = temp.number ;
             if (to.number!=0) {
                 to.name = temp.name ;
                 for (int j=0 ; j<to.number ; j++) {
                    to.sameData[j] = temp.sameData[j] ;
                    temp.sameData[j] = 0 ;
                 } // for
                 temp.name.clear();
             }
         } //  moveListing()

         listing replaceList( listing from, listing&to ) {
             if (to.number!=0) {
                to.name.clear();
                //delete [] to.sameData ;
                 for (int j=0 ; j<to.number ; j++) {
                    to.sameData[j] = 0 ;
                 } // for
                 to.number = 0 ;
             }
             return from ;
         } // replaceList()

         void cleanListing(listing& target) {

             if (target.number!= 0 ) {
                 target.name.clear();
                 for(int i = 0 ; i < target.number ; i++ ) {
                    target.sameData[i] = 0 ;
                 } // for
             } // if

             target.number = 0 ;
         } // cleanListing()

         void deleteNode( node* temp ) {

             cleanListing(temp->nameBig) ;
             cleanListing(temp->nameMiddle) ;
             cleanListing(temp->nameSmall) ;

             delete temp ;
         } // deleteNode

         void creat23Tree () { //創造2-3樹
             node* temp = tree ;
             node* tail = NULL ;

             for( int i = 1 ; i<=length ; i++ ) {
                temp = tree ;
                if(tree == NULL) {                       // 先放入
                        tree = creatNode( creatListing( i ) ) ;
                        height = 1 ;
                }//if()
                else {                                     // 尋找到最底並放入
                        insertTree( temp ,i ) ;
                }

             } //for

         } //creat23Tree()

         void insertTree( node* temp ,int location) {   // 找到插入資料的位置  (locaton = 新增的資料代碼)
             bool alreadyIn = false ;
             //cout << endl << "in" ;
             alreadyIn = sameName( temp , location )  ;     // 檢查有沒有同樣的學校名

            if ( alreadyIn!=true ) {        // 使否已經放入同樣的學校名

                if ( temp->nameMiddle.name > data[1][location] ) {
                     if ( (temp->middle!=NULL) && (temp->nameSmall.number!=0) && (temp->nameSmall.name < data[1][location]) ) {   //中間存在，比最小還大
                        insertTree( temp->middle , location) ;
                     }
                     else if (temp->left!=NULL){          // 繼續往左走
                        //cout << endl <<"to left:   " << data[1][location] ;
                        insertTree( temp->left , location) ;
                    }
                    // ------------------------------------------------------------- 已經走到最底
                     else {
                            listing newList = creatListing( location ) ;
                            setRanking ( newList, temp ) ;
                            setTreeNode( temp ) ;
                            if (newList.number!=0)
                                cleanListing(newList) ;
                     }
                 } // if()

                 else if ( temp->nameMiddle.name < data[1][location] ) {
                     if ( (temp->middle!=NULL) && (temp->nameBig.number!=0) && (temp->nameBig.name > data[1][location]) ) {   //中間存在，比最大還小
                        insertTree( temp->middle , location) ;
                     }
                     else if (temp->right!=NULL){          // 繼續往右走
                        insertTree( temp->right , location) ;
                    }
                    // ------------------------------------------------------------- 已經走到最底
                    else {
                            listing newList = creatListing( location ) ;
                            setRanking ( newList, temp ) ;
                            setTreeNode( temp ) ;
                            if (newList.number!=0)
                                cleanListing(newList) ;
                    }
                 } // else if()

            } // if()

         } // insertTree()

         bool sameName( node* temp ,int location ) {  // 檢查有沒有同樣的學校名

             if ( temp->nameMiddle.name == data[1][location] ) {        // 等於中間值
                temp->nameMiddle = increaseListing( temp->nameMiddle, location ) ;
                return true ;
             } // if
             else if ( temp->nameBig.number!=0 && temp->nameBig.name == data[1][location] ) {  // 等於較大值
                temp->nameBig = increaseListing( temp->nameBig, location ) ;
                return true ;
             } // else if
             else if (temp->nameSmall.number!=0 && temp->nameSmall.name == data[1][location] ) {  // 等於較小值
                temp->nameSmall = increaseListing( temp->nameSmall, location ) ;
                return true ;
             }
             else {
                return false ;
             }
         } // sameName()




         void setRanking ( listing& newList, node* temp ) {  // 設定節點中數字排行

             if( newList.name > temp->nameMiddle.name) {

                    if(temp->nameBig.number!=0){                       // 最大值存在(已經有兩數據)
                        if ( temp->nameBig.name < newList.name  ) { // 出現更大的數值，交換位置(全部後移)
                            exchangeListing( temp->nameSmall, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, temp->nameBig ) ;
                            exchangeListing( temp->nameBig, newList ) ;
                        }
                        else {                                                 // 成為新的中間值，原中間值後移
                            exchangeListing( temp->nameSmall, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, newList ) ;
                        }
                    } // if()
                    else {                                                     //最大值空著
                        temp->nameBig = replaceList( newList, temp->nameBig ) ;
                    }
             }
             else  {
                    if(temp->nameSmall.number!=0){                          // 最小值存在(已經有兩數據)
                        if ( temp->nameSmall.name > newList.name  ) { // 出現更小的數值，交換位置(全部前移)
                            exchangeListing( temp->nameBig, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, temp->nameSmall ) ;
                            exchangeListing( temp->nameSmall, newList ) ;
                        }
                        else {                                                    // 成為新的中間值，原中間值前移
                            exchangeListing( temp->nameBig, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, newList ) ;
                        }
                    } // if()
                    else {
                        temp->nameSmall = replaceList( newList, temp->nameSmall )   ;                           // 最小值空著
                    }
             }
         } // setRanking ()

         node* cutNode( node* newBig ) {          // 切割節點

             node* newSmall = creatNode( newBig->nameSmall ) ;

             cleanListing(newBig->nameSmall) ;
             exchangeListing( newBig->nameBig, newBig->nameMiddle ) ;
             cleanListing(newBig->nameBig) ;
             return newSmall ;

         } // cutNode()

         node* setTreeNode( node* temp ) { //調整節點

             node* newBig = temp ;
             node* newSmall  = temp ;
             if( temp->nameBig.number!=0 && temp->nameSmall.number!= 0 ) {  // 檢查是否超過3項

                 if (temp->parent!=NULL) {       // 不在樹頂
                     setRanking ( temp->nameMiddle ,temp->parent ) ;
                     node* smallParent = setTreeNode( temp->parent ) ;
                     newSmall = cutNode( newBig ) ; // 切割節點，新節點中各為各自的中間值

                     if (temp->parent->middle!=NULL) {                        // 父母有三個孩子

                         if( temp->nameMiddle.name > temp->parent->middle->nameMiddle.name ){  // 確認目前為右節點

                             node* moveToSmall = temp->parent->middle ;        // 移動中節點
                             moveToSmall->parent = smallParent ;
                             smallParent->right = moveToSmall ;
                             temp->parent->middle = NULL ;
                             moveToSmall = temp->parent->left ;                 // 移動左節點
                             moveToSmall->parent = smallParent ;
                             smallParent ->left = moveToSmall;
                             newSmall->parent = temp->parent;
                             temp->parent->left = newSmall ;
                         }
                         else if ( temp->nameMiddle.name == temp->parent->middle->nameMiddle.name) { // 確認目前為中間節點

                             node* moveToSmall = temp->parent->left ;            // 移動左節點(最小)
                             moveToSmall->parent = smallParent ;
                             smallParent->left = moveToSmall ;
                             temp->parent->left = newBig ;
                             temp->parent->middle = NULL ;
                             newSmall->parent = smallParent ;                   // 移動小節點(較大)
                             smallParent->right = newSmall ;
                         }
                         else {

                             node* moveToBigLeft = newBig->parent->middle ;
                             moveToBigLeft->parent->left = moveToBigLeft ;
                             moveToBigLeft->parent->middle = NULL ;
                             newBig->parent = smallParent ;
                             smallParent->right = newBig ;
                             newSmall->parent = smallParent ;
                             smallParent->left = newSmall ;
                         }
                     } // if()
                     else{                                                 //父母只有兩個孩子

                        if (newBig->nameMiddle.name < temp->parent->nameMiddle.name) {  // 原為左節點
                            newSmall->parent = temp->parent;
                            newSmall->parent->middle = newBig ;
                            newSmall->parent->left = newSmall ;
                        }
                        else {                                                                 // 原為右節點

                            newSmall->parent = temp->parent;
                            temp->parent->middle = newSmall ;
                        }
                     } // else
                 } // if()
                 else {                     //在樹頂，更動樹頂指標
                      node* newTop = creatNode( temp->nameMiddle ) ;
                      newSmall = cutNode( newBig ) ;
                      newTop->right = newBig ;
                      newTop->left = newSmall ;
                      newBig->parent = newTop ;
                      newSmall->parent = newTop ;
                      tree = newTop ;
                      tree->parent = NULL ;             // 新的首節點
                      height++ ;
                  } // else

             } // if
             return newSmall ;
         } // setTreeNode()


} ;

//------------------------avl tree-------------------------------


class AVL { //以【科系名稱】建立一棵 AVL 樹
  public:
    TreeNode * root;
    AVL() {  root = NULL; } //AVL
    bool isTreeEmpty() { if (root == NULL)  return true;  else  return false; } // isTreeEmpty()
    void delete_avl(){ root = NULL; delete root;} // delete_avl
    int height(TreeNode * r); //樹高
    int getBalanceNum(TreeNode * n);//計算平衡係數
    TreeNode * R_Rotate(TreeNode * y);//往右轉
    TreeNode * L_Rotate(TreeNode * x); //往左轉
    TreeNode * insert_recur(TreeNode * r, TreeNode * new_node);
    void insert(SchoolList::schoolType newdata);  //將資料一個一個插進AVL樹
    void printroot(TreeNode * r);
    TreeNode * searchDepartment(TreeNode * cur, string name) ;
    void printDepartment(TreeNode * r) ;
}; //end AVLtree 以【科系名稱】建立一棵 AVL 樹

    int AVL::height(TreeNode * root) {
      if (root == NULL)
        return -1;
      else {
	    //計算每個子樹的高度
        int lheight = height(root -> left);
        int rheight = height(root -> right);

        if (lheight > rheight) //取較大的
          return (lheight + 1);
        else return (rheight + 1);
      } // else
    } // height

    // Get Balance factor of node N
    int AVL::getBalanceNum(TreeNode * n) { //計算平衡係數
      if (n == NULL)
        return -1;
      return height(n -> left) - height(n -> right);
    } // getBalanceNum

    TreeNode * AVL::R_Rotate(TreeNode * cur) {   //往右轉
      TreeNode * lc = cur -> left;    //左小孩
      TreeNode * temp = lc -> right;  //左小孩的右小孩(即將要被cur連到左邊

      cur -> left = temp;
      lc -> right = cur;  //小孩推翻爸爸成為父節點 root

      return lc;  //回傳新爸爸
    } // 往右轉

    TreeNode * AVL::L_Rotate(TreeNode * cur) {   //往左轉
      TreeNode * rc = cur -> right;   //右小孩
      TreeNode * temp = rc -> left;   //右小孩的左小孩(即將要被cur連到右邊

      cur -> right = temp;
      rc -> left = cur;   //小孩推翻爸爸成為父節點 root

      return rc;  //回傳新爸爸
    } // 往左轉

    TreeNode * AVL::insert_recur(TreeNode * cur, TreeNode * new_node) {
      if (cur == NULL) { //如果是第一個就直接放root
        cur = new_node;
        return cur;
      } // if
      if (new_node -> key > cur -> key)  //比較大往右走
        cur -> right = insert_recur(cur -> right, new_node);
	  else if (new_node -> key < cur -> key)  //比較小往左走
        cur -> left = insert_recur(cur -> left, new_node);
	  else if (new_node -> key == cur -> key){ // 鍵值(科系名稱)一樣的
        cur->data.push_back(new_node -> data[0]);  //將那筆資料allR推進 這個節點的資料庫
        cur->num ++;                               //數量加一
        return cur;
      } // else

      //這邊是加入完新資料 後檢查是否要做調整  從剛新增的一路檢查回來
      int bf = getBalanceNum(cur);  //算出此節點的平衡係數
      if (bf > 1 && new_node -> key < cur -> left -> key) //正->左邊重 // Left Left Case
        return R_Rotate(cur);

      if (bf > 1 && new_node -> key > cur -> left -> key) { //正->左邊重 // Left Right Case
        cur -> left = L_Rotate(cur -> left);
        return R_Rotate(cur);
      } // if

      if (bf < -1 && new_node -> key > cur -> right -> key) //負->右邊重 // Right Right Case
        return L_Rotate(cur);

      if (bf < -1 && new_node -> key < cur -> right -> key) { //負->右邊重 // Right Left Case
        cur -> right = R_Rotate(cur -> right);
        return L_Rotate(cur);
      } // if

      return cur; //回傳沒調整的

    } // insert_recur

  void AVL::insert(SchoolList::schoolType newdata){ //將資料一個一個插進AVL樹
    TreeNode * new_node = new TreeNode();
    new_node -> key = newdata.dname;     //設置鍵值  //有可能會有很多一樣科系名稱的  這時要將他們放在同一個節點
    new_node -> num = 1;                 //num是每個節點中這個鍵值(科系名稱)所擁有的data數量
    new_node -> data.push_back(newdata); //每個節點仍是資料庫
    root = insert_recur(root, new_node);
  } // insert

  void AVL::printroot(TreeNode * r) {
    if (r == NULL) // Base case  1
      return;
    for ( int i = 0 ; i < root->data.size() ; i++ )   //將樹根裡所有資料全部印出
      cout << i+1 << ": [" << r->data[i].num << "] " << r->data[i].sname << ", " << r->data[i].dname
           	<< ", " << r->data[i].type << ", " << r->data[i].level << ", " << r->data[i].nstud << endl ;
  } // printroot

  void AVL::printDepartment(TreeNode * r) {
    if (r == NULL) // Base case  1
      return;
    for ( int i = 0 ; i < r->data.size() ; i++ )   //將樹根裡所有資料全部印出
      cout << i+1 << ": [" << r->data[i].num << "] " << r->data[i].sname << ", " << r->data[i].dname
           	<< ", " << r->data[i].type << ", " << r->data[i].level << ", " << r->data[i].nstud << endl ;
  } // printDepartment

  TreeNode * AVL::searchDepartment(TreeNode * cur, string name) {
      TreeNode * ans = NULL ;

      if (cur == NULL) {
        return ans;
      } // if

      if (name > cur -> key)  //比較大往右走
        ans = searchDepartment(cur -> right, name);
	  else if ( name < cur -> key)  //比較小往左走
        ans = searchDepartment(cur -> left, name);
	  else if (name == cur -> key){ // 鍵值(科系名稱)一樣的
        return cur ;
      } // else

      return ans ;
  } // searchDepartment()





//------------------------avl tree-------------------------------


int main(){
    int command = -1 ;
    int num = 0 ;
    SchoolList list;
    AVL avl;
    TwoThreeTree aTree ;
    string schoolname ;
    string fileName ;
    bool success = false ;
    bool firsttime = true ;
    clock_t Start, End ;
    do{
        printf("\n\n*** Search Tree Utilities **\n* 0. QUIT                  *\n* 1. Build 2-3 tree        *\n* 2. Build AVL tree        *") ;
        printf("\n* 3. Intersection Query    *") ;
        printf("\n**********************************************") ;
        printf("\nInput a command(0, 1, 2, 3):") ;
        scanf("%d",&command) ;
        while ( command > 3 || command < 0 ) {
            printf("請輸入正確的數 :") ;
            scanf("%d",&command) ;
        }
        if ( command == 1 ) {
            printf( "\nInput a file number ([0] Quit): " ) ;
            cin >> fileName ;
            if ( fileName !="0") {

                if ( !firsttime ) aTree.deletefile() ;
                while ( !list.readFile(fileName) ) //讀檔並將每筆資料附上唯一序號後
                    list.reset();
                firsttime = false ;
                aTree.getfileName( fileName ) ;
                aTree.checkfileline();
                success = aTree.readandcreatefile() ;
                if ( success ) {
                  //aTree.printfile() ;
                  aTree.creat23Tree () ;
                  aTree.printTree () ;
                }
                //aTree.deletefile() ;
            }
        }

        else if ( command == 2 ) {

                if ( list.empty() ){ //先確認是否command過1
        	            cout << "### Choose 1 first. ###" << endl;

                } // if
                else {
                    if ( !avl.isTreeEmpty() )  // 如果先前已經建過avl樹要先刪除
                        avl.delete_avl();
        	        for ( int i = 0 ; i < list.allR.size() ; i++ )
                        avl.insert( list.allR[i] ); //將資料一個一個推進AVL樹

                    //印出「科系名稱」為鍵值的 AVL樹的樹高
                        cout << "Tree height = " << avl.height(avl.root)+1 << endl ;
                    //印出「科系名稱」為鍵值的 AVL樹的樹根
                    avl.printroot(avl.root);
                    cout << endl;

                } // else


        }

        else if ( command == 3 ) {

                if ( firsttime || avl.isTreeEmpty() ){ //先確認是否command過1
        	            cout << "### Choose 1 and 2 first. ###" << endl;

                } // if
                else {
                    listing targetS ;
                    TreeNode * targetD ;
                    cout << endl << "Enter a college name to search [*]: " ;
                    string Sname ;
                    string Dname ;
                    cin >> Sname ;
                    cout << endl << "Enter a department name to search [*]: " ;
                    cin >> Dname ;
                    if(Sname == "*" && Dname !="*"){
                        targetD = avl.searchDepartment(avl.root,Dname) ;
                        avl.printDepartment(targetD) ;
                    }

                    else if(Sname !="*"&&Dname =="*"){
                        targetS = aTree.searchSchool(aTree.getRoot(), Sname) ;
                        int num = 1 ;
                        aTree.printData( targetS, num ) ;
                    }

                    else if (Sname =="*"&&Dname =="*") {
                        aTree.printAll() ;
                    }

                    else {
                        targetS = aTree.searchSchool(aTree.getRoot(), Sname) ;
                        targetD = avl.searchDepartment(avl.root,Dname) ;
                        aTree.checkDepartment(targetD, targetS ) ;
                    }

                } // else


        }

        else if (command!=0 && command!=1 && command!=2 && command!=3 ){
            cout << endl << "Command does not exist!" << endl;
        }

    }while( command != 0 ) ;
    system ( "pause" );        // pause the display
    return 0;
}


