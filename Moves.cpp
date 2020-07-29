#include "Moves.h"
#include <iostream>

using namespace std;

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
            options.push_back({ far_r, far_c, close_r, close_c });
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
                options.push_back({ close_r, close_c });
            }
        }

    }

    if (options.empty() == false) final = true;
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
                if (options.size() > index)
                {
                    options[index].push_back(far_r); options[index].push_back(far_c); options[index].push_back(close_r); options[index].push_back(close_c);
                }

                else options.push_back({ far_r, far_c, close_r, close_c });

                close_r += step_r; close_c += step_c; far_r += step_r; far_c += step_c;
            }
            else if (board[close_r][close_c] == ' ')
            {
                close_r += step_r; close_c += step_c; far_r += step_r; far_c += step_c;
            }
            else end = true;
        }
        if (options.size() > index) index++;


        while (
            (type == 2)
            && (close_r < size) && (close_r >= 0) && (close_c < size) && (close_c >= 0)
            && ((board[close_r][close_c] == ' '))
            )
        {
            options.push_back({ close_r, close_c });
            close_r += step_r; close_c += step_c;
        }
    }

    return end;
}


void Moves::check_move(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    options.clear();

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

    options.clear();

    surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    if (options.empty() == false) possible_pieces.push_back({ coefficient_r,coefficient_c });
}

void Moves::check_king_beat(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    char opponent_m;
    char opponent_k;
    if (color == 'B') { opponent_m = 'c'; opponent_k = 'C'; }
    else { opponent_m = 'b'; opponent_k = 'B'; }

    options.clear();

    king_surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    if (options.empty() == false) possible_pieces.push_back({ coefficient_r,coefficient_c });
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
                    if (options.empty() == false) possible_pieces.push_back({ i , j });
                }
                else if (board[i][j] == color_k)
                {
                    check_move(i, j, color_k, board);
                    if (options.empty() == false) possible_pieces.push_back({ i , j });
                }
            }
        }
    }
    else beats = true;
}

void Moves::create_man_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    possible_moves.clear();
    options.clear();

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

    for (int i = 0; i < options.size(); ++i)
    {
        possible_moves.push_back(options[i]);
    }

    if (beats == true)
    {
        for (int k = 0; k < possible_moves.size(); ++k)
        {
            options.clear();
            surroundings<char, 8>(opponent_m, opponent_k, board, possible_moves[k][0], possible_moves[k][1], 1);
            if (options.size() == 1) for (int i = 0; i < options[0].size(); ++i) possible_moves[k].push_back(options[0][i]);
        }
    }
}

void Moves::create_king_possibilities(int coefficient_r, int coefficient_c, char color, char board[8][8])
{
    possible_moves.clear();
    options.clear();

    char opponent_m = 'd';
    char opponent_k = 'D';
    if (color == 'B') { opponent_m = 'c'; opponent_k = 'C'; }
    else { opponent_m = 'b'; opponent_k = 'B'; }

    if (beats == false)
    {
        king_surroundings<char, 8>('n', 'N', board, coefficient_r, coefficient_c, 2);
    }

    else king_surroundings<char, 8>(opponent_m, opponent_k, board, coefficient_r, coefficient_c, 1);

    for (int i = 0; i < options.size(); ++i)
    {
        possible_moves.push_back(options[i]);
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

