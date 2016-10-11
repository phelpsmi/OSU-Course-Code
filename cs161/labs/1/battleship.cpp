#include <iostream>
#include <string>

using namespace std;

main(){
	string response, coordinate1, coordinate2, attack;
	int players, selectedShip, direction;	

	cout << "WELCOME TO BATTLESHIP" << endl;

	cout << " 1|2|3|4|5|6|7|8|9|10" << endl;
	cout << "A | | | | | | | | |  " << endl;
	cout << "B | | | | | | | | |  " << endl;
	cout << "C | | | | | | | | |  " << endl;
	cout << "D | | | | | | | | |  " << endl;
	cout << "E | | | | | | | | |  " << endl;
	cout << "f | | | | | | | | |  " << endl;
	cout << "G | | | | | | | | |  " << endl;
	cout << "H | | | | | | | | |  " << endl;
	cout << "I | | | | | | | | |  " << endl;
	cout << "J | | | | | | | | |  " << endl << endl << endl;

	cout << "1) Get the number of players" << endl;
	cout << "2) which ship the user is putting on the board" << endl;
	cout << "3) spot where the user wants to put their ships on the board" << endl;
	cout << "4) spot on board selecting where to hit the opponent's ships." << endl;

	cout << "Please select 1 to continue or anything else to quit: ";
	cin >> response;

	if(response == "1"){
		cout << "Enter number of players: ";
		cin >> players;
	}
	else if(response == "2"){
		cout << "What length ship would you like to place: ";
		cin >> selectedShip;
	}
	else if(response == "3"){
		cout << "Enter the first coordinate e.g. 4b: ";
		cin >> coordinate1;
		cout << "Enter the second coordinate e.g. 4b: ";
		cin >> coordinate2;
	}
	else if(response == "4"){
		cout << "Enter cooridnate you would like to attack: ";
		cin >> attack;
	}


	return 0; 
}
