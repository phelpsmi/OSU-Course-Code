/********************************************************************* 
 ** Program Filename: connect_four.cpp
 ** Author: Michael Phelps
 ** Date: 4/8/2014
 ** Description: Plays a game of connect four between two people
 ** Input: dimensions, win length, moves
 ** Output: Board view, win announcement
 *********************************************************************/ 
#include "connect_four.h"

using namespace std;

/********************************************************************* 
 ** Function: printBoard
 ** Description: prints the game board
 ** Parameters: char** b, int rows, int cols
 ** Pre-Conditions: rows and cols are possitive
 ** Post-Conditions: none
 *********************************************************************/ 
void printBoard(char** b, int rows, int cols){
	for(int x=0; x < rows; ++x){
		for(int y=0; y < cols; ++y)
			cout << "| " << b[x][y] << ' ';
		cout << "|" << endl;
		for(int y=0; y < cols; ++y)
			cout << "----";
		cout << "-" << endl;
	}
}

/********************************************************************* 
 ** Function: makeBoard
 ** Description: initializes the board with blank spaces
 ** Parameters: int rows, int cols
 ** Pre-Conditions: cols and rows are possitive
 ** Post-Conditions: char** has dimensions rows by cols
 *********************************************************************/ 
char** makeBoard(int rows, int cols){
	char **board;
	board = new char*[rows];

	for(int i = 0; i < rows; ++i){
		board[i] = new char[cols];
	}
	for(int x = 0; x < rows; ++x){
		for(int y = 0; y < cols; ++y){
			board[x][y] = ' ';
		}
	}

	return board;
}

/********************************************************************* 
 ** Function: validInt
 ** Description: returns true if the string can be converted to an int
 ** Parameters: string s
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
bool validInt(string s){
	for(int x=0;x < s.size();++x){
    	if(!isdigit( s.at(x) )){
     		if(!x == 0 && !s.at(x) == '-')
     			return false;
    	}
	}
   return true;
}

/********************************************************************* 
 ** Function: getInt
 ** Description: Retrieves a valid int from the user
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
int getInt(){
	string s;
	cin >> s;
	while(!validInt(s)){
		cout << "Please input a valid integer: ";
		cin >> s;
	}
	return atoi(s.c_str());
}

/********************************************************************* 
 ** Function: getCmdArg
 ** Description: sets all valid command line arguments
 ** Parameters: Game &g, char** arg, int count
 ** Pre-Conditions: count is the amount of argument in arg
 ** Post-Conditions: none
 *********************************************************************/ 
void getCmdArg(Game &g, char** arg, int count){
	string s;
	for (int i = 1; i < count-1; i++){
		s = arg[i+1];
		if(strcmp(arg[i],"-rows") == 0 && validInt(s)){
			g.rows = atoi(arg[i+1]);
		}
		else if(strcmp(arg[i],"-cols") == 0 && validInt(s)){
			g.cols = atoi(arg[i+1]);
		}
		else if(strcmp(arg[i],"-p") == 0 && validInt(s)){
			g.p = atoi(arg[i+1]);
		}
	}
	return;
}

/********************************************************************* 
 ** Function: getInitialInput
 ** Description: Game &g
 ** Parameters: gets user input for rows, cols, win count, color if not set
 ** Pre-Conditions: none
 ** Post-Conditions: g has valid values for rows, cols, p, p1, p2
 *********************************************************************/ 
void getInitialInput(Game &g){
	while(g.rows < 1){
		cout << "Please input the number of rows you want: ";
		g.rows = getInt();
	}
	while(g.cols < 1){
		cout << "Please input the number of columns you want: ";
		g.cols = getInt();
	}
	while((g.p > g.cols && g.p > g.rows) || g.p < 1){
		cout << "Please input the length of pieces to connect: ";
		g.p = getInt();
	}
	string s;
	while(g.p1 != 'r' && g.p1 != 'y'){
		cout << "Player one, do you want red or yellow (r or y)? ";
		cin >> s;
		if(s == "r"){
			g.p1 = 'r'; g.p2 = 'y';
		}
		else if(s == "y"){
			g.p1 = 'y'; g.p2 = 'r';
		}
	}
}

