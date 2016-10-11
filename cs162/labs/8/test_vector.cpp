#include "vector.hpp" 
#include <vector> 
#include <iostream> 
//We do not want to include either stmt. We wouldn't 
//be able to compare our vector template to the Standard 
//using namespace std; 
//using std::vector; 
using std::cout; 
using std::endl; 
 
int main (){
	vector<int> v; //Our vector class 
	std::vector<int> stdv; //Standard vector 
	//Compare operation of our vector to std 
	v.push_back(23); 


	vector<int> x, y;
	y.push_back(2);
	x = y;
	vector<int> *a;
	a = new vector<int>(x);

	vector<int> c;
	for (int i = 0; i < 5; ++i){
		c.push_back(i);
	}

	cout << c.at(3) << endl;
	cout << c[0] << endl;
	cout << c.size() << endl;

	for (int i = 0; i < 10; ++i){
		stdv.push_back(i);
	}

	for(std::vector<int>::iterator it = stdv.begin(); it != stdv.end(); ++it) {
    	cout << *it << " ";
	}
	cout << endl;

	for(std::vector<int>::iterator it = stdv.end()-1; it != stdv.begin()-1; --it) {
    	cout << *it << " ";
	}
	cout << endl;

/*	for (int i = 0; i < stdv.size(); ++i){
		cout << stdv[i] << endl;
	}

	for (int i = stdv.size()-1; i >= 0; --i){
		cout << stdv[i] << endl;
	}*/
 
	return 0; 
} 
