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

#define F1 "2x^5 + x^3 - 10x + 2"
#define F2 "6x^2 - x + 10"
#define F3 "5x + 3"
#define F4 "2x^3 + 120"
#define F5 "2x^2" 

using namespace std;

void getInput(int &, double &, double &, int &, int &);
void cmdLineInput(int &, double &, double &, int &, int &);
double f1(double);
double f2(double);
double f3(double);
double f4(double);
double f5(double);
double f(double, int);
double intRec(float, float, int, int);
double intTrap(float, float, int, int);
void runFunctions(double, double, int, int, int);

main(int argc, char *argv){
	double start, end;
	int itCount, method, function;

	getInput(itCount, start, end, method, function);
	runFunctions(start, end, itCount, method, function);
}

void cmdLineInput(int &itCount, double &start, double &end, int &method, int &function){
	for (int i = 0; i <= argc/2; ++i){
		x = 2*i+1;
		y = argv[x+1];
		switch(argv[x]){
			case "-f": function = atoi(y);
			break;
			case "-a": start = atof(y);
			break;
			case "-b": end = atof(y);
			break;
			case "-m": method = y[0];
			break;
			case "-n": itCount = atoi(y);


		}
	}

}

/********************************************************************* 
 ** Function: getInput
 ** Description: gets the initial input from the user
 ** Parameters: int, double, double, int, int by address
 ** Pre-Conditions: none
 ** Post-Conditions: method is 1,2,3
 *********************************************************************/ 
void getInput(int &itCount, double &start, double &end, int &method, int &function){
	cout << "FUNCTION OPTIONS" << endl;
	cout << "1. " << F1 << endl;
	cout << "2. " << F2 << endl;
	cout << "3. " << F3 << endl;
	cout << "4. " << F4 << endl;
	cout << "5. " << F5 << endl;
	cout << "Pick a function (1-5): ";
	cin >> function;

	cout << "Input left bound: ";
	cin >> start;

	cout << "Input right bound: ";
	cin >> end;

	cout << "Input number of iterations: ";
	cin >> itCount;

	cout << "Input method (1 - Rectangle, 2 - Trapazoid, 3 - Both): ";
	cin >> method;

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
void runFunctions(double start, double end, int itCount, int method, int f){
	cout << endl;
	if(method == 1 || method == 3){
		cout << "Rectangle Integral: " << intRec(start, end, itCount, f) << endl;
	}
	if(method == 2 || method == 3){
		cout << "Trapazoid Integral: " << intTrap(start, end, itCount, f) << endl;
	}
	cout << endl;		
}