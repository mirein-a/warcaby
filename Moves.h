#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Moves
{
public:
    vector<vector<int> > possible_pieces;
    vector<vector<int> > possible_moves;
    vector<vector<int> > options;
    vector<vector<int> > dangerous_pieces;
    bool beats;
    vector<int> ways;
    int coming_from;

    template<typename Col, int size>
    bool surroundings(Col color_checking_m, Col color_checking_k, Col board[size][size], int r, int c, int type);

    template<typename Col, int size>
    bool king_surroundings(Col color_checking_m, Col color_checking_k, Col board[size][size], int r, int c, int type);

    void get_possible_pieces(char color, char board[8][8]);
    void check_move(int coefficient_r, int coefficient_c, char color, char board[8][8]);
    void check_beat(int coefficient_r, int coefficient_c, char color, char board[8][8]);
    void create_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8]);
    void create_king_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8]);
    void create_man_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8]);
    void check_king_beat(int coefficient_r, int coefficient_c, char color, char board[8][8]);

    template<typename Col, int size>
    void check_danger(int r, int c, Col color, Col board[size][size]);
    void get_dangerous_pieces(int coefficient_r, int coefficient_c, char color, char board[8][8]);
};


