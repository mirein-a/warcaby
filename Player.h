#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include "Pieces.h"
#include "Moves.h"
#include "ProtoBoard.h"
#include "Estimation.h"

using namespace std;

class Player
{
public:

    char Color;

    int Pieces; // aktualna liczba pionów gracza

    Piece* actual_piece; // wskaŸnik na pionek którym siê zamierza ruszyæ

    Player(char color);

    virtual void set_name() = 0;

    virtual void pick_up_piece(Moves& m, ProtoBoard* pb) = 0; // funkcja ustala ctual_piece

    virtual bool move_piece(Moves& m, ProtoBoard* pb, Player* opponent) = 0;

    void damage(); // Funkcja odejmuje HP gracza.

    virtual void info();

    //TUTAJ DODA£AM
    virtual string get_name() = 0;
    virtual void set_name_from_save(string name) = 0;
    string player_type;
    bool damage_happened;
};

class UserPlayer : virtual public Player
{
    string Name; // Gracz-cz³owiek dodatkowa ma imiê
public:
    UserPlayer(char color) : Player(color) {};

    void set_name() override;

    void pick_up_piece(Moves& m, ProtoBoard* pb) override;

    bool move_piece(Moves& m, ProtoBoard* pb, Player* opponent) override;

    void info() override;

    //TUTAJ DODA£AM
    string get_name() override;
    void set_name_from_save(string name) override;
    string player_type;
};

class ComputerPlayer : virtual public Player
{
    string Name;
public:
    Estimation estimation;

    ComputerPlayer(char color) : Player(color) {};

    void set_name() override;

    void pick_up_piece(Moves& m, ProtoBoard* pb) override;

    bool move_piece(Moves& m, ProtoBoard* pb, Player* opponent) override;
    
    void info() override;

    //TUTAJ DODA£AM
    string get_name() override;
    void set_name_from_save(string name) override;
    string player_type;
};


