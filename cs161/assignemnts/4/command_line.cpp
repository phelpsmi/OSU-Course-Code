/********************************************************************* 
 ** Program Filename: integral.cpp
 ** Author: Michael Phelps
 ** Date: 2/11/2014
 ** Description: Computes the integral of multiple equations
 ** Input: integral boundaries, rectangle count, integration style
 ** Output: Estimation of integrals
 *********************************************************************/ 
#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>

#define F1 "2x^5 + x^3 - 10x + 2"
#define F2 "6x^2 - x + 10"
#define F3 "5x + 3"
#define F4 "2x^3 + 120"
#define F5 "2x^2" 
#define INITDOUBLE 2555.456124

using namespace std;

void getInput(int &, double &, double &, char &, int &);
double f1(double);
double f2(double);
double f3(double);
double f4(double);
double f5(double);
double f(double, int);
double intRec(float, float, int, int);
double intTrap(float, float, int, int);
void runFunctions(double, double, int, char, int);
bool validInt(string s);
bool validDouble(string s);
void getCmdArg(int &, double &, double &, char &, int &, char **, int count );

main(int argc, char* argv[]){
	double start = INITDOUBLE, end = INITDOUBLE;
	int itCount = -1, function = 0;
	char method = 'a';

	getCmdArg(itCount, start, end, method, function, argv, argc);
	getInput(itCount, start, end, method, function);
	runFunctions(start, end, itCount, method, function);
}

void getCmdArg(int &itCount, double &start, double &end, char &method, int &function, char **arg, int count){
	for (int i = 1; i < count-1; i ++){
		if(arg[i][0] == '-'){
			switch(arg[i][1]){
				case 'n': if (validInt(string(arg[i+1]))){
					itCount = atoi(arg[i+1]);
				}
				break;
				case 'a': if (validDouble(string(arg[i+1]))){
					start = atoi(arg[i+1]);
				}
				break;
				case 'b': if (validDouble(string(arg[i+1]))){
					end = atoi(arg[i+1]);
				}
				break;
				case 'm': method = arg[i+1][0];
				break;
				case 'f': if (validInt(string(arg[i+1]))){
					function = atoi(arg[i+1]);
				}
				break;
			}
		}
	}
	return;
}

bool validInt(string s){
   for(int x=0;x < s.size();++x){
     if(!isdigit( s.at(x) )){
     	if(!x == 0 && !s.at(x) == '-')
     		return false;
     }
   }
   return true;
}

bool validDouble(string s){
	bool has_dot = false;

	for(int x=0; x < s.size(); ++x){
		if(isdigit( s.at(x) )){
		} else if(s.at(x) == '.' && !has_dot){
			has_dot == true;
		} else if(x == 0 && s.at(x) == '-'){
		} else{
			return false;
		}
	}

	return true;
}

/********************************************************************* 
 ** Function: getInput
 ** Description: gets the initial input from the user
 ** Parameters: int, double, double, int, int by address
 ** Pre-Conditions: none
 ** Post-Conditions: method is 1,2,3
 *********************************************************************/ 
void getInput(int &itCount, double &start, double &end, char &method, int &function){
	string s;

	while(function < 0 && function > 6){
		cout << "Pick a function (1-5): ";
		cin >> s;
		if(validInt(s))
			function = atoi(s.c_str());
	}
	while(start == INITDOUBLE){
		cout << "Input left bound: ";
		cin >> s;
		if(validDouble(s))
			start = atoi(s.c_str());
	}
	while(end == INITDOUBLE){
		cout << "Input right bound: ";
		cin >> s;
		if(validDouble(s))
			end = atoi(s.c_str());
	}
	while(itCount <= 0){
		cout << "Input number of iterations: ";
		cin >> s;
		if(validInt(s))
			itCount = atoi(s.c_str());
	}
	while(method != 'r' && method != 't' && method != 'b'){
		cout << "Input method (r - Rectangle, t - Trapazoid, b - Both): ";
		cin >> s;
		if(s.length() == 1)
			method = s[0];
	}

	return;
}

/********************************************************************* 
 ** Function: f
 ** Description: runs desired f(x) function
 ** Parameters: double, int
 ** Pre-Conditions: equation is 1,2,3,4,5
 ** Post-Conditions: none
 *********************************************************************/ 
double f1(double x){
	return pow(x,5)*2 + pow(x,5) - 10*x + 2;
}
double f2(double x){
	return 6*pow(x,2) - x + 10;
}
double f3(double x){
	return 5*x + 3;
}
double f4(double x){
	return 2*pow(x,3) + 120;
}
double f5(double x){
	return 2*pow(x,2);
}

double f(double x, int type = 1){
	double y;
	switch(type){
		case 1: y = f1(x);
			break;
		case 2: y = f2(x);
			break;
		case 3: y = f3(x);
			break;
		case 4: y = f4(x);
			break;
		case 5: y = f5(x);
			break;
		default: cout << endl << "Something whent wrong with f() function" << endl;
	}
	return y;
}

/********************************************************************* 
 ** Function: intRec
 ** Description: uses rectangle integration method
 ** Parameters: float, float, int, int
 ** Pre-Conditions: equation is 1,2,3,4,5
 ** Post-Conditions: none
 *********************************************************************/ 
double intRec(float a, float b, int n, int equation){
	double y = a, distance, value = 0, space;
	distance = b - a;
	space = distance/n;

	for(int x=0; x<n; x++){
		value += f(y, equation)*space;
		y += space;
	}
	return value;
}

/********************************************************************* 
 ** Function: intTrap
 ** Description: uses trapezoid integration method
 ** Parameters: float, float, int, int
 ** Pre-Conditions: equation is 1,2,3,4,5
 ** Post-Conditions: none
 *********************************************************************/ 
double intTrap(float a, float b, int n, int equation){
	double y = a, distance, value = 0, space;
	distance = b - a;
	space = distance/n;

	for(int x=0; x<n; x++){
		value += (float)((f(y, equation) + f(y+space, equation))/2.0)*space;
		y += space;

	}
	return value;
}

/********************************************************************* 
 ** Function: runFunctions
 ** Description: runs the desired integration methods
 ** Parameters: double, double, int, int, int
 ** Pre-Conditions: int method is 1,2 or 3
 ** Post-Conditions: none
 *********************************************************************/ 
void runFunctions(double start, double end, int itCount, char method, int f){
	cout << endl;
	if(method == 'r' || method == 'b'){
		cout << "Rectangle Integral: " << intRec(start, end, itCount, f) << endl;
	}
	if(method == 't' || method == 'b'){
		cout << "Trapazoid Integral: " << intTrap(start, end, itCount, f) << endl;
	}
	cout << endl;		
}