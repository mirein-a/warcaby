#include "ProtoBoard.h"
#include <iostream>
#include <string>

/*
TA KLASA POWSTALA JAKO TYMCZASOWA, SYMBOLICZNA PLANSZA W CELU SPRAWDZENIA FUNKCJONALNOSCI
POZOSTALYCH KLAS I PRZEPROWADZENIA GRY W KONSOLI.

AUTORAMI SA OBCOWSKA WERONIKA I STANKIEWICZ STANISLAW
*/

using namespace std;

void ProtoBoard::create_men_vector() // wektor MenVector
{


    for (int i = 0; i < 8; i++)
    {
        vector<Piece*> row;// jeden wiersz 2d wektora

        for (int j = 0; j < 8; j++)
            if ((i + j) % 2 != 0 && i != 3 && i != 4)// algorytm wystawieania pionów(w 3 oraz 4 wierszy nie ma pionów)
            {
                if (i >= 0 && i < 3)// górne wiersze
                    row.push_back(new Man('b', i, j));
                else if (i > 4 && i <= 7)// dolne wiersze
                    row.push_back(new Man('c', i, j));
            }
            else
                row.push_back(nullptr);
        Vector.push_back(row);
    }
};


//void ProtoBoard::get_board()//vector<vector<Piece*>>& v)
//{
//
//    for (int i = 0; i < 8; i++)
//    {
//        for (int j = 0; j < 8; j++)
//        {
//            if (Vector[i][j] == nullptr)//na pustym miejscu ' '
//                board[i][j] = ' ';
//            else if (Vector[i][j]->Color == 'c' && Vector[i][j]->GetStatus() == 'm')// 'c' tam gdzie stoi czarny pionek
//                board[i][j] = 'c';
//            else if (Vector[i][j]->Color == 'c' && Vector[i][j]->GetStatus() == 'k')// 'C' tam gdzie stoi czarna damka
//                board[i][j] = 'C';
//            else if (Vector[i][j]->Color == 'b' && Vector[i][j]->GetStatus() == 'm')// 'b' tam gdzie stoi bia?y pionek
//                board[i][j] = 'b';
//            else if (Vector[i][j]->Color == 'b' && Vector[i][j]->GetStatus() == 'k')// 'B' tam gdzie stoi bia?a damka
//                board[i][j] = 'B';
//        }
//    }
//}

void ProtoBoard::get_board()//vector<vector<Piece*>>& v)
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Vector[i][j] == nullptr)//na pustym miejscu ' '
                board[i][j] = ' ';
            else
                board[i][j] = Vector[i][j]->Color;
        }
    }
}

