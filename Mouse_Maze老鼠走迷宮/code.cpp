//DS1101ex2_第27組_10833230李郁含_10844149謝宜庭 
#include<iostream>    // cin,cout,endl
#include<string>      // c_str,length
#include<cstdlib>     //strtoul,system
# include <vector>
#include<fstream>
#include<typeinfo>
using namespace std;
struct Maze {
	int column, row; //檔案一開始的數字  第一個數是row 列  第二個數是 column 行  
	char data[100][100]; //放檔案二維陣列 
	int num;  //紀錄成功的路線步數 
	char visitedX[100] , visitedY[100] ; //存取走過的座標
	bool cannotfind; //辨認最後的最後是否找到G 
	bool open; //辨認是否可以開啟 
	int columnMax, rowMax ; //紀錄此陣列行列各自最大數 
	int Gnum ; //目標數 
	int length ; //長度 
	bool shortfind ;//是否找到最短路線  
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
    initialstruct ( M ); //初始化Maze 
	string inputS;
	string demo("input.txt");  //先寫一個字串demo 
	cout << endl << "Input a file number (e.g., 201, 202, ...): ";   
	cin >> inputS;   
	demo.insert(5, inputS); //再將使用者輸入的字串插入demo 
	ifstream newfile; 
	newfile.open(demo.c_str()); //開啟檔案
	if (!newfile.is_open()) {  
        cout << endl << demo << " does not exist!" << endl;
    } 
	else {
	  M.open = true;  
	  newfile >> M.row; //第一個數是列數（row）
	  newfile >> M.column;  //第二個數是行數（column）
	  for (int a = 0; a < M.column ; a++) { //定義行（column）迴圈
		for (int b = 0; b < M.row ; b++) { //定義列（row）迴圈
			newfile >> M.data[a][b];//行列不斷迴圈把檔案的內容放到一個二維陣列  
		}
	  }
	  newfile.close();//讀檔完後關閉檔案
	}
	
	M.columnMax = M.column ; //紀錄此陣列行數，代表行數最大到這 
	M.rowMax = M.row ;       //紀錄此陣列列數，代表列數最大到這

}


void right( Maze &M, Maze &Copy, int &column, int &row ) {
	if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && ( row+1 ) < M.rowMax && Copy.data[column][row]!= 'G' ){ //往右下一步不是障礙也不是走過的路且也還沒到邊界外(還沒超過一開始檔案給的列數
		M.visitedX[M.num]= column ; //設定這步是走過的 
		M.visitedY[M.num] = row ;
		M.num++ ; //下一步 
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //走過的變成V 
		row++;//往右一格 
		right( M, Copy, column, row );
	}//往右可不可行 
}

void left( Maze &M, Maze &Copy, int &column, int &row ) {
	if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && ( row-1 ) >= 0 && Copy.data[column][row]!= 'G' ){ //往左下一步不是障礙也不是走過的路且也還沒到邊界外(列數沒有變負的 
		M.visitedX[M.num]= column ;  //設定這步是走過的
		M.visitedY[M.num] = row ;
		M.num++ ;  //下一步  
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //走過的變成V 
		row--;;//往左一格 		
		left( M, Copy, column, row );			
	} //往左可不可行
}

void down( Maze &M, Maze &Copy, int &column, int &row ) {
	if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && ( column+1 )< M.columnMax && Copy.data[column][row]!= 'G' ){ //往下下一步不是障礙也不是走過的路且也還沒到邊界外(還沒超過一開始檔案給的行數 
		M.visitedX[M.num]= column ; //設定這步是走過的
		M.visitedY[M.num] = row ;
		M.num++ ; //下一步  
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //走過的變成V 
		column++;//往下一格 
		down( M, Copy, column, row );
	}//往下可不可行
}

void up( Maze &M, Maze &Copy, int &column, int &row ) {
	if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >= 0 && Copy.data[column][row]!= 'G' ) {  //往上下一步不是障礙也不是走過的路且也還沒到邊界外(行數沒有變負的 
		M.visitedX[M.num]= column ; //設定這步是走過的 
		M.visitedY[M.num] = row ;
		M.num++ ; //下一步  
		if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //走過的變成V 
		column--;//往上一格 
		up( M, Copy, column, row );
	}
}

