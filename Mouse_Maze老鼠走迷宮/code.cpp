//DS1101ex2_��27��_10833230�����t_10844149�©y�x 
#include<iostream>    // cin,cout,endl
#include<string>      // c_str,length
#include<cstdlib>     //strtoul,system
# include <vector>
#include<fstream>
#include<typeinfo>
using namespace std;
struct Maze {
	int column, row; //�ɮפ@�}�l���Ʀr  �Ĥ@�ӼƬOrow �C  �ĤG�ӼƬO column ��  
	char data[100][100]; //���ɮפG���}�C 
	int num;  //�������\�����u�B�� 
	char visitedX[100] , visitedY[100] ; //�s�����L���y��
	bool cannotfind; //��{�̫᪺�̫�O�_���G 
	bool open; //��{�O�_�i�H�}�� 
	int columnMax, rowMax ; //�������}�C��C�U�۳̤j�� 
	int Gnum ; //�ؼм� 
	int length ; //���� 
	bool shortfind ;//�O�_���̵u���u  
};

void initialstruct ( Maze &M ) {
	M.cannotfind = false;
    M.column = 0;
    M.data[100][100] ={0};
	M.num = 0;
	M.open = false;
	M.row = 0;
	M.visitedX[100] ={0};
	M.visitedY[100] ={0};
	M.columnMax = 0;
	M.rowMax = 0;
	M.Gnum = 0;
	M.length = 0;
	M.shortfind = false;
}

void inputfile( Maze &M ) {  //get the file from user
    initialstruct ( M ); //��l��Maze 
	string inputS;
	string demo("input.txt");  //���g�@�Ӧr��demo 
	cout << endl << "Input a file number (e.g., 201, 202, ...): ";   
	cin >> inputS;   
	demo.insert(5, inputS); //�A�N�ϥΪ̿�J���r�괡�Jdemo 
	ifstream newfile; 
	newfile.open(demo.c_str()); //�}���ɮ�
	if (!newfile.is_open()) {  
        cout << endl << demo << " does not exist!" << endl;
    } 
	else {
	  M.open = true;  
	  newfile >> M.row; //�Ĥ@�ӼƬO�C�ơ]row�^
	  newfile >> M.column;  //�ĤG�ӼƬO��ơ]column�^
	  for (int a = 0; a < M.column ; a++) { //�w�q��]column�^�j��
		for (int b = 0; b < M.row ; b++) { //�w�q�C�]row�^�j��
			newfile >> M.data[a][b];//��C���_�j����ɮת����e���@�ӤG���}�C  
		}
	  }
	  newfile.close();//Ū�ɧ��������ɮ�
	}
	
	M.columnMax = M.column ; //�������}�C��ơA�N���Ƴ̤j��o 
	M.rowMax = M.row ;       //�������}�C�C�ơA�N��C�Ƴ̤j��o

}


void right( Maze &M, Maze &Copy, int &column, int &row ) {
	if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && ( row+1 ) < M.rowMax && Copy.data[column][row]!= 'G' ){ //���k�U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(�٨S�W�L�@�}�l�ɮ׵����C��
		M.visitedX[M.num]= column ; //�]�w�o�B�O���L�� 
		M.visitedY[M.num] = row ;
		M.num++ ; //�U�@�B 
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //���L���ܦ�V 
		row++;//���k�@�� 
		right( M, Copy, column, row );
	}//���k�i���i�� 
}

void left( Maze &M, Maze &Copy, int &column, int &row ) {
	if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && ( row-1 ) >= 0 && Copy.data[column][row]!= 'G' ){ //�����U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(�C�ƨS���ܭt�� 
		M.visitedX[M.num]= column ;  //�]�w�o�B�O���L��
		M.visitedY[M.num] = row ;
		M.num++ ;  //�U�@�B  
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //���L���ܦ�V 
		row--;;//�����@�� 		
		left( M, Copy, column, row );			
	} //�����i���i��
}

void down( Maze &M, Maze &Copy, int &column, int &row ) {
	if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && ( column+1 )< M.columnMax && Copy.data[column][row]!= 'G' ){ //���U�U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(�٨S�W�L�@�}�l�ɮ׵������ 
		M.visitedX[M.num]= column ; //�]�w�o�B�O���L��
		M.visitedY[M.num] = row ;
		M.num++ ; //�U�@�B  
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //���L���ܦ�V 
		column++;//���U�@�� 
		down( M, Copy, column, row );
	}//���U�i���i��
}

void up( Maze &M, Maze &Copy, int &column, int &row ) {
	if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >= 0 && Copy.data[column][row]!= 'G' ) {  //���W�U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(��ƨS���ܭt�� 
		M.visitedX[M.num]= column ; //�]�w�o�B�O���L�� 
		M.visitedY[M.num] = row ;
		M.num++ ; //�U�@�B  
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //���L���ܦ�V 
		column--;//���W�@�� 
		up( M, Copy, column, row );
	}
}

