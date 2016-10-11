#include<iostream>
#include<cmath>
#include<string>

using namespace std;

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

void precisionLoss(){

	int increment = 0;
	float fltOrigin, fltNew, fltTest = 0, fltEpsilon;
	double dblOrigin, dblNew, dblTest = 0, dblEpsilon;

	cout << "Enter your desired float epsilon: ";
	cin >> fltEpsilon;

	cout << "Enter your desired float value: ";
	cin >> fltOrigin;

	fltNew = fltOrigin;
	while(fltTest < fltEpsilon){
		increment++;
		fltNew = fltNew - .01;
		fltTest = abs((fltOrigin - increment*.01) - fltNew);
	}
	cout << "Was able to subtract by .01 " << increment - 1 << " Times" << endl << endl;

	increment = 0;
	cout << "Enter your desired double epsilon: ";
	cin >> dblEpsilon;
	cout << "Enter your desired double value: ";
	cin >> dblOrigin;

	dblNew = dblOrigin;
	while(dblTest < dblEpsilon){
		increment++;
		dblNew = dblNew - .01;
		dblTest = abs((dblOrigin - increment*.01) - dblNew);
	}
	cout << "Was able to subtract by .01 " << increment - 1 << " Times" << endl << endl;


}

int main(){

	//decimalToBinary();
	precisionLoss();

	return 0;
}