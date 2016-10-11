/********************************************************************* 
 ** Program Filename: battleship.cpp
 ** Author: Michael Phelps
 ** Date: 3/16/2014
 ** Description: Plays a two player game of battleship
 ** Input: Ship placements, attack coordinates
 ** Output: Players' board graph, standard battleship player responses
 *********************************************************************/ 
#include <iostream>
#include <string>

#define UP TRUE
#define RIGHT FALSE
#define BOARD_SIZE 10

using namespace std;

const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *alphabet_lower = "abcdefghijklmnopqrstuvwxyz";

struct Coordinate{
	int x,y;

	Coordinate(int a=0, int b=0):
		x(a),
		y(b){}
};

struct Ship{
	string name;
	int length, hits;
	bool horizontal, sunk;
	Coordinate location;
	char letter;

	Ship(string n="", int l = 0, char c = 's'):
		name(n),
		length(l),
		hits(0),
		horizontal(false),
		sunk(false),
		location(Coordinate()),
		letter(c){}
};

struct Player{
	int player;
	int attacks_made;
	Ship carrier, battleship, destroyer, submarine, cruiser;
	char (*board) [BOARD_SIZE];

	Player(int p = 1):
		player(p),
		carrier(Ship("carrier",5,'C')),
		battleship(Ship("battleship",4,'B')),
		destroyer(Ship("destroyer",2,'D')),
		submarine(Ship("submarine",3,'S')),
		cruiser(Ship("cruiser",3,'R')),
		board(new char [BOARD_SIZE][BOARD_SIZE]){}
};

Coordinate coordinate_input();
void print_board(char [BOARD_SIZE][BOARD_SIZE]);
void print_attacks(char [BOARD_SIZE][BOARD_SIZE]);
void initialize_player(Player &, int);
void send_attack(Player &, Player &);
int letter_to_int(char);
void place_ship(Ship &, Player &);
bool win_condition(Player, Player);
void ship_sunk(Ship &);
bool spots_clear(Ship s, char[BOARD_SIZE][BOARD_SIZE]);
bool get_bool();

int main(){

	Player p_one = Player(1), p_two = Player(2);

	initialize_player(p_one, 1);
	initialize_player(p_two, 2);

	int turn = 1;
	while(!win_condition(p_one, p_two)){
		if(turn == 1){
			turn = 2;
			send_attack(p_one, p_two);
		}
		else if(turn == 2){
			turn = 1;
			send_attack(p_two, p_one);
		}
	}
}

/********************************************************************* 
 ** Function: initialize_player
 ** Description: handles the processes to get all the initial values for a player
 ** Parameters: Player, int
 ** Pre-Conditions: none
 ** Post-Conditions: Player has been given placement for all ships, player board has blank spaces
 *********************************************************************/ 
void initialize_player(Player &p, int num){

	for (int x = 0; x < BOARD_SIZE; ++x){
		for(int y = 0; y < BOARD_SIZE; ++y){
			p.board[x][y] = ' ';
		}
	}
	p.player = num;
	place_ship(p.carrier, p);
	place_ship(p.battleship, p);
	place_ship(p.destroyer, p);
	place_ship(p.submarine, p);
	place_ship(p.cruiser, p);
	print_board(p.board);
	cout << string(200, '\n');
	cout << "All your ships have been placed. Give control to the other player" << endl;

}

/********************************************************************* 
 ** Function: place_ship
 ** Description: get's player input for where to put their ship
 ** Parameters: Ship, Player
 ** Pre-Conditions: none
 ** Post-Conditions: Ship has coordinate, and orientation
 *********************************************************************/ 
void place_ship(Ship &ship, Player &p){
	int horizontal;

	print_board(p.board);

	cout << "Player " << p.player << ", Input north/west " << ship.name << " coordinates" << endl;
	ship.location = coordinate_input();

	cout << "Is your ship horizontal? (Y/N): ";
	ship.horizontal = get_bool();

	if(!spots_clear(ship, p.board)){
		cout << "You can't place your ship there!!" << endl;
		place_ship(ship, p);
		return;
	}
	int x = ship.location.x;
	int y = ship.location.y;
	for (int i = 0; i < ship.length; ++i){
		if(ship.horizontal){
			p.board[x+i][y] = ship.letter;
		}
		else{
			p.board[x][y+i] = ship.letter;
		}
	}
}

/********************************************************************* 
 ** Function: print_board
 ** Description: print a players board with all their ships
 ** Parameters: char[][]
 ** Pre-Conditions: board is initialized with values
 ** Post-Conditions: none
 *********************************************************************/ 
void print_board(char b[BOARD_SIZE][BOARD_SIZE]){
	for (int i = 0; i < BOARD_SIZE; ++i){
		cout << "   " << alphabet[i];
	}
	cout << endl;
	for (int y = 0; y < BOARD_SIZE; ++y){
		if(y < 9)
			cout << y+1 << "  ";
		else if(y >= 9 )
			cout << y+1 << " ";
		for(int x=0; x<BOARD_SIZE; ++x){
			cout << b[x][y] << " | ";
		}
		cout << endl << "------------------------------------------" << endl;
	}
}

/********************************************************************* 
 ** Function: print_attacks
 ** Description: only prints the attacks made on a player's board (not their ship placements)
 ** Parameters: char[][]
 ** Pre-Conditions: board is initialized with values
 ** Post-Conditions: none
 *********************************************************************/ 
