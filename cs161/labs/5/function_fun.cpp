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

int main(){
   int a, b;

   cout << "Input your first parameter: ";
   cin >> a;
   cout << "Input your second parameter: ";
   cin >> b;

   countUp(a);
   countDown(a);
   countBetween(a,b);
   return 0;
}
