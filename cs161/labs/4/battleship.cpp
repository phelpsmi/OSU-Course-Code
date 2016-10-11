#include<iostream>
#include<ctime>
#include<cstdlib>

#define SHIPCOUNT 4

using namespace std;

main(){   
	int response, length, players, col, repeat = 1;
	char direction, row, hit;
	string shipCoordinate, attackCoordinate;	
	bool repeat = true;

	srand(time(NULL));

while(repeat){
	cout << "Input number of players (1/2): ";
	cin >> players;

	for (int i = 0; i < players; ++i){

		cout << "It is player " << i+1 << "'s turn to place his ships!" << endl;
		
		for (int k = 0; k < SHIPCOUNT; ++k)
		{
			cout << "Select the ship (1 - Carrier, 2 - Destroyer, 3 - Submarine, 4 - Patrol): ";
			cin >> response;

			cout << "Row (A-J): ";
			cin >> row;
			cout << "Col (1-10): ";
			cin >> col;

			cout << "Direction (N/S/E/W): ";
			cin >> direction;

			cout << endl;
		}
	}

	for (int i = 0; i < SHIPCOUNT; ++i){
		cout << "Player 1, pick a spot on the board to hit a ship:" << endl;
		cout << "Row (A-J): ";
		cin >> row;
		cout << "Col (1-10): ";
		cin >> col;

		if(players == 1){
			col = rand()%10 + 1;
			switch(rand()%10){
				case 0:
					row = 'A';
				case 1:
					row = 'B';
				case 2:
					row = 'C';
				case 3:
					row = 'D';
				case 4:
					row = 'E';
				case 5:
					row = 'F';
				case 6:
					row = 'G';
				case 7:
					row = 'H';
				case 8:
					row = 'I';
				case 9:
					row = 'J';
				default:
					row = 'A';
			}
		}
		else if(players == 2){
			cout << "Player 1 guessed " << row << " " << col << "." << endl;
			cout << "Was this a hit or miss (H/M): ";
			cin >> hit;	

			cout << "Player 2, pick a spot on the board to hit a ship: " << endl;
			cout << "Row: ";
			cin >> row;
			cout << "Col: ";
			cin >> col;
		}

		cout << "Player 2 attacked " << row << " " << col << "." << endl;
		cout << "Was this a hit or miss (H/M): ";
		cin >> hit;
		cout << endl;
	}
	cout << "Would you like to play again? (1 - yes, 0 - no): ";
	cin << repeat;
}
}