void ProtoBoard::the_display()
{

    //wyswietlenie planszy
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// // // // // // // //
//jak GUI bêdzie gotowe, t¹ funckjê ponizej mozna wykomentowaæ
// // // // // // // //
vector<int> ProtoBoard::choose_piece(Moves& m)
{
    /*
    metoda wywolywana w momencie, gdy gracz ma wybrac pionek, ktory chce przesunac
    */
    string s_num;
    int num;
    int chosen = 0;
    int yes = 0;

    while (chosen == 0)
    {
        while (yes == 0)
        {
            cout << "choose the piece by number: ";
            cin >> s_num;
            if (check_input(s_num) == false) yes = 0;
            else yes = 1;
        }

        num = stoi(s_num);
        if (num < m.possible_pieces.size())
        {
            chosen = 1;
            return m.possible_pieces[num];
        }
        else { chosen = 0; yes = 0; }
    }
    get_board();
    return m.possible_pieces[num];
}

// // // // // // // //
//jak GUI bêdzie gotowe, t¹ funckje ponizej mozna wykomentowaæ
// // // // // // // //
vector<int> ProtoBoard::choose_the_field(Moves& m)
{
    /*
    metoda wywolywana w momencie, gdy gracz ma wybrac pole,
    na ktore chce przesunac wczesniej wybrany pionek
    */
    string s_num;
    int num;
    int chosen = 0;
    int yes = 0;

    while (chosen == 0)
    {
        while (yes == 0)
        {
            cout << "choose the field by number / to cancel chosen piece Press 'c' : ";
            cin >> s_num;

            if (check_input(s_num) || s_num == "c") yes = 1;
            else yes = 0;

        }
        if (s_num == "c")
            return { 8,8 };
        num = stoi(s_num);
        if (num < m.possible_moves.size())
        {
            chosen = 1;
            //get_board();
            //return m.possible_moves[num];
        }
        else { chosen = 0; yes = 0; }
    }
    get_board();
    return m.possible_moves[num];
}


void ProtoBoard::show_possible_pieces(Moves& m)
{
    /*
    metoda wywolywana w celu symbolicznego "podswietlenia" na planszy
    pionkow, ktore mozna przesunac
    */

    for (int i = 0; i < m.possible_pieces.size(); ++i)
    {
        char iChar = ('0' + i);
        board[m.possible_pieces[i][0]][m.possible_pieces[i][1]] = iChar;
    }
    the_display();
}

void ProtoBoard::show_possibilities(Moves& m, Piece* actual_piece)
{
    /*
    metoda wywolywana w celu symbolicznego "podswietlenia" na planszy
    pol, na ktore mozna przesunac wczesniej wybrany pionek
    */
    get_board();
    for (int i = 0; i < m.possible_moves.size(); ++i)
    {
        char iChar = ('0' + i);
        for (int j = 0; j < m.possible_moves[i].size(); j += 4)
            board[m.possible_moves[i][j]][m.possible_moves[i][j + 1]] = iChar;
    }
    board[actual_piece->coordinate_r][actual_piece->coordinate_c] = 'A';
    the_display();
}

bool check_input(const string& s_num)
{
    /*
    Ta metoda sprawdza czy zmienna s_num jest liczba calkowita,
    jest wywolywana przy wybieraniu pionka i wybieraniu pola.
    */
    return !s_num.empty() && find_if(s_num.begin(), s_num.end(), [](unsigned char c)
        {
            return !isdigit(c);
        }) == s_num.end();
}




ProtoBoard& ProtoBoard::operator=(const ProtoBoard& actual_board) // Przeci¹¿enie operatora = potrzebne do tego ¿eby
                                                                  //przypisanie do jednego objektu ProtoBoard drugiego objekta Protoboard
                                                                  // powodowa³o "g³êbokie" kopiowanie tzn kopiowanie wszystkich objektów
                                                                  // na które s¹ wskazania w ProtoBoard a nie tylko proste skopiowanie wskaŸników.
{

    for (int i = 0; i < 8; i++)
    {
        vector<Piece*> row;

        for (int j = 0; j < 8; j++)
        {
            if (actual_board.Vector[i][j] == nullptr)
                row.push_back(nullptr);
            else if (actual_board.Vector[i][j]->GetStatus() == 'm')
                row.push_back(new Man(actual_board.Vector[i][j]->Color, i, j));
            else if (actual_board.Vector[i][j]->GetStatus() == 'k')
                row.push_back(new King(actual_board.Vector[i][j]->Color, i, j));
        }

        Vector.push_back(row);
    }

    get_board();

    return *this;

}

ProtoBoard::~ProtoBoard() // Destruktor ProtoBoard który usuwa z pamiêci wszystkie pionki.
{
    //cout << "Destroyed ProtoBoard!" << endl;

    for (int i = 0; i < 8; i++)
    {

        for (int j = 0; j < 8; j++)
        {
            if (Vector[i][j] != nullptr)
                delete Vector[i][j];
        }

    }

}



void ProtoBoard::create_man_vector_from_save(vector<vector<int> >& coords, vector<char>& colors)
{
    int n = 0;
    for (int i = 0; i < 8; i++)
    {
        vector<Piece*> row;

        for (int j = 0; j < 8; j++)
        {
            if (colors[n] != 'n') row.push_back(new Man(colors[n], i, j));
            else row.push_back(nullptr);
            n++;
        }
        Vector.push_back(row);
    }
}