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

    damage_happened = false;
}

void Player::damage()
{
    Pieces--;

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

void UserPlayer::pick_up_piece(Moves& m, ProtoBoard* pb, Game* g)
{
    vector<int> piece_coords;

    piece_coords = (*g).processEvents('p', m, Color);

    cout << "The chosen piece coordinates:" << endl << "x: " << piece_coords[0] << ", y: " << piece_coords[1] << endl;
    (*g).sth_changed = 888;


    actual_piece = (*pb).Vector[piece_coords[0]][piece_coords[1]];
}

bool UserPlayer::move_piece(Moves& m, ProtoBoard* pb, Player* opponent, Game* g)
{
    vector<int> field_coords;
    bool field_chosen = false;
    while (!field_chosen)
    {

        field_coords = (*g).processEvents('f', m, Color);
        if (field_coords[0] == 440)
        {
            return false;
        }

        (*g).sth_changed = 888;
        (*g).render();

        if (field_coords[0] == 8)
            return false;
        ///// najpierw ruszy siê w tymczasowej symulacji ////
        ProtoBoard temp_pb;
        temp_pb = *pb;

        temp_pb.Vector[actual_piece->coordinate_r][actual_piece->coordinate_c]->move(field_coords, temp_pb.Vector);

        g->Message = "To switch turn press 's' / to cancel move press 'c' ";
        g->render();
        //        cout << "To Switch Turn Press 'S' / To Cancel Move Press 'C' " << endl;
        char switchcancel;
        //        cin >> switchcancel;
        vector <int> switchcancel_vector = (*g).processEvents('c', m, Color);
        (*g).sth_changed = 888;
        switchcancel = (char)switchcancel_vector[0];

        if (switchcancel != 'c')
        {
            field_chosen = true;
        }
        else
        {
            g->BringThePastBack();
            g->HighlightFields(m);
        }
    }

    actual_piece->move(field_coords, (*pb).Vector);
    for (int i = 4; i <= field_coords.size(); i += 4)
    {
        opponent->damage(); // Im wiêksza d³ugoœæ ³añcuszka field_coords tym wiêksza liczba pobitych pionków tym wiêcej razy wywo³ana jest damage()
    }

    if (Color == 'b')
        g->white_player_score = 12 - opponent->Pieces;
    if (Color == 'c')
        g->black_player_score = 12 - opponent->Pieces;
    g->render();

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

void ComputerPlayer::pick_up_piece(Moves& m, ProtoBoard* pb, Game* g)
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


bool ComputerPlayer::move_piece(Moves& m, ProtoBoard* pb, Player* opponent, Game* g)
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

    if (Color == 'b')
        g->white_player_score = 12 - opponent->Pieces;
    if (Color == 'c')
        g->black_player_score = 12 - opponent->Pieces;
    g->render();

    vector<int> only_fields;// only_fields to bêdzie ten sam field_coords tylko bez wspó³rzêdnych pobitych pionków
    for (int i = 0; i < field_coords.size(); i += 4)
    {
        // dodawamy odpowiedne wspó³rzêdne z field_coords do only fields
        only_fields.push_back(field_coords[i]);
        only_fields.push_back(field_coords[i + 1]);


        if (field_coords.size() >= 4)
        {
            int del_x = field_coords[i + 2];
            int del_y = field_coords[i + 3];
            if (g->myBoard.GuiPiece[del_x][del_y] != nullptr)
            {
                g->RemovePiece(del_x, del_y, Color);
            }
        }
    }

    int new_pos_coord_x = only_fields[only_fields.size() - 2];
    int new_pos_coord_y = only_fields[only_fields.size() - 1];

    sf::Vector2f new_position;
    new_position.x = g->myBoard.XY_positions[7 - new_pos_coord_x].x + 67.5;
    new_position.y = g->myBoard.XY_positions[new_pos_coord_y].y + 67.5;
    g->myBoard.GuiPiece[piece_coords[0]][piece_coords[1]]->piece_sprite.setPosition(new_position);

    g->myBoard.GuiPiece[piece_coords[0]][piece_coords[1]]->UpdateGuiPiece(piece_coords[0], piece_coords[1], new_pos_coord_x, new_pos_coord_y, g->myBoard.GuiPiece);

    (*g).render();

    // komputer informuje u¿ytkownika z którego na które pole ruszy³.
    cout << "I just moved " << piece_coords << "to " << only_fields << endl;

    return true;
}

void ComputerPlayer::info()
{
    cout << "ComputerPlayer: " << Name << ". Color: " << Color << ". Pieces left: " << Pieces << "." << endl;
}


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