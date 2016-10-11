#include <iostream>
#include <string>
#include <stdexcept>

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

	Ship(string n="", int l = 0):
		name(n),
		length(l),
		hits(0),
		horizontal(false),
		sunk(false),
		location(Coordinate()){}
};

struct Player{
	int player;
	int attacks_made;
	Ship carrier, battleship, destroyer, submarine, cruiser;
	char (*attacks) [BOARD_SIZE];
	int (*board) [BOARD_SIZE];

	Player(int p = 1):
		player(p),
		carrier(Ship("carrier",5)),
		battleship(Ship("battleship",4)),
		destroyer(Ship("destroyer",2)),
		submarine(Ship("submarine",3)),
		cruiser(Ship("cruiser",3)),
		attacks(new char [BOARD_SIZE][BOARD_SIZE]),
		board(new int [BOARD_SIZE][BOARD_SIZE]){}
};

Coordinate coordinate_input();
void print_board(int [BOARD_SIZE][BOARD_SIZE]);
void print_attacks(char [BOARD_SIZE][BOARD_SIZE]);
void initialize_player(Player &, int);
void send_attack(Player &, Player &);
int letter_to_int(char);
void place_ship(Ship &, Player &);
bool win_condition(Player, Player);
void ship_sunk(Ship &);

int main(){

	Player p_one = Player(1), p_two = Player(2);

	initialize_player(p_one, 1);

	print_board(p_one.board);

	cout << p_one.carrier.name << " " << p_one.carrier.length << endl;
}

void initialize_player(Player &p, int num){

	for (int x = 0; x < BOARD_SIZE; ++x){
		for(int y = 0; y < BOARD_SIZE; ++y){
			p.attacks[x][y] = ' ';
		}
	}
	place_ship(p.carrier, p);
	place_ship(p.battleship, p);
	place_ship(p.destroyer, p);
	place_ship(p.submarine, p);
	place_ship(p.cruiser, p);
	
}

void place_ship(Ship &ship, Player &p){
	int horizontal;
	cout << "Input north/west " << ship.name << " coordinates" << endl;
	ship.location = coordinate_input();
	cout << "Is your ship horizontal? (1/0): ";
	cin >> horizontal;
	if(horizontal == 1){
		ship.horizontal = true;
	}
	else{
		ship.horizontal = false;
	}
	int x = ship.location.x;
	int y = ship.location.y;
	for (int i = 0; i < ship.length; ++i){
		if(ship.horizontal){
			p.board[x+i][y] = 1;
		}
		else{
			p.board[x][y+i] = 1;
		}
	}
}

void print_board(int b[BOARD_SIZE][BOARD_SIZE]){
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

void print_attacks(char a[BOARD_SIZE][BOARD_SIZE]){
	for (int i = 0; i < BOARD_SIZE; ++i){
		cout << "   " << alphabet[i];
	}
	for(int x=0; x < BOARD_SIZE; ++x){
		if(x<9)
			cout << x+1 << "  ";
		else if(x >= 9)
			cout << x+1 << " ";
		for(int y=0; y<BOARD_SIZE; ++y){
			cout << a[x][y] << " | ";
		}
		cout << endl << "------------------------------------------" << endl;
	}
}



void send_attack(Player & attacker, Player & receiver){
	Coordinate attack;
	bool loop = true;


	while(loop){
		cout << "Player " << attacker.player << "Select a place to attack" << endl;
		attack = coordinate_input();
		if(attacker.attacks[attack.x][attack.y] = ' '){
			if(receiver.board[attack.x][attack.y] = 1){
				attacker.attacks[attack.x][attack.y] = 'X';
				cout << "HIT" << endl;
			}
			else{
				attack.attack[attack.x][attack.y] = 'O';
			}

		}
		else
			cout << "You already attacked there" << endl;

	}

}

Coordinate coordinate_input(){
	Coordinate input = Coordinate();
	char x;

	cout << "X-Coordinate(A-J): ";
	cin >> x;
	input.x = letter_to_int(x);
	cout << "Y-Coordinate(1-10): ";
	cin >> input.y;
	input.y--;

	return input;

}

int letter_to_int(char x){
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if(x == alphabet_lower[i] || x == alphabet[i]){
			return i;
		}
	}
	return 0;
}

bool win_condition(Player p){
	if(p.carrier.sunk && p.battleship.sunk && p.destroyer.sunk && p.submarine.sunk && p.cruiser.sunk){
		cout << "PLAYER " << p.player << " WINS" << endl;
		return true;
	}
	else
		return false;
}

void ship_sunk(Ship &s){
	if(s.length == s.hits){
		cout << "You sunk my " << s.name << "!!" << endl;
		s.sunk = true;
	}
}