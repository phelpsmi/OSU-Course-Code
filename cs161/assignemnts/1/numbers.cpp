/********************************************************************* 
 ** Program Filename: numbers.cpp
 ** Author: Michael Phelps
 ** Date: 1/15/2014
 ** Description: Gives the user information of number types
 ** Input: 
 ** Output: 
 *********************************************************************/ 

#include <iostream>
#include <cfloat>
#include <climits>
#include <cmath>
	
using namespace std;
	
int main(){
	//All unsigned numbers can be created with a value of zero because subtracting 1 will get the max
	//short values were working weird so I created two seperate variables for the min and max
	unsigned int uInt = 0;
	int sInt = INT_MIN;
	unsigned short uShort = 0, uShort2 = -1;
	short sShort = SHRT_MIN, sShort2 = SHRT_MAX;
	unsigned long uLong = 0;
	long sLong = LONG_MIN;
	float floater;
	double doubler;
	
	cout << endl << endl << "BYTE QUANTITIES FOR VARIOUS DATA TYPE" << endl;
	cout << "      Integer: " << sizeof(int) << endl;
	cout << "      Short: " << sizeof(short) << endl;
	cout << "      Long: " << sizeof(long) << endl;
	cout << "      Float: " << sizeof(float) << endl;
	cout << "      Double: " << sizeof(double) << endl;
	cout << "      Bool: " << sizeof(bool) << endl;
	cout << "      Char: " << sizeof(char) << endl << endl;
	
	cout << "RANGES FOR INTEGER TYPES:" << endl;
	cout << "      Unsigned integer: " << uInt << " to " << uInt - 1 << endl; 
	cout << "      Signed integer: " << sInt << " to " << sInt - 1 << endl;
	cout << "      Unsigned short: " << uShort << " to " << uShort2 << endl;
	cout << "      Signed short: " << sShort << " to " << sShort2 << endl;
	cout << "      Unsigned long: " << uLong << " to " << uLong - 1 << endl;
	cout << "      Signed long: " << sLong << " to " << sLong - 1 << endl << endl;

	cout << "MANTISSA AND RANGE FOR FLOATS AND DOUBLES" << endl;
	cout << "      Float mantissa: " << FLT_MANT_DIG << endl;
	cout << "      Double mantissa: " << DBL_MANT_DIG << endl;
	cout << "      Float range: " << FLT_MIN_EXP << " to " << FLT_MAX_EXP << endl;
	cout << "      Double range: " << DBL_MIN_EXP << " to " << DBL_MAX_EXP << endl << endl;
	
	cout << "Input a number: ";
	cin >> floater;
	doubler = floater;
	
	doubler = doubler - .01;
	floater = floater - .01;
	
	cout << "value of double: " << doubler << endl;
	cout << "Value of float: " << floater << endl;
	
	return 0;
	
}