/*********************************************************************
 ** Program Filename: more_with_numbers.cpp
 ** Author: Michael Phelps
 ** Date: 1/31/2014
 ** Description: Converts decimal input to binary. Tests accuracy of floats/doubles
 ** Input: decimal, float, double, epsilon values
 ** Output: binary number, loops until epsilon failed
 *********************************************************************/

#include<iostream>
#include<cmath>
#include<string>

using namespace std;

/*********************************************************************
 ** Function: decimalToBinary
 ** Description: converts decimal input to binary
 ** Parameters: nil
 ** Pre-Conditions: nil 
 ** Post-Conditions: nil
 *********************************************************************/
void decimalToBinary(){
	long test;
	unsigned int integer, bits = sizeof(int)*8, intMax, output;
	long divider;
	string binary;
	bool overflow = true, append = false;

	intMax = pow(2, (sizeof(int)*8))-1;
	divider = intMax;
	divider++;

	while (overflow){
		cout << "Input a positive humber as big as " << intMax << ": ";
		cin >> test;
		integer = test;

		if (integer != test){
			cout << "ERROR: The number you entered was not within the range" << endl;
		}
		else{
			overflow = false;
			cout << "Decimal: " << integer << endl << "Binary: ";
		}
	}
	
	for (int i = 0; i < bits; ++i){
		divider /= 2;
		output = integer/divider;

		if (append == true){
			cout << output;
		}
		else if (output == 1){
			cout << output;
			append = true;
		}
		else if(i == (bits - 1)){
			cout << "0";
		}
		
		integer -= divider*output;

	}
	cout << endl << endl;
}

/********************************************************************* 
 ** Function: precisionLoss
 ** Description: gets epsilon and value from user and tests the precision with it
 ** Parameters: nil
 ** Pre-Conditions: nil 
 ** Post-Conditions: nil
 *********************************************************************/
void precisionLoss(){

	int fltIncrement = 0, dblIncrement = 0;
	float fltOrigin, fltNew, fltTest = 0, fltEpsilon;
	double dblOrigin, dblNew, dblTest = 0, dblEpsilon;

	cout << "Enter your desired float epsilon e.g. 0.0001: ";
	cin >> fltEpsilon;
	cout << "Enter your desired float value: ";
	cin >> fltOrigin;

	fltNew = fltOrigin;

	
	/*
	 * fltIncrement determines how many loops we have done
	 * every loop we subtract our float by .01
	 * We get the difference of this and what the value should be
	*/
	

	while(fltTest < fltEpsilon){
		fltIncrement++;
		fltNew = fltNew - .01;
		fltTest = abs((fltOrigin - fltIncrement*.01) - fltNew);
	}

	cout << "Was able to subtract by .01 " << fltIncrement - 1 << " times before failing epsilon" << endl << endl;

	/*
	 * Repeats the same process but with doubles instead of floats
	*/

	cout << "Enter your desired double epsilon e.g. 0.0001: ";
	cin >> dblEpsilon;
	cout << "Enter your desired double value: ";
	cin >> dblOrigin;

	dblNew = dblOrigin;
	while(dblTest < dblEpsilon){
		dblIncrement++;
		dblNew = dblNew - .01;
		dblTest = abs((dblOrigin - dblIncrement*.01) - dblNew);
	}
	cout << "Was able to subtract by .01 " << dblIncrement - 1 << " times before failing epsilon" << endl << endl;


}

int main(){

	decimalToBinary();
	precisionLoss();

	return 0;
}