void case1( Maze &M, Maze &Copy ) {  //���Ȥ@ �q���W���X�o����ؼ� G���@�����| 
	int column = 0, row = 0;  
	int check = false;
	while( Copy.data[column][row]!='G' && check == false ){  //�٨S���ؼЦӥB�]�٨S�������L
	    if ( Copy.data[column][row]=='G' ) { //���ؼ� 
		  check = true;
	    }
	    else if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && ( row-1 ) >= 0 && Copy.data[column][row]!= 'G' ){ //�����U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(�C�ƨS���ܭt��
			left( M, Copy, column, row );		
	    } //�����i���i��
	    else if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && ( row+1 ) < M.rowMax && Copy.data[column][row]!= 'G' ){ //���k�U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(�٨S�W�L�@�}�l�ɮ׵����C��
		  right( M, Copy, column, row );
	    }//���k�i���i�� 
	    else if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >= 0 && Copy.data[column][row]!= 'G' ) {  //���W�U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(��ƨS���ܭt�� 
			up( M, Copy, column, row );
		}//���W�i���i��
	    else if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && ( column+1 )< M.columnMax && Copy.data[column][row]!= 'G' ){ //���U�U�@�B���O��ê�]���O���L�����B�]�٨S����ɥ~(�٨S�W�L�@�}�l�ɮ׵������ 
			down( M, Copy, column, row );
		}//���U�i���i��	
		else{ //�����O�A�즺�� �A�ҥH�˰h�@�B
			Copy.data[column][row]='V' ; //���L���ܦ�V 
			M.num--;  //�˰h�@�B
			column = M.visitedX[ M.num ] ; //�h�^�e�@�Ӯy�� 
			row = M.visitedY[ M.num ] ; 
			if ( M.num == 0 && Copy.data[column][row] == 'V' && Copy.data[column+1][row] =='V' )  { //�䤣��G 
				M.cannotfind = true;
				check = true;
			}
	    }
	}//while
}

void case1print( Maze &M, Maze &Copy ) {
	if ( !M.cannotfind ) { //�����\��쪺 
		for (int a = 0; a < Copy.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < Copy.row ; b++) { //�w�q�C�]row�^�j��
			cout << Copy.data[a][b]; //�����@�Ӥ@�ӦL�Xcopy�A���L�����u���w����V 
			if ( b+1 == Copy.row ) //�@�C�@�C�L���n����  
			  cout << endl; 
		  }
	    }
	    cout << endl;
	    for ( int i = 0; i < M.num ; i++ ) {  
		  M.data[ M.visitedX[ i ]][M.visitedY[ i ] ] ='R' ;  
        }
        for (int a = 0; a < M.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < M.row ; b++) { //�w�q�C�]row�^�j��
			cout << M.data[a][b];  
			if ( b+1 == M.row ) //�@�C�@�C�L���n����  
			  cout << endl; 
		  }
	    }
    }
	else { //�S�����\��쪺 
		for (int a = 0; a < Copy.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < Copy.row ; b++) { //�w�q�C�]row�^�j��
			cout << Copy.data[a][b]; //�����@�Ӥ@�ӦL�Xcopy�A���L�����u���w����V 
			if ( b+1 == Copy.row ) //�@�C�@�C�L���n����  
			  cout << endl; 
		  }
	    }
	}
	cout << endl; 
}

int getM( ) {  //get a number from user
	int temp ;
	string inputS;
	bool isNum;
	do {
		cout << endl << "Number of G (goals): ";
		cin >> inputS;
		isNum = true;
		for ( int i = 0 ; ( i < inputS.length() ) && ( isNum ) ; i++ )
		  if ( ( inputS[i] >'9' ) || ( inputS[i] < '0' ))
		    isNum = false;
		if ( !isNum )
		  continue;
		temp = strtoul ( inputS.c_str(), NULL, 10);
		if ( temp >=1 && temp <= 100 )
		  break;
		else 
		  cout << endl << "### The number must be in [1,100] ###" << endl ;
	} while (true);
	return temp;
}

void G ( Maze &M ) { //���ȤG �W�[�@�Ӷ���:�n����J�n���X�ӥؼ� 
		M.Gnum = getM() ;
}