void case1( Maze &M, Maze &Copy ) {  //任務一 從左上角出發走到目標 G的一條路徑 
	int column = 0, row = 0;  
	int check = false;
	while( Copy.data[column][row]!='G' && check == false ){  //還沒找到目標而且也還沒全部走過
	    if ( Copy.data[column][row]=='G' ) { //找到目標 
		  check = true;
	    }
	    else if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && ( row-1 ) >= 0 && Copy.data[column][row]!= 'G' ){ //往左下一步不是障礙也不是走過的路且也還沒到邊界外(列數沒有變負的
			left( M, Copy, column, row );		
	    } //往左可不可行
	    else if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && ( row+1 ) < M.rowMax && Copy.data[column][row]!= 'G' ){ //往右下一步不是障礙也不是走過的路且也還沒到邊界外(還沒超過一開始檔案給的列數
		  right( M, Copy, column, row );
	    }//往右可不可行 
	    else if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >= 0 && Copy.data[column][row]!= 'G' ) {  //往上下一步不是障礙也不是走過的路且也還沒到邊界外(行數沒有變負的 
			up( M, Copy, column, row );
		}//往上可不可行
	    else if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && ( column+1 )< M.columnMax && Copy.data[column][row]!= 'G' ){ //往下下一步不是障礙也不是走過的路且也還沒到邊界外(還沒超過一開始檔案給的行數 
			down( M, Copy, column, row );
		}//往下可不可行	
		else{ //都不是，到死路 ，所以倒退一步
			Copy.data[column][row]='V' ; //走過的變成V 
			M.num--;  //倒退一步
			column = M.visitedX[ M.num ] ; //退回前一個座標 
			row = M.visitedY[ M.num ] ; 
			if ( M.num == 0 && Copy.data[column][row] == 'V' && Copy.data[column+1][row] =='V' )  { //找不到G 
				M.cannotfind = true;
				check = true;
			}
	    }
	}//while
}

void case1print( Maze &M, Maze &Copy ) {
	if ( !M.cannotfind ) { //有成功找到的 
		for (int a = 0; a < Copy.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < Copy.row ; b++) { //定義列（row）迴圈
			cout << Copy.data[a][b]; //直接一個一個印出copy，走過的路線都已更改至V 
			if ( b+1 == Copy.row ) //一列一列印完要換行  
			  cout << endl; 
		  }
	    }
	    cout << endl;
	    for ( int i = 0; i < M.num ; i++ ) {  
		  M.data[ M.visitedX[ i ]][M.visitedY[ i ] ] ='R' ;  
        }
        for (int a = 0; a < M.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < M.row ; b++) { //定義列（row）迴圈
			cout << M.data[a][b];  
			if ( b+1 == M.row ) //一列一列印完要換行  
			  cout << endl; 
		  }
	    }
    }
	else { //沒有成功找到的 
		for (int a = 0; a < Copy.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < Copy.row ; b++) { //定義列（row）迴圈
			cout << Copy.data[a][b]; //直接一個一個印出copy，走過的路線都已更改至V 
			if ( b+1 == Copy.row ) //一列一列印完要換行  
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

void G ( Maze &M ) { //任務二 增加一個項目:要先輸入要找到幾個目標 
		M.Gnum = getM() ;
}

void case2( Maze &M, Maze &Copy, Maze &printdata ) {  // 任務二 從左上角出發走過 N 個目標的一條路徑 
	int column = 0, row = 0;
	bool check = false; //已找齊目標數或已走完全部還沒找齊的檢查 
	int i = 0; //紀錄找到幾個G了 
	while( check == false ){  //還沒找齊目標而且也還沒全部走過 
	  if ( Copy.data[column][row]=='G' ) { //找到目標 
		i++; //增加一個目標數 
		Copy.data[column][row]='K'; //將找過的目標改成K 
		for ( int a = 0; a < M.num ; a++ ) {
	      if ( Copy.data[M.visitedX[ a ]][M.visitedY[ a ]] == 'V' )
		    printdata.data[ M.visitedX[ a ]][M.visitedY[ a ] ] ='V' ; //每次找到目標的路線紀錄 
		}
		if ( i == M.Gnum ) //檢查找齊目標了沒 
		  check = true; 
	  }
	  else if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && (row-1) >= 0 && Copy.data[column][row-1]!= 'K' ){ //往左下一步不是障礙不是找過的目標也不是走過的路且也還沒到邊界外(列數沒有變負的 
		left( M, Copy, column, row );				
	  } //往左可不可行	
	  else if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && (row+1) < M.rowMax  && Copy.data[column][row+1]!= 'K' ){  //往右下一步不是障礙不是找過的目標也不是走過的路且也還沒到邊界外(還沒超過一開始檔案給的列數 
		right( M, Copy, column, row );
	  }//往右可不可行 
	  else if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >=0 && Copy.data[column-1][row]!= 'K' ) { //往上下一步不是障礙不是找過的目標也不是走過的路且也還沒到邊界外(行數沒有變負的 
	    up( M, Copy, column, row );
	  }//往上可不可行
	  else if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && (column+1) < M.columnMax && Copy.data[column+1][row]!= 'K' ){ //往下下一步不是障礙不是找過的目標也不是走過的路且也還沒到邊界外(還沒超過一開始檔案給的行數 
	    down( M, Copy, column, row );
	  }//往下可不可行
	  else{ //都不是，到死路 ，所以倒退一步 
	    if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //走過的變成V 
		M.num--; //倒退一步
		column = M.visitedX[ M.num ] ; //退回前一個座標  
		row = M.visitedY[ M.num ] ; 
		if ( M.num == 0 && Copy.data[column][row] == 'V' ) { //是否回到原點 
			M.cannotfind = true;
			check = true;
		} 
	  }
	}//while
}

