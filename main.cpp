
#include "Moves.h"
#include "PlayGameNew.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "ProtoBoard.h"
#include "ResumeGame.h"
#include "Game.hpp"

using namespace std;

void print(vector<vector<int> > v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
            cout << v[i][j] << ", ";
        cout << endl;
    }
}

char board[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', 'B', ' ', 'b', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
};

char board_1[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', ' '},
      {' ', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', 'B', ' ', 'b', ' ', 'b'},
      {'b', ' ', ' ', ' ', 'b', ' ', ' ', ' '},
      {' ', 'c', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
}; //create_king_possibilities(2, 3, 'b', board1) op: 5,0 4,1

char board_2[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', 'c', ' ', 'b', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', 'c', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', ' ', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
}; //create_possibilities(1,4,'b',board_2) op: 3,2 2,3 5,0 4,1
//   create_possibilities(4,1,'c',board_2)

char board_3[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', 'c', ' ', 'b', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', ' ', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
};// create_possibilities(1,4,'b',board_3) op: 3,2 2,3 (dziala)
//   create_possibilities(2,1,'b', board_3) op: 3,2 3,0 (dziala)

char board_4[8][8] = {
      {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
      {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
      {' ', 'b', ' ', 'c', ' ', 'c', ' ', 'b'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', 'c', ' ', ' ', ' ', 'c', ' ', ' '},
      {' ', ' ', 'c', ' ', ' ', ' ', 'c', ' '},
      {' ', 'c', ' ', 'c', ' ', ' ', ' ', 'c'},
      {'c', ' ', 'c', ' ', 'c', ' ', 'c', ' '},
};// create_possibilities(1,4,'b',board_3) op: 3,2 2,3 5,0 4,1 oraz 3,6 2,5 5,4 4,5



int main()
{
    string s_mode = "nie cyfra";
    int mode = 3;
    vector<vector<int> > default1; /*deafultowe wektory dla PlayGameNew*/
    vector<char> default2;
    while (mode > 2) /*pytamy u¿ytkownika o wybór gry dopóki nie wybierze cyfry 0,1,2*/
    {
        s_mode = "nie cyfra";
        while (check_input(s_mode) == false)
        {
            cout << "Choose the game mode:" << endl;
            cout << "User vs User (entr: 0)" << endl;
            cout << "User vs Computer (enter: 1)" << endl;
            cout << "Reload and reload the previous game (enter: 2)" << endl;
            cin >> s_mode;
        }
        mode = stoi(s_mode);
    }

    if (mode == 0) /*jesli 0 -> wywo³aj grê z UserPlayerem, menu samo nastawia defaluty*/
    {
        PlayGameNew<UserPlayer> pg(false, default1, default2); /*tu s¹ te defaulty i to jest jedyna "poprawna wersja"*/
        pg.lets_play();
    }
    else if (mode == 1) /*analogicznie, wybór trybu gry*/
    {
        PlayGameNew<ComputerPlayer> pg(false, default1, default2); /*tu te¿ defaulty*/
        pg.lets_play();
    }
    if (mode == 2) /*jeœli wczytujemy z pliku to nie ma potrzeby nastawiania, ResumeGame zrobi to automatycznie*/
    {
        ResumeGame rg;
        rg.resume_game();
    }

    return 0;

}