void case2( Maze &M, Maze &Copy, Maze &printdata ) {  // ���ȤG �q���W���X�o���L N �ӥؼЪ��@�����| 
	int column = 0, row = 0;
	bool check = false; //�w����ؼмƩΤw���������٨S������ˬd 
	int i = 0; //�������X��G�F 
	while( check == false ){  //�٨S����ؼЦӥB�]�٨S�������L 
	  if ( Copy.data[column][row]=='G' ) { //���ؼ� 
		i++; //�W�[�@�ӥؼм� 
		Copy.data[column][row]='K'; //�N��L���ؼЧ令K 
		for ( int a = 0; a < M.num ; a++ ) {
	      if ( Copy.data[M.visitedX[ a ]][M.visitedY[ a ]] == 'V' )
		    printdata.data[ M.visitedX[ a ]][M.visitedY[ a ] ] ='V' ; //�C�����ؼЪ����u���� 
		}
		if ( i == M.Gnum ) //�ˬd����ؼФF�S 
		  check = true; 
	  }
	  else if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && (row-1) >= 0 && Copy.data[column][row-1]!= 'K' ){ //�����U�@�B���O��ê���O��L���ؼФ]���O���L�����B�]�٨S����ɥ~(�C�ƨS���ܭt�� 
		left( M, Copy, column, row );				
	  } //�����i���i��	
	  else if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && (row+1) < M.rowMax  && Copy.data[column][row+1]!= 'K' ){  //���k�U�@�B���O��ê���O��L���ؼФ]���O���L�����B�]�٨S����ɥ~(�٨S�W�L�@�}�l�ɮ׵����C�� 
		right( M, Copy, column, row );
	  }//���k�i���i�� 
	  else if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >=0 && Copy.data[column-1][row]!= 'K' ) { //���W�U�@�B���O��ê���O��L���ؼФ]���O���L�����B�]�٨S����ɥ~(��ƨS���ܭt�� 
	    up( M, Copy, column, row );
	  }//���W�i���i��
	  else if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && (column+1) < M.columnMax && Copy.data[column+1][row]!= 'K' ){ //���U�U�@�B���O��ê���O��L���ؼФ]���O���L�����B�]�٨S����ɥ~(�٨S�W�L�@�}�l�ɮ׵������ 
	    down( M, Copy, column, row );
	  }//���U�i���i��
	  else{ //�����O�A�즺�� �A�ҥH�˰h�@�B 
	    if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //���L���ܦ�V 
		M.num--; //�˰h�@�B
		column = M.visitedX[ M.num ] ; //�h�^�e�@�Ӯy��  
		row = M.visitedY[ M.num ] ; 
		if ( M.num == 0 && Copy.data[column][row] == 'V' ) { //�O�_�^����I 
			M.cannotfind = true;
			check = true;
		} 
	  }
	}//while
}

void case2print( Maze &M, Maze &Copy, Maze &printdata ) {
	if ( !M.cannotfind ) { //�����\��쪺 
	    for (int a = 0; a < Copy.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < Copy.row ; b++) { //�w�q�C�]row�^�j��
		    if ( Copy.data[a][b] == 'K')  //���N�e����L��L���ؼЧ�^G 
		      Copy.data[a][b] = 'G';  
			cout << Copy.data[a][b];  //�����@�Ӥ@�ӦL�Xcopy�A���L�����u���w����V 
			if ( b+1 == Copy.row ) //�@�C�@�C�L���n����  
			  cout << endl;  
		  }
	    }
	    cout << endl;
	    for (int a = 0; a < M.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < M.row ; b++) { //�w�q�C�]row�^�j��
		    if ( printdata.data[a][b] == 'V')  
		      printdata.data[a][b] = 'R';
			cout << printdata.data[a][b];  
			if ( b+1 == M.row ) //�@�C�@�C�L���n���� 
			  cout << endl;  
		  }
	    }
    }
	else { //�S�����\��쪺 
		for (int a = 0; a < Copy.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < Copy.row ; b++) { //�w�q�C�]row�^�j��
		    if ( Copy.data[a][b] == 'K')  //���N�e����L��L���ؼЧ�^G 
		      Copy.data[a][b] = 'G';  
			cout << Copy.data[a][b];  //�����@�Ӥ@�ӦL�Xcopy�A���L�����u���w����V 
			if ( b+1 == Copy.row ) //�@�C�@�C�L���n����  
			  cout << endl;  
		  }
	    }
	}
	cout << endl; 
}


