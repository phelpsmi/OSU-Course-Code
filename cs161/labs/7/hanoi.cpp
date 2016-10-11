#include <iostream>
#include <cmath>

#define COLS 3
#define FROM 0
#define TO 1
#define SPARE 2

using namespace std;

void towers(int, int[][COLS], int, int, int, int);
void printboard(int[][COLS], int);

int main(){

	int n = 3;

	cin >> n;

	int board[n][COLS];

	for (int i = 0; i <= n; ++i){
		for(int x=0;x<COLS;++x){
			if(x == 0)
				board[i][x] = i+1;
			else
				board[i][x] = 0;
		}
	}
	printboard(board, n);
	towers(n, board, FROM, TO, SPARE, n);

}

void printboard(int b[][COLS], int n){
	for (int x = 0; x < n; ++x){
		for(int y = 0; y<COLS;++y){
			cout << b[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void towers(int disks, int b[][COLS], int from_col, int to_col, int spare, int total){
	if(disks >= 1){
		towers(disks-1, b, from_col, spare, to_col, total);

		int size;
		for (int i = 0; i < total; ++i)
		{
			if(b[i][from_col] != 0){
				size = b[from_col][i];
				b[from_col][i] = 0;
				i = total;
			}
		}
		for (int i = 0; i <= total; ++i)
		{
			if(b[i][to_col] > 0 || i == total){
				b[i-1][to_col] = size;
				i = total+1;
			}
		}

		printboard(b, total);

		towers(disks-1, b, spare, to_col, from_col, total);
	}


}