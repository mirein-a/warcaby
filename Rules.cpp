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

    //AD (3)
    if (num_king_moves >= 30) game_over = true;

}


void Rules::evaluate_results(Player* player1, Player* player2, Game* g) //(UserPlayer player1, UserPlayer player2, Moves m, Board board)
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
        g->myBoard.WhoWonString = "PLAYER 2 (black pieces) HAS WON!";
        g->game_over = true;
        g->render();
    }
    else if ((*player2).Pieces == 0)
    {
        player1_won = true;
        g->myBoard.WhoWonString = "PLAYER 1 (white pieces) HAS WON!";
        g->game_over = true;
        g->render();

    }
    else if (((*player1).Pieces != 0) && ((*player2).Pieces != 0))
    {
        player1_won = false;
        player2_won = false;
        g->myBoard.WhoWonString = "      BOTH PLAYERS WON!";
        g->game_over = true;
        g->render();
    }


    //Ad (4)
    else if (num_king_moves >= 30)
    {
        player1_won = false;
        player2_won = false;
        g->myBoard.WhoWonString = "      BOTH PLAYERS WON!";
        g->game_over = true;
        g->render();
    }

}


void Rules::check_status(Player* player, char color, ProtoBoard* pb, Game* g)
{
    /*
    tutaj bedziemy sprawdzac czy pionek zwykly (Man) powinien zmienic atrybut na damke (King)
    (atrybut statusu danego obiektu klasy Piece)
    */

    vector<int> coord_vector = { 30,30 };
    if ((player->actual_piece != nullptr))
    {
        if ((color == 'b') && (*player).actual_piece->coordinate_r == 7)
        {
            int coord_r = player->actual_piece->coordinate_r;
            int coord_c = player->actual_piece->coordinate_c;
            delete (*pb).Vector[coord_r][coord_c];
            player->actual_piece = nullptr;
            (*pb).Vector[coord_r][coord_c] = nullptr;
            (*pb).Vector[coord_r][coord_c] = new King('B', coord_r, coord_c);
            player->actual_piece = (*pb).Vector[coord_r][coord_c];

            coord_vector = { coord_r, coord_c };

            sf::Vector2f king_position;
            king_position.x = g->myBoard.GuiPiece[coord_r][coord_c]->piece_sprite.getPosition().x;
            king_position.y = g->myBoard.GuiPiece[coord_r][coord_c]->piece_sprite.getPosition().y;

            delete g->myBoard.GuiPiece[coord_r][coord_c];
            g->myBoard.GuiPiece[coord_r][coord_c] = nullptr;
            g->myBoard.GuiPiece[coord_r][coord_c] = new GUI_King(coord_r, coord_c, 'b');

            g->myBoard.GuiPiece[coord_r][coord_c]->piece_sprite.setPosition(king_position.x, king_position.y);

        }

        else if ((color == 'c') && (*player).actual_piece->coordinate_r == 0)
        {
            int coord_r = player->actual_piece->coordinate_r;
            int coord_c = player->actual_piece->coordinate_c;
            delete (*pb).Vector[coord_r][coord_c];
            player->actual_piece = nullptr;
            (*pb).Vector[coord_r][coord_c] = nullptr;
            (*pb).Vector[coord_r][coord_c] = new King('C', coord_r, coord_c);
            player->actual_piece = (*pb).Vector[coord_r][coord_c];
            g->myBoard.GuiPiece[coord_r][coord_c]->piece_status = 'k';

            coord_vector = { coord_r, coord_c };

            sf::Vector2f king_position;
            king_position.x = g->myBoard.GuiPiece[coord_r][coord_c]->piece_sprite.getPosition().x;
            king_position.y = g->myBoard.GuiPiece[coord_r][coord_c]->piece_sprite.getPosition().y;

            delete g->myBoard.GuiPiece[coord_r][coord_c];
            g->myBoard.GuiPiece[coord_r][coord_c] = nullptr;
            g->myBoard.GuiPiece[coord_r][coord_c] = new GUI_King(coord_r, coord_c, 'c');
            g->myBoard.GuiPiece[coord_r][coord_c]->piece_sprite.setPosition(king_position.x, king_position.y);
        }
    }
}



