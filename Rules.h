#pragma once
#include <iostream>
#include "Moves.h"
#include "Player.h"
#include "Moves.h"
#include "ProtoBoard.h"

using namespace std;

class Rules
{
public:
	bool game_over;
	bool player1_won;
	bool player2_won;
	int num_king_moves;

	Rules();
	void check_if_game_over(Moves& m, Player* player1, Player* player2, ProtoBoard* pb); // (UserPlayer player1, UserPlayer player2);
	void evaluate_results(Player* player1, Player* player2);
	void check_status(Player* player, char color, ProtoBoard* pb);
};




