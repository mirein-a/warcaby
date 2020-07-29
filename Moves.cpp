#include "Moves.h"
#include <iostream>

using namespace std;

Moves::Moves()
{
    //down_right[0] = 1; down_right[1] = 1;
    //down_left[0] = 1; down_left[1] = -1;
    //up_right[0] = -1; up_right[1] = 1;
    //up_left[0] = -1; up_left[1] = -1;
}

template<typename Col, int size>
bool Moves::surroundings(Col color_checking_m, Col color_checking_k, Col board[size][size], int r, int c, int type)
{
    int close_r;
    int close_c;
    int far_r;
    int far_c;
    bool final = false;

    for (int i = 0; i < 4; ++i)
    {
        if (i == 0) { close_r = r + 1; close_c = c + 1; far_r = r + 2; far_c = c + 2; }
        else if (i == 1) { close_r = r + 1; close_c = c - 1; far_r = r + 2; far_c = c - 2; }
        else if (i == 2) { close_r = r - 1; close_c = c + 1; far_r = r - 2; far_c = c + 2; }
        else if (i == 3) { close_r = r - 1; close_c = c - 1; far_r = r - 2; far_c = c - 2; }

        if (
            (type == 1)
            && (far_r < size) && (far_r >= 0) && (far_c < size) && (far_c >= 0)
            && ((board[close_r][close_c] == color_checking_m) || (board[close_r][close_c] == color_checking_k))
            && (board[far_r][far_c] == ' ')
            )
        {
            opts.push_back({ far_r, far_c, close_r, close_c });
            final = true;
        }

        if (
            ((type == 2) && ((i == 0) || (i == 1)))
            || ((type == 3) && ((i == 2) || (i == 3)))
            )
        {
            if (
                (close_r < size) && (close_r >= 0) && (close_c < size) && (close_c >= 0)
                && ((board[close_r][close_c] == ' '))
                )
            {
                opts.push_back({ close_r, close_c });
            }
        }

    }

    if (opts.empty() == false) final = true;
    return final;
}

template<typename Col, int size>
bool Moves::king_surroundings(Col color_checking_m, Col color_checking_k, Col board[size][size], int r, int c, int type)
{
    int close_r = 10;
    int close_c = 10;
    int far_r = 10;
    int far_c = 10;
    int step_r;
    int step_c;
    bool end = false;
    int index = 0;

    for (int i = 0; i < 4; ++i)
    {
        if (i == 0) { close_r = r + 1; close_c = c + 1; far_r = r + 2; far_c = c + 2; step_r = 1; step_c = 1; end = false; }
        else if (i == 1) { close_r = r + 1; close_c = c - 1; far_r = r + 2; far_c = c - 2; step_r = 1; step_c = -1; end = false; }
        else if (i == 2) { close_r = r - 1; close_c = c + 1; far_r = r - 2; far_c = c + 2; step_r = -1; step_c = 1; end = false; }
        else if (i == 3) { close_r = r - 1; close_c = c - 1; far_r = r - 2; far_c = c - 2; step_r = -1; step_c = -1; end = false; }

        while (
            (type == 1)
            && (end == false)
            && (far_r < size) && (far_r >= 0) && (far_c < size) && (far_c >= 0)
            )
        {
            if (
                ((board[close_r][close_c] == color_checking_m) || (board[close_r][close_c] == color_checking_k))
                && (board[far_r][far_c] == ' ')
                )
            {
                if (opts.size() > index)
                {
                    opts[index].push_back(far_r); opts[index].push_back(far_c); opts[index].push_back(close_r); opts[index].push_back(close_c);
                }

                else opts.push_back({ far_r, far_c, close_r, close_c });

                close_r += step_r; close_c += step_c; far_r += step_r; far_c += step_c;
            }
            else if (board[close_r][close_c] == ' ')
            {
                close_r += step_r; close_c += step_c; far_r += step_r; far_c += step_c;
            }
            else end = true;
        }
        if (opts.size() > index) index++;


        while (
            (type == 2)
            && (close_r < size) && (close_r >= 0) && (close_c < size) && (close_c >= 0)
            && ((board[close_r][close_c] == ' '))
            )
        {
            opts.push_back({ close_r, close_c });
            close_r += step_r; close_c += step_c;
        }
    }

    return end;
}


