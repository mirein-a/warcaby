#pragma once
#include <iostream>
#include <vector>
#include "Pieces.h"
#include "Moves.h"
#include <algorithm>

using namespace std;

class ProtoBoard
{
public:
	char board[8][8];
	vector<vector<Piece*>> Vector;

	void get_board();
	void create_men_vector();
	void the_display();
	void show_possible_pieces(Moves& m);
	void show_possibilities(Moves& m, Piece* actual_piece);
	vector<int> choose_piece(Moves& m);
	vector<int> choose_the_field(Moves& m);
	ProtoBoard& operator=(const ProtoBoard& actual_board);
	void create_man_vector_from_save(vector<vector<int> >& coords, vector<char>& colors);
	~ProtoBoard();


};

bool check_input(const string& s_num);