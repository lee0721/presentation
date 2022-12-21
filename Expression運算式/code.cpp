//DS1101ex3_��27��_10833230�����t_10844149�©y�x
#include<iostream>    // cin,cout,endl
#include <new> // new
#include<string>      // c_str,length
#include <string.h> 
#include <stdio.h> 
#include <cstdlib> // system, atoi
#include<typeinfo>
#define MAX_LEN 255   // maximum string length
using namespace std;
using std::stoi;

class expSTACK {  //���|�B��l�M�A�� 
	
  typedef struct sN {// structure of operator&parenthesis element in stack ��B��l�M�A�� 
    string value; 
    struct sN *next; // next operator||parenthesis
  } stackNode;
  
  stackNode *topPtr, *head; // only one data member
  
  public: //stack
  	
    expSTACK(): topPtr(NULL) // constructor with initialization
    {}  //end expSTACK initializer
    
    bool isEmpty() const { // decide whether stack is empty
      return topPtr == NULL;
    } //end expSTACK::isEmpty
    
    void push(string inValue) { // add one element into stack
      try {
        stackNode *newNode = new stackNode();   // �t�m�s���O����
        newNode->value = inValue ;
        newNode->next = NULL;

        if (topPtr == NULL) {                      // �Y�O�Ĥ@�ӴN��topPtr 
          topPtr = newNode;
          head = newNode;
          return;
        }
        else{
       	  topPtr->next = newNode;               // �NnewNode���blist��topPtr
       	  topPtr = newNode;
	    }
      } // end try
      
      catch (std::bad_alloc& ba) { // unable to allocate space
        std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
      } // end catch
    } // end expSTACK::push
    
    void pop() {// remove the top of stack
		stackNode *pre = head;  
		if ( pre != topPtr ) { //�N���O�Ĥ@�� 
		  while ( pre->next != topPtr )  //����head���topPtr���e�@�� 
            pre = pre->next;
          delete topPtr;
       	  topPtr = pre;
       	  topPtr->next = NULL;
		} // if
		else{
		  delete topPtr;
       	  topPtr = NULL;
       	  head = NULL;
		} 
    } // end expSTACK::pop without output parameter
    
    void getTop(string &outValue) {// get the top of stack without removal
      outValue = topPtr->value;
    } // end expSTACK::getTop
    
    bool getpre(string &outValue) {// get the pre of the top
      stackNode *pre = head;
      if ( pre != topPtr ) {  //�N���O�Ĥ@�� 
		  while ( pre->next != topPtr )  //����head���topPtr���e�@�� 
            pre = pre->next;
          outValue = pre->value; 
      } // if
      else 
        return false; //�N��{�btop�O�Ĥ@�� 
    } // end expSTACK::getTop

    
    void pop(string &outValue) {// get the top of stack and remove it
      getTop(outValue);
      stackNode *pre = head;  
      if ( pre != topPtr ) { //�N���O�Ĥ@�� 
		while ( pre->next != topPtr )  //����head���topPtr���e�@�� 
          pre = pre->next;
        delete topPtr;
       	topPtr = pre;
       	topPtr->next = NULL;
	  } // if
	  else{
		delete topPtr;
       	topPtr = NULL;
       	head = NULL;
	  } 
    } // end expSTACK::pop with output parameter
    
    
    bool isOp(){ // check whether the topPtr is an operator + - * /
     if ( isEmpty() )  //top�O�Ū��� 
       return false;
     else {
       string temp = topPtr->value; 
       if ( ( temp[0] == '+' ) || ( temp[0] == '-' ) || ( temp[0] == '*' ) || ( temp[0] == '/' ) )
         return true;
       else
         return false;
	 }
   }

   bool isPar(){ // check whether the character is a parenthesis(�A��)
     if ( isEmpty() ) //top�O�Ū��� 
       return false;
     else {
       string temp = topPtr->value; 
       if ( ( temp[0] == '(' ) || ( temp[0] == ')' ) )  
          return true;
       else
         return false;
     }
   }
    
