#include <iostream>
#include <cmath>

#define WATER_WEIGHT 62.4;

using namespace std;

int main(){
	int radius, bforce, weight;
	float PI = 3.14159, volume;

	cout << "Please enter the weight (lbs): ";
	cin >> weight;

	cout << "Please enter the radius: ";
	cin >> radius;

	volume = 4/3*PI*pow(radius, 3);
	bforce = volume * WATER_WEIGHT;

	if(bforce >= weight){
	   cout << "The sphere will float!" << endl;
	}
	else{
	   cout << "The sphere will sink!" << endl;
	}
	return 0;
}
