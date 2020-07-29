#pragma once
#include<iostream>
#include "Moves.h"
#include "Pieces.h"
#include "ProtoBoard.h"
#include <map>

//using namespace std;

class Estimation
{
public:


	double acceptable_rating = 0;
	map< Piece*, vector<vector<int>> > pieces_with_moves;
	map< Piece*, double > pieces_with_rating;

	template<typename T>
	void sort(map< T, double>& options);

	template<typename T>
	void set_acceptable_rating(map< T, double>& options);

	void get_pieces(Moves& m, ProtoBoard* pb);

	template<typename T>
	map< T, double> prerate(vector<T> options);

	void rate_endangered_pieces(ProtoBoard& pb);

	void test_piece(Piece* piece, Moves& m, ProtoBoard& pb);

	vector<Piece*> best_pieces(Moves& m, ProtoBoard* pb);

	vector<vector<int>> best_moves(Moves& m, ProtoBoard* pb);

	bool good_move(Piece* piece, vector<int>& move, ProtoBoard& pb);

};
