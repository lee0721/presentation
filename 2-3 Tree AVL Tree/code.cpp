// 10920110 ���fڬ 10833230 �����t
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

    int sameData[1000] ;  // �P�˪��W�٩�i�@�}�C
    int number ;     // �P�˪��W�ټ�
    string name ;    // �W��

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

//------------------------Ū��-------------------------------

class SchoolList { //Ū�ɪ�����
  public:
    typedef struct sT{
      int num;   // �Ǹ�
      string sname; // �ǮզW��school name
      string dname; // ��t�W��department name
      string type; // �鶡�A�i�קOeither day or night
      string level; // ���ŧOgraduate or undergraduate
      int nstud; // �ǥͼ�number of students
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

bool SchoolList::readFile( string inName ){ // definition: read all from a file
  int n = 0; //�Ǹ�
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

//------------------------Ū��-------------------------------

class TreeNode {
  public:
  	vector<SchoolList::schoolType> data; //�C�Ӹ`�I���O��Ʈw
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
        int length = 0 ;  // �x�s�Ϫ�
        string filenum ;
        string fileName ;
        node* tree ;     // ��A�̭��u���Ʀ�m
        string** data ;  // ����x�s��
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
                data = new string*[10] ;  // �إ߰ʺA�}�C
                for ( int i = 0 ; i < 10 ; i++ ) data[i] = new string[length+1] ;
                for ( int x = 1 ; fscanf(infile,"%s",&temp) != EOF ; x++ ) {
                    data[0][x] = to_string(x) ;  // 0 �O��l����
                    fscanf(infile,"%s",&temp) ;  // �����奻�Ǹ�
                    data[1][x] = temp ;         // �ǮզW
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
                            fscanf(infile,"%s",&temp) ; // Ū���S�Ϊ�
                    }
                }
            }
            fclose(infile);
            return true ;
        }

        void printfile() {
            cout << "\n�ǮեN�X\t�ǮզW��\t��t�N�X\t��t�W��\t�鶡�A�i�קO\t���ŧO\t�ǥͼ�\t�Юv��\t�W�Ǧ~�ײ��~�ͼ�\t�����W��\t��t�O\n" ;
            for ( int x = 0 ; x < length ; x++ ) {
                for ( int y = 1 ; y < 8 ; y++ ) {
                    cout << data[y][x] << "\t";
                }
                cout << "\n" ;
            }
        }


