//�t�ε{���@�~�G_10833230�����t 
#include<iostream>    // cin,cout,endl
#include<string>      // c_str,length
#include<string.h>    //strcpy
#include<stdio.h>    
#include<stdlib.h>    //atoi()
#include<cstdlib>     //strtoul,system
#include <vector>
#include<fstream>
#include<typeinfo>

#define MAX_TOKENS 30 //���p�@��{���̦h���X�� tokens
#define MAX_TOKEN_GROUP 100 //���p�̦h�X�� 
 
using namespace std;
using std::string;

typedef char STRING20 [20]; //�u�r��A�̦h19�Ӧr��
typedef char STRING200 [200]; //���r��A�̦h199�Ӧr��

struct Sicxe_Instruction_Set {
	string instruction;
	int format = 0; //format1�� format2��format3/4(���]�w��3 �᭱�P�_��+�N��4
	int opformat = 0; //�᭱op���Φ�  (1) x (�S����) [1/3/4]
	                  //              (2) m          [3/4]
					  //              (3) r1         [2]
					  //              (4) r1,r2      [2]
					  //              (5) r1,n       [2]
					  //              (6) n          [2]
	string objectcode;
}; // Sicxe_Instruction_Set

void Sicxe_Instruction_input( Sicxe_Instruction_Set sicxe[59] ) {
	ifstream newfile; 
	newfile.open("Sicxe_Instruction_Set.table"); //�}���ɮ�
	int num = 0; // �h�֭ӫ��O 
	for ( int i = 0 ; i < 236 ; i++) {
	  newfile >> sicxe[num].instruction; //�N�@��@�檺�r��Ū�ɶistruct�̭�  ���O 
	  newfile >> sicxe[num].format; //�N�@��@�檺�r��Ū�ɶistruct�̭�  �Φ� 
	  newfile >> sicxe[num].opformat; //�N�@��@�檺�r��Ū�ɶistruct�̭�  op�Φ� 
	  newfile >> sicxe[num].objectcode; //�N�@��@�檺�r��Ū�ɶistruct�̭�  code
	  num++;
	} //for 
	newfile.close();//Ū�ɧ��������ɮ�
}  // Sicxe_Instruction_input

struct Sic_Instruction_Set {
	string instruction;
	string objectcode;
}; // Sic_Instruction_Set

void Sic_Instruction_input( Sic_Instruction_Set sic[26] ) {
	ifstream newfile; 
	newfile.open("Sic_Instruction_Set.table"); //�}���ɮ�
	int num = 0; // �h�֭ӫ��O 
	for ( int i = 0 ; i < 52 ; i++) {
	  newfile >> sic[num].instruction; //�N�@��@�檺�r��Ū�ɶistruct�̭�  ���O 
	  newfile >> sic[num].objectcode; //�N�@��@�檺�r��Ū�ɶistruct�̭�  code
	  num++;
	} //for 
	newfile.close();//Ū�ɧ��������ɮ�
}  // Sic_Instruction_input

void Sicxe_Instruction_print( Sicxe_Instruction_Set sicxe[59] ) {  //test
	for ( int i = 0 ; i < 59 ; i++) {
	  cout << sicxe[i].instruction << " "; //�N�@��@�檺�r��Ū�ɶistruct�̭�  ���O 
	  cout << sicxe[i].format << " "; //�N�@��@�檺�r��Ū�ɶistruct�̭�  op�Φ� 
	  cout << sicxe[i].opformat << " "; //�N�@��@�檺�r��Ū�ɶistruct�̭�  �Φ� 
	  cout << sicxe[i].objectcode; //�N�@��@�檺�r��Ū�ɶistruct�̭�  code
	  cout << endl ;
	} //for 
}  // Sicxe_Instruction_print

void Sic_Instruction_print( Sic_Instruction_Set sic[26] ) {  //test
	for ( int i = 0 ; i < 26 ; i++) {
	  cout << sic[i].instruction << " "; //�N�@��@�檺�r��Ū�ɶistruct�̭�  ���O 
	  cout << sic[i].objectcode; //�N�@��@�檺�r��Ū�ɶistruct�̭�  code
	  cout << endl ;
	} //for 
}  // Sic_Instruction_print

struct Token{
    string value;    
    int tokentype = 0;  //��b����table 
    int tokenvalue = 0; //��btable�̲ĴX��index 
}; // Token

struct Literal{
	int location = 0; //������}(�Q�i�쪺�ҥH�᭱�n�令�Q���i��) 
	string c_x_w ;
    string label;    
    string WORDorBYTE;
    string literal;
}; // Literal

struct Tokens{
    unsigned amount; //�����o�� source ������ڦ��X�� token
    int label_length = 0; //�����o����O���� 
    string error;    //�����o�� source ���J�쪺error 
    bool forwardreference = false; //���S���ݭn forward reference
    bool end = false;  //�o�榳end 
    bool base = false;  //�o�榳base
    bool comment = false; //�o��O���� 
    bool EQU = false; 
    bool START = false ;
    bool pseudo = false;
    //--------------------------------------------------
    string c_x_w ;
    string sourcestatement; //�����o��{������l�{�� 
    int b = 0;   //�O�_���ϥ� base register 
    int p = 0;   //�O�_���ϥ� program counter
    int x = 0;   //�O�_���ϥ� index register 
    int i = 0;   //�O�_���ϥ� immediate mode
	int n = 0;   //�O�_���ϥ� indirect mode
	int line = 0;
	string setedline;  //�ɧ��ťժ�line 
    int location = 0; //������}(�Q�i�쪺�ҥH�᭱�n�令�Q���i��) 
    string hex_location; //�Q���i���}
    string objectcode;  //����objectcode(�Q���i��) 
    //--------------------------------------------------
    int format = 0 ; //format1234
    int opformat = 0; //�᭱op���Φ�
    string label; //�o��{���X�� Label�A�p�G�S�����ܴN�O�Ŧr��
    string ins; //�o��{���X�� "���O" �� "�������O"�A�p�G�S�����ܴN�O�Ŧr��
    string group1;
    string group2;
    Literal literal;
    //--------------------------------------------------
    Token tokens[MAX_TOKENS]; //��ڬ��� token ���a��
};  // Tokens

struct Packed_Token{ //�`�N�o�ӦW�� -> "�]�˹L�� tokens"
    unsigned amount; //��ڤW Tokens Group ���ƶq�A�S�����ܴN�O 0
    int longestnum = 0; //�����̪���source 
    bool end = false;
    bool base = false;
    string base_label;
    string base_hexlocation;
    int basenum = 0;
    Tokens token_groups[MAX_TOKEN_GROUP]; //�u���ΨӥΨӰO�� tokens groups ���a��
}; // Packed_Token

struct Table{
    int index;
    string value;
}; //Table

void removespace( string &str ){ //�����ť� //test
  int index = 0;
    if( !str.empty()) {
      while( (index = str.find(' ',index)) != string::npos)
        str.erase(index,1);
    } // if
} // removespace

void tableinput( Table table1[59], Table table2[9], Table table3[9], Table table4[13] ) {  //get the table1.2.3.4 
	ifstream newfile; 
	newfile.open("Table1.table"); //�}���ɮ�
	for ( int i = 1 ; i < 60 ; i++) {
	  newfile >> table1[i-1].value; //�N�@��@�檺�r��Ū�ɶistruct�̭� 
	  table1[i-1].index = i;
	} //for 
	newfile.close();//Ū�ɧ��������ɮ�
	
	newfile.open("Table2.table"); //�}���ɮ�
	for ( int i = 1 ; i < 10; i++) {
	  newfile >> table2[i-1].value; //�N�@��@�檺�r��Ū�ɶistruct�̭� 
	  table2[i-1].index = i;
	} //for 
	newfile.close();//Ū�ɧ��������ɮ�
	
	newfile.open("Table3.table"); //�}���ɮ�
	for ( int i = 1 ; i < 10; i++) {
	  newfile >> table3[i-1].value; //�N�@��@�檺�r��Ū�ɶistruct�̭� 
	  table3[i-1].index = i;
	} //for 
	newfile.close();//Ū�ɧ��������ɮ�
	
	newfile.open("Table4.table"); //�}���ɮ�
	for ( int i = 1 ; i < 14; i++) {
	  newfile >> table4[i-1].value; //�N�@��@�檺�r��Ū�ɶistruct�̭� 
	  table4[i-1].index = i;
	} //for 
	newfile.close();//Ū�ɧ��������ɮ�
} // tableinput

string to_upper( string token ) { //���j�g 
	for ( int a = 0; a < token.length() ; a++ ) {
        if (islower(token[a]))                 // �Y���p�g�r��
            token[a] = toupper(token[a]); 
    } // for 
    return token;
} // to_upper

string to_lower( string token ) { //���p�g 
	for ( int a = 0; a < token.length() ; a++ ) {
        if (isupper(token[a]))                 // �Y���j�g�r��
            token[a] = tolower(token[a]); 
    } // for 
    return token;
} // to_lower

bool find( string token, Table table1[59], Table table2[9], Table table3[9], Table table4[13], 
          Table table5[100], Table table6[100], Table table7[100], int &tokentype, int &tokenvalue ){
    string upper = to_upper(token); 
	string lower = to_lower(token);     	
    for ( int i = 0 ; i < 59; i++) { // �htable1�䦹token
	  if ( lower == table1[i].value ) {
	  	tokentype = 1;
	  	tokenvalue = table1[i].index;
	  	return true;
	  } // if
	} //for 
	
	for ( int i = 0 ; i < 9; i++) { // �htable2�䦹token
	  if ( upper == table2[i].value ) {
	  	tokentype = 2;
	  	tokenvalue = table2[i].index;
	  	return true;
	  } // if
	} //for 

    for ( int i = 0 ; i < 9; i++) { // �htable3�䦹token
	  if ( upper == table3[i].value ) {
	  	tokentype = 3;
	  	tokenvalue = table3[i].index;
	  	return true;
	  } // if
	} //for 

	for ( int i = 0 ; i < 13; i++) { // �htable4�䦹token
	  if ( token == table4[i].value ) {
	  	tokentype = 4;
	  	tokenvalue = table4[i].index;
	  	return true;
	  } // if
	} //for 
	for ( int i = 0 ; i < 100; i++) { // �htable5�䦹token
	  if ( upper == table5[i].value ) {
	  	tokentype = 5;
	  	tokenvalue = table5[i].index;
	  	return true;
	  } // if
	} //for 
	for ( int i = 0 ; i < 100; i++) { // �htable6�䦹token
	  if ( upper == table6[i].value ) {
	  	tokentype = 6;
	  	tokenvalue = table6[i].index;
	  	return true;
	  } // if
	} //for 
	for ( int i = 0 ; i < 100; i++) { // �htable7�䦹token
	  if ( token == table7[i].value ) {
	  	tokentype = 7;
	  	tokenvalue = table7[i].index;
	  	return true;
	  } // if
	} //for 
	return false;
} // find

bool iswhitespce( char iswhitespace ){ // check whether the character is a number
  if ( iswhitespace == ' ' )
    return true;
  if ( iswhitespace == '\t' )
    return true;
  if ( iswhitespace == '\n' )
    return true;
  else
    return false;
} // iswhitespce

bool isNumber( string isnum ){ // check whether the character is a number
  if ( ( isnum[0] <= '9' ) && ( isnum[0] >= '0' ))
    return true;
  else
    return false;
} // isNumber

bool isLetter( string islet ){ // check whether the character is a number
  if ( ( islet[0] >= 'a' ) && ( islet[0] <= 'z' ))
  	return true;
  if ( ( islet[0] >= 'A' ) && ( islet[0] <= 'Z' ))
  	return true;
  else
    return false;
} // isLetter

bool isOp( char isop ){ // check whether the character is table4
     if ( ( isop == ',' ) || ( isop == '+' ) || ( isop == '-' ) || ( isop == '*' ) 
	           || ( isop == '/' ) || ( isop == ':' ) || ( isop == ';' ) || ( isop == '?' ) 
			      || ( isop == '@' ) || ( isop == '.' ) || ( isop == '=' ) || ( isop == '#' ) || ( int(isop) == 39 ) )
       return true;
     else
       return false;
} //isOp


void instable( string token, Table table[100], int &tokentype, int &tokenvalue){ //
  bool alreadyhave = false;
  int a = 0;
  for ( a = 0 ; a < 100 ; a++)  //�����ݦۤv��table�]�\�� 
    if ( token == table[a].value )
      alreadyhave = true;
  if ( alreadyhave )
  	tokenvalue = a;
  else {
  	int num = 0; //�˦�token��ascii�X
    for ( int i = 0 ; i < token.length(); i++) 
   	  num = num + int(token[i]);
    num = num % 100;
    if ( !table[num].value.empty() )
      num++;
    table[num].value = token;
    table[num].index = num;
    tokenvalue = num;
  } // else
} // instable