void Moves::check_move(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    opts.clear();

    if (color == 'b')
        surroundings<char, 8>('b', 'B', board, coefficient_r, coefficient_c, 2);
    else if (color == 'c')
        surroundings<char, 8>('c', 'C', board, coefficient_r, coefficient_c, 3);
    else if ((color == 'B') || (color == 'C'))
    {
        surroundings<char, 8>('b', 'B', board, coefficient_r, coefficient_c, 2);

        surroundings<char, 8>('c', 'C', board, coefficient_r, coefficient_c, 3);
    }

}


void Moves::check_beat(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    char opponent_m;
    char opponent_k;
    if (color == 'b') { opponent_m = 'c'; opponent_k = 'C'; }
    else { opponent_m = 'b'; opponent_k = 'C'; }

    opts.clear();

    surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    if (opts.empty() == false) possible_pieces.push_back({ coefficient_r,coefficient_c });
}

void Moves::check_king_beat(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    char opponent_m;
    char opponent_k;
    if (color == 'B') { opponent_m = 'c'; opponent_k = 'C'; }
    else { opponent_m = 'b'; opponent_k = 'B'; }

    opts.clear();

    king_surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    if (opts.empty() == false) possible_pieces.push_back({ coefficient_r,coefficient_c });
}


void Moves::get_possible_pieces(char color, char board[8][8])
{
    possible_pieces.clear();

    char color_m; char color_k;
    if ((color == 'b') || (color == 'B')) { color_m = 'b'; color_k = 'B'; }
    else { color_m = 'c'; color_k = 'C'; }

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] == color_m) check_beat(i, j, color, board);
            else if (board[i][j] == color_k) check_king_beat(i, j, color_k, board);
        }
    }

    if (possible_pieces.empty())
    {
        beats = false;
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (board[i][j] == color_m)
                {
                    check_move(i, j, color_m, board);
                    if (opts.empty() == false) possible_pieces.push_back({ i , j });
                }
                else if (board[i][j] == color_k)
                {
                    check_move(i, j, color_k, board);
                    if (opts.empty() == false) possible_pieces.push_back({ i , j });
                }
            }
        }
    }
    else beats = true;
}

void Moves::create_man_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    possible_moves.clear();
    opts.clear();

    char opponent_m = 'd';
    char opponent_k = 'D';
    if (color == 'b') { opponent_m = 'c'; opponent_k = 'C'; }
    else { opponent_m = 'b'; opponent_k = 'B'; }

    if (beats == false)
    {
        if (color == 'b') surroundings<char, 8>('b', 'B', board, coefficient_r, coefficient_c, 2);
        else if (color == 'c') surroundings<char, 8>('c', 'C', board, coefficient_r, coefficient_c, 3);
    }

    else surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    for (int i = 0; i < opts.size(); ++i)
    {
        possible_moves.push_back(opts[i]);
    }

    if (beats == true)
    {
        for (int k = 0; k < possible_moves.size(); ++k)
        {
            opts.clear();
            surroundings<char, 8>(opponent_m, opponent_k, board, possible_moves[k][0], possible_moves[k][1], 1);
            if (opts.size() == 1) for (int i = 0; i < opts[0].size(); ++i) possible_moves[k].push_back(opts[0][i]);
        }
    }
}

void Moves::create_king_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    possible_moves.clear();
    opts.clear();

    char opponent_m = 'd';
    char opponent_k = 'D';
    if (color == 'B') { opponent_m = 'c'; opponent_k = 'C'; }
    else { opponent_m = 'b'; opponent_k = 'B'; }

    if (beats == false)
    {
        king_surroundings<char, 8>('n', 'N', board, coefficient_r, coefficient_c, 2);
    }

    else king_surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    for (int i = 0; i < opts.size(); ++i)
    {
        possible_moves.push_back(opts[i]);
    }

}

void Moves::create_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    if ((color == 'b') || (color == 'c')) create_man_possibilities(coefficient_r, coefficient_c, color, board);
    else create_king_possibilities(coefficient_r, coefficient_c, color, board);
}