/********************************************************************* 
 ** Function: placePiece
 ** Description: Has a player place a piece
 ** Parameters: Game &g, int player
 ** Pre-Conditions: game board is set, player = (1 || 2)
 ** Post-Conditions: none
 *********************************************************************/ 
void placePiece(Game &g, int player){
	char c;
	int play = 0;
	if(player == 1){
		c = g.p1;
	}
	else{
		c = g.p2;
	}
	while(play < 1 || play > g.cols || g.board[0][play-1] != ' '){
		cout << "Player " << player << ", pick a column to place your piece: ";
		play = getInt();
	}
	g.col = play-1;
	for (int i = g.rows - 1; i >= 0; --i){
		if(g.board[i][play-1] == ' '){
			g.row = i;
			g.board[i][play-1] = c;
			break;
		}
	}
	g.moves++;
}

/********************************************************************* 
 ** Function: countLine
 ** Description: checks connected line length in one direction
 ** Parameters: Game g, int x, int y, int a, int b, char c
 ** Pre-Conditions: int x/y is within cols/rows, a/b = 1 || -1 || 0
 ** Post-Conditions: none
 *********************************************************************/ 
int countLine(Game g, int x, int y, int a, int b, char c){
	int count = 1, i = 1;
	while( x+(a*i) >= 0 && x+(a*i) < g.rows && y+(b*i) >= 0 && y+(b*i) < g.cols && g.board[x+(a*i)][y+(b*i)] == c ){
		count++;
		i++;
	}
	i = -1;
	while( x+(a*i) >= 0 && x+(a*i) < g.rows && y+(b*i) >= 0 && y+(b*i) < g.cols && g.board[x+(a*i)][y+(b*i)] == c ){
		count++;
		i--;
	}
	return count;
}

/********************************************************************* 
 ** Function: checkWin
 ** Description: uses countLine to check if the last move connects to a win
 ** Parameters: Game g, int p
 ** Pre-Conditions: p is 1 or 2
 ** Post-Conditions: none
 *********************************************************************/ 
bool checkWin(Game g, int p){
	char c;
	if(p == 2){
		c = g.p1;
	}
	else{
		c = g.p2;
	}
	if(countLine(g, g.row, g.col, 1, 0, c) >= g.p)
		return true;
	if(countLine(g, g.row, g.col, 0, 1, c) >= g.p)
		return true;
	if(countLine(g, g.row, g.col, 1, 1, c) >= g.p)
		return true;
	if(countLine(g, g.row, g.col, 1, -1, c) >= g.p)
		return true;
	return false;
}

/********************************************************************* 
 ** Function: finish
 ** Description: prints end game message
 ** Parameters: int p
 ** Pre-Conditions: p = 1,2,3
 ** Post-Conditions: none
 *********************************************************************/ 
void finish(int p){
	if(p == 3){
		cout << "All spots have been filled, the game is a draw!" << endl;
	}
	else if(p == 1){
		cout << "Player two WINS!!!" << endl;
	}
	else
		cout << "Player one WINS!!!" << endl;
	exit;
}

/********************************************************************* 
 ** Function: play
 ** Description: iterates between each player's move
 ** Parameters: Game g
 ** Pre-Conditions: game has been initialized
 ** Post-Conditions: none
 *********************************************************************/ 
void play(Game g){
	int player = 1;
	do {
		if(g.moves == g.rows * g.cols){
			finish(3);
			return;
		}
		if(player == 1){
			player = 2;
			placePiece(g, 1);
		}
		else if(player == 2){
			player = 1;
			placePiece(g, 2);
		}
		printBoard(g.board, g.rows, g.cols);
	} while(!checkWin(g, player));
	finish(player);
}

/********************************************************************* 
 ** Function: playAgain
 ** Description: determiines if the player wants to play again
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
bool playAgain(){
	string play = " ";
	while(play != "1" && play != "0"){
		cout << "Would you like to play again? (1 - yes, 0 - no): ";
		cin >> play;
	}
	if(play == "1")
		return true;
	return false;
}