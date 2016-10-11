/********************************************************************* 
 ** Program Filename: array_conversion.ccp
 ** Author: Michael Phelps
 ** Date: 3/6/2014
 ** Description: Takes an NxN array and generates a n-1xn-1 array
 ** Input: matrix size, matrix values
 ** Output: original matrix, generated matrix
 *********************************************************************/ 
#include <iostream>
#include <string>

using namespace std;

void calculate_result(int n, int** &original, int** &result);
void recursive_calculate_result(int n, int** &original, int** &result, int x=0, int y=0);
void get_numbers(int n, int** &array);
void print_array(int n, int **array);
void initialize_matrix(int n, int** &original, int** &result);

int main(){

	int n, **original, **result;

	cout << "Input matrix dimension: ";
	cin >> n;
	
	initialize_matrix(n, original, result);
	get_numbers(n, original);
	calculate_result(n, original, result);

	cout << "Original Matrix: " << endl;
	print_array(n, original);

	cout << "New Matrix:" << endl;
	print_array(n-1, result);
}

/********************************************************************* 
 ** Function: get_numbers
 ** Description: Takes an array and prompts the user for its values
 ** Parameters: int n, int** %array
 ** Pre-Conditions: n is possitive integer, array is same dimensions as n
 ** Post-Conditions: array have values in all of it's spots
 *********************************************************************/ 
void get_numbers(int n, int** &array){
	cout << "Input coordinate values" << endl;
	for (int x = 0; x < n; ++x){
		for(int y = 0; y < n; ++y){
			cout << "Input (" << x+1 << "," << y+1 << ")" << ": ";
			cin >> array[x][y];
		}
	}
}

/********************************************************************* 
 ** Function: initialize_matrix
 ** Description: takes the two array double pointers and initializes them with 0's
 ** Parameters: int n, int** &original, int** &result
 ** Pre-Conditions: 
 ** Post-Conditions: 
 *********************************************************************/ 
void initialize_matrix(int n, int** &original, int** &result){
	original = new int*[n];

	for(int i = 0; i < n; ++i){
		original[i] = new int[n];
	}

	result = new int*[n-1];

	for(int i = 0; i < n-1; ++i){
		result[i] = new int[n-1];
	}
}

/********************************************************************* 
 ** Function: print_array
 ** Description: prints out an array with 0,0 in top left
 ** Parameters: int n, int **array
 ** Pre-Conditions: n is the dimensions of array
 ** Post-Conditions: none
 *********************************************************************/ 
void print_array(int n, int **array){
	for(int x = 0; x < n; ++x){
		for(int y = 0; y < n; ++y){
			cout << array[x][y] << " ";
		}
		cout << endl;
	}
}

/********************************************************************* 
 ** Function: calculate_result
 ** Description: Generates the new matrix by adding the four values around each point
 ** Parameters: int n, int** &original, int** &result
 ** Pre-Conditions: original is size nXn, result is size n-1xn-1
 ** Post-Conditions: none
 *********************************************************************/ 
void calculate_result(int n, int** &original, int** &result){
	for(int x = 0; x < n-1; ++x){
		for(int y = 0; y < n-1; ++y){
			result[x][y] = original[x][y]+original[x+1][y]+original[x][y+1]+original[x+1][y+1];
		}
	}
}

/********************************************************************* 
 ** Function: recursive_calculate_result
 ** Description: Recursively generates the new matrix by adding the four values around each point
 ** Parameters: int n, int** &original, int** &result, int x, int y
 ** Pre-Conditions: original is size nXn, result is size n-1xn-1
 ** Post-Conditions: none
 *********************************************************************/ 
void recursive_calculate_result(int n, int** &original, int** &result, int x, int y){
	if(y == n-1){
		return;
	}
	else if(x == n-1){
		recursive_calculate_result(n, original, result, 0, y+1);
		return;
	}
	else{
		result[x][y] = original[x][y]+original[x+1][y]+original[x][y+1]+original[x+1][y+1];
		recursive_calculate_result(n, original, result, x+1, y);	
	}

}
