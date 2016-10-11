/****************************************************** 
** Program: play_cf.cpp 
** Author: Michael Phelps
** Date: 04/08/2014 
** Description: contains main function for connect for
** Input: dimensions, win length, moves
** Output: Board view, win announcement
******************************************************/
#include "connect_four.h"

using namespace std;

int main(int argc, char** argv){
	Game g = Game();

	getCmdArg(g, argv, argc); //Attempts to set initial variables off command line

	do{
		getInitialInput(g); //Has the user input any necessary variables which arn't set
		g.board = makeBoard(g.rows, g.cols); //Initializes the board with blank spaces
		play(g); //Plays the game
		g = Game();
	} while(playAgain());

}