void case2print( Maze &M, Maze &Copy, Maze &printdata ) {
	if ( !M.cannotfind ) { //有成功找到的 
	    for (int a = 0; a < Copy.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < Copy.row ; b++) { //定義列（row）迴圈
		    if ( Copy.data[a][b] == 'K')  //先將前面改過找過的目標改回G 
		      Copy.data[a][b] = 'G';  
			cout << Copy.data[a][b];  //直接一個一個印出copy，走過的路線都已更改至V 
			if ( b+1 == Copy.row ) //一列一列印完要換行  
			  cout << endl;  
		  }
	    }
	    cout << endl;
	    for (int a = 0; a < M.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < M.row ; b++) { //定義列（row）迴圈
		    if ( printdata.data[a][b] == 'V')  
		      printdata.data[a][b] = 'R';
			cout << printdata.data[a][b];  
			if ( b+1 == M.row ) //一列一列印完要換行 
			  cout << endl;  
		  }
	    }
    }
	else { //沒有成功找到的 
		for (int a = 0; a < Copy.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < Copy.row ; b++) { //定義列（row）迴圈
		    if ( Copy.data[a][b] == 'K')  //先將前面改過找過的目標改回G 
		      Copy.data[a][b] = 'G';  
			cout << Copy.data[a][b];  //直接一個一個印出copy，走過的路線都已更改至V 
			if ( b+1 == Copy.row ) //一列一列印完要換行  
			  cout << endl;  
		  }
	    }
	}
	cout << endl; 
}