void removewhitespace( string &str ){ //�����ť�/tab/���� 
  if ( str[str.length()-1] == ' ' )  {
  	int index = 0;
    if( !str.empty()) {
      while( (index = str.find(' ',index)) != string::npos)
        str.erase(index,1);
    } // if
  } // if
  else if ( str[str.length()-1] == '\t' )  {
  	int index = 0;
    if( !str.empty()) {
      while( (index = str.find('\t',index)) != string::npos)
        str.erase(index,1);
    } // if
  } // else if
  else if ( str[str.length()-1] == '\n' )  {
  	int index = 0;
    if( !str.empty()) {
      while( (index = str.find('\n',index)) != string::npos)
        str.erase(index,1);
    } // if
  } // else if
} // removewhitespace

bool onespace ( string token ) { //�O�_�u�O�@�Ӫť�
  bool check = false;
  if ( token.length() == 1 ) 
    if ( token[0] == ' ' )
	   check = true;
  if ( check == true )
    return true;
  return false;
} // onespace

void ins_Tokens( Token &tok, string token, int type, int value ){
  tok.value = token;
  tok.tokentype = type;
  tok.tokenvalue = value;
} // ins_Tokens

void ins_packer( Tokens &toks, string token, int tokentype, int tokenvalue ){
  ins_Tokens(toks.tokens[toks.amount], token, tokentype, tokenvalue);
  //cout << toks.tokens[toks.amount].value << endl ; // test
  //cout << toks.tokens[toks.amount].tokentype << endl ; // test
  //cout << toks.tokens[toks.amount].tokenvalue << endl ; // test
  toks.amount++;
} // ins_packer

string getTokens( Token tok ) { //TEST 
	string outputdemo("(,)");  //���g�@�Ӧr��demo
	outputdemo.insert(1, std::to_string(tok.tokentype)); //�Ntokentype���Joutputdemo 
	outputdemo.insert(outputdemo.length()-1, std::to_string(tok.tokenvalue)); //�Ntokenvalue���Joutputdemo
	outputdemo.insert(0, tok.value); //�Ntokenvalue���Joutputdemo
	return outputdemo;
} // getTokens

string getpacker( Tokens toks ) { //TEST
	string outputdemo;
	for ( int b = 0 ; b < toks.amount; b++) {
		//cout << getTokens( toks.tokens[b]) << endl ; // test
		string token = getTokens( toks.tokens[b]) ; 
		outputdemo.insert(outputdemo.length(), token); //�Ntokenvalue���Joutputdemo
		outputdemo.insert(outputdemo.length(), " "); //�Ntokenvalue���Joutputdemo
	} // for
	return outputdemo;
} // getpacker

void DecToHexa(int n, string &hex){ // �N�Q�i����Q���i�� de_to_hex 
    // char array to store hexadecimal number
    char hexaDeciNum[100];
 
    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;
 
        // storing remainder in temp variable.
        temp = n % 16;
 
        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        } // if
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        } // else
 
        n = n / 16;
    } // while (n != 0)
 
    // printing hexadecimal number array in reverse order
    for (int j = i - 1; j >= 0; j--)
        hex.append( 1, hexaDeciNum[j] ) ;
} // DecToHexa

void HexToDe( string s, int &sum ){
  int t = 0;
  for(int i=0;s[i];i++){
    if(s[i]<='9')
      t=s[i]-'0';
    else
      t=s[i]-'A'+10;
    sum=sum*16+t;
  } //for
} // HexToDe

void negativeDecToHexa( int disp, string &hexdisp ){
    int temp = 0;
    int de = 0;
    string hex;
    string str;
    disp = - disp;
    DecToHexa(disp, str);
    for ( int i = 0; i < str.length() ; i++ ) {
    	de = 0;
    	string t;
    	t.append(1,str[i]);
    	if ( i == 0 ) {
    	  HexToDe( t, de );
    	  temp = 15 - de ;
		}
		else {
			HexToDe( t, de );
			temp = 15 - de + 1 ;
		}
		DecToHexa(temp, hex);
		hexdisp.insert(hexdisp.length(),hex);
		hex.clear();
	} // for
} // negativeDecToHexa

void BinToHexa( string &xbpe ){  //�N�G�i����Q���i��bin_to_hex
  if ( xbpe == "0000" )
    xbpe = "0";
  else if ( xbpe == "0001" )
    xbpe = "1";
  else if ( xbpe == "0010" )
    xbpe = "2";
  else if ( xbpe == "0011" )
    xbpe = "3";
  else if ( xbpe == "0100" )
    xbpe = "4";
  else if ( xbpe == "0101" )
    xbpe = "5";
  else if ( xbpe == "0110" )
    xbpe = "6";
  else if ( xbpe == "0111" )
    xbpe = "7";
  else if ( xbpe == "1000" )
    xbpe = "8";
  else if ( xbpe == "1001" )
    xbpe = "9";
  else if ( xbpe == "1010" )
    xbpe = "A";
  else if ( xbpe == "1011" )
    xbpe = "B";
  else if ( xbpe == "1100" )
    xbpe = "C";
  else if ( xbpe == "1101" )
    xbpe = "D";
  else if ( xbpe == "1110" )
    xbpe = "E";
  else if ( xbpe == "1111" )
    xbpe = "F";
} // BinToHexa

void HexaToBin( string &t ){  //�N�G�i����Q���i��bin_to_hex
  if ( t == "0" )
    t = "0000";
  else if ( t == "1" )
    t = "0001";
  else if ( t == "2" )
    t = "0010";
  else if ( t == "3" )
    t = "0011";
  else if ( t == "4" )
    t = "0100";
  else if ( t == "5" )
    t = "0101";
  else if ( t == "6" )
    t = "0110";
  else if ( t == "7" )
    t = "0111";
  else if ( t == "8" )
    t = "1000";
  else if ( t == "9" )
    t = "1001";
  else if ( t == "A" )
    t = "1010";
  else if ( t == "B" )
    t = "1011";
  else if ( t == "C" )
    t = "1100";
  else if ( t == "D" )
    t = "1101";
  else if ( t == "E" )
    t = "1110";
  else if ( t == "F" )
    t = "1111";
} // HexaToBin


//-----------------------sicxe----------------------------------

void sicxe_Search_Instruction_Set( Sicxe_Instruction_Set sicxe[59], string token, int &format, int &opformat, string &objectcode ) {
	string lower = to_lower(token);
	int num = 0;
	for ( int i = 0 ; i < 59 ; i++ )
	  if ( sicxe[i].instruction == lower )
	    num = i;
	if ( format == 0 )
	  format = sicxe[num].format;
	opformat = sicxe[num].opformat;
	objectcode = sicxe[num].objectcode;
} // sicxe_Search_Instruction_Set

void sicxe_setlocation ( int n, string &hex ) {
	DecToHexa(n, hex);
	string result;
    if ( hex.length() != 4 ) {
      for ( int i = 4-hex.length() ; i > 0 ; i-- ){
    	if ( !hex.empty() ) {
    	  result.insert( 0 , hex);
    	  hex.clear();
		} // if
    	result.insert( 0 , "0");
	  } // for
	} // if
	else 
      result = hex;
	hex = result;
} //sicxe_setlocation

void sicxe_setline( string &setedline, int line ) {
	string result;
	string temp = std::to_string(line);
    if ( temp.length() != 4 ) {
      for ( int i = 4-temp.length() ; i > 0 ; i-- ){
    	if ( !temp.empty() ) {
    	  result.insert( 0 , temp);
    	  temp.clear();
		} // if
    	result.insert( 0 , " ");
	  } // for
	} // if
	else 
      result = temp;
	setedline = result;
} //sicxe_setline

void sicxe_gettokenvalue( Tokens toks, int &r1, string token ){
	for ( int i = 0; i < toks.amount ; i++ )
	  if ( token == toks.tokens[i].value )
	    r1 = toks.tokens[i].tokenvalue;
	r1--;
} // sicxe_gettokenvalue

void sicxe_set_xbpe( Tokens &toks ) {
	string x = std::to_string(toks.x);
	string b = std::to_string(toks.b);
	string p = std::to_string(toks.p);
	string e;
	if ( toks.format == 3 )
	  e = "0";
	else if ( toks.format == 4 )
	  e = "1";
	x.insert(x.length(),b);
	x.insert(x.length(),p);
	x.insert(x.length(),e);
	BinToHexa( x );  //�G�i����Q���i�� 
	toks.objectcode.insert(toks.objectcode.length(),x);
} //sicxe_set_xbpe

void sicxe_set_disp( Packed_Token token_packer, Tokens toks, string &hexdisp ){
  int disp = 0;
  int base_location = 0;
  HexToDe( hexdisp, base_location );
  if ( !toks.forwardreference && !token_packer.base_hexlocation.empty() && token_packer.end ) { //base
  	 for ( int i = 0; i < token_packer.amount ; i++ ) 
    	if ( toks.group1 == token_packer.token_groups[i].label )
    	  disp = token_packer.token_groups[i].location - base_location; 
     hexdisp.clear();
     if ( disp > 0 )
       DecToHexa(disp, hexdisp);
     else
       negativeDecToHexa( disp, hexdisp );
  } // 
  else if ( !toks.forwardreference ) { //�|�O�t�� 
     for ( int i = 0; i < token_packer.amount ; i++ ) 
    	if ( toks.group1 == token_packer.token_groups[i].label )
    	  disp = token_packer.token_groups[i].location - ( toks.location + toks.label_length ); 
     negativeDecToHexa( disp, hexdisp );
  } // else if
  else { //�|�O���� 
    for ( int i = 0; i < token_packer.amount ; i++ ) 
    	if ( toks.group1 == token_packer.token_groups[i].label )
    	  disp = token_packer.token_groups[i].location - ( toks.location + toks.label_length ); 
	DecToHexa(disp, hexdisp);
  } // else
} //  sicxe_set_disp

void sicxe_set_address( Packed_Token token_packer, Tokens toks, string &address ){
    for ( int i = 0; i < token_packer.amount ; i++ ) 
      if ( toks.group1 == token_packer.token_groups[i].label )
    	address = token_packer.token_groups[i].hex_location; 
} //  sicxe_set_address

        //(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base       ->�]�wp=1
		//(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base         ->�]�wb=1
		//(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base   ->�]�wp=1

