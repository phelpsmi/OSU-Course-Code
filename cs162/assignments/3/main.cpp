#include <iostream>
#include "card_game.h"
#include "poker.h"
#include "go_fish.h"
#include "resources.h"

int main(){
	card_game *game;
	char game_choice;

	game_choice = choose_game();

	if(game_choice == 'p')
		game = new poker;
	else if(game_choice == 'g')
		game = new go_fish;

	game->playGame();
}