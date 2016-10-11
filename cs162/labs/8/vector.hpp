#include <cstddef>
#include <iostream>

using std::cout;
using std::endl;
template <class T>
class vector {
	private:
		T *v;
		int s;
		int c;
	public:
		vector(){
			v= new T[4];
			s=0;
			c=4;
		}

		~vector(){
			delete [] v;
		}

		vector(vector<T> &other){
			if(other.v == NULL){
				v = new T[4];
				s = 0;
				c = 4;
				return;
			}
			v = new T(*other.v);
			s = other.s;
			c = other.c;
		}

		void operator=(vector<T> &other){
			if(other.v == NULL){
				v = new T[4];
				s = 0;
				c = 4;
				return;
			}
			v = new T(*other.v);
			s = other.s;
			c = other.c;
		}

		void push_back(T ele) {
			if(s < c){
				v[s] = ele;
				s++;
				return;
			}

			T *temp=new T[s]; 

 			for(int i=0; i<s; i++) 
 				temp[i]=v[i]; 
 			delete [] v; 

 			s++;
 			c += 4;
 			v=new T[c]; 

 			for(int i=0; i<s-1; i++) 
 				v[i]=temp[i]; 
 			v[s-1]=ele; 

			delete [] temp; 
 		}

 		int size(){
 			return s;
 		}

 		int capacity(){
 			return c;
 		}

 		T at(int i){
 			if(i >= s)
 				return NULL;
 			return v[i];
 		}

 		T operator[](int i){
 			if(i >= s)
 				return NULL;
 			return v[i];
 		}
}; 