void sicxe_setcode( Packed_Token token_packer, Tokens &toks ) {
	int r1 = 0;
	int r2 = 0;
	string disp;
	string address;
	if ( toks.format == 2 ) {
		if ( toks.opformat == 3 ) {
			sicxe_gettokenvalue( toks, r1 ,toks.group1 );
			toks.objectcode.insert( 2, std::to_string(r1) );
			toks.objectcode.insert( 3, "0" );
		} // if
	    else if ( toks.opformat == 4 ) {
	    	sicxe_gettokenvalue( toks, r1 ,toks.group1 );
	    	sicxe_gettokenvalue( toks, r2 ,toks.group2 );
	    	toks.objectcode.insert( 2, std::to_string(r1) );
			toks.objectcode.insert( 3, std::to_string(r2) );
		} // else if
		else if ( toks.opformat == 5 ) {
			sicxe_gettokenvalue( toks, r1 ,toks.group1 );
	    	toks.objectcode.insert( 2, std::to_string(r1) );
			toks.objectcode.insert( 3, toks.group2 );
		} // else if
		else if ( toks.opformat == 6 ) {
			toks.objectcode.insert( 2, toks.group1 );
			toks.objectcode.insert( 3, "0" );
		} // else if
	} // if
	else if ( toks.format == 3 ) {
		if ( toks.opformat == 2 ) {
		  if ( toks.n == 1 && toks.i == 1 ) { //  n=1i=1
		    if ( isNumber( toks.group1 ) ) {
		      string temp;
		      temp.append(1,toks.objectcode[1]);
		      if ( temp == "0" ) { // 0000 0 -> 0011 3
		  	    toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	    toks.objectcode.insert(toks.objectcode.length(),"3");
		  	    if ( toks.group1.length() == 1 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"000");
		  	    else if ( toks.group1.length() == 2 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"00");
		  	    else if ( toks.group1.length() == 3 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"0");
		  	    toks.objectcode.insert(toks.objectcode.length(),toks.group1);
			  } // if
			  else if ( temp == "4" ) { // 0100 4 -> 0111 7
		  	    toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	    toks.objectcode.insert(toks.objectcode.length(),"7");
		  	    if ( toks.group1.length() == 1 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"000");
		  	    else if ( toks.group1.length() == 2 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"00");
		  	    else if ( toks.group1.length() == 3 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"0");
		  	    toks.objectcode.insert(toks.objectcode.length(),toks.group1);
			  } // else if
		  	  else if ( temp == "8" ) { // 1000 8 -> 1011 B
		  	    toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	    toks.objectcode.insert(toks.objectcode.length(),"B");
		  	    if ( toks.group1.length() == 1 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"000");
		  	    else if ( toks.group1.length() == 2 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"00");
		  	    else if ( toks.group1.length() == 3 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"0");
		  	    toks.objectcode.insert(toks.objectcode.length(),toks.group1);
			  } // else if
			  else if ( temp == "C" ) { // 1100 C -> 1111 F
		  	    toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	    toks.objectcode.insert(toks.objectcode.length(),"F");
		  	    if ( toks.group1.length() == 1 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"000");
		  	    else if ( toks.group1.length() == 2 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"00");
		  	    else if ( toks.group1.length() == 3 )
		  	      toks.objectcode.insert(toks.objectcode.length(),"0");
		  	    toks.objectcode.insert(toks.objectcode.length(),toks.group1);
			  } // else if
			} // if	   
			else {  
		    string temp;
		    temp.append(1,toks.objectcode[1]);
		  	if ( temp == "0" ) { // 0000 0 -> 0011 3
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"3");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.p == 1 && toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( toks.p == 1 && !toks.forwardreference ) { //(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base ->p=1 
		  	    sicxe_set_disp(token_packer, toks, disp);   //�p�G���ݭn forwardreference�᭱disp�N�����]�w #Immediate Addressing 
				toks.objectcode.insert(toks.objectcode.length(),"F");
				toks.objectcode.insert(toks.objectcode.length(),disp);
		      } // else if
		  	  else if ( toks.b == 1 ) //(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base    ->b=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //base�i��ݭn forwardreference�᭱disp�N���]�w000
			} // if
			else if ( temp == "4" ) { // 0100 4 -> 0111 7
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"7");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.p == 1 && toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( toks.p == 1 && !toks.forwardreference ) { //(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base ->p=1 
		  	    sicxe_set_disp(token_packer, toks, disp);   //�p�G���ݭn forwardreference�᭱disp�N�����]�w #Immediate Addressing  
		  	    toks.objectcode.insert(toks.objectcode.length(),"F");
				toks.objectcode.insert(toks.objectcode.length(),disp);
		      } // else if
		  	  else if ( toks.b == 1 ) //(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base    ->b=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //base�i��ݭn forwardreference�᭱disp�N���]�w000
			} // else if
			else if ( temp == "8" ) { // 1000 8 -> 1011 B
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"B");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.p == 1 && toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( toks.p == 1 && !toks.forwardreference ) { //(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base ->p=1 
		  	    sicxe_set_disp(token_packer, toks, disp);   //�p�G���ݭn forwardreference�᭱disp�N�����]�w #Immediate Addressing  
                toks.objectcode.insert(toks.objectcode.length(),"F");
				toks.objectcode.insert(toks.objectcode.length(),disp);
		      } // else if
		  	  else if ( toks.b == 1 ) //(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base    ->b=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //base�i��ݭn forwardreference�᭱disp�N���]�w000
			} // else if
			else if ( temp == "C" ) { // 1100 C -> 1111 F
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"F");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.p == 1 && toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( toks.p == 1 && !toks.forwardreference ) { //(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base ->p=1 
		  	    sicxe_set_disp(token_packer, toks, disp);   //�p�G���ݭn forwardreference�᭱disp�N�����]�w #Immediate Addressing  
                toks.objectcode.insert(toks.objectcode.length(),"F");
				toks.objectcode.insert(toks.objectcode.length(),disp); 
		      } // else if
		  	  else if ( toks.b == 1 ) //(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base    ->b=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"000");  //base�i��ݭn forwardreference�᭱disp�N���]�w000
			} // else if // 1100 C -> 1111 F
		} // else
		  } // else if
		} //  if
	} // else if
	else if ( toks.format == 4 ) {
		if ( toks.opformat == 2 ) {
		  if ( toks.n == 1 && toks.i == 1 ) { //  n=1i=1
		    string temp;
		    temp.append(1,toks.objectcode[1]);
		  	if ( temp == "0" ) { // 0000 0 -> 0011 3
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"3");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"00000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w00000
			  else if ( !toks.forwardreference ) { //(1)	�e���p�G��o��
		  	    sicxe_set_address(token_packer, toks, address); 
		  	    toks.objectcode.insert(toks.objectcode.length(),"0");
				toks.objectcode.insert(toks.objectcode.length(),address); 
		      } // else if
			} // if
			else if ( temp == "4" ) { // 0100 4 -> 0111 7
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"7");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"00000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( !toks.forwardreference ) { //(1)	�e���p�G��o��
			    sicxe_set_address(token_packer, toks, address); 
		  	    toks.objectcode.insert(toks.objectcode.length(),"0");
				toks.objectcode.insert(toks.objectcode.length(),address); 
		      } // else if
		    } // else if
			else if ( temp == "8" ) { // 1000 8 -> 1011 B
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"B");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"00000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( !toks.forwardreference ) { //(1)	�e���p�G��o��
                sicxe_set_address(token_packer, toks, address); 
		  	    toks.objectcode.insert(toks.objectcode.length(),"0");
				toks.objectcode.insert(toks.objectcode.length(),address); 
		      } // else if
		    } // else if
			else if ( temp == "C" ) { // 1100 C -> 1111 F
		  	  toks.objectcode.erase(toks.objectcode.length()-1,1);
		  	  toks.objectcode.insert(toks.objectcode.length(),"F");
		  	  sicxe_set_xbpe( toks );
		  	  if ( toks.forwardreference ) //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base  ->p=1 
		  	    toks.objectcode.insert(toks.objectcode.length(),"00000");  //�p�G�ݭn forwardreference�᭱disp�N���]�w000
			  else if ( !toks.forwardreference ) { //(1)	�e���p�G��o��
			    sicxe_set_address(token_packer, toks, address); 
		  	    toks.objectcode.insert(toks.objectcode.length(),"0");
				toks.objectcode.insert(toks.objectcode.length(),address); 
		      } // else if
		    } // else if
		  } // if
		} // if
	} // else if
} //sicxe_setcode

bool sicxe_Set_p_b ( Packed_Token token_packer, Tokens &toks, string token ){  // format3 �ݭn�]�wbp �Ntoken���e���h�䦳�S���@��label 
		//(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base       ->�]�wp=1
		//(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base         ->�]�wb=1
		//(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base   ->�]�wp=1
	if ( toks.format == 3 ) {
	  int num = 0;
	  for ( int i = 0 ; i < token_packer.amount ; i++ ){
		num = i;
		if ( token == token_packer.token_groups[i].label )
		  break;
	  } // for
	  if ( token == token_packer.token_groups[num].label ) {
		if ( token_packer.base )  //(2)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)����base         ->�]�wb=1
		  toks.b = 1;
		else //(1)	�e���p�G��o��(�N��ت�-�ӷ�(�U�@��)�|�O�t��)�B�S��base       ->�]�wp=1
		  toks.p = 1;
		return true;
	  } // ��o��
	  else { //(3)	�e���p�G�䤣��(�N��ت�-�ӷ�(�U�@��)�|�O����)���ަ��S��base   ->�]�wp=1
		toks.p = 1;
		return false;
	  } // else �䤣��	
    } // if
    else if ( toks.format == 4 ){
      for ( int i = 0 ; i < token_packer.amount ; i++ ){
		if ( token == token_packer.token_groups[i].label )
		  return true;
	  } // for
	  return false;
	} // else if
	
} // sicxe_Set_p_b

