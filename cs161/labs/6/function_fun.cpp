/*****************************************************
 * Program Filename: function_fun.cpp
 * Author: Michael, Brooks
 * Date: 2/3/2014
 * Description: Gets 2 values and does various counting methods
 * Input: integer a, integer b
 * Output: various countings
 * *************************************************/
#include<iostream>
#include<cmath>
#include<string>
#include<cctype>
#include <cstdlib>

using namespace std;

/***************************************************
 * Function: countUp
 * Description: Counts from zero to the parameter
 * Parameters: int a
 * Pre-Conditions: integer is non-negative
 * Post-Conditions: none
 * ************************************************/
void countUp(int a){
   for(int x=0;x <= a;++x){
      cout << x << " ";
   }
   cout << endl;
   return;
}

/**************************************************
 * Function: countDown
 * Description: Counts down from the parameter to zero
 * Parameters: int a
 * Pre-Conditions: integer is non-negative
 * Post-Conditions: none
 * ************************************************/
void countDown(int a){
   for(int x=a; x >= 0;--x){
      cout << x << " ";
   }
   cout << endl;
   return;
}

/*******************************************************
 * Function: countBetween
 * Description: Counts from first to second parameter
 * Parameters: int a,b
 * Pre-conditions: none
 * Post-conditions: none
 * ******************************************************/
void countBetween(int a, int b){
   if(a>b){
      for(int x=a; x >= b; --x){
	cout << x << " ";
      }
   }
   else{
      for(int x=a; x <= b; ++x){
	cout << x << " ";
      }
   }
   cout << endl;
   return;
}


bool is_positive_int(string s){
   for(int x=0;x < s.size();++x){
     if(!isdigit( s.at(x) ))
	return false;
   }
   return true;
	
}

bool is_positive_int_recurse(string s){
 
   if(s.size() == 0) {
      return true;
   }
   else if(!isdigit(s.at(0)))
      return false;
 

   s.erase(0,1);
   
   return is_positive_int_recurse(s);
}


int get_positive_int(){ 
   string a;
   cin >> a;

   while(!is_positive_int_recurse(a)){
      cout << "Please enter a positive integer: ";
      cin >> a;
   }

   return atoi(a.c_str());
}



int main(int argc, char *argv[]){
   int a, b;

   a = atoi(argv[1]);
   b = atoi(argv[2]);

   countUp(a);
   countDown(a);
   countBetween(a,b);
   return 0;
}