    bool compare1( string &p ){ // ����W�@�ө�bstack��op||par 
      if ( isEmpty() ) //top�O�Ū��� 
       return false;
      else {
        string temp = topPtr->value;
        if ( (p[0] == '*' || p[0] == '/') && (temp[0] == '+' || temp[0] == '-') )
          return false;
        else {
      	  pop ();
      	  p = temp;
      	  return true;
	    } 
	    return false;
      } //else
    } //compare1()
    
    bool compare2( string &p ){ // ����W�@�ө�bstack��op||par 
      if ( isEmpty() ) //top�O�Ū��� 
       return false;
      else {
        string temp = topPtr->value;
        if ( (p[0] == '*' || p[0] == '/') && (temp[0] == '+' || temp[0] == '-') )
          push( p );
        else {
      	  pop ();
      	  push( p );
      	  p = temp;
      	  return true;
	    } 
	    return false;
      } //else
    } //compare2()
    
    bool to_openpar_ornot(){ //�O���O( 
      if ( isEmpty() ) //top�O�Ū���
        return false;
      else {
        string temp = topPtr->value; 
        if ( temp[0] == '(' )
          return true;
        else
          return false;
      }//else
	} //to_openpar_ornot()
	
	~expSTACK() {// destructor
      while (!isEmpty())
        pop();
    } // end destructor
    
}; //end expSTACK clas

class postfixexpLIST{ 
 
 typedef struct pN {// structure of each postfixexp element in list
    string value;
    struct pN *next; // next postfixexp
  } postfixNode;
  
  postfixNode *head, *tail; 
 
 public:
   postfixexpLIST(): head(NULL), tail(NULL)  { // constructor with initialization
   } //end postfixexpLIST initializer
   
   bool isEmpty() const {// decide whether list is empty
     return head == NULL;
   } //end postfixexpLIST::isEmpty
   
   void ins(string inValue) {// append one value into list
     try{
       postfixNode *newNode = new postfixNode();   // �t�m�s���O����
       newNode->value = inValue ;
       newNode->next = NULL;

       if (head == NULL) {                      // �Y�O�Ĥ@�ӴN��head 
         head = newNode;
         tail = newNode;
         return;
       }
       else{
       	 tail->next = newNode;               // �NnewNode���blist������
       	 tail = newNode;
	   }
     } // end try
     catch (std::bad_alloc& ba) {// unable to allocate space
       std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
     } // end catch
   } // end postfixexpLIST::ins
   
   void clearUp() { // clear up the entire list
     while (head != 0) {            // �q�Y������X 
        postfixNode *cur = head;
        head = head->next;
        delete cur;
        cur = NULL;
     } // while
   } // end postfixexpLIST::clearUp
   
   void printList(){
      cout << "Postfix expression:";
      postfixNode *cur = head;             // ��cur�blist�����ʨ��X
	  bool first = true;  //�O���O�Ĥ@�� 
      while (cur != NULL) {                 // ���X
        if ( first == false )
		  cout << "," ; 
        cout << " " << cur->value;
        first = false;
        cur = cur->next;
      }
      cout << endl;
   }//printList()
   
   bool isNumber( char isnum ){ // check whether the character is a number
     if ( ( isnum <= '9' ) && ( isnum >= '0' ))
       return true;
     else
       return false;
   } // isNumber

   bool isOp( char isop ){ // check whether the character is an operator + - * /
     if ( ( isop == '+' ) || ( isop == '-' ) || ( isop == '*' ) || ( isop == '/' ) )
       return true;
     else
       return false;
   } //isOp
   
   ~postfixexpLIST() { // destructor
     clearUp();
   } // end destructor
   