void case3( Maze &M, Maze &Copy, Maze &printdata ) { 
	int column = 0, row = 0;
	bool check = false; //�O�_���x�s�����׵u 
	int i = 0; //�������X��G�F 
	M.length = M.columnMax * M.rowMax ;
	while( check == false ){  
	  if ( Copy.data[column][row]=='G' ) {
		i++;
		Copy.data[column][row]='K';
		if ( M.num + 1 < M.length || i == 1 ) { 
		  M.length =M.num + 1 ;
		  initialstruct ( printdata );
		  for ( int a = 0; a < M.num ; a++ ) {
	        if ( Copy.data[M.visitedX[ a ]][M.visitedY[ a ]] == 'V' )
		      printdata.data[ M.visitedX[ a ]][M.visitedY[ a ] ] ='V' ; //�C�����ؼЪ����u���� 
		  }
		} 
      	M.num--;
		column = M.visitedX[ M.num ] ;
		row = M.visitedY[ M.num ] ; //�h�^�e�@�Ӯy��
	  }
	  else if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && (row-1) >= 0 && Copy.data[column][row-1]!= 'K'&& M.num + 1 < M.length ){
		left( M, Copy, column, row );				
	  } //�����i���i��	
	  else if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && (row+1) < M.rowMax  && Copy.data[column][row+1]!= 'K' && M.num + 1 < M.length ){ 
		right( M, Copy, column, row );
	  }//���k�i���i�� 
	  else if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >=0 && Copy.data[column-1][row]!= 'K'&& M.num + 1 < M.length ) {
	    up( M, Copy, column, row );
	  }//���W�i���i��
	  else if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && (column+1) < M.columnMax && Copy.data[column+1][row]!= 'K'&& M.num + 1 < M.length ){
	    down( M, Copy, column, row );
	  }//���U�i���i��
	  else{
	  	if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //���L���ܦ�V 
		M.num--;
		column = M.visitedX[ M.num ] ;
		row = M.visitedY[ M.num ] ; //�h�^�e�@�Ӯy�� 
		if ( M.num == 0 && Copy.data[column][row] == 'V' ) { //�w���L�Ҧ����u�Τw���̵u���u 
			if ( i > 0 )
			M.shortfind = true;
			check = true;
	    }  
	  }
	}//while
}

void case3print( Maze &M, Maze &Copy, Maze &printdata ) {
	if ( M.shortfind ) {
	    for (int a = 0; a < Copy.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < Copy.row ; b++) { //�w�q�C�]row�^�j��
		    if ( Copy.data[a][b] == 'K')
		      Copy.data[a][b] = 'G';
			cout << Copy.data[a][b];  
			if ( b+1 == Copy.row )
			  cout << endl;  
		  }
	    }
	    cout << endl;
	    for (int a = 0; a < M.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < M.row ; b++) { //�w�q�C�]row�^�j��
		    if ( printdata.data[a][b] == 'V')
		      printdata.data[a][b] = 'R';
			cout << printdata.data[a][b];  
			if ( b+1 == M.row )
			  cout << endl;  
		  }
	    }
	    cout << endl;
	    cout << endl << "Shortest path length = " << M.length << endl ; 
    }
	else {
		for (int a = 0; a < Copy.column ; a++) { //�w�q��]column�^�j��
		  for (int b = 0; b < Copy.row ; b++) { //�w�q�C�]row�^�j��
			cout << Copy.data[a][b];  
			if ( b+1 == Copy.row )
			  cout << endl;  
		  }
	    }
	    cout << endl << endl << "### There is no path to find a goal! ###" << endl  ;
	}
}


int main() {
	int command = 0; //�Ĥ@��input(0, 1, 2)
	do {  
	  cout << endl << "*** Path Finding ***";
	  cout << endl << "* 0. Quit          *";
	  cout << endl << "* 1. One goal      *"; 
	  cout << endl << "* 2. More goals    *"; 
	  cout << endl << "* 3. Shortest path *";
	  cout << endl << "********************"; 
	  cout << endl << "Input a command(0, 1, 2, 3): "; 
	  cin >> command;  //cin�Ĥ@��input(0, 1, 2, 3)
	  switch(command){	
	  	case 0 : break;
	  	case 1 :   
	  	  Maze M ;
	  	  initialstruct ( M ); //��l��Maze
	  	  inputfile( M );
		  if ( M.open ) {
		  	Maze Copy = M; //���᭱print���ɭԦ��\�i�H�uprint���\��
		  	case1( M, Copy );
	  	    case1print( M, Copy );
		  }
		  break;
	    case 2 :  
	      Maze N ;
	      inputfile( N );
	      if ( N.open ) {
		    G ( N ); // input �n��X��G 
		    Maze Copy = N; //���᭱print���ɭԦ��\�i�H�uprint���\��
		    Maze printdata = N; //���᭱print���ɭԥi�Hprint��h��G�����u 
		    case2( N, Copy, printdata );
		    case2print( N, Copy, printdata );
	      }
	      break;
	    case 3 :   
	      Maze O ;
	      inputfile( O );
	      if ( O.open ) {
		    Maze Copy = O; //���᭱print���ɭԦ��\�i�H�uprint���\��
		    Maze printdata = O; //���᭱print���ɭԥi�Hprint��h��G�����u 
		    case3( O, Copy, printdata );
		    case3print( O, Copy, printdata );
	      }
	      break;
	    default : cout << endl << "Command does not exist!" << endl; //input 0,1,2�H�~�� 
	  }
	} while ( command != 0 );
	system ( "pause" );
	return 0;
}


