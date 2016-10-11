#include<iostream>
#include<cmath>

using namespace std;

int f(int x){
   return pow(x,5)+10;
}

int sum(int n){
	int y = 0;
	for(int x=0;x<n;++x){
	   y += f(x+1);
	}
	return y;
}

int main(){
	int n;

	cout << "Enter the number of iterations: ";
	cin >> n;

	cout << endl << sum(n) << endl << endl;


}
