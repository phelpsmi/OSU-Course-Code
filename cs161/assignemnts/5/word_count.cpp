#include <iostream>
#include <string>

#define SIZE 101
#define ALPHABET_SIZE 26
#define ALPHABET_LOWER "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

using namespace std;

void letter_count(string);
int word_count(string);

main(){
	int count[26];
	char input[SIZE];
	string s;

	cout << "Input a sentence: ";
	cin.getline(input,100);

	s = input;

	cout << "You have " << word_count(s) << " words with these letters:" << endl;
	letter_count(s);
	

}

void letter_count(string s){
	
	string case1 = ALPHABET_UPPER, case2 = ALPHABET_LOWER;
	int count[ALPHABET_SIZE];

	fill_n(count, 26, 0);

	for (int a = 0; a < ALPHABET_SIZE; ++a){
		for (int i = 0; i < s.size(); ++i){
			if(s[i] == case1[a] || s[i] == case2[a]){
				count[a]++;
			}
		}
		if(count[a] != 0){
			cout << count[a] << " " << case1[a] << "'s" << endl;
		}
		
	}
}

int word_count(string s){
	string case1 = ALPHABET_UPPER, case2 = ALPHABET_LOWER;
	int count = 0;
	bool last_letter = false;

	for(int i = 0; i < s.size(); ++i){

		if((s[i] == ',' || s[i] == '.' || s[i] == ' ') && last_letter)
			count ++;

		last_letter = false;

		for(int a = 0; a < ALPHABET_SIZE; ++a){
			if(s[i] == case1[a] || s[i] == case2[a]){
				last_letter = true;
				if(i+1 == s.size())
					count++;
			}
		}
	}
	return count;
}