void sicxe_RecordAndSyntax( Packed_Token &token_packer, Tokens &toks, Sicxe_Instruction_Set sicxe[59] ) { 
  if ( toks.tokens[0].tokentype == 5 ) { //��label 
  	toks.label = toks.tokens[0].value;
  	if ( toks.tokens[1].tokentype == 4 ) { // ��label +�}�Y (format4) 
  	  toks.format = 4;
  	  toks.label_length = 4;
  	  toks.ins = toks.tokens[2].value;
  	  sicxe_Search_Instruction_Set( sicxe, toks.tokens[2].value, toks.format, toks.opformat, toks.objectcode );
  	  if ( toks.opformat == 1 )    // (1) x (�S����) [1/3/4]
  	  	if ( !toks.tokens[3].value.empty() )
  	  	  toks.error = "Syntax Error! : It should be nothing here.";
	  else if ( toks.opformat == 2 ) {  //(2) m          [3/4]
	  	if ( toks.tokens[3].value.empty() )
  	  	  toks.error = "Syntax Error! : It should have something here.";
  	  	else {
  	  	  if ( toks.tokens[3].tokentype == 4 && toks.tokens[3].tokenvalue == 12 ){ // Immediate Addressing #
  	  	    toks.i = 1;
  	  	    if ( toks.tokens[4].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind #.";
  	  	    else
  	  	      toks.group1 = toks.tokens[4].value;
  	      } // if Immediate Addressing #
  	      else if ( toks.tokens[3].tokentype == 4 && toks.tokens[3].tokenvalue == 13 ){ // Indirect Addressing @
  	  	    toks.n = 1;
  	  	    if ( toks.tokens[4].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind @.";
  	  	    else
  	  	      toks.group1 = toks.tokens[4].value;
  	      } // else if Indirect Addressing @
  	      else { // <direct>|<index>|<literal>
  	        toks.i = 1;
  	        toks.n = 1;
  	        if ( toks.tokens[4].tokentype == 4 && toks.tokens[4].tokenvalue == 1 ) { // <index>�G <symbol>, X
  	          toks.x = 1;
  	          if ( toks.tokens[3].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group1 = toks.tokens[3].value;
  	          if ( toks.tokens[5].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group2 = toks.tokens[5].value;
  	        } // if <index>�G <symbol>, X
  	        else if ( toks.tokens[3].tokentype == 4 && toks.tokens[3].tokenvalue == 11 ) { // <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	          if ( toks.tokens[5].tokentype = 7 ) {  // (1)= C''�K(BYTE) (C�w�g�����F 
  	            toks.literal.label = toks.tokens[5].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[5].value;
                toks.literal.literal.insert( 0, toks.tokens[4].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[4].value );
                toks.literal.literal.insert( 0, "C" );
                toks.group1 = toks.tokens[5].value;
			  } // if (1)= X''�K(BYTE) (X�w�g�����F  
			  if ( toks.tokens[5].tokentype == 6 ) {  //  (2) = X''�K(BYTE) (X�w�g�����F
  	            toks.literal.label = toks.tokens[5].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[5].value;
                toks.literal.literal.insert( 0, toks.tokens[4].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[4].value );
                toks.literal.literal.insert( 0, "X" );
                toks.group1 = toks.tokens[5].value;
			  } // if  (2) = C''�K(BYTE) (C�w�g�����F
			  else if ( toks.tokens[4].tokentype == 6 ) {  // (3) =�`�� (WORD) 
			    toks.literal.label = toks.tokens[4].value;
			    toks.literal.label.insert( 0, toks.tokens[3].value );
			    toks.literal.WORDorBYTE = "WORD";
			    toks.literal.literal = toks.tokens[4].value;
			    toks.group1 = toks.literal.label;
			  } // else if (3) =�`�� (WORD)
  	        } // else if <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	        else if ( !toks.tokens[3].value.empty() && toks.tokens[4].value.empty() ) { // <symbol> | address
  	          toks.group1 = toks.tokens[3].value;
  	        } // else if <symbol> | address
  	        else 
  	          toks.error = "Syntax Error! : It should be something here.";
		  } // else <direct>|<index>|<literal>
		} // else
	  } // else if (2) m          [3/4]
	} // if
	else if ( toks.tokens[1].tokentype == 1 ) { //format123 
	  toks.ins = toks.tokens[1].value;
  	  sicxe_Search_Instruction_Set( sicxe, toks.tokens[1].value, toks.format, toks.opformat, toks.objectcode );
  	  if ( toks.opformat == 1 )  {   // (1) x (�S����) [1/3/4]  �o�̥u�|��1/3���i�� 
  	    toks.label_length = 1;
  	  	if ( !toks.tokens[2].value.empty() )
  	  	  toks.error = "Syntax Error! : It should be nothing here.";
      } // if
	  else if ( toks.opformat == 2 ) {  //(2) m          [3/4]  �o�̥u�|��3���i�� 
	    toks.label_length = 3;
	  	if ( toks.tokens[2].value.empty() )
  	  	  toks.error = "Syntax Error! : It should have something here.";
  	  	else {
  	  	  if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 12 ){ // Immediate Addressing #
  	  	    if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[3].value ) )
  	  	      toks.forwardreference = true;
  	  	    toks.i = 1;
  	  	    if ( toks.tokens[3].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind #.";
  	  	    else
  	  	      toks.group1 = toks.tokens[3].value;
  	      } // if Immediate Addressing #
  	      else if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 13 ){ // Indirect Addressing @
  	        if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[3].value ) )
  	  	      toks.forwardreference = true;
  	  	    toks.n = 1;
  	  	    if ( toks.tokens[3].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind @.";
  	  	    else
  	  	      toks.group1 = toks.tokens[3].value;
  	      } // else if Indirect Addressing @
  	      else { // <direct>|<index>|<literal>
  	        toks.i = 1;
  	        toks.n = 1;
  	        if ( toks.tokens[3].tokentype == 4 && toks.tokens[3].tokenvalue == 1 ) { // <index>�G <symbol>, X
  	          if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[2].value ) )
  	  	        toks.forwardreference = true;
  	          toks.x = 1;
  	          if ( toks.tokens[2].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group1 = toks.tokens[2].value;
  	          if ( toks.tokens[4].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group2 = toks.tokens[4].value;
  	        } // if <index>�G <symbol>, X
  	        else if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 11 ) { // <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	          if ( toks.tokens[4].tokentype == 7 ) {  // (1)= C''�K(BYTE) (C�w�g�����F 
  	            toks.literal.label = toks.tokens[4].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[4].value;
                toks.literal.literal.insert( 0, toks.tokens[3].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[3].value );
                toks.literal.literal.insert( 0, "C" );
                toks.group1 = toks.tokens[4].value;
			  } // if (1)= X''�K(BYTE) (X�w�g�����F  
			  if ( toks.tokens[4].tokentype == 6 ) {  //  (2) = X''�K(BYTE) (X�w�g�����F
  	            toks.literal.label = toks.tokens[4].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[4].value;
                toks.literal.literal.insert( 0, toks.tokens[3].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[3].value );
                toks.literal.literal.insert( 0, "X" );
                toks.group1 = toks.tokens[4].value;
			  } // if  (2) = C''�K(BYTE) (C�w�g�����F
			  else if ( toks.tokens[3].tokentype == 6 ) {  // (3) =�`�� (WORD) 
			    toks.literal.label = toks.tokens[3].value;
			    toks.literal.label.insert( 0, toks.tokens[2].value );
			    toks.literal.WORDorBYTE = "WORD";
			    toks.literal.literal = toks.tokens[3].value;
			    toks.group1 = toks.literal.label;
			  } // else if (3) =�`�� (WORD)
  	        } // else if <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	        else if ( !toks.tokens[2].value.empty() && toks.tokens[3].value.empty() ) { // <symbol> | address
  	          if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[2].value ) )
  	  	        toks.forwardreference = true;
  	          toks.group1 = toks.tokens[2].value;
  	        } // else if <symbol> | address
  	        else 
  	          toks.error = "Syntax Error! : It should be something here.";
		  } // else <direct>|<index>|<literal>
		} // else
	  } // else if (2) m     [3/4] �̥u�|��3���i��  
	  else if ( toks.opformat == 3 ) {  //(3) r1         [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[2].value;
	  } // else if (3) r1         [2]
	  else if ( toks.opformat == 4 ) {  //(4) r1,r2      [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[2].value;
	    toks.group2 = toks.tokens[4].value;
	  } // else if (4) r1,r2      [2]
	  else if ( toks.opformat == 5 ) {  //(5) r1,n       [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[2].value;
	    toks.group2 = toks.tokens[4].value;
	  } // else if (5) r1,n       [2]
	  else if ( toks.opformat == 6 ) {  //(6) n          [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[2].value;
	  } // else if (6) n          [2]
	} // else if format123 
	else if ( toks.tokens[1].tokentype == 2 ) { // pseudo instruction 1.START 2.END 3.EQU 4.BYTE 5.WORD 6.LTORG 7.BASE 8.RESB 9.RESW
	  toks.ins = toks.tokens[1].value;
	  if ( toks.tokens[1].tokenvalue == 1 ) {//  {label} START hex_num
	    toks.group1 = toks.tokens[2].value;
	    toks.START = true;
	    int num = atoi(toks.tokens[2].value.c_str());
	    toks.location = num;  //�]�w�_�l��m 
      }// if START
      else if ( toks.tokens[1].tokenvalue == 2 || toks.tokens[1].tokenvalue == 6 ) { //  {label} END {label} || {label} LTORG
        toks.end =true;
        toks.group1 = toks.tokens[2].value;
	    token_packer.end = true;
      } // else of
      else if ( toks.tokens[1].tokenvalue == 3 ) {//  label EQU label | dec_num | *  �|�h�B�⭭�w��label�Plabel
        toks.EQU = true;
        if ( toks.tokens[2].tokentype == 6 )
          toks.location = atoi(toks.tokens[2].value.c_str());
        toks.group1 = toks.tokens[2].value;
      }// else if EQU
      else if ( toks.tokens[1].tokenvalue == 4 ) {// {label} BYTE X''�K | C''�K | dec_num
        if ( toks.tokens[3].tokentype = 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(BYTE) (C�w�g�����F
          toks.group1 = toks.tokens[3].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	    } // if
	    else if ( toks.tokens[3].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(BYTE) (X�w�g�����F 
	      toks.group1 = toks.tokens[3].value;  //������object code    
		} // else if
		else if ( toks.tokens[2].tokentype == 6 ) {  // dec_num
	      toks.group1 = toks.tokens[2].value; 
		} // else if
      }// else if BYTE
      else if ( toks.tokens[1].tokenvalue == 5 ) {//  {label} WORD X''�K | C''�K | dec_num
	    if ( toks.tokens[3].tokentype = 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(WORD) (C�w�g�����F
          toks.group1 = toks.tokens[3].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	    } // if
	    else if ( toks.tokens[3].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(WORD) (X�w�g�����F 
	      toks.group1 = toks.tokens[3].value;  //������object code    
		} // else if
		else if ( toks.tokens[2].tokentype == 6 ) {  // dec_num
	      toks.group1 = toks.tokens[2].value; 
		} // else if
      }// else if WORD
      else if ( toks.tokens[1].tokenvalue == 7 ) {//  {label} BASE dec_num | symbol
        toks.base = true;
        token_packer.base = true;
        toks.group1 = toks.tokens[2].value; 
        token_packer.base_label = toks.tokens[2].value; 
      }// else if BASE
      else if ( toks.tokens[1].tokenvalue == 8 ) {//  {label} RESB dec_num
        toks.label_length = atoi(toks.tokens[2].value.c_str());
        toks.group1 = toks.tokens[2].value;
      }// else if RESB
      else if ( toks.tokens[1].tokenvalue == 9 ) {//  {label} RESW dec_num
        toks.label_length = atoi(toks.tokens[2].value.c_str())*3;
        //cout << toks.label_length ; // test
        toks.group1 = toks.tokens[2].value;
      }// else if RESW
	} // else if  pseudo instruction
	else if ( toks.tokens[0].tokentype == 5 && toks.tokens[1].tokentype != 1 && toks.tokens[1].tokentype != 2 && toks.tokens[1].tokentype != 4 )
      toks.error = "Syntax Error! : It doesn't have instructions.";
  } // if ��label 
  else if ( toks.tokens[0].tokentype == 4 ) {  //�S��label +�}�Y (format4) 
    toks.label_length = 4;
  	  toks.ins = toks.tokens[1].value;
  	  sicxe_Search_Instruction_Set( sicxe, toks.tokens[1].value, toks.format, toks.opformat, toks.objectcode );
  	  toks.format = 4;
  	  if ( toks.opformat == 1 ) {   // (1) x (�S����) [1/3/4]
  	  	if ( !toks.tokens[2].value.empty() )
  	  	  toks.error = "Syntax Error! : It should be nothing here.";
      } // if
	  else if ( toks.opformat == 2 ) {  //(2) m          [3/4]
	  	if ( toks.tokens[2].value.empty() )
  	  	  toks.error = "Syntax Error! : It should have something here.";
  	  	else {
  	  	  if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 12 ){ // Immediate Addressing # 
  	  	    toks.i = 1;
  	  	    if ( toks.tokens[3].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind #.";
  	  	    else
  	  	      toks.group1 = toks.tokens[3].value;
  	      } // if Immediate Addressing #
  	      else if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 13 ){ // Indirect Addressing @
  	  	    toks.n = 1;
  	  	    if ( toks.tokens[3].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind @.";
  	  	    else
  	  	      toks.group1 = toks.tokens[3].value;
  	      } // else if Indirect Addressing @
  	      else { // <direct>|<index>|<literal>
  	        toks.i = 1;
  	        toks.n = 1;
  	        if ( toks.tokens[3].tokentype == 4 && toks.tokens[3].tokenvalue == 1 ) { // <index>�G <symbol>, X
  	          toks.x = 1;
  	          if ( toks.tokens[2].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group1 = toks.tokens[2].value;
  	          if ( toks.tokens[4].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group2 = toks.tokens[4].value;
  	        } // if <index>�G <symbol>, X
  	        else if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 11 ) { // <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	          if ( toks.tokens[4].tokentype == 7 ) {  // (1)= C''�K(BYTE) (C�w�g�����F 
  	            toks.literal.label = toks.tokens[4].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[4].value;
                toks.literal.literal.insert( 0, toks.tokens[3].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[3].value );
                toks.literal.literal.insert( 0, "C" );
                toks.group1 = toks.tokens[4].value;
			  } // if (1)= X''�K(BYTE) (X�w�g�����F  
			  if ( toks.tokens[4].tokentype == 6 ) {  //  (2) = X''�K(BYTE) (X�w�g�����F
  	            toks.literal.label = toks.tokens[4].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[4].value;
                toks.literal.literal.insert( 0, toks.tokens[3].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[3].value );
                toks.literal.literal.insert( 0, "X" );
                toks.group1 = toks.tokens[4].value;
			  } // if  (2) = C''�K(BYTE) (C�w�g�����F
			  else if ( toks.tokens[3].tokentype == 6 ) {  // (3) =�`�� (WORD) 
			    toks.literal.label = toks.tokens[3].value;
			    toks.literal.label.insert( 0, toks.tokens[2].value );
			    toks.literal.WORDorBYTE = "WORD";
			    toks.literal.literal = toks.tokens[3].value;
			    toks.group1 = toks.literal.label;
			  } // else if (3) =�`�� (WORD)
  	        } // else if <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	        else if ( !toks.tokens[2].value.empty() && toks.tokens[3].value.empty() ) { // <symbol> | address
  	          if ( !isNumber(toks.tokens[2].value) )
  	            if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[2].value ) )
  	  	          toks.forwardreference = true;
  	          toks.group1 = toks.tokens[2].value;
  	        } // else if <symbol> | address
  	        else 
  	          toks.error = "Syntax Error! : It should be something here.";
		  } // else <direct>|<index>|<literal>
		} // else
	  } // else if (2) m          [3/4]
  } // else if 
  else if ( toks.tokens[0].tokentype == 1 ) {  //�S��label format123
      toks.ins = toks.tokens[0].value;
  	  sicxe_Search_Instruction_Set( sicxe, toks.tokens[0].value, toks.format, toks.opformat, toks.objectcode );
  	  if ( toks.opformat == 1 ) {   // (1) x (�S����) [1/3/4]  �o�̥u�|��1/3���i�� 
  	    toks.label_length = 1;
  	  	if ( !toks.tokens[1].value.empty() )
  	  	  toks.error = "Syntax Error! : It should be nothing here.";
      } // if
	  else if ( toks.opformat == 2 ) {  //(2) m          [3/4]  �o�̥u�|��3���i�� 
	    toks.label_length = 3;
	  	if ( toks.tokens[1].value.empty() )
  	  	  toks.error = "Syntax Error! : It should have something here.";
  	  	else {
  	  	  if ( toks.tokens[1].tokentype == 4 && toks.tokens[1].tokenvalue == 12 ){ // Immediate Addressing #
  	  	    if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[2].value ) )
  	  	      toks.forwardreference = true;
  	  	    toks.i = 1;
  	  	    if ( toks.tokens[2].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind #.";
  	  	    else
  	  	      toks.group1 = toks.tokens[2].value;
  	      } // if Immediate Addressing #
  	      else if ( toks.tokens[1].tokentype == 4 && toks.tokens[1].tokenvalue == 13 ){ // Indirect Addressing @
  	        if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[2].value ) )
  	  	      toks.forwardreference = true;
  	  	    toks.n = 1;
  	  	    if ( toks.tokens[2].value.empty() )
  	  	      toks.error = "Syntax Error! : It should have something behind @.";
  	  	    else
  	  	      toks.group1 = toks.tokens[2].value;
  	      } // else if Indirect Addressing @
  	      else { // <direct>|<index>|<literal>
  	        toks.i = 1;
  	        toks.n = 1;
  	        if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 1 ) { // <index>�G <symbol>, X
  	          if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[1].value ) )
  	  	        toks.forwardreference = true;
  	          toks.x = 1;
  	          if ( toks.tokens[1].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group1 = toks.tokens[1].value;
  	          if ( toks.tokens[3].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	          else
  	            toks.group2 = toks.tokens[3].value;
  	        } // if <index>�G <symbol>, X
  	        else if ( toks.tokens[1].tokentype == 4 && toks.tokens[1].tokenvalue == 11 ) { // <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	          if ( toks.tokens[3].tokentype == 7 ) {  // (1)= C''�K(BYTE) (C�w�g�����F 
  	            toks.literal.label = toks.tokens[3].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[3].value;
                toks.literal.literal.insert( 0, toks.tokens[2].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[2].value );
                toks.literal.literal.insert( 0, "C" );
                toks.group1 = toks.tokens[3].value;
			  } // if (1)= X''�K(BYTE) (X�w�g�����F  
			  if ( toks.tokens[3].tokentype == 6 ) {  //  (2) = X''�K(BYTE) (X�w�g�����F
  	            toks.literal.label = toks.tokens[3].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[3].value;
                toks.literal.literal.insert( 0, toks.tokens[2].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[2].value );
                toks.literal.literal.insert( 0, "X" );
                toks.group1 = toks.tokens[3].value;
			  } // if  (2) = C''�K(BYTE) (C�w�g�����F
			  else if ( toks.tokens[2].tokentype == 6 ) {  // (3) =�`�� (WORD) 
			    toks.literal.label = toks.tokens[2].value;
			    toks.literal.label.insert( 0, toks.tokens[1].value );
			    toks.literal.WORDorBYTE = "WORD";
			    toks.literal.literal = toks.tokens[2].value;
			    toks.group1 = toks.literal.label;
			  } // else if (3) =�`�� (WORD)
  	        } // else if <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	        else if ( !toks.tokens[1].value.empty() && toks.tokens[2].value.empty() ) { // <symbol> | address
  	          if ( !isNumber(toks.tokens[1].value) )
  	            if ( !sicxe_Set_p_b ( token_packer, toks, toks.tokens[1].value ) )
  	  	          toks.forwardreference = true;
  	          toks.group1 = toks.tokens[1].value;
  	        } // else if <symbol> | address
  	        else 
  	          toks.error = "Syntax Error! : It should be something here.";
		  } // else <direct>|<index>|<literal>
		} // else
	  } // else if (2) m     [3/4] �̥u�|��3���i��  
	  else if ( toks.opformat == 3 ) {  //(3) r1         [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[1].value;
	  } // else if (3) r1         [2]
	  else if ( toks.opformat == 4 ) {  //(4) r1,r2      [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[1].value;
	    toks.group2 = toks.tokens[3].value;
	  } // else if (4) r1,r2      [2]
	  else if ( toks.opformat == 5 ) {  //(5) r1,n       [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[1].value;
	    toks.group2 = toks.tokens[3].value;
	  } // else if (5) r1,n       [2]
	  else if ( toks.opformat == 6 ) {  //(6) n          [2]
	    toks.label_length = 2;
	    toks.group1 = toks.tokens[1].value;
	  } // else if (6) n          [2]
	} // else if �S��label format123 
  else if ( toks.tokens[0].tokentype == 2 ) {  //�S��label pseudo instruction
	  toks.ins = toks.tokens[0].value;
	  if ( toks.tokens[0].tokenvalue == 1 ) {//  {label} START hex_num
	    toks.START = true;
	    toks.group1 = toks.tokens[1].value;
	    int num = atoi(toks.tokens[1].value.c_str());
	    toks.location = num;  //�]�w�_�l��m 
      }// if START
      else if ( toks.tokens[0].tokenvalue == 2 || toks.tokens[0].tokenvalue == 6 ) {//  {label} END {label} || {label} LTORG
        toks.end =true;
        toks.group1 = toks.tokens[1].value;
	    token_packer.end = true;
	  }// else if {label} END {label} || {label} LTORG
      else if ( toks.tokens[0].tokenvalue == 3 ) { //  label EQU label | dec_num | *  �|�h�B�⭭�w��label�Plabel
        toks.EQU = true;
        if ( toks.tokens[1].tokentype == 6 )
          toks.location = atoi(toks.tokens[1].value.c_str());
        toks.group1 = toks.tokens[1].value;
      }// else if label EQU label | dec_num | *  �|�h�B�⭭�w��label�Plabel
      else if ( toks.tokens[0].tokenvalue == 4 ) {// {label} BYTE X''�K | C''�K | dec_num
        if ( toks.tokens[2].tokentype == 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(BYTE) (C�w�g�����F
          toks.group1 = toks.tokens[2].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	    } // if
	    else if ( toks.tokens[2].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(BYTE) (X�w�g�����F 
	      toks.group1 = toks.tokens[2].value;  //������object code    
		} // else if
		else if ( toks.tokens[1].tokentype == 6 ) {  // dec_num
	      toks.group1 = toks.tokens[1].value; 
		} // else if
      }// else if BYTE
      else if ( toks.tokens[0].tokenvalue == 5 ) {//  {label} WORD X''�K | C''�K | dec_num
	    if ( toks.tokens[2].tokentype == 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(WORD) (C�w�g�����F
          toks.group1 = toks.tokens[2].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	    } // if
	    else if ( toks.tokens[2].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(WORD) (X�w�g�����F 
	      toks.group1 = toks.tokens[2].value;  //������object code    
		} // else if
		else if ( toks.tokens[1].tokentype == 6 ) {  // dec_num
	      toks.group1 = toks.tokens[1].value; 
		} // else if
      }// else if WORD
      else if ( toks.tokens[0].tokenvalue == 7 ) {//  {label} BASE dec_num | symbol
        toks.base = true;
        token_packer.base = true;
        toks.group1 = toks.tokens[1].value; 
        token_packer.base_label = toks.tokens[1].value; 
      }// else if BASE
      else if ( toks.tokens[0].tokenvalue == 8 ) {//  {label} RESB dec_num
        toks.label_length = atoi(toks.tokens[1].value.c_str());
        toks.group1 = toks.tokens[1].value;
      }// else if RESB
      else if ( toks.tokens[0].tokenvalue == 9 ) {//  {label} RESW dec_num
        toks.label_length = atoi(toks.tokens[1].value.c_str())*3;
        toks.group1 = toks.tokens[1].value;
      }// else if RESW
  } // else if �S��label pseudo instruction
  else if ( toks.tokens[0].tokentype != 5 && toks.tokens[0].tokentype != 1 && toks.tokens[0].tokentype != 2 && toks.tokens[0].tokentype != 4 )
    toks.error = "Syntax Error! : It doesn't have label and instructions.";
} // sicxe_RecordAndSyntax

void sicxe_setbase( Packed_Token &token_packer ){
	int base_address;
	for ( int i = 0 ; i < token_packer.amount ; i++ ) 
		if ( token_packer.base_label == token_packer.token_groups[i].label )
		  token_packer.base_hexlocation =  token_packer.token_groups[i].hex_location;
} // sicxe_setbase

void sicxe_resetcodedisp( Packed_Token &token_packer ){
	for ( int i = 0 ; i < token_packer.amount ; i++ ){
		string disp = token_packer.base_hexlocation;
		if ( token_packer.token_groups[i].b && !token_packer.token_groups[i].forwardreference ) {
			sicxe_set_disp( token_packer, token_packer.token_groups[i], disp );
			token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),"F");
			token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),disp);
		} // 
	} // for
} //sicxe_resetcodedisp