void print_attacks(char b[BOARD_SIZE][BOARD_SIZE]){
	for (int i = 0; i < BOARD_SIZE; ++i){
		cout << "   " << alphabet[i];
	}
	cout << endl;
	for (int y = 0; y < BOARD_SIZE; ++y){
		if(y < 9)
			cout << y+1 << "  ";
		else if(y >= 9 )
			cout << y+1 << " ";
		for(int x=0; x<BOARD_SIZE; ++x){
			if(b[x][y] == 'O' || b[x][y] == 'X'){
				cout << b[x][y];
			}
			else{
				cout << " ";
			}
			cout << " | ";
		}
		cout << endl << "------------------------------------------" << endl;
	}
}

/********************************************************************* 
 ** Function: send_attack
 ** Description: get attack coordinate from player and determines if it hit or missed
 ** Parameters: Player attacker, Player receiver
 ** Pre-Conditions: attacker has player numner, receiver has initialized board
 ** Post-Conditions: none
 *********************************************************************/ 
void send_attack(Player & attacker, Player & receiver){
	Coordinate attack;
	bool loop = true;

	print_attacks(receiver.board);

	while(loop){
		cout << "Player " << attacker.player << ", Select a place to attack" << endl;
		attack = coordinate_input();
		int x = attack.x, y = attack.y;
		char letter = receiver.board[x][y];


		if(letter != 'X' && letter != 'O'){
			loop = false;
			if(letter != ' '){
				cout << "HIT" << endl;
				receiver.board[x][y] = 'X';
				switch(letter) {
					case 'C': receiver.carrier.hits++;
						ship_sunk(receiver.carrier);
						break;
					case 'B': receiver.battleship.hits++;
						ship_sunk(receiver.battleship);
						break;
					case 'D': receiver.destroyer.hits++;
						ship_sunk(receiver.destroyer);
						break;
					case 'S': receiver.submarine.hits++;
						ship_sunk(receiver.submarine);
						break;
					case 'R': receiver.cruiser.hits++;
						ship_sunk(receiver.cruiser);
						break;
					default: cout << "For some reason this letter was there " << letter << endl;
				}
			}
			else{
				cout << "MISS" << endl;
				receiver.board[x][y] = 'O';
			}
		}
		else
			cout << "You already attacked there" << endl;
	}
}

/********************************************************************* 
 ** Function: coordinate_input
 ** Description: gets coordinate selection from the user
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: Coordinate with x,y values
 *********************************************************************/ 
Coordinate coordinate_input(){
	Coordinate input = Coordinate();
	char x;

	cout << "Enter Coordinate eg A 1: ";
	cin >> x >> input.y;

	input.x = letter_to_int(x);
	input.y--;

	if(input.y > 9 || input.y < 0 || input.x > 9 || input.y < 0){
		cout << "You entered an impropper coordinate" << endl;
		return coordinate_input();
	}
	return input;

}

/********************************************************************* 
 ** Function: letter_to_int
 ** Description: converts letter component of coordinate to number
 ** Parameters: char
 ** Pre-Conditions: char is within board range
 ** Post-Conditions: int is within board range
 *********************************************************************/ 
int letter_to_int(char x){
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if(x == alphabet_lower[i] || x == alphabet[i]){
			return i;
		}
	}
	return 0;
}

/********************************************************************* 
 ** Function: ship_sunk
 ** Description: determines whether or not ship is sunk
 ** Parameters: Ship
 ** Pre-Conditions: ship has value for hits and length
 ** Post-Conditions: none
 *********************************************************************/ 
void ship_sunk(Ship &s){
	if(s.length == s.hits){
		cout << "You sunk my " << s.name << "!!" << endl;
		s.sunk = true;
	}
}

/********************************************************************* 
 ** Function: win_condition
 ** Description: determines if either player has won yet
 ** Parameters: Player one, Player two
 ** Pre-Conditions: player's ships have sunk values
 ** Post-Conditions: none
 *********************************************************************/ 
bool win_condition(Player p_one, Player p_two){
	if(p_one.carrier.sunk && p_one.battleship.sunk && p_one.submarine.sunk && p_one.cruiser.sunk && p_one.destroyer.sunk){
		cout << "Player two wins!!!!" << endl;
		return true;
	}
	else if(p_two.carrier.sunk && p_two.battleship.sunk && p_two.submarine.sunk && p_two.cruiser.sunk && p_two.destroyer.sunk){
		cout << "Player one wins!!!!" << endl;
		return true;
	}
	return false;
}

/********************************************************************* 
 ** Function: spots_clear
 ** Description: determines if a given ship location values are valid for the player's board
 ** Parameters: Ship, char[][]
 ** Pre-Conditions: ship has coordinate and direction
 ** Post-Conditions: none
 *********************************************************************/ 
bool spots_clear(Ship s, char board[BOARD_SIZE][BOARD_SIZE]){
	int x = s.location.x, y = s.location.y;

	if(s.horizontal){
		if((x+s.length) > 10)
			return false;
	}
	else{
		if((y+s.length) > 10)
			return false;
	}

	cout << "Made it past this test" << endl;

	for (int i = 0; i < s.length; ++i){
		if(s.horizontal){
			if(board[x+i][y] != ' '){
				return false;
			}
		}
		else{
			if(board[x][y+i] != ' '){
				return false;
			}
		}
	}
	return true;
}

/********************************************************************* 
 ** Function: get_bool
 ** Description: get's a yes/no response from the user
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
bool get_bool(){
	string booly = "bad input";
	bool good_input = false;

	cin >> booly;
	if(booly == "Y" || booly == "y"){
		return true;
	}
	else if(booly == "N" || booly == "n"){
		return false;
	}
	else{
		cout << "Please enter Y or N: ";
		return get_bool();
	}

}