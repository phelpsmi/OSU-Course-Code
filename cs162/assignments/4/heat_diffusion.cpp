 /****************************************************** 
** Program: heat_diff.cpp 
** Author: Michael Phelps
** Date: 5/21/2014
** Description: Reads paramatars for heat settings on a wire and simulates diffussion over time
** Input: none
** Output: temperature on wire are different points along the wire
******************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>


using namespace std;

void set_vars(float &, float &, float &, float &, float &,  float &,  float &,  float &, float &);


int main(){

	system("clear");
	float k, p, c, t0, tf, length, sections, interval, timeSeg;
	
	set_vars(k, p, c, t0, tf, length, sections, interval, timeSeg);

	int x = (int)sections;
	int y = (int)interval;
	float temp[y][x];
	
	for(int i=0; i < y; i++){
		for(int j=0; j < x; j++)
			temp[i][j] = t0;
	}
	for(int i=0; i < y; i++){
		temp[i][0] = tf;
		cout << tf << t0 << endl;
	}
	cout << temp[0][0] << " " << endl;
	
	for(int i=1; i < y; i++){
		
		cout << "Time: " << i << endl;
		cout << temp[i][0] << " ";
		for(int j=1; j < x-1; j++){

			temp[i][j] = ((k*timeSeg)/(c*p))*((temp[i-1][j+1]+temp[i-1][j-1]-2*temp[i-1][j])/pow((length/sections),2))+temp[i-1][j];
			cout << fixed << setprecision(2) << temp[i][j] << " ";
		}
		
		cout << temp[i][x-1] << endl << endl;
	}

	ofstream dataOut;
	dataOut.open("heat_bin.dat", ios::out | ios::binary);
	
	for (int i = 0; i < y; i++){
		for (int j = x-1; j > -1; j--){	
				float cTemp = temp[i][j];
				dataOut.write(reinterpret_cast<const char *>(&cTemp), sizeof(float));
		}
	}	
	dataOut.close();
}

/********************************************************************* 
 ** Function: set_vars
 ** Description: gets the initial variables from the input file
 ** Parameters: float &k, float &p, float &c, float &t0, float&tf, float &length, float &sections, float &interval, float &timeSeg
 ** Pre-Conditions: het_input.dat exists
 ** Post-Conditions: all values have are initialized
 *********************************************************************/
void set_vars(float &k, float &p, float &c, float &t0, float &tf, float &length, float &sections, float &interval, float &timeSeg){
	
	ifstream inFile;
	char inputFilename[] = "heat_input.dat";
	inFile.open(inputFilename, ios::in);
	
	string x;

	inFile >> x >> k; 
	inFile >> x >> p;
	inFile >> x >> c;
	inFile >> x >> t0;
	inFile >> x >> tf;
	inFile >> x >> length;
	inFile >> x >> sections;
	inFile >> x >> interval;
	inFile >> x >> timeSeg;
	
	return; 	
}