#pragma once
#include <iostream>
#include <vector>
#include "Moves.h"
#include "Rules.h"
#include "Player.h"
#include "ProtoBoard.h"
#include "SaveGame.h"

using namespace std;

template<class PlayerOfChoice>
class PlayGameNew
{
public:
    ProtoBoard* pb;
    UserPlayer* player1;
    PlayerOfChoice* player2;
    Player* current_player;
    Player* current_opponent;
    Moves m;
    Rules r;

    //int num_king_moves;
    char current_color;
    string player_type;
    string name1;
    string name2;
    int num_pieces_1;
    int num_pieces_2;


    PlayGameNew(bool from_saved, vector<vector<int> >& coords, vector<char>& colors, char currentcolor = 'b', string name_1 = "", string name_2 = "", int num_pieces1 = 12, int num_pieces2 = 12);
    void one_full_turn();
    void switch_turn();
    void lets_play();
    void prepare_and_save();
};




template<class PlayerOfChoice> PlayGameNew<PlayerOfChoice>::PlayGameNew(bool from_saved, vector<vector<int> >& coords, vector<char>& colors, char currentcolor, string name1, string name2, int num_pieces1, int num_pieces2)
{
    /*
    Konstruktor klasy PlayGame.
    Wywolane sa w nim obiekty pozostalych klas wykorzystywanych do prowadzenia rozgrywki.
    Innymi slowy sa tu przygotowane wszystkie elementy potrzebne do przeprowadzenia pelnej gry.
    */

    if (from_saved == false)
    {


        pb = new ProtoBoard;

        player1 = new UserPlayer('b');
        player2 = new PlayerOfChoice('c');
        player1->set_name();
        player2->set_name();
        current_player = player1;
        current_opponent = player2;
        player1->info();
        player2->info();
        pb->create_men_vector();
        pb->get_board();

        r.num_king_moves = 0;
    }

    else
    {

        pb = new ProtoBoard;

        player1 = new UserPlayer('b');
        player2 = new PlayerOfChoice('c');
        player1->set_name_from_save(name1);
        player2->set_name_from_save(name2);
        player1->Pieces = num_pieces1;
        player2->Pieces = num_pieces2;
        if (currentcolor == 'b') { current_player = player1; current_opponent = player2; }
        else { current_player = player2; current_opponent = player1; }
        player1->info();
        player2->info();
        pb->create_man_vector_from_save(coords, colors);
        pb->get_board();

        r.num_king_moves = 0;
    }
};

template<class PlayerOfChoice> void PlayGameNew<PlayerOfChoice>::switch_turn()
{
    /*
    Ta metoda co kolejke zmienia atrybut "obecnego gracza" i "obecnego przeciwnika"
    */

    if (current_player == player1)
    {
        current_player = player2;
        current_opponent = player1;
    }
    else
    {
        current_player = player1;
        current_opponent = player2;
    }
}

template<class PlayerOfChoice> void PlayGameNew<PlayerOfChoice>::one_full_turn()
{
    /*
    Ta metoda odpowiada za przeprowadzenie jednej pelnej rundy w grze.
    Wywolywane sa tutaj metody na obiektach pozostalych klas (bedacymi atrybutami PlayGame)
    w schematycznej kolejnosci
    */

    current_player->info();

    bool piece_is_chosen = false;

    while (!piece_is_chosen)
    {
        m.get_possible_pieces((*current_player).Color, (*pb).board);

        pb->show_possible_pieces(m);

        current_player->pick_up_piece(m, pb);

        m.create_possibilities((*current_player).actual_piece->coordinate_r, (*current_player).actual_piece->coordinate_c, (*current_player).actual_piece->Color, (*pb).board);

        pb->show_possibilities(m, (*current_player).actual_piece);

        piece_is_chosen = current_player->move_piece(m, pb, current_opponent);

        r.check_status(current_player, (*current_player).actual_piece->Color, pb); //TU DODA£AM ZMIANE DAMEK

        pb->get_board();
    }

    pb->the_display();

    if (current_player->damage_happened) r.num_king_moves = 0;
    else r.num_king_moves++;
    current_player->damage_happened = false;

    switch_turn();
}

template<class PlayerOfChoice> void PlayGameNew<PlayerOfChoice>::lets_play()
{
    /*
    Ta metoda odpowiada za "uruchomienie" gry przygotowanej w Konstruktorze.
    Po kazdym wywolaniu metody one_full_turn sprawdzany jest stan na planszy
    i na tej podstawie kontynuowana lub przerywana jest petla dalszego prowadzenia gry.
    */

    //Rules r;
    char ans = 's';
    (*pb).the_display();
    while ((r.game_over == false) && (ans == 's'))
    {
        one_full_turn();
        r.check_if_game_over(m, player1, player2, pb);
        cout << "To pause game press 'p'/ to switch turn press 's'" << endl;
        cin >> ans;
    }
    if (ans == 'p') prepare_and_save();
    else r.evaluate_results(player1, player2);
}

template<class PlayerOfChoice> void PlayGameNew<PlayerOfChoice>::prepare_and_save()
{
    SaveGame sv;

    sv.current_color = current_player->Color;
    sv.name1 = player1->get_name();
    sv.name2 = player2->get_name();
    sv.num_pieces_1 = player1->Pieces;
    sv.num_pieces_2 = player2->Pieces;

    if (player2->player_type == "computer") sv.player_type = "computer";
    else sv.player_type = "user";

    sv.save_game(pb);
}
