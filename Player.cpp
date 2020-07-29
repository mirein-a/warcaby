#include "Player.h"
#include <random>
#include <iostream>
using namespace std;

template<typename T>
T random_from_vector(vector<T> vector)
{
    int size = vector.size();
    srand((unsigned)time(0));
    int num = rand() % size;
    return vector[num];
}

Player::Player(char color)
{
    Color = color;
    Pieces = 12;


    //TUTAJ ZMIENIA£AM
    damage_happened = false;
}

void Player::damage()
{
    Pieces--;

    //TUTAJ ZMIENIA£AM
    damage_happened = true;
};

void Player::info()
{
    cout << "I'm a player with " << Pieces << " pieces left, my color is " << Color << endl;
}

void UserPlayer::set_name()
{
    cout << "What's your name?" << endl;
    cin >> Name;
}

void UserPlayer::pick_up_piece(Moves& m, ProtoBoard* pb)
{
    vector<int> piece_coords;
    /*    while (true)
        {
            ProtoBoard temp_pb;
            temp_pb = *pb;
            Moves temp_m = m;
            piece_coords = temp_pb.choose_piece(temp_m);
            actual_piece = temp_pb.Vector[piece_coords[0]][piece_coords[1]];
            temp_m.create_possibilities(actual_piece->coordinate_r, actual_piece->coordinate_c, Color, temp_pb.board);
            temp_pb.show_possibilities(temp_m, actual_piece);
            piece_coords = { actual_piece->coordinate_r, actual_piece->coordinate_c };
            cout << "Are you sure? (0 - nie, 1 - tak)" << endl;
            int sure;
            cin >> sure;
            if (sure == 1)
                break;
            else
                (*pb).show_possible_pieces(m);
        }*/
    piece_coords = (*pb).choose_piece(m);
    actual_piece = (*pb).Vector[piece_coords[0]][piece_coords[1]];
}

bool UserPlayer::move_piece(Moves& m, ProtoBoard* pb, Player* opponent)
{
    vector<int> field_coords;
    bool field_chosen = false;
    while (!field_chosen)
    {
        field_coords = (*pb).choose_the_field(m);
        if (field_coords[0] == 8)
            return false;
        ///// najpierw ruszy siê w tymczasowej symulacji ////
        ProtoBoard temp_pb;
        temp_pb = *pb;
        temp_pb.Vector[actual_piece->coordinate_r][actual_piece->coordinate_c]->move(field_coords, temp_pb.Vector);
        temp_pb.get_board();
        temp_pb.the_display();
        cout << "To Switch Turn Press 's' / To Cancel Move Press 'c' " << endl;
        char switchcancel;
        cin >> switchcancel;
        if (switchcancel != 'c')
            field_chosen = true;
        else
            pb->show_possibilities(m, actual_piece);
    }
    actual_piece->move(field_coords, (*pb).Vector);
    for (int i = 4; i <= field_coords.size(); i += 4)
        opponent->damage(); // Im wiêksza d³ugoœæ ³añcuszka field_coords tym wiêksza liczba pobitych pionków tym wiêcej razy wywo³ana jest damage()
    return true;
}

void UserPlayer::info()
{
    cout << "Player: " << Name << ". Color: " << Color << ". Pieces left: " << Pieces << "." << endl;
}

void ComputerPlayer::set_name()
{

    //Niektóre mo¿liwe imiona dla gracza-komputera
    vector<string> names = {
    "CALEB" ,	"CHARLOTTE",
    "BENJAMIN",	"LAYLA",
    "THEODORE", 	"OPHELIA",
    "LIAM", 	"PENELOPE",
    "HENRY",	"ACELYNN",
    "GABRIEL",	"KAIA",
    "ETHAN",	"LUNA",
    "AUGUST",	"NORA",
    "JONAH",	"ACACIA",
    "XANDER",	"ADELINE",
    "EMMETT",	"AMARA",
    "LEVI",	"AVA",
    "MILO",	"ELLA",
    "LUCAS",	"ESME",
    "OLIVER",	"IVY",
    "SEBASTIAN",	"HANNAH",
    "WILLIAM",	"MIA",
    "ACE",	"OLIVIA",
    "GRAYSON",	"VIOLET",
    "OWEN",	"ANASTASIA" };
    Name = random_from_vector(names);

}

void ComputerPlayer::pick_up_piece(Moves& m, ProtoBoard* pb)
{

    vector<Piece*> pieces = estimation.best_pieces(m, pb);

    actual_piece = random_from_vector(pieces);
}


// przeci¹¿enie operatora << potrzebne do tego ¿eby wyœwietliæ zawartoœæ wektora intów poprzez cout
ostream& operator<<(ostream& os, const vector<int>& coords)
{
    for (auto const& i : coords)
    {
        os << i << " ";
    }
    return os;
}


bool ComputerPlayer::move_piece(Moves& m, ProtoBoard* pb, Player* opponent)
{
    vector<int> field_coords;

    if (!estimation.pieces_with_moves[actual_piece].empty())
        field_coords = random_from_vector(estimation.pieces_with_moves[actual_piece]);
    else
        field_coords = random_from_vector(m.possible_moves);
    vector<int> piece_coords = { actual_piece->coordinate_r, actual_piece->coordinate_c };
    actual_piece->move(field_coords, (*pb).Vector);
    // Im wiêksza d³ugoœæ ³añcuszka field_coords tym wiêksza liczba pobitych pionków tym wiêcej razy wywo³ana jest damage()
    for (int i = 4; i <= field_coords.size(); i += 4)
    {
        opponent->damage();
    }

    vector<int> only_fields;// only_fields to bêdzie ten sam field_coords tylko bez wspó³rzêdnych pobitych pionków
    for (int i = 0; i < field_coords.size(); i += 4)
    {
        // dodawamy odpowiedne wspó³rzêdne z field_coords do only fields
        only_fields.push_back(field_coords[i]);
        only_fields.push_back(field_coords[i + 1]);
    }
    // komputer informuje u¿ytkownika z którego na które pole ruszy³.
    cout << "I just moved " << piece_coords << "to " << only_fields << endl;
    return true;
}

void ComputerPlayer::info()
{
    cout << "ComputerPlayer: " << Name << ". Color: " << Color << ". Pieces left: " << Pieces << "." << endl;
}

//TUTAJ DODA£AM

string UserPlayer::get_name()
{
    return Name;
}

string ComputerPlayer::get_name()
{
    return Name;
}

void UserPlayer::set_name_from_save(string name)
{
    Name = name;
}

void ComputerPlayer::set_name_from_save(string name)
{
    Name = name;
}