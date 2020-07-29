#include "Moves.h"
//#include "PlayGameNew.h"
#include <iostream>
#include <string>
#include <vector>
//#include "Player.h"
//#include "ProtoBoard.h"
//#include "ResumeGame.h"

using namespace std;

void print(vector<vector<int> > v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
            cout << v[i][j] << ", ";
        std::cout << endl;
    }
}

char board[8][8] = {
      {' ', 'c', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'B', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', ' ', ' ', ' ', ' ', 'b', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', 'c', ' ', ' ', ' ', ' '},
      {'c', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', ' ', ' '},
}; // create_king_possibilities(1, 0, 'B', board) op: 3,2 2,1 5,4 4,3 7,6 6,5

char board_1[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', ' '},
      {' ', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', 'B', ' ', 'b', ' ', 'b'},
      {'b', ' ', ' ', ' ', 'b', ' ', ' ', ' '},
      {' ', 'c', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
}; // create_king_possibilities(2, 3, 'B', board_1) op: 5,0 4,1

char board_2[8][8] = {
      {' ', 'b', ' ', 'b', ' ', ' ', ' ', 'b'},
      {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', ' ', ' ', 'b', ' ', 'b'},
      {' ', ' ', 'b', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'C', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
      {' ', 'b', ' ', 'c', ' ', ' ', ' ', 'c'},
      {'c', ' ', ' ', ' ', 'c', ' ', 'c', ' '},
};// create_king_possibilities(5,0,'C',board_2) op: 2,3 3,2 0,5 1,4 oraz 7,2 6,1

char board_3[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'b', ' ', 'C', ' ', 'b', ' ', 'b', ' '},
      {' ', ' ', ' ', ' ', ' ', 'b', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', 'b', ' ', ' '},
      {' ', ' ', 'c', ' ', 'c', ' ', ' ', ' '},
      {' ', 'c', ' ', 'c', ' ', 'b', ' ', 'c'},
      {'c', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
};//create_king_possibilities(1,2,'C',board_3) op: 6,5 4,5

char board_4[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'B', ' ', 'c', ' ', 'c', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', ' '},
      {' ', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', ' ', ' '},
};//create_king_possibilities(2,1,'B',board_4) op: 5,4 4,3 7,6 6,5

char board_5[8][8] = {
      {' ', 'b', ' ', ' ', ' ', ' ', ' ', 'C'},
      {'b', ' ', ' ', ' ', 'b', ' ', 'b', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', 'b', ' ', 'B', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', 'C', ' ', ' '},
      {'b', ' ', ' ', ' ', 'b', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', ' ', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', ' ', ' '},
};//create_king_possibilities(4,3,'B',board_5)

char board_6[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'B', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'c', ' ', 'B', ' ', 'b', ' ', 'b'},
      {' ', ' ', 'c', ' ', 'c', ' ', ' ', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', ' '},
      {' ', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', ' '},
      {'c', ' ', 'c', ' ', 'c', ' ', ' ', ' '},
};//create_king_possibilities(2,3,'B',board_6) op: 0

//bool operator<(vector<int> v, int limits[2])
//{
//    return ((v[0] < limits[0]) || (v[1] < limits[1]));
//}

//bool operator<(vector<int> v, int limits[2])
//{
//    return  (v[0] >= limits[0]) && (v[0] <= limits[1]) && (v[1] >= limits[0]) && (v[1] <= limits[1]);
//}

int main()
{
    //string s_mode = "nie cyfra";
    //int mode = 3;
    //vector<vector<int> > default1;
    //vector<char> default2;


    //while (mode > 2)
    //{
    //    s_mode = "nie cyfra";
    //    while (check_input(s_mode) == false)
    //    {
    //        cout << "Choose the game mode:" << endl;
    //        cout << "User vs User (entr: 0)" << endl;
    //        cout << "User vs Computer (enter: 1)" << endl;
    //        cout << "Reload and reload the previous game (enter: 2)" << endl;
    //        cin >> s_mode;
    //    }
    //    mode = stoi(s_mode);
    //}

    //if (mode == 0)
    //{
    //    PlayGameNew<UserPlayer> pg(false, default1, default2);
    //    pg.lets_play();
    //}
    //else if (mode == 1)
    //{
    //    PlayGameNew<ComputerPlayer> pg(false, default1, default2);
    //    pg.lets_play();
    //}
    //if (mode == 2)
    //{
    //    ResumeGame rg;
    //    rg.resume_game();
    //}

    //vector<int> vect = { 1,2 };
    //const int dir[2] = { 2,4 };

    //vector<int> vect1;
    //vect1 = vect + dir;

    //cout << vect1[0] << "," << vect[1];

    //Moves m;

    //vector<int> v = { 1,2 };
    //int lim1[] { 0,1 };
    //int lim2[] { 1,3 };
    //int lim3[] { 3,4 };

    //std::cout << (v < lim1); //true
    //std::cout << (v < lim2); //false
    //std::cout << (v < lim3); //false

    vector<int> v1 = { 1,2 };
    vector<int> v2 = { 1,0 };
    vector<int> v3 = { 3,8 };

    Moves m;

    m.possible_pieces = { { 1,2 } };

    std::cout << m.check_k_piece(v2, board);
    //std::cout << (v2 < m.limits);
    //std::cout << (v3 < m.limits);

    return 0;
}