#include <iostream>
#include "Rules.h"

using namespace std;

Rules::Rules()
{
	game_over = false;
	player1_won = false;
	player2_won = false;
}

void Rules::check_if_game_over(Moves& m, Player* player1, Player* player2, ProtoBoard* pb) // (UserPlayer* &player1, UserPlayer* &player2, Moves m, Board board)
{
	/*
	KRYTERIA ZAKONCZENIA GRY:
	(1) wszystkie pionki ktoregos gracza zostaly zbite (wygr lub przegr)
	(2) wszystkie pionki ktoregos gracza zostaly zablokowane (wygr lub przegr)
	(3) kazdy gracz wykonuje po 15 kolejek damkami bez zbjania (remis)
	*/

	//AD (1)
	if (
		((*player1).Pieces == 0)
		||
		((*player2).Pieces == 0)
		)
		game_over = true;

	//AD (2)
	m.get_possible_pieces((*player1).Color, (*pb).board);
	if (m.possible_pieces.size() == 0) game_over = true;

	m.get_possible_pieces((*player2).Color, (*pb).board);
	if (m.possible_pieces.size() == 0) game_over = true;

	//AD (3) pojawi sie w nastepnej wersji gry
	if (num_king_moves >= 30) game_over = true;

}


void Rules::evaluate_results(Player* player1, Player* player2) //(UserPlayer player1, UserPlayer player2, Moves m, Board board)
{
	/*
	(1) jesli atrybut liczby pionkow obiektu player1 wynosi 0 -> player2_won = true
	(2) jesli atrybut liczby pionkow obiektu player2 wynosi 0 -> player1_won = true
	(3) jesli obydwa w/w atrybuty wynosza 0 -> player1_won = false, player2_won = false (remis)
	(4) jesli gracze ruszyli sie po 15 razy damkami bez bic -> player1_won = false, player2_won = false (remis)
	*/

	// AD (1), (2) i (3):
	if ((*player1).Pieces == 0)
	{
		player2_won = true;
		cout << "player2 has won!" << endl;
	}
	else if ((*player2).Pieces == 0)
	{
		player1_won = true;
		cout << "player1 has won!" << endl;
	}
	else if (
		((*player1).Pieces != 0) && ((*player2).Pieces != 0)
		)
	{
		player1_won = false;
		player2_won = false;
		cout << "both players won!" << endl;
	}


	//Ad (4)

	else if (num_king_moves >= 30)
	{
		player1_won = false;
		player2_won = false;
		cout << "both players won!" << endl;
	}
}


void Rules::check_status(Player* player, char color, ProtoBoard* pb)
{
	/*
	tutaj bedziemy sprawdzac czy pionek zwykly (Man) powinien zmienic atrybut na damke (King)
	(atrybut statusu danego obiektu klasy Piece)
	ta metoda pojawi sie w nastepnej wersji gry
	*/

	if (
		(player->actual_piece != nullptr)
		)
	{
		if (
			(color == 'b')
			&& (*player).actual_piece->coordinate_r == 7
			)
		{
			int coord_r = player->actual_piece->coordinate_r;
			int coord_c = player->actual_piece->coordinate_c;
			delete (*pb).Vector[coord_r][coord_c];
			player->actual_piece = nullptr;
			(*pb).Vector[coord_r][coord_c] = nullptr;
			(*pb).Vector[coord_r][coord_c] = new King('B', coord_r, coord_c);
			player->actual_piece = (*pb).Vector[coord_r][coord_c];

		}
		else if (
			(color == 'c')
			&& (*player).actual_piece->coordinate_r == 0)
		{
			int coord_r = player->actual_piece->coordinate_r;
			int coord_c = player->actual_piece->coordinate_c;
			delete (*pb).Vector[coord_r][coord_c];
			player->actual_piece = nullptr;
			(*pb).Vector[coord_r][coord_c] = nullptr;
			(*pb).Vector[coord_r][coord_c] = new King('C', coord_r, coord_c);
			player->actual_piece = (*pb).Vector[coord_r][coord_c];
		}
	}
}