void sicxe_pass2( Packed_Token &token_packer ){
	for ( int i = 0 ; i < token_packer.amount ; i++ ) {
		string address;
		//cout << token_packer.token_groups[i].ins << token_packer.token_groups[i].forwardreference <<endl ; // test
		if ( token_packer.token_groups[i].forwardreference ) {
			if ( token_packer.token_groups[i].format == 4 ) {
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
				sicxe_set_address( token_packer, token_packer.token_groups[i], address );
			    token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),address);
			}
			if ( token_packer.token_groups[i].format == 3 ) {
			  string disp ;
			  sicxe_set_disp( token_packer, token_packer.token_groups[i], disp );
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			  token_packer.token_groups[i].objectcode.erase(token_packer.token_groups[i].objectcode.length()-1,1);
			  if ( disp.length() == 1 )
		  	    token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),"00");
		  	  else if ( disp.length() == 2 )
		  	    token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),"0");
			  token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),disp);
			}
		} // if
	} // for
} //sicxe_pass2

//----------------------------sicxe-----------------------------------------
//----------------------------sic-----------------------------------------

void sic_Search_Instruction_Set( Sic_Instruction_Set sic[26], string token, string &objectcode ) {
	string lower = to_lower(token);
	int num = 0;
	for ( int i = 0 ; i < 26 ; i++ )
	  if ( sic[i].instruction == lower )
	    num = i;
	objectcode = sic[num].objectcode;
} // sic_Search_Instruction_Set

void sic_setlocation ( int n, string &hex ) {
	DecToHexa(n, hex);
	string result;
    if ( hex.length() != 4 ) {
      for ( int i = 4-hex.length() ; i > 0 ; i-- ){
    	if ( !hex.empty() ) {
    	  result.insert( 0 , hex);
    	  hex.clear();
		} // if
    	result.insert( 0 , "0");
	  } // for
	} // if
	else 
      result = hex;
	hex = result;
} //sic_setlocation

void sic_setline( string &setedline, int line ) {
	string result;
	string temp = std::to_string(line);
    if ( temp.length() != 4 ) {
      for ( int i = 4-temp.length() ; i > 0 ; i-- ){
    	if ( !temp.empty() ) {
    	  result.insert( 0 , temp);
    	  temp.clear();
		} // if
    	result.insert( 0 , " ");
	  } // for
	} // if
	else 
      result = temp;
	setedline = result;
} //sic_setline

void sic_index_set_address( Tokens &toks, string address ) {
	// test 1039
	string temp;
	string x = "1";
	temp.append(1, address[0]); //1
	address.erase(0,1); //039
	// test 1
	HexaToBin( temp );
	// test 0001
	temp.erase(0,1);
	// test 001
	x.insert(x.length(),temp);
	// test 1001
	BinToHexa( x );
	x.insert(x.length(),address);
	toks.objectcode.insert(toks.objectcode.length(),x);
} // sic_index_set_address

void sic_set_address( Packed_Token token_packer, Tokens toks, string &address ){
    for ( int i = 0; i < token_packer.amount ; i++ ) 
      if ( toks.group1 == token_packer.token_groups[i].label )
    	address = token_packer.token_groups[i].hex_location; 
} //  sic_set_address

bool sic_havefind( Packed_Token token_packer, Tokens toks, string token ){  
	for ( int i = 0 ; i < token_packer.amount ; i++ ){
		if ( token == token_packer.token_groups[i].label ) // ��o��
		  return true;
	} // for
    return false;
    // else �䤣��
} // sic_havefind


void sic_setcode( Packed_Token token_packer, Tokens &toks ) {
	string address;
	string result;
	int asciicode = 0 ;
	if ( toks.x == 1 ) { //  index
	    if ( !toks.forwardreference ) {
	        //cout << toks.ins << toks.group1 << toks.group2 << toks.objectcode ; // test
	    	sic_set_address(token_packer, toks, address);
	    	sic_index_set_address( toks, address );
	    	//cout << toks.ins << toks.objectcode << endl; // test
		} // if
    } // if  index
    else if ( toks.c_x_w == "c" ) {
    	for ( int i = 0; i < toks.group1.length() ; i++ ) {
    		string temp;
    		asciicode = int(toks.group1[i]);
    		DecToHexa(asciicode, temp);
    		result.insert(result.length(),temp);
		} // for
		toks.objectcode = result;
	} // else if
	else if ( toks.c_x_w == "x" ) {
    	toks.objectcode = toks.group1;
	} // else if
	else if ( toks.c_x_w == "w" ) {
    	for ( int i = toks.group1.length() ; i < 6 ; i++ )
    	  toks.objectcode.insert(toks.objectcode.length(),"0");
    	int temp = atoi(toks.group1.c_str());
    	string hex;
    	DecToHexa(temp, hex);
    	if ( toks.group1 == "0" )
    	  toks.objectcode.insert(toks.objectcode.length(),"0");
    	else
    	  toks.objectcode.insert(toks.objectcode.length(),hex);
	} // else if
	else if ( toks.x == 0 ) {
    	sic_set_address(token_packer, toks, address);
    	toks.objectcode.insert(toks.objectcode.length(),address);
    } // else if
} //sic_setcode

void sic_pass2( Packed_Token &token_packer ){
	for ( int i = 0 ; i < token_packer.amount ; i++ ) {
		string address;
		if ( token_packer.token_groups[i].forwardreference ) {
			if ( token_packer.token_groups[i].x == 1 ) { //  index
	          sic_set_address(token_packer, token_packer.token_groups[i], address);
	    	  sic_index_set_address( token_packer.token_groups[i], address );
            } // if  index
            else if ( token_packer.token_groups[i].x == 0 ) {
    	      sic_set_address(token_packer, token_packer.token_groups[i], address);
    	      token_packer.token_groups[i].objectcode.insert(token_packer.token_groups[i].objectcode.length(),address);
            } // else if 
		} // if
	} // for
} //sic_pass2

void sic_RecordAndSyntax( Packed_Token &token_packer, Tokens &toks, Sic_Instruction_Set sic[26] ) { 
  //cout << toks.tokens[0].tokentype << toks.tokens[1].tokentype << toks.tokens[2].tokentype << endl ; // test
  //cout << toks.tokens[0].tokenvalue << toks.tokens[1].tokenvalue << toks.tokens[2].tokenvalue <<endl ; // test
  //cout << toks.tokens[0].value << toks.tokens[1].value << toks.tokens[2].value <<endl ; // test
  if ( toks.tokens[0].tokentype == 5 ) { //��label 
  	toks.label = toks.tokens[0].value;
  	if ( toks.tokens[1].tokentype == 1 ) { // ��label instructions
  	  toks.label_length = 3;
  	  toks.ins = toks.tokens[1].value;
  	  sic_Search_Instruction_Set( sic, toks.tokens[1].value, toks.objectcode );
  	    if ( toks.tokens[3].tokentype == 4 && toks.tokens[3].tokenvalue == 1 ) { // <index>�G <symbol>, X
  	        if ( !sic_havefind( token_packer, toks, toks.tokens[2].value ) )
  	  	        toks.forwardreference = true;
  	        toks.x = 1;
  	        if ( toks.tokens[2].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	        else
  	            toks.group1 = toks.tokens[2].value;
  	        if ( toks.tokens[4].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	        else
  	            toks.group2 = toks.tokens[4].value;
  	    } // if <index>�G <symbol>, X
  	    else if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 11 ) { // <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	        if ( toks.tokens[4].tokentype == 7 ) {  // (1)= C''�K(BYTE) (C�w�g�����F 
  	            toks.label_length = toks.tokens[4].value.length();
  	            toks.literal.c_x_w = "c";
  	            toks.literal.label = toks.tokens[4].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[4].value;
                toks.literal.literal.insert( 0, toks.tokens[3].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[3].value );
                toks.literal.literal.insert( 0, "C" );
                toks.group1 = toks.tokens[4].value;
			} // if (1)= X''�K(BYTE) (X�w�g�����F  
			else if ( toks.tokens[4].tokentype == 6 ) {  //  (2) = X''�K(BYTE) (X�w�g�����F
			    toks.label_length = toks.tokens[4].value.length()/2;
			    toks.literal.c_x_w = "x";
  	            toks.literal.label = toks.tokens[4].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[4].value;
                toks.literal.literal.insert( 0, toks.tokens[3].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[3].value );
                toks.literal.literal.insert( 0, "X" );
                toks.group1 = toks.tokens[4].value;
			} // else if  (2) = C''�K(BYTE) (C�w�g�����F
			else if ( toks.tokens[3].tokentype == 6 ) {  // (3) =�`�� (WORD) 
			    toks.label_length = 3;
			    toks.literal.c_x_w = "w";
			    toks.literal.label = toks.tokens[3].value;
			    toks.literal.label.insert( 0, toks.tokens[2].value );
			    toks.literal.WORDorBYTE = "WORD";
			    toks.literal.literal = toks.tokens[3].value;
			    toks.group1 = toks.literal.label;
			} // else if (3) =�`�� (WORD)
  	    } // else if <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	    else if ( !toks.tokens[2].value.empty() && toks.tokens[3].value.empty() ) { // <symbol> | address
  	        if ( !sic_havefind( token_packer, toks, toks.tokens[2].value ) )
  	  	        toks.forwardreference = true;
  	        toks.group1 = toks.tokens[2].value;
  	    } // else if <symbol> | address
  	    else if ( toks.tokens[1].value == "RSUB" )
  	      toks.objectcode = "4C0000";
  	    else 
  	        toks.error = "Syntax Error! : It should be something here.";
    } // if ��label instructions
	else if ( toks.tokens[1].tokentype == 2 ) { // ��label pseudo instruction 1.START 2.END 3.EQU 4.BYTE 5.WORD 6.LTORG 7.BASE 8.RESB 9.RESW
	  toks.ins = toks.tokens[1].value;
	  if ( toks.tokens[1].tokenvalue == 1 ) {//  {label} START hex_num
	    toks.pseudo = true;
	    int num = 0; 
	    toks.START = true;
	    toks.group1 = toks.tokens[2].value;
	    HexToDe( toks.tokens[2].value, num );
	    toks.location = num;  //�]�w�_�l��m 
      }// if START
      else if ( toks.tokens[1].tokenvalue == 2 || toks.tokens[1].tokenvalue == 6 ) { //  {label} END {label} || {label} LTORG
        toks.pseudo = true;
        toks.end =true;
        toks.group1 = toks.tokens[2].value;
	    token_packer.end = true;
      } // else of
      else if ( toks.tokens[1].tokenvalue == 3 ) {//  label EQU label | dec_num | *  �|�h�B�⭭�w��label�Plabel
        toks.EQU = true;
        if ( toks.tokens[2].tokentype == 6 )
          toks.location = atoi(toks.tokens[2].value.c_str());
        toks.group1 = toks.tokens[2].value;
      }// else if EQU
      else if ( toks.tokens[1].tokenvalue == 4 ) {// {label} BYTE X''�K | C''�K | dec_num
        if ( toks.tokens[3].tokentype == 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(BYTE) (C�w�g�����F
          toks.c_x_w = "c";
          toks.label_length = toks.tokens[3].value.length();
          toks.group1 = toks.tokens[3].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	    } // if
	    else if ( toks.tokens[3].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(BYTE) (X�w�g�����F 
	      toks.c_x_w = "x";
	      toks.label_length = toks.tokens[3].value.length()/2;
	      toks.group1 = toks.tokens[3].value;  //������object code    
		} // else if
		else if ( toks.tokens[2].tokentype == 6 ) {  // dec_num
		  toks.label_length = 3;
	      toks.group1 = toks.tokens[2].value; 
		} // else if
      }// else if BYTE
      else if ( toks.tokens[1].tokenvalue == 5 ) {//  {label} WORD X''�K | C''�K | dec_num
        if ( toks.tokens[2].tokentype == 6 ) {  // dec_num
          toks.c_x_w = "w";
		  toks.label_length = 3;
	      toks.group1 = toks.tokens[2].value; 
		} // if
	    else if ( toks.tokens[3].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(WORD) (X�w�g�����F 
	      toks.c_x_w = "x";
	      toks.label_length = toks.tokens[3].value.length()/2;
	      toks.group1 = toks.tokens[3].value;  //������object code  
		} // else if
		else if ( toks.tokens[3].tokentype == 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(WORD) (C�w�g�����F
		  toks.c_x_w = "c";
	      toks.label_length = toks.tokens[3].value.length();
          toks.group1 = toks.tokens[3].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	    } // else if
      }// else if WORD
      else if ( toks.tokens[1].tokenvalue == 7 ) {//  {label} BASE dec_num | symbol
        toks.pseudo = true;
        token_packer.base = true;
        toks.group1 = toks.tokens[2].value; 
      }// else if BASE
      else if ( toks.tokens[1].tokenvalue == 8 ) {//  {label} RESB dec_num
        toks.pseudo = true;
        toks.label_length = atoi(toks.tokens[2].value.c_str());
        toks.group1 = toks.tokens[2].value;
      }// else if RESB
      else if ( toks.tokens[1].tokenvalue == 9 ) {//  {label} RESW dec_num
        toks.pseudo = true;
        toks.label_length = atoi(toks.tokens[2].value.c_str())*3;
        //cout << toks.label_length ; // test
        toks.group1 = toks.tokens[2].value;
      }// else if RESW
	} // else if  pseudo instruction
	else if ( toks.tokens[0].tokentype == 5 && toks.tokens[1].tokentype != 1 && toks.tokens[1].tokentype != 2 )
      toks.error = "Syntax Error! : It doesn't have instructions.";
  } // if ��label 
  else if ( toks.tokens[0].tokentype == 1 ) {  //�S��label  instrunctions
    toks.label_length = 3;
  	toks.ins = toks.tokens[0].value;
  	sic_Search_Instruction_Set( sic, toks.tokens[0].value, toks.objectcode );
  	    if ( toks.tokens[2].tokentype == 4 && toks.tokens[2].tokenvalue == 1 ) { // <index>�G <symbol>, X
  	        if ( !sic_havefind( token_packer, toks, toks.tokens[1].value ) )
  	  	        toks.forwardreference = true;
  	        toks.x = 1;
  	        if ( toks.tokens[1].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	        else
  	            toks.group1 = toks.tokens[1].value;
  	        if ( toks.tokens[3].value.empty() )
  	            toks.error = "Syntax Error! : It's index mode.It should have something behind.";
  	        else
  	            toks.group2 = toks.tokens[3].value;
  	    } // if <index>�G <symbol>, X
  	    else if ( toks.tokens[1].tokentype == 4 && toks.tokens[1].tokenvalue == 11 ) { // <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	        if ( toks.tokens[3].tokentype == 7 ) {  // (1)= C''�K(BYTE) (C�w�g�����F 
  	            toks.label_length = toks.tokens[3].value.length();
  	            toks.literal.c_x_w = "c";
  	            toks.literal.label = toks.tokens[3].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[3].value;
                toks.literal.literal.insert( 0, toks.tokens[1].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[2].value );
                toks.literal.literal.insert( 0, "C" );
                toks.group1 = toks.tokens[3].value;
			} // if (1)= X''�K(BYTE) (X�w�g�����F  
			else if ( toks.tokens[3].tokentype == 6 ) {  //  (2) = X''�K(BYTE) (X�w�g�����F
			    toks.label_length = toks.tokens[3].value.length()/2;
			    toks.literal.c_x_w = "x";
  	            toks.literal.label = toks.tokens[3].value;
  	            toks.literal.WORDorBYTE = "BYTE";
                toks.literal.literal = toks.tokens[3].value;
                toks.literal.literal.insert( 0, toks.tokens[2].value );
                toks.literal.literal.insert( toks.literal.literal.length()-1, toks.tokens[2].value );
                toks.literal.literal.insert( 0, "X" );
                toks.group1 = toks.tokens[3].value;
			} // else if  (2) = C''�K(BYTE) (C�w�g�����F
			else if ( toks.tokens[2].tokentype == 6 ) {  // (3) =�`�� (WORD) 
			    toks.label_length = 3;
			    toks.literal.c_x_w = "w";
			    toks.literal.label = toks.tokens[2].value;
			    toks.literal.label.insert( 0, toks.tokens[1].value );
			    toks.literal.WORDorBYTE = "WORD";
			    toks.literal.literal = toks.tokens[2].value;
			    toks.group1 = toks.literal.label;
			} // else if (3) =�`�� (WORD)
  	    } // else if <literal>�G (1)= C''�K(BYTE) (2) = X''�K(BYTE) (3) =�`�� (WORD)
  	    else if ( !toks.tokens[1].value.empty() && toks.tokens[2].value.empty() ) { // <symbol> | address
  	        if ( !sic_havefind( token_packer, toks, toks.tokens[1].value ) )
  	  	        toks.forwardreference = true;
  	        toks.group1 = toks.tokens[1].value;
  	    } // else if <symbol> | address
  	    else if ( toks.tokens[0].value == "RSUB" )
  	      toks.objectcode = "4C0000";
  	    else 
  	        toks.error = "Syntax Error! : It should be something here.";
    } // else if �S��label  instrunctions
    else if ( toks.tokens[0].tokentype == 2 ) {  //�S��label pseudo instruction
	    toks.ins = toks.tokens[0].value;
	    if ( toks.tokens[0].tokenvalue == 1 ) {//  {label} START hex_num
	      toks.pseudo = true;
	      int num = 0; 
	      toks.START = true;
	      toks.group1 = toks.tokens[1].value;
	      HexToDe( toks.tokens[2].value, num );
	      toks.location = num;  //�]�w�_�l��m 
        }// if START
        else if ( toks.tokens[0].tokenvalue == 2 || toks.tokens[0].tokenvalue == 6 ) {//  {label} END {label} || {label} LTORG
          toks.pseudo = true;
          toks.end =true;
          toks.group1 = toks.tokens[1].value;
	      token_packer.end = true;
	    }// else if {label} END {label} || {label} LTORG
        else if ( toks.tokens[0].tokenvalue == 3 ) { //  label EQU label | dec_num | *  �|�h�B�⭭�w��label�Plabel
          toks.EQU = true;
          if ( toks.tokens[1].tokentype == 6 )
            toks.location = atoi(toks.tokens[1].value.c_str());
          toks.group1 = toks.tokens[1].value;
        }// else if label EQU label | dec_num | *  �|�h�B�⭭�w��label�Plabel
        else if ( toks.tokens[0].tokenvalue == 4 ) {// {label} BYTE X''�K | C''�K | dec_num
          if ( toks.tokens[1].tokentype == 6 ) {  // dec_num
		    toks.label_length = 3;
	        toks.group1 = toks.tokens[1].value; 
		  } // if
          else if ( toks.tokens[2].tokentype == 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(BYTE) (C�w�g�����F
            toks.c_x_w = "c";
            toks.label_length = toks.tokens[2].value.length();
            toks.group1 = toks.tokens[2].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	      } // else if
	      else if ( toks.tokens[2].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(BYTE) (X�w�g�����F 
	        toks.c_x_w = "x";
	        toks.label_length = toks.tokens[2].value.length()/2;
	        toks.group1 = toks.tokens[2].value;  //������object code    
	  	  } // else if
        }// else if BYTE
        else if ( toks.tokens[0].tokenvalue == 5 ) {//  {label} WORD X''�K | C''�K | dec_num
	      if ( toks.tokens[2].tokentype == 7 ) {  // '(4,9) EOF(7,18) '(4,9) // C'�K(WORD) (C�w�g�����F
	        toks.c_x_w = "c";
	        toks.label_length = toks.tokens[2].value.length();
            toks.group1 = toks.tokens[2].value;  //������ EOF �@�Ӥ@��½���Q���i�� 
	      } // if
	      else if ( toks.tokens[2].tokentype == 6 ) {  // '(4,9) F 1(6,51) '(4,9) // X''�K(WORD) (X�w�g�����F 
	        toks.c_x_w = "x";
	        toks.label_length = toks.tokens[2].value.length()/2;
	        toks.group1 = toks.tokens[2].value;  //������object code    
	  	  } // else if
		  else if ( toks.tokens[1].tokentype == 6 ) {  // dec_num
		    toks.c_x_w = "w";
		    toks.label_length = 3;
	        toks.group1 = toks.tokens[1].value; 
		  } // else if
        }// else if WORD
        else if ( toks.tokens[0].tokenvalue == 7 ) {//  {label} BASE dec_num | symbol
          token_packer.base = true;
          toks.group1 = toks.tokens[1].value; 
        }// else if BASE
        else if ( toks.tokens[0].tokenvalue == 8 ) {//  {label} RESB dec_num
          toks.pseudo = true;
          toks.label_length = atoi(toks.tokens[1].value.c_str());
          toks.group1 = toks.tokens[1].value;
        }// else if RESB
        else if ( toks.tokens[0].tokenvalue == 9 ) {//  {label} RESW dec_num
          toks.pseudo = true;
          toks.label_length = atoi(toks.tokens[1].value.c_str())*3;
          toks.group1 = toks.tokens[1].value;
        }// else if RESW
    } // else if �S��label pseudo instruction
    else if ( toks.tokens[0].tokentype != 5 && toks.tokens[0].tokentype != 1 && toks.tokens[0].tokentype != 2 )
      toks.error = "Syntax Error! : It doesn't have label and instructions.";
} // sic_RecordAndSyntax

//----------------------------sic-----------------------------------------



void sic () {
	Sic_Instruction_Set sic[26];  //��sic�����O�� 
	Sic_Instruction_input( sic );
	//Sic_Instruction_print( sic ); // test
	Table table1[59];  //��table1  59�Ӥ���     Instruction
	Table table2[9];  //��table2  9�Ӥ���       Pseudo and Extra �ڼW�[�FEQU LTORG BASE
	Table table3[9];  //��table3  9�Ӥ���       Register
	Table table4[13];  //��table4  13�Ӥ���     Delimiter
	Table table5[100];  //��table5  100�Ӥ���   Symbol
	Table table6[100];  //��table6  100�Ӥ���   Integer/Real
	Table table7[100];  //��table7  100�Ӥ���   String , table4 );
	Packed_Token token_packer; //��@��@��]�˦n��Tokens
	token_packer.amount = 0;
	tableinput( table1, table2, table3, table4 );
    ifstream newfile; 
    ofstream outfile;
    string demo("SIC_input.txt");  //���g�@�Ӧr��demo 
	newfile.open(demo.c_str()); //�}���ɮ�
	demo.replace(demo.find("input"), 5, "output");
	outfile.open(demo.c_str()); //�g�J�ɮ�
	string line;
	string token;
	int tokentype = 0;
	int tokenvalue = 0;
	int is_string = 0; // C'EOF'�N��EOF�r��
	int is_integer = 0; // X'F1'�N��16�i�쪺F1
	while ( getline(newfile, line) ) {
	  if ( !line.empty() )
	    if ( token_packer.amount != 0 )
	      token_packer.token_groups[token_packer.amount].line =  token_packer.token_groups[token_packer.amount-1].line + 5;
	    else 
	      token_packer.token_groups[token_packer.amount].line = 5;
	  token_packer.token_groups[token_packer.amount].sourcestatement = line ;  //�C�檺�s��l�{�� 
	  if ( token_packer.token_groups[token_packer.amount].sourcestatement[0] == '\t' )
	    token_packer.token_groups[token_packer.amount].sourcestatement.erase( 0, 1 );
	  if ( token_packer.longestnum < line.length() ) //�����̪���source 
	    token_packer.longestnum = line.length();
	  //cout << line << endl ; // test
	  token_packer.token_groups[token_packer.amount].amount = 0;  //�C�檺token�q�Y�}�l��n�k�s 
	  is_string = 0;
	  is_integer = 0;
	  for ( int a = 0; a < line.length() ; a++ ) { 
	  	if ( line[a] == '.' ) { 
	  	  token_packer.token_groups[token_packer.amount].comment = true;
	  	  break;
	  	} // if 
	  	token.append(1, line[a]);
	  	if ( is_string != 1 && is_integer != 1 ) {
	  	  while ( !iswhitespce( line[a] ) && !isOp( line[a] ) && a+1 < line.length() ){ //���otoken 
            a++;
	  		token.append(1, line[a]);
	  		//cout << endl << token ; // test
	  		int end = a+1;
	  		if ( end >= line.length() )
	  		  break;
		  } //while
		} // if
		else if ( is_string == 1 || is_integer == 1 ) {
		  while ( int(line[a+1]) != 39 ){ //string��integer���otoken 
            a++;
	  		token.append(1, line[a]);
		  } //while
		} // if else
		
		//cout << endl << token ; // test
		if ( int(line[a]) == 39 && (int(line[a-1]) == 99 || int(line[a-1]) == 67) ) { // C'EOF'�N��EOF�r��
		  token.erase(0,1);
		  is_string ++;
	    } // if
	    if ( int(line[a]) == 39 && (int(line[a-1]) == 120 || int(line[a-1]) == 88) ) { // X'F1'�N��16�i�쪺F1
	      token.erase(0,1);
		  is_integer ++;
	    } // if
	    
	    if ( iswhitespce( line[a] ) )
	       removewhitespace( token ); //������whitespce 
	    
	    if ( isOp( line[a] ) && is_string != 1 && is_integer != 1 && token.length() != 1 ) {  //���token ���o�e������token�M��˰h�᭱���� delimiter �U�@�Ӧb�� 
			token.erase(token.length()-1, 1); //�R���᭱���� delimiter
			if ( find( token, table1, table2, table3, table4, 
              table5, table6, table7, tokentype, tokenvalue ) ) { //��btable�̧�� 
              ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		    } // if 
		    else if ( !find( token, table1, table2, table3, table4, 
              table5, table6, table7, tokentype, tokenvalue ) ) { // �btable�䤣��A�ۤv�� 
              string upper = to_upper(token); 
		      if ( isNumber( upper ) ) {  //�P�_�O�_��table6:�Ʀr
		        tokentype = 6;
		        instable( upper, table6, tokentype, tokenvalue);  
		      } // if
		      else {  //�P�_�O�_��table5
		        tokentype = 5;
		        instable( upper, table5, tokentype, tokenvalue);
		      } // else
		      ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		    } //else  if 
			a--; //�˰h 
		}//if 
		else if ( isOp( line[a] ) && token.length() == 1 ) {  //�@��token delimiter 
		  if ( find( token, table1, table2, table3, table4, 
            table5, table6, table7, tokentype, tokenvalue ) ) { //��btable�̧�� 
            ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  } // if 
		}//else  if 
		else if ( is_string == 1 && !isOp( line[a] )  ) {  //�Ostr !isOp( line[a] ) ->�קK�O' 
          tokentype = 7;
		  instable( token, table7, tokentype, tokenvalue);
		  ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  is_string ++;
		}//else  if
		else if ( is_integer == 1 && !isOp( line[a] )  ) {  //�Ointeger  !isOp( line[a] ) ->�קK�O'
          string upper = to_upper(token); 
          tokentype = 6;
		  instable( upper, table6, tokentype, tokenvalue);
		  ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue); 
		  is_integer ++;
		}//else  if
		else if ( !onespace( token ) && !token.empty() ){ 
		  if ( find( token, table1, table2, table3, table4, 
            table5, table6, table7, tokentype, tokenvalue ) ) { //��btable�̧�� 
            ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  } // if 
		  else if ( !find( token, table1, table2, table3, table4, 
            table5, table6, table7, tokentype, tokenvalue ) ) { // �btable�䤣��A�ۤv�� 
		    if ( is_integer == 1 ) { //�P�_�O�_��table7:literal('�r��') 
		      tokentype = 7;
		      instable( token, table7, tokentype, tokenvalue);
	     	} // if
		    else if ( isNumber( token ) ) { //�P�_�O�_��table6:�Ʀr
		      string upper = to_upper(token); 
		      tokentype = 6;
		      instable( upper, table6, tokentype, tokenvalue); 
		    } // else if
		    else {  //�P�_�O�_��table5
		      string upper = to_upper(token); 
		      tokentype = 5;
		      instable( upper, table5, tokentype, tokenvalue); 
		    } // else
		    ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  } //else  if 
		} // else  if	
	    token.clear();
	  } // for 
	  if ( !token_packer.token_groups[token_packer.amount].sourcestatement.empty() && !token_packer.token_groups[token_packer.amount].comment )
	    sic_RecordAndSyntax( token_packer, token_packer.token_groups[token_packer.amount], sic ) ; // �����@��@�檺label ins group1 group2/ ����nixpb�M�O�_forward reference
	  int temp = token_packer.amount-1; //�W�@�� 
	  if ( temp != -1 )
	    while ( token_packer.token_groups[temp].EQU )
	      temp--;
	  if ( temp != -1 && !token_packer.token_groups[token_packer.amount].EQU && !token_packer.token_groups[token_packer.amount].START )
	    token_packer.token_groups[token_packer.amount].location = token_packer.token_groups[temp].location + token_packer.token_groups[temp].label_length;
	  sic_setlocation ( token_packer.token_groups[token_packer.amount].location, token_packer.token_groups[token_packer.amount].hex_location );
	  sic_setline( token_packer.token_groups[token_packer.amount].setedline, token_packer.token_groups[token_packer.amount].line ) ;
	  if ( token_packer.token_groups[token_packer.amount].ins != "RSUB" )
	    sic_setcode( token_packer, token_packer.token_groups[token_packer.amount] );
	  //cout << token_packer.token_groups[token_packer.amount].ins << token_packer.token_groups[token_packer.amount].hex_location << endl ; // test
	  token_packer.amount++;
	} // while
	sic_pass2(token_packer);
	newfile.close();//Ū�ɧ��������ɮ�
	outfile << "Line" << "  " << "Location" << "  " ;
	outfile << "Source code" ;
	for ( int i = 10 ; i < 50 ; i++ )
	  outfile << " ";
	outfile << "  ";
	outfile << "Object code" << endl ;
	for ( int b = 0 ; b < token_packer.amount; b++) { //TEST
	    if( token_packer.token_groups[b].sourcestatement.empty() )
	      outfile << endl ;
	    else {
	      outfile << token_packer.token_groups[b].setedline << "  ";
	      if ( token_packer.token_groups[b].error.empty() ) {
	      	if ( token_packer.token_groups[b].end || token_packer.token_groups[b].comment )
	        outfile << "          ";
	        else
	          outfile << token_packer.token_groups[b].hex_location << "      ";
	        if ( token_packer.token_groups[b].label.empty() && !token_packer.token_groups[b].comment )
	          outfile << "        ";
		    outfile << token_packer.token_groups[b].sourcestatement << "  ";
		    for ( int i = token_packer.token_groups[b].sourcestatement.length() ; i < 50 ; i++ )
	          outfile << " ";
	        //cout << token_packer.token_groups[b].ins << token_packer.token_groups[b].objectcode << endl ; // test
	        if ( !token_packer.token_groups[b].pseudo && !token_packer.token_groups[b].comment )
		      outfile << token_packer.token_groups[b].objectcode;
		    //outfile <<  getpacker( token_packer.token_groups[b]) ; //�g�J�ɮ� //TEST
		    outfile << endl;
		  } // if
		  else
		    outfile << token_packer.token_groups[b].error << endl;
		} // else
	} // for
	outfile.close();//�g�ɧ��������ɮ� 
} // sic

void sicxe () {
	Sicxe_Instruction_Set sicxe[59];  //��sicxe�����O�� 
	Sicxe_Instruction_input( sicxe );
	Table table1[59];  //��table1  59�Ӥ���     Instruction
	Table table2[9];  //��table2  9�Ӥ���       Pseudo and Extra �ڼW�[�FEQU LTORG BASE
	Table table3[9];  //��table3  9�Ӥ���       Register
	Table table4[13];  //��table4  13�Ӥ���     Delimiter
	Table table5[100];  //��table5  100�Ӥ���   Symbol
	Table table6[100];  //��table6  100�Ӥ���   Integer/Real
	Table table7[100];  //��table7  100�Ӥ���   String , table4 );
	Packed_Token token_packer; //��@��@��]�˦n��Tokens
	token_packer.amount = 0;
	tableinput( table1, table2, table3, table4 );
    ifstream newfile; 
    ofstream outfile;
    string demo("SICXE_input.txt");  //���g�@�Ӧr��demo 
	newfile.open(demo.c_str()); //�}���ɮ�
	demo.replace(demo.find("input"), 5, "output");
	outfile.open(demo.c_str()); //�g�J�ɮ�
	string line;
	string token;
	int tokentype = 0;
	int tokenvalue = 0;
	int is_string = 0; // C'EOF'�N��EOF�r��
	int is_integer = 0; // X'F1'�N��16�i�쪺F1
	while ( getline(newfile, line) ) {
		//cout << line << endl ; // test
	  if ( !line.empty() )
	    if ( token_packer.amount != 0 )
	      token_packer.token_groups[token_packer.amount].line =  token_packer.token_groups[token_packer.amount-1].line + 5;
	    else 
	      token_packer.token_groups[token_packer.amount].line = 5;
	  token_packer.token_groups[token_packer.amount].sourcestatement = line ;  //�C�檺�s��l�{�� 
	  if ( token_packer.token_groups[token_packer.amount].sourcestatement[0] == '\t' )
	    token_packer.token_groups[token_packer.amount].sourcestatement.erase( 0, 1 );
	  if ( token_packer.longestnum < line.length() ) //�����̪���source 
	    token_packer.longestnum = line.length();
	  //cout << line << endl ; // test
	  token_packer.token_groups[token_packer.amount].amount = 0;  //�C�檺token�q�Y�}�l��n�k�s 
	  is_string = 0;
	  is_integer = 0;
	  for ( int a = 0; a < line.length() ; a++ ) { 
	  	if ( line[a] == '.' ) { 
	  	  token_packer.token_groups[token_packer.amount].comment = true;
	  	  break;
	  	} // if 
	  	token.append(1, line[a]);
	  	if ( is_string != 1 && is_integer != 1 ) {
	  	  while ( !iswhitespce( line[a] ) && !isOp( line[a] ) && a+1 < line.length() ){ //���otoken 
            a++;
	  		token.append(1, line[a]);
	  		//cout << endl << token ; // test
	  		int end = a+1;
	  		if ( end >= line.length() )
	  		  break;
		  } //while
		} // if
		else if ( is_string == 1 || is_integer == 1 ) {
		  while ( int(line[a+1]) != 39 ){ //string��integer���otoken 
            a++;
	  		token.append(1, line[a]);
		  } //while
		} // if else
		
		//cout << endl << token ; // test
		if ( int(line[a]) == 39 && (int(line[a-1]) == 99 || int(line[a-1]) == 67) ) { // C'EOF'�N��EOF�r��
		  token.erase(0,1);
		  is_string ++;
	    } // if
	    if ( int(line[a]) == 39 && (int(line[a-1]) == 120 || int(line[a-1]) == 88) ) { // X'F1'�N��16�i�쪺F1
	      token.erase(0,1);
		  is_integer ++;
	    } // if
	    
	    if ( iswhitespce( line[a] ) )
	       removewhitespace( token ); //������whitespce 
	    
	    if ( isOp( line[a] ) && is_string != 1 && is_integer != 1 && token.length() != 1 ) {  //���token ���o�e������token�M��˰h�᭱���� delimiter �U�@�Ӧb�� 
			token.erase(token.length()-1, 1); //�R���᭱���� delimiter
			if ( find( token, table1, table2, table3, table4, 
              table5, table6, table7, tokentype, tokenvalue ) ) { //��btable�̧�� 
              ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		    } // if 
		    else if ( !find( token, table1, table2, table3, table4, 
              table5, table6, table7, tokentype, tokenvalue ) ) { // �btable�䤣��A�ۤv�� 
              string upper = to_upper(token); 
		      if ( isNumber( upper ) ) {  //�P�_�O�_��table6:�Ʀr
		        tokentype = 6;
		        instable( upper, table6, tokentype, tokenvalue);  
		      } // if
		      else {  //�P�_�O�_��table5
		        tokentype = 5;
		        instable( upper, table5, tokentype, tokenvalue);
		      } // else
		      ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		    } //else  if 
			a--; //�˰h 
		}//if 
		else if ( isOp( line[a] ) && token.length() == 1 ) {  //�@��token delimiter 
		  if ( find( token, table1, table2, table3, table4, 
            table5, table6, table7, tokentype, tokenvalue ) ) { //��btable�̧�� 
            ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  } // if 
		}//else  if 
		else if ( is_string == 1 && !isOp( line[a] )  ) {  //�Ostr !isOp( line[a] ) ->�קK�O' 
          tokentype = 7;
		  instable( token, table7, tokentype, tokenvalue);
		  ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  is_string ++;
		}//else  if
		else if ( is_integer == 1 && !isOp( line[a] )  ) {  //�Ointeger  !isOp( line[a] ) ->�קK�O'
          string upper = to_upper(token); 
          tokentype = 6;
		  instable( upper, table6, tokentype, tokenvalue);
		  ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue); 
		  is_integer ++;
		}//else  if
		else if ( !onespace( token ) && !token.empty() ){ 
		  if ( find( token, table1, table2, table3, table4, 
            table5, table6, table7, tokentype, tokenvalue ) ) { //��btable�̧�� 
            ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  } // if 
		  else if ( !find( token, table1, table2, table3, table4, 
            table5, table6, table7, tokentype, tokenvalue ) ) { // �btable�䤣��A�ۤv�� 
		    if ( is_integer == 1 ) { //�P�_�O�_��table7:literal('�r��') 
		      tokentype = 7;
		      instable( token, table7, tokentype, tokenvalue);
	     	} // if
		    else if ( isNumber( token ) ) { //�P�_�O�_��table6:�Ʀr�ε�����H
		      string upper = to_upper(token); 
		      tokentype = 6;
		      instable( upper, table6, tokentype, tokenvalue); 
		    } // else if
		    else {  //�P�_�O�_��table5
		      string upper = to_upper(token); 
		      tokentype = 5;
		      instable( upper, table5, tokentype, tokenvalue); 
		    } // else
		    ins_packer(token_packer.token_groups[token_packer.amount], token, tokentype, tokenvalue);
		  } //else  if 
		} // else  if	
	    token.clear();
	  } // for 
	  if ( !token_packer.token_groups[token_packer.amount].sourcestatement.empty() && !token_packer.token_groups[token_packer.amount].comment )
	     sicxe_RecordAndSyntax( token_packer, token_packer.token_groups[token_packer.amount], sicxe ) ; // �����@��@�檺label ins group1 group2/ ����nixpb�M�O�_forward reference
	  int temp = token_packer.amount-1; //�W�@�� 
	  if ( temp != -1 )
	    while ( token_packer.token_groups[temp].EQU )
	      temp--;
	  if ( temp != -1 && !token_packer.token_groups[token_packer.amount].EQU && !token_packer.token_groups[token_packer.amount].START )
	    token_packer.token_groups[token_packer.amount].location = token_packer.token_groups[temp].location + token_packer.token_groups[temp].label_length;
	  sicxe_setlocation ( token_packer.token_groups[token_packer.amount].location, token_packer.token_groups[token_packer.amount].hex_location );
	  sicxe_setline( token_packer.token_groups[token_packer.amount].setedline, token_packer.token_groups[token_packer.amount].line ) ;
	  sicxe_setcode( token_packer, token_packer.token_groups[token_packer.amount] );
	  token_packer.amount++;
	} // while
	sicxe_setbase(token_packer);
	sicxe_resetcodedisp(token_packer); //format3 && !forwardreference
	sicxe_pass2( token_packer );
	newfile.close();//Ū�ɧ��������ɮ�
	outfile << "Line" << "  " << "Location" << "  " ;
	outfile << "Source code" ;
	for ( int i = 10 ; i < 50 ; i++ )
	  outfile << " ";
	outfile << "  ";
	outfile << "Object code" << endl ;
	outfile << "----" << "  " << "--------" << "  " ;
	outfile << "-----------" ;
	for ( int i = 10 ; i < 50 ; i++ )
	  outfile << " ";
	outfile << "  ";
	outfile << "-----------" << endl ;
	for ( int b = 0 ; b < token_packer.amount; b++) { //TEST
	    outfile << token_packer.token_groups[b].setedline << "  ";
	    if ( token_packer.token_groups[b].error.empty() ) {
	      if ( token_packer.token_groups[b].end || token_packer.token_groups[b].comment || token_packer.token_groups[b].base )
	        outfile << "          ";
	      else
	        outfile << token_packer.token_groups[b].hex_location << "      ";
	      if ( token_packer.token_groups[b].label.empty() )
	        outfile << "        ";
		  outfile << token_packer.token_groups[b].sourcestatement << "  ";
		  for ( int i = 10 ; i < 50 ; i++ )
	        outfile << " ";
		  outfile << token_packer.token_groups[b].objectcode;
		  //outfile <<  getpacker( token_packer.token_groups[b]) ; //�g�J�ɮ� //TEST
		  outfile << endl;
		} // if
		  else
		    outfile << token_packer.token_groups[b].error << endl;
	} // for
    //Sicxe_Instruction_print( sicxe ); // test
	outfile.close();//�g�ɧ��������ɮ� 
} // sicxe

int main() {
	int command = 0; //�Ĥ@��input(0, 1, 2)
	do { 
	  cout << endl << "** Assembler **";
	  cout << endl << "* 0. Quit     *";
	  cout << endl << "* 1. SIC      *"; 
	  cout << endl << "* 2. SICXE    *"; 
	  cout << endl << "***************"; 
	  cout << endl << "Input a command(0, 1, 2): "; 
	  cin >> command;  //cin�Ĥ@��input(0, 1, 2)
	  switch(command){
	  	case 0 : break;
	  	case 1 : 
	      sic();
	      break;
	    case 2 : 
	      sicxe();  
	      break;
	    default : cout << endl << "Command does not exist!" << endl; //input 0,1,2�H�~�� 
	  }
	} while ( command != 0 );
	system ( "pause" );
	return 0;
} //main