template<typename Col, int size> void Moves::check_danger(int r, int c, Col color_checking, Col board[size][size])
{

    int op_r;
    int op_c;
    int empt_r;
    int empt_c;

    for (int i = 0; i < 4; ++i)
    {
        if (i == 0) { op_r = r - 1; op_c = c - 1; empt_r = r + 1; empt_c = c + 1; }
        if (i == 1) { op_r = r + 1; op_c = c + 1; empt_r = r - 1; empt_c = c - 1; }
        if (i == 2) { op_r = r - 1; op_c = c + 1; empt_r = r + 1; empt_c = c - 1; }
        if (i == 3) { op_r = r + 1; op_c = c - 1; empt_r = r - 1; empt_c = c + 1; }

        if (
            (op_r >= 0) && (op_r < size) && (op_c >= 0) && (op_c < size)
            && (empt_r >= 0) && (empt_r < size) && (empt_c >= 0) && (empt_c < size)
            && (board[op_r][op_c] == color_checking) && (board[empt_r][empt_c] == ' ')
            )
        {
            dangerous_pieces.push_back({ op_r, op_c });
        }
    }
}

void Moves::get_dangerous_pieces(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    dangerous_pieces.clear();
    char danger_m;
    char danger_k;
    if (color == 'b') { danger_m = 'c'; danger_k = 'C'; }
    else { danger_m = 'b'; danger_k = 'B'; }

    check_danger<char, 8>(coefficient_r, coefficient_c, danger_m, board);
    check_danger<char, 8>(coefficient_r, coefficient_c, danger_k, board);
}


// NOWE

vector<int> operator+(vector<int> v, int directions[2])
{
    v[0] = v[0] + directions[0];
    v[1] = v[1] + directions[1];
    return v;
}

bool operator<(vector<int> v, int limits[2]) // limits = (0,7)
{
    return  (v[0] >= limits[0]) && (v[0] <= limits[1]) && (v[1] >= limits[0]) && (v[1] <= limits[1]);
}

bool Moves::check_m_piece(vector<int> coords, char board[8][8])
{
    // zwraca true jesli ktorys kierunek ruchu danego pionka jest mozliwy.
    // tym bedziemy sprawdzac po kolei ZWYKLE pionki szukajac ruchu
    // TESTOWANE: TROCHE
    
    vector<int> r_field = coords + up_right; // pole na skos po prawej
    vector<int> l_field = coords + up_left; // j.w. ale po lewej

    if (
           ((r_field < limits) && (board[r_field[0]][r_field[1]] == ' '))
        || ((l_field < limits) && (board[l_field[0]][l_field[1]] == ' '))
        ) return true;
    else return false;

}

bool Moves::check_k_piece(vector<int> coords, char board[8][8])
{
    // tak jak check_m_piece, ale dla damek
    // TESTOWANE: TROCHE

    vector<int> up_r_field = coords + up_right; // pole do gory po prawej
    vector<int> up_l_field = coords + up_left; // j.w. ale po lewej
    vector<int> down_r_field = coords + down_right; // pole do dolu po prawej
    vector<int> down_l_field = coords + down_left; // j.w. ale po lewej

    if (
           ((down_r_field < limits) && (board[down_r_field[0]][down_r_field[1]] == ' '))
        || ((down_l_field < limits) && (board[down_l_field[0]][down_l_field[1]] == ' '))
        || ((up_r_field < limits) && (board[up_r_field[0]][up_r_field[1]] == ' '))
        || ((up_l_field < limits) && (board[up_l_field[0]][up_l_field[1]] == ' '))
        ) return true;
    else return false;
}

void Moves::get_pos_pieces(char c_color, vector<vector<int> > c_player, vector<vector<int> > c_opponent, char board[8][8])
{
    // na razie zwykle pionki.
    // tu jest miejsce na to zeby sprawdzic dostepne bicia i jesli ich nie ma,
    // dopiero wtedy sprawdzamy czy sa zwykle pionki
    
    // TESTOWANE: NIE

    if ((c_color == 'b') || (c_color == 'c'))
        for (int i; i < c_player.size(); ++i)
            if (check_m_piece(c_player[i], board) == true) possible_pieces.push_back(c_player[i]);
    
            else if ((c_color == 'B') || (c_color == 'C'))
        for (int i; i < c_player.size(); ++i)
            if (check_m_piece(c_player[i], board) == true) possible_pieces.push_back(c_player[i]);
}