void case3( Maze &M, Maze &Copy, Maze &printdata ) { 
	int column = 0, row = 0;
	bool check = false; //是否比儲存的長度短 
	int i = 0; //紀錄找到幾個G了 
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
		      printdata.data[ M.visitedX[ a ]][M.visitedY[ a ] ] ='V' ; //每次找到目標的路線紀錄 
		  }
		} 
      	M.num--;
		column = M.visitedX[ M.num ] ;
		row = M.visitedY[ M.num ] ; //退回前一個座標
	  }
	  else if( Copy.data[column][row-1]!='O' && Copy.data[column][row-1]!='V' && (row-1) >= 0 && Copy.data[column][row-1]!= 'K'&& M.num + 1 < M.length ){
		left( M, Copy, column, row );				
	  } //往左可不可行	
	  else if( Copy.data[column][row+1]!='O' && Copy.data[column][row+1]!='V' && (row+1) < M.rowMax  && Copy.data[column][row+1]!= 'K' && M.num + 1 < M.length ){ 
		right( M, Copy, column, row );
	  }//往右可不可行 
	  else if ( Copy.data[column-1][row]!='O' && Copy.data[column-1][row]!='V' && (column-1) >=0 && Copy.data[column-1][row]!= 'K'&& M.num + 1 < M.length ) {
	    up( M, Copy, column, row );
	  }//往上可不可行
	  else if( Copy.data[column+1][row]!='O' && Copy.data[column+1][row]!='V' && (column+1) < M.columnMax && Copy.data[column+1][row]!= 'K'&& M.num + 1 < M.length ){
	    down( M, Copy, column, row );
	  }//往下可不可行
	  else{
	  	if ( Copy.data[column][row] == 'E' )
		  Copy.data[column][row]='V' ; //走過的變成V 
		M.num--;
		column = M.visitedX[ M.num ] ;
		row = M.visitedY[ M.num ] ; //退回前一個座標 
		if ( M.num == 0 && Copy.data[column][row] == 'V' ) { //已走過所有路線或已找到最短路線 
			if ( i > 0 )
			M.shortfind = true;
			check = true;
	    }  
	  }
	}//while
}

void case3print( Maze &M, Maze &Copy, Maze &printdata ) {
	if ( M.shortfind ) {
	    for (int a = 0; a < Copy.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < Copy.row ; b++) { //定義列（row）迴圈
		    if ( Copy.data[a][b] == 'K')
		      Copy.data[a][b] = 'G';
			cout << Copy.data[a][b];  
			if ( b+1 == Copy.row )
			  cout << endl;  
		  }
	    }
	    cout << endl;
	    for (int a = 0; a < M.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < M.row ; b++) { //定義列（row）迴圈
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
		for (int a = 0; a < Copy.column ; a++) { //定義行（column）迴圈
		  for (int b = 0; b < Copy.row ; b++) { //定義列（row）迴圈
			cout << Copy.data[a][b];  
			if ( b+1 == Copy.row )
			  cout << endl;  
		  }
	    }
	    cout << endl << endl << "### There is no path to find a goal! ###" << endl  ;
	}
}


int main() {
	int command = 0; //第一個input(0, 1, 2)
	do {  
	  cout << endl << "*** Path Finding ***";
	  cout << endl << "* 0. Quit          *";
	  cout << endl << "* 1. One goal      *"; 
	  cout << endl << "* 2. More goals    *"; 
	  cout << endl << "* 3. Shortest path *";
	  cout << endl << "********************"; 
	  cout << endl << "Input a command(0, 1, 2, 3): "; 
	  cin >> command;  //cin第一個input(0, 1, 2, 3)
	  switch(command){	
	  	case 0 : break;
	  	case 1 :   
	  	  Maze M ;
	  	  initialstruct ( M ); //初始化Maze
	  	  inputfile( M );
		  if ( M.open ) {
		  	Maze Copy = M; //讓後面print的時候成功可以只print成功的
		  	case1( M, Copy );
	  	    case1print( M, Copy );
		  }
		  break;
	    case 2 :  
	      Maze N ;
	      inputfile( N );
	      if ( N.open ) {
		    G ( N ); // input 要找幾個G 
		    Maze Copy = N; //讓後面print的時候成功可以只print成功的
		    Maze printdata = N; //讓後面print的時候可以print找多個G的路線 
		    case2( N, Copy, printdata );
		    case2print( N, Copy, printdata );
	      }
	      break;
	    case 3 :   
	      Maze O ;
	      inputfile( O );
	      if ( O.open ) {
		    Maze Copy = O; //讓後面print的時候成功可以只print成功的
		    Maze printdata = O; //讓後面print的時候可以print找多個G的路線 
		    case3( O, Copy, printdata );
		    case3print( O, Copy, printdata );
	      }
	      break;
	    default : cout << endl << "Command does not exist!" << endl; //input 0,1,2以外的 
	  }
	} while ( command != 0 );
	system ( "pause" );
	return 0;
}