   void missionthree() { //calculate
      expSTACK calstack; //��stack calculate
      postfixNode *cur = head;             // ��cur�blist�����ʨ��X
      string temp; //�˫�ǥثecur��value 
      string top;  //��stack���n�Q�R����top 
      int result = 0;
      int num1 = 0, num2 = 0;
      bool haserror = false;
      while ( cur != NULL ){
      	temp = cur->value;
      	if ( isNumber( temp[0] ) ) {
      	  calstack.push( temp );
		} // if
      	else if ( isOp( temp[0] ) ) {
      	  calstack.pop( top );
      	  num2 = stoi( top );
      	  calstack.pop( top );
      	  num1 = stoi( top );
      	  if ( temp[0] == '+' )
      	    result = num1 + num2;
      	  else if ( temp[0] == '-' )
      	    result = num1 - num2;
      	  else if ( temp[0] == '*' )
      	    result = num1 * num2;
      	  else if ( temp[0] == '/' ) {
      	  	if ( num2 == 0 ) {
      	  	  haserror = true;
      	  	  cout << endl <<  "### Error: Divided by ZERO! ###" << endl;
      	  	  cout << endl <<  "### It cannot be successfully evaluated! ###" << endl;
			}
      	  	else
      	  	  result = num1 / num2;
		  }
      	  temp = to_string(result);
      	  calstack.push( temp );
		} // else if
		cur = cur->next;
	  } //while
	  if ( !haserror )
	    cout << "Answer: " << result << endl;
    } // missionthree()
   
}; //end postfixexpLIST class


class expLIST{ 

  typedef struct qN { // structure of each node in list
    string value;
    qN *next; // next element
  } listNode;
  
 listNode *head, *tail, *cur; 
 
 public:
   expLIST(): head(NULL), tail(NULL), cur(NULL)  { // constructor with initialization
   } //end expLIST initializer
   
   bool isEmpty() const {// decide whether list is empty
     return cur == NULL;
   } //end expLIST::isEmpty
   
   void ins(string inValue) {// append one value into list
     try{
       listNode *newNode = new listNode();   // �t�m�s���O����
       newNode->value = inValue ;
       newNode->next = NULL;

       if (head == NULL) {                      // �Y�O�Ĥ@�ӴN��head 
         head = newNode;
         tail = newNode;
         return;
       }
       else{
       	 tail->next = newNode;               // �NnewNode���blist������
       	 tail = newNode;
	   }
     } // end try
     catch (std::bad_alloc& ba) {// unable to allocate space
       std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
     } // end catch
   } // end expLIST::ins
   
   void clearUp() { // clear up the entire list
     while (head != 0) {            // �q�Y������X 
        listNode *cur = head;
        head = head->next;
        delete cur;
        cur = NULL;
     } // while
   } // end expLIST::clearUp
   
   void printList(){
    if (head == NULL) {                      // �p�Ghead���VNULL, ���list�S�����
        cout << "List is empty.\n";
        return;
    } // if

    listNode *cur = head;             // ��cur�blist�����ʨ��X 
    while (cur != NULL) {                 // ���X
        cout << cur->value << " ";
        cur = cur->next;
    } // while
    cout << endl;
   }//printList()
   
   ~expLIST() { // destructor
     clearUp();
   } // end destructor
   
   void removeSpace( string &str ){ //�����ť� 
     int index = 0;
     if( !str.empty()) {
       while( (index = str.find(' ',index)) != string::npos)
         str.erase(index,1);
     } // if
   } // removeSpace
   
   bool isNumber( char isnum ){ // check whether the character is a number
     if ( ( isnum <= '9' ) && ( isnum >= '0' ))
       return true;
     else
       return false;
   } // isNumber

   bool isOp( char isop ){ // check whether the character is an operator + - * /
     if ( ( isop == '+' ) || ( isop == '-' ) || ( isop == '*' ) || ( isop == '/' ) )
       return true;
     else
       return false;
   } //isOp

   bool isPar( char ispar ){ // check whether the character is a parenthesis(�A��)
     if ( ( ispar == '(' ) || ( ispar == ')' ) )  
       return true;
     else
       return false;
   } //isPar