        void deletefile() {  //����O����
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

         void printData( listing temp, int& num ) {  // �L�X�S�w��m�����
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

         int getLength() {  //�����}�C��
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

             if ( temp->nameMiddle.name == name ) {        // ���󤤶���
                return temp->nameMiddle ;

             } // if
             else if ( temp->nameBig.number!=0 && temp->nameBig.name == name ) {  // ������j��
                return temp->nameBig ;
             } // else if
             else if (temp->nameSmall.number!=0 && temp->nameSmall.name == name ) {  // ������p��
                return temp->nameSmall ;
             }

             // ----------------------------�~���-----------------------------------------------------------------

            if ( temp->nameMiddle.name > name ) {
               if ( (temp->middle!=NULL) && (temp->nameSmall.number!=0) && (temp->nameSmall.name < name) ) {   //�����s�b�A��̤p�٤j
                        target = searchSchool( temp->middle , name) ;
               }
               else if (temp->left!=NULL){          // �~�򩹥���
                        //cout << endl <<"to left:   " << data[1][location] ;
                  target = searchSchool( temp->left , name) ;
               }
                    // ------------------------------------------------------------- �w�g����̩�
              else {
                  return target;
              }
            } // if()

            else if ( temp->nameMiddle.name < name ) {
              if ( (temp->middle!=NULL) && (temp->nameBig.number!=0) && (temp->nameBig.name > name) ) {   //�����s�b�A��̤j�٤p
                 target = searchSchool( temp->middle , name) ;
              }
              else if (temp->right!=NULL){          // �~�򩹥k��
                 target = searchSchool( temp->right , name) ;
              }
                    // ------------------------------------------------------------- �w�g����̩�
              else {
                 return target ;
              }
            } // else if()

            return target ;

         } // searchSchool()

         // -----------------------------------------------------------------------------------------------�s�@2_3��D�{��

         listing increaseListing( listing nameList, int i ) {  // �s�W�`�I���W�[���ǮեN�X

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
             temp.name = data[1][i] ;                              // �W�r
             temp.number = 1 ;                                     // ���X�ӦP�˪�(�ثe�u���@��)
             temp.sameData[temp.number-1] = i ;                   // �P�˦W�r����ƦC��(�ثe�u���@��)
             return temp ;
         } // creatListing

         void exchangeListing( listing& from, listing& to ) {    // �洫List���

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

         void creat23Tree () { //�гy2-3��
             node* temp = tree ;
             node* tail = NULL ;

             for( int i = 1 ; i<=length ; i++ ) {
                temp = tree ;
                if(tree == NULL) {                       // ����J
                        tree = creatNode( creatListing( i ) ) ;
                        height = 1 ;
                }//if()
                else {                                     // �M���̩��é�J
                        insertTree( temp ,i ) ;
                }

             } //for

         } //creat23Tree()

         void insertTree( node* temp ,int location) {   // ��촡�J��ƪ���m  (locaton = �s�W����ƥN�X)
             bool alreadyIn = false ;
             //cout << endl << "in" ;
             alreadyIn = sameName( temp , location )  ;     // �ˬd���S���P�˪��ǮզW

            if ( alreadyIn!=true ) {        // �ϧ_�w�g��J�P�˪��ǮզW

                if ( temp->nameMiddle.name > data[1][location] ) {
                     if ( (temp->middle!=NULL) && (temp->nameSmall.number!=0) && (temp->nameSmall.name < data[1][location]) ) {   //�����s�b�A��̤p�٤j
                        insertTree( temp->middle , location) ;
                     }
                     else if (temp->left!=NULL){          // �~�򩹥���
                        //cout << endl <<"to left:   " << data[1][location] ;
                        insertTree( temp->left , location) ;
                    }
                    // ------------------------------------------------------------- �w�g����̩�
                     else {
                            listing newList = creatListing( location ) ;
                            setRanking ( newList, temp ) ;
                            setTreeNode( temp ) ;
                            if (newList.number!=0)
                                cleanListing(newList) ;
                     }
                 } // if()

                 else if ( temp->nameMiddle.name < data[1][location] ) {
                     if ( (temp->middle!=NULL) && (temp->nameBig.number!=0) && (temp->nameBig.name > data[1][location]) ) {   //�����s�b�A��̤j�٤p
                        insertTree( temp->middle , location) ;
                     }
                     else if (temp->right!=NULL){          // �~�򩹥k��
                        insertTree( temp->right , location) ;
                    }
                    // ------------------------------------------------------------- �w�g����̩�
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

         bool sameName( node* temp ,int location ) {  // �ˬd���S���P�˪��ǮզW

             if ( temp->nameMiddle.name == data[1][location] ) {        // ���󤤶���
                temp->nameMiddle = increaseListing( temp->nameMiddle, location ) ;
                return true ;
             } // if
             else if ( temp->nameBig.number!=0 && temp->nameBig.name == data[1][location] ) {  // ������j��
                temp->nameBig = increaseListing( temp->nameBig, location ) ;
                return true ;
             } // else if
             else if (temp->nameSmall.number!=0 && temp->nameSmall.name == data[1][location] ) {  // ������p��
                temp->nameSmall = increaseListing( temp->nameSmall, location ) ;
                return true ;
             }
             else {
                return false ;
             }
         } // sameName()




         void setRanking ( listing& newList, node* temp ) {  // �]�w�`�I���Ʀr�Ʀ�

             if( newList.name > temp->nameMiddle.name) {

                    if(temp->nameBig.number!=0){                       // �̤j�Ȧs�b(�w�g����ƾ�)
                        if ( temp->nameBig.name < newList.name  ) { // �X�{��j���ƭȡA�洫��m(�����Ჾ)
                            exchangeListing( temp->nameSmall, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, temp->nameBig ) ;
                            exchangeListing( temp->nameBig, newList ) ;
                        }
                        else {                                                 // �����s�������ȡA�줤���ȫᲾ
                            exchangeListing( temp->nameSmall, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, newList ) ;
                        }
                    } // if()
                    else {                                                     //�̤j�Ȫŵ�
                        temp->nameBig = replaceList( newList, temp->nameBig ) ;
                    }
             }
             else  {
                    if(temp->nameSmall.number!=0){                          // �̤p�Ȧs�b(�w�g����ƾ�)
                        if ( temp->nameSmall.name > newList.name  ) { // �X�{��p���ƭȡA�洫��m(�����e��)
                            exchangeListing( temp->nameBig, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, temp->nameSmall ) ;
                            exchangeListing( temp->nameSmall, newList ) ;
                        }
                        else {                                                    // �����s�������ȡA�줤���ȫe��
                            exchangeListing( temp->nameBig, temp->nameMiddle ) ;
                            exchangeListing( temp->nameMiddle, newList ) ;
                        }
                    } // if()
                    else {
                        temp->nameSmall = replaceList( newList, temp->nameSmall )   ;                           // �̤p�Ȫŵ�
                    }
             }
         } // setRanking ()

         node* cutNode( node* newBig ) {          // ���θ`�I

             node* newSmall = creatNode( newBig->nameSmall ) ;

             cleanListing(newBig->nameSmall) ;
             exchangeListing( newBig->nameBig, newBig->nameMiddle ) ;
             cleanListing(newBig->nameBig) ;
             return newSmall ;

         } // cutNode()

         node* setTreeNode( node* temp ) { //�վ�`�I

             node* newBig = temp ;
             node* newSmall  = temp ;
             if( temp->nameBig.number!=0 && temp->nameSmall.number!= 0 ) {  // �ˬd�O�_�W�L3��

                 if (temp->parent!=NULL) {       // ���b��
                     setRanking ( temp->nameMiddle ,temp->parent ) ;
                     node* smallParent = setTreeNode( temp->parent ) ;
                     newSmall = cutNode( newBig ) ; // ���θ`�I�A�s�`�I���U���U�۪�������

                     if (temp->parent->middle!=NULL) {                        // �������T�ӫĤl

                         if( temp->nameMiddle.name > temp->parent->middle->nameMiddle.name ){  // �T�{�ثe���k�`�I

                             node* moveToSmall = temp->parent->middle ;        // ���ʤ��`�I
                             moveToSmall->parent = smallParent ;
                             smallParent->right = moveToSmall ;
                             temp->parent->middle = NULL ;
                             moveToSmall = temp->parent->left ;                 // ���ʥ��`�I
                             moveToSmall->parent = smallParent ;
                             smallParent ->left = moveToSmall;
                             newSmall->parent = temp->parent;
                             temp->parent->left = newSmall ;
                         }
                         else if ( temp->nameMiddle.name == temp->parent->middle->nameMiddle.name) { // �T�{�ثe�������`�I

                             node* moveToSmall = temp->parent->left ;            // ���ʥ��`�I(�̤p)
                             moveToSmall->parent = smallParent ;
                             smallParent->left = moveToSmall ;
                             temp->parent->left = newBig ;
                             temp->parent->middle = NULL ;
                             newSmall->parent = smallParent ;                   // ���ʤp�`�I(���j)
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
                     else{                                                 //�����u����ӫĤl

                        if (newBig->nameMiddle.name < temp->parent->nameMiddle.name) {  // �쬰���`�I
                            newSmall->parent = temp->parent;
                            newSmall->parent->middle = newBig ;
                            newSmall->parent->left = newSmall ;
                        }
                        else {                                                                 // �쬰�k�`�I

                            newSmall->parent = temp->parent;
                            temp->parent->middle = newSmall ;
                        }
                     } // else
                 } // if()
                 else {                     //�b�𳻡A��ʾ𳻫���
                      node* newTop = creatNode( temp->nameMiddle ) ;
                      newSmall = cutNode( newBig ) ;
                      newTop->right = newBig ;
                      newTop->left = newSmall ;
                      newBig->parent = newTop ;
                      newSmall->parent = newTop ;
                      tree = newTop ;
                      tree->parent = NULL ;             // �s�����`�I
                      height++ ;
                  } // else

             } // if
             return newSmall ;
         } // setTreeNode()


} ;

//------------------------avl tree-------------------------------


class AVL { //�H�i��t�W�١j�إߤ@�� AVL ��
  public:
    TreeNode * root;
    AVL() {  root = NULL; } //AVL
    bool isTreeEmpty() { if (root == NULL)  return true;  else  return false; } // isTreeEmpty()
    void delete_avl(){ root = NULL; delete root;} // delete_avl
    int height(TreeNode * r); //��
    int getBalanceNum(TreeNode * n);//�p�⥭�ūY��
    TreeNode * R_Rotate(TreeNode * y);//���k��
    TreeNode * L_Rotate(TreeNode * x); //������
    TreeNode * insert_recur(TreeNode * r, TreeNode * new_node);
    void insert(SchoolList::schoolType newdata);  //�N��Ƥ@�Ӥ@�Ӵ��iAVL��
    void printroot(TreeNode * r);
    TreeNode * searchDepartment(TreeNode * cur, string name) ;
    void printDepartment(TreeNode * r) ;
}; //end AVLtree �H�i��t�W�١j�إߤ@�� AVL ��

    int AVL::height(TreeNode * root) {
      if (root == NULL)
        return -1;
      else {
	    //�p��C�Ӥl�𪺰���
        int lheight = height(root -> left);
        int rheight = height(root -> right);

        if (lheight > rheight) //�����j��
          return (lheight + 1);
        else return (rheight + 1);
      } // else
    } // height

    // Get Balance factor of node N
    int AVL::getBalanceNum(TreeNode * n) { //�p�⥭�ūY��
      if (n == NULL)
        return -1;
      return height(n -> left) - height(n -> right);
    } // getBalanceNum

    TreeNode * AVL::R_Rotate(TreeNode * cur) {   //���k��
      TreeNode * lc = cur -> left;    //���p��
      TreeNode * temp = lc -> right;  //���p�Ī��k�p��(�Y�N�n�Qcur�s�쥪��

      cur -> left = temp;
      lc -> right = cur;  //�p�ı�½�����������`�I root

      return lc;  //�^�Ƿs����
    } // ���k��

    TreeNode * AVL::L_Rotate(TreeNode * cur) {   //������
      TreeNode * rc = cur -> right;   //�k�p��
      TreeNode * temp = rc -> left;   //�k�p�Ī����p��(�Y�N�n�Qcur�s��k��

      cur -> right = temp;
      rc -> left = cur;   //�p�ı�½�����������`�I root

      return rc;  //�^�Ƿs����
    } // ������

    TreeNode * AVL::insert_recur(TreeNode * cur, TreeNode * new_node) {
      if (cur == NULL) { //�p�G�O�Ĥ@�ӴN������root
        cur = new_node;
        return cur;
      } // if
      if (new_node -> key > cur -> key)  //����j���k��
        cur -> right = insert_recur(cur -> right, new_node);
	  else if (new_node -> key < cur -> key)  //����p������
        cur -> left = insert_recur(cur -> left, new_node);
	  else if (new_node -> key == cur -> key){ // ���(��t�W��)�@�˪�
        cur->data.push_back(new_node -> data[0]);  //�N�������allR���i �o�Ӹ`�I����Ʈw
        cur->num ++;                               //�ƶq�[�@
        return cur;
      } // else

      //�o��O�[�J���s��� ���ˬd�O�_�n���վ�  �q��s�W���@���ˬd�^��
      int bf = getBalanceNum(cur);  //��X���`�I�����ūY��
      if (bf > 1 && new_node -> key < cur -> left -> key) //��->���䭫 // Left Left Case
        return R_Rotate(cur);

      if (bf > 1 && new_node -> key > cur -> left -> key) { //��->���䭫 // Left Right Case
        cur -> left = L_Rotate(cur -> left);
        return R_Rotate(cur);
      } // if

      if (bf < -1 && new_node -> key > cur -> right -> key) //�t->�k�䭫 // Right Right Case
        return L_Rotate(cur);

      if (bf < -1 && new_node -> key < cur -> right -> key) { //�t->�k�䭫 // Right Left Case
        cur -> right = R_Rotate(cur -> right);
        return L_Rotate(cur);
      } // if

      return cur; //�^�ǨS�վ㪺

    } // insert_recur

  void AVL::insert(SchoolList::schoolType newdata){ //�N��Ƥ@�Ӥ@�Ӵ��iAVL��
    TreeNode * new_node = new TreeNode();
    new_node -> key = newdata.dname;     //�]�m���  //���i��|���ܦh�@�ˬ�t�W�٪�  �o�ɭn�N�L�̩�b�P�@�Ӹ`�I
    new_node -> num = 1;                 //num�O�C�Ӹ`�I���o�����(��t�W��)�Ҿ֦���data�ƶq
    new_node -> data.push_back(newdata); //�C�Ӹ`�I���O��Ʈw
    root = insert_recur(root, new_node);
  } // insert

  void AVL::printroot(TreeNode * r) {
    if (r == NULL) // Base case  1
      return;
    for ( int i = 0 ; i < root->data.size() ; i++ )   //�N��ڸ̩Ҧ���ƥ����L�X
      cout << i+1 << ": [" << r->data[i].num << "] " << r->data[i].sname << ", " << r->data[i].dname
           	<< ", " << r->data[i].type << ", " << r->data[i].level << ", " << r->data[i].nstud << endl ;
  } // printroot

  void AVL::printDepartment(TreeNode * r) {
    if (r == NULL) // Base case  1
      return;
    for ( int i = 0 ; i < r->data.size() ; i++ )   //�N��ڸ̩Ҧ���ƥ����L�X
      cout << i+1 << ": [" << r->data[i].num << "] " << r->data[i].sname << ", " << r->data[i].dname
           	<< ", " << r->data[i].type << ", " << r->data[i].level << ", " << r->data[i].nstud << endl ;
  } // printDepartment

  TreeNode * AVL::searchDepartment(TreeNode * cur, string name) {
      TreeNode * ans = NULL ;

      if (cur == NULL) {
        return ans;
      } // if

      if (name > cur -> key)  //����j���k��
        ans = searchDepartment(cur -> right, name);
	  else if ( name < cur -> key)  //����p������
        ans = searchDepartment(cur -> left, name);
	  else if (name == cur -> key){ // ���(��t�W��)�@�˪�
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
            printf("�п�J���T���� :") ;
            scanf("%d",&command) ;
        }
        if ( command == 1 ) {
            printf( "\nInput a file number ([0] Quit): " ) ;
            cin >> fileName ;
            if ( fileName !="0") {

                if ( !firsttime ) aTree.deletefile() ;
                while ( !list.readFile(fileName) ) //Ū�ɨñN�C����ƪ��W�ߤ@�Ǹ���
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

                if ( list.empty() ){ //���T�{�O�_command�L1
        	            cout << "### Choose 1 first. ###" << endl;

                } // if
                else {
                    if ( !avl.isTreeEmpty() )  // �p�G���e�w�g�عLavl��n���R��
                        avl.delete_avl();
        	        for ( int i = 0 ; i < list.allR.size() ; i++ )
                        avl.insert( list.allR[i] ); //�N��Ƥ@�Ӥ@�ӱ��iAVL��

                    //�L�X�u��t�W�١v����Ȫ� AVL�𪺾�
                        cout << "Tree height = " << avl.height(avl.root)+1 << endl ;
                    //�L�X�u��t�W�١v����Ȫ� AVL�𪺾��
                    avl.printroot(avl.root);
                    cout << endl;

                } // else


        }

        else if ( command == 3 ) {

                if ( firsttime || avl.isTreeEmpty() ){ //���T�{�O�_command�L1
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


