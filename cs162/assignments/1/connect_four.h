/********************************************************************* 
 ** Program Filename: connect_four.h
 ** Author: Michael Phelps
 ** Date: 4/8/2014
 ** Description: function headers and struct for connnect_four.cpp
 ** Input:
 ** Output:
 *********************************************************************/ 
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <string> 
#include <string.h>

struct Game{
	char **board;
	int rows, cols, p, row, col, moves;
	char p1;
	char p2;

	Game(int r = 0, int c = 0, int p = 0):
		rows(r),
		cols(c),
		p1(' '),
		p2(' '),
		row(0),
		col(0),
		moves(0){}
};


void printBoard(char**, int, int);
char** makeBoard(int, int);
bool validInt(std::string);
int getInt();
void getCmdArg(Game &g, char**, int);
void getInitialInput(Game &g);
void placePiece(Game &, int);
int countLine(char**, int, int, int, int, char);
bool checkWin(Game, int);
void finish(int);
void play(Game g);
bool playAgain();