   void missionone( string infixS, bool &haserror ) {  //check whether it is an infix expression and removespace stored as a linked list
     removeSpace( infixS ); //�����ť� 
     string temp; //��n�s�i�h 
     int openpar = 0; //���䪺�A��
	 int closepar = 0;//�k�䪺�A�� 
	 if ( infixS.empty() ) {
	 	cout <<"Error 3: there is one extra operator."<< endl;
	 	haserror = true; 
	    return;
	 } // if
     for ( int i = 0; i < infixS.size() ; i++) {
       temp.clear();
	     if ( isNumber( infixS[i] ) ) { //�B�z�Ʀr������ 
	  	   temp.append(infixS,i,1);
	  	   while ( isNumber( infixS[i+1] ) ){
	  		 temp.append(infixS,i+1,1);
	  		 i++;
		   } // while  
		   ins(temp) ;//��Ʀr�����s�i�h 
		   if ( infixS[i+1] == '(' ) { //�U�@�ӬO(���ܬOerror3 
		   	 cout <<"Error 3: there is one extra operand."<< endl;
		   	 haserror = true; 
	       	 return;
		   } // if �Ʀr��(�����n���|�h�B�� 
	     } // if 
	     else if( isOp( infixS[i] ) ) {  //�B�z�|�h�B�⪺����+ - * /
	       if ( isOp( infixS[i+1] ) ) { 
	       	 cout <<"Error 3: there is one extra operator."<< endl;
	       	 haserror = true; 
	       	 return;
		   } // if 
		   else if ( ( isOp( infixS[i] ) ) && ( (i == 0) || (i == infixS.size()-1) ) ) {      
		     cout <<"Error 3: there is one extra operator."<< endl;
	       	 haserror = true; 
	       	 return; 
		   } // else if
	       else {
	       	 temp.append(infixS,i,1);
	       	 ins(temp) ; //��operator�����s�i�h 
		   }
		   if ( infixS[i+1] == ')' ) { //�U�@�ӬO(���ܬOerror3 
		   	cout <<"Error 3: it is not infix in the parentheses."<< endl;
		   	haserror = true; 
	       	return;
		   } // if �|�h�B���)����s�@�_ 
		 } // else if
	     else if( isPar( infixS[i] ) ) { //�B�z�A��������() 
	       if ( infixS[i] == ')' ){
	       	 closepar++;
	       	 if ( openpar < closepar ){
	       	 	cout <<"Error 2: there is one extra close parenthesis."<< endl;
	       	 	haserror = true; 
	       	    return;
			 } // if 
			 else {
			   temp.append(infixS,i,1);
	       	   ins(temp) ; //��close parenthesis�����s�i�h
			 } // else
			 if ( isNumber( infixS[i+1] ) ) { //�U�@�ӬO�Ʀr���ܬOerror3 
		   	   cout <<"Error 3: there is one extra operand."<< endl;
		   	   haserror = true; 
	       	   return;
		     } // if )��Ʀr�����n���|�h�B�� 
		     if ( infixS[i+1] == '(' ) { //�U�@�ӬO(���ܬOerror3 
		   	   cout <<"Error 3: there is one extra operand."<< endl;
		   	   haserror = true; 
	       	   return;
		     } // if )��(�����n���|�h�B��
		   } // if 
	       else if ( infixS[i] == '(' ) {
	       	 openpar++;
	       	 temp.append(infixS,i,1);
	       	 ins(temp) ; //��open parenthesis�����s�i�h
	       	 if ( infixS[i+1] == ')' ) { //�U�@�ӬO(���ܬOerror3 
		   	   cout <<"Error 3: it is not infix in the parentheses."<< endl;
		   	   haserror = true; 
	       	   return;
		     } // if (��)����s�@�_ 
		     if ( isOp( infixS[i+1] ) ) { 
	       	   cout <<"Error 3: it is not infix in the parentheses."<< endl;
	       	   haserror = true; 
	       	   return;
		     } // if (�᭱���ઽ�����|�h�B�� 
		   } // else if
		 } // else if
	     else{
	       cout <<"Error 1: "<< infixS[i] <<" is not a legitimate character."<< endl;
	       haserror = true; 
	       return;
		 }//else
     } // for
     if ( openpar > closepar  ) {
     	cout << "Error 2: there is one extra open parenthesis." << endl;
     	haserror = true; 
     	return;
	 } // if 
     else if ( openpar < closepar ) {
     	cout << "Error 2: there is one extra close parenthesis." << endl;
     	haserror = true; 
		return;
	 } // else if 
	 if ( !haserror )
	   cout << "It is a legitimate infix expression." << endl;
   } // missionone
   
   
   void missiontwo( postfixexpLIST &postfix ) { // transform infix to postfix, stored as a linked list
     expSTACK stack;
     cur = head;
     string temp = cur->value; //���ثe�]�쪺value 
     while ( !isEmpty() ) {
     	if ( isNumber( temp[0] ) ) //�p�G��infixexp�O�Ʀr 
     	  postfix.ins(temp) ;//��Ʀr�����s�i�hpostfixlist 
	    else if ( isOp( temp[0] ) ){ //�p�G��infixexp�O�|�h�B��
	      if ( stack.isOp() ) {
	      	string opornot ; 
	      	if ( stack.getpre(opornot) && isOp( opornot[0] )  ) {
	      	  string copy = temp;
	      	  if ( stack.compare1( temp ) )
	      	    postfix.ins(temp) ;//��op�s�i�hpostfixlist
	      	  if ( stack.compare2( copy ) )    //
	      	    postfix.ins(copy) ;//��op�s�i�hpostfixlist
			} // if
			else
			  if ( stack.compare2( temp ) )
	      	    postfix.ins(temp) ;//��op�s�i�hpostfixlist
		  } // if
	      else {
	      	stack.push( temp );
		  } // else
		} // else if
		else if ( isPar( temp[0] ) ){ //�p�G��infixexp�O�A��
		  if ( temp[0] == '(' ) 
		  	stack.push( temp );
		  else{
		  	while ( !stack.to_openpar_ornot() ) { //���openpar�H�e��op����X�� 
		  	  stack.pop( temp );
		  	  postfix.ins(temp) ;//��b���|�n�Q�R����op�s�i�hpostfixlist
			} // while
			if ( stack.to_openpar_ornot() )  //����|�̪�openpar�R�� 
			  stack.pop();
		  } // else
		} // else if
	    cur = cur->next; //�U�@��infixexp 
	    if ( !isEmpty() ) 
	      temp = cur->value;
	 } //while
	 while ( !stack.isEmpty() ) { //��ѤU��op����X�� 
		stack.pop( temp );
		postfix.ins(temp) ;//��b���|�n�Q�R����op�s�i�hpostfixlist
     } // while
	 postfix.printList();
	 stack.~expSTACK();
   } // missiontwo()
   
}; //end expLIST class

