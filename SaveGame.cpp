#include "SaveGame.h"

using namespace std;


void SaveGame::save_game(ProtoBoard* pb)
{
    /*
    zapisanie:
    player 2 - computer czy user ('k' lub 'u')
    current player
    imie player1
    imie player2
    liczba pionkow player 1
    liczba pionkow player 2

    wspolrzedne kolor
    wspolrzedne kolor
    ... (16 razy)
    (kolory: 'c', 'C', 'b', 'B', 'n' - brak pionka)
    */


    fstream saved_game;
    string game_name = "game1.txt";
    saved_game.open(game_name.c_str(), ios::out);
    saved_game << current_color << endl;
    saved_game << name1 << endl;
    saved_game << name2 << endl;
    saved_game << num_pieces_1 << endl;
    saved_game << num_pieces_2 << endl;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pb->Vector[i][j] == nullptr)//na pustym miejscu ' '
                saved_game << i << j << endl << 'n' << endl;
            else if (pb->Vector[i][j]->Color == 'c' && pb->Vector[i][j]->GetStatus() == 'm')// 'c' tam gdzie stoi czarny pionek
                saved_game << i << j << endl << 'c' << endl;
            else if (pb->Vector[i][j]->Color == 'C' && pb->Vector[i][j]->GetStatus() == 'k')// 'C' tam gdzie stoi czarna damka
                saved_game << i << j << endl << 'C' << endl;
            else if (pb->Vector[i][j]->Color == 'b' && pb->Vector[i][j]->GetStatus() == 'm')// 'b' tam gdzie stoi bia?y pionek
                saved_game << i << j << endl << 'b' << endl;
            else if (pb->Vector[i][j]->Color == 'B' && pb->Vector[i][j]->GetStatus() == 'k')// 'B' tam gdzie stoi bia?a damka
                saved_game << i << j << endl << 'B' << endl;
        }// dane  formie: ij [\n] 'color'. pol jest 16, czyli takich pozycji bedzie 32
    }
    saved_game << player_type << endl; //typ gracza w ostatniej linijce
    saved_game.close();
}

void SaveGame::get_coords(int i, int j)
{
    coords.push_back({ i, j });
}

void SaveGame::get_colors(char color)
{
    colors.push_back(color);
}