int main() {
	int command = 0; //�Ĥ@��input(0, 1, 2)
	do {  
	  string infixS, postfixS;
	  expLIST list ;
	  postfixexpLIST postfix;
	  bool haserror = false; //�O�_�����~ 
	  cout << endl << "* Arithmetic Expression Evaluator *";
	  cout << endl << "* 0. QUIT                         *";
	  cout << endl << "* 1. Infix2postfix Evaluation     *"; 
	  cout << endl << "***********************************"; 
	  cout << endl << "Input a choice(0, 1): "; 
	  cin >> command;  //cin�Ĥ@��input(0, 1)
      cin.ignore(MAX_LEN, '\n');   //�M��input buffer 
	  switch(command){	
	  	case 0 : break;
	  	case 1 :   
	  	  cout << endl << "Input an infix expression: ";
	  	  getline(cin, infixS);
	  	  list.missionone( infixS, haserror );
	  	  if ( !haserror ) {
	  	  	list.missiontwo( postfix );
	  	  	postfix.missionthree();
		  }
	  	  infixS.clear();
	  	  list.~expLIST();
	  	  postfix.~postfixexpLIST();
		  break;
	    default : cout << endl << "Command does not exist!" << endl; //input 0,1�H�~�� 
	  } // end switch
	} while ( command != 0 );  //'0':stop the program
	system ( "pause" );        // pause the display
	return 0;
} // end main


