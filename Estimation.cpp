#include "Estimation.h"

void Estimation::get_pieces(Moves& m, ProtoBoard* pb)
{
    // funkcja bierze vector<vector<int>> possible_pieces i zwraca na podstawie go vector<Piece*> pieces, tzn wektor wska¿ników na mo¿liwe piony
    vector<Piece*> pieces;

    for (int i = 0; i < m.possible_pieces.size(); ++i)
    {
        pieces.push_back((*pb).Vector[m.possible_pieces[i][0]][m.possible_pieces[i][1]]);
    }

    pieces_with_rating = prerate(pieces);
}

template<typename T>
map< T, double> Estimation::prerate(vector<T> options)
{
    // funkcja przypisuje ka¿demu pionkowi rating = 0
    // zwraca map w którym first to pionek (pointer na pionek) a second to go rating.
    map< T, double> rated;

    for (int i = 0; i < options.size(); i++)
        rated[options[i]] = 0;

    return rated;
}

void Estimation::rate_endangered_pieces(ProtoBoard& pb)
{
    // funckja podwy¿sza rating pionkom dla których istnieje zagro¿enie ze strony innych pionków
    Moves temp_m;

    for (auto it = pieces_with_rating.begin(); it != pieces_with_rating.end(); ++it)
    {
        temp_m.get_dangerous_pieces(it->first->coordinate_r, it->first->coordinate_c, it->first->Color, pb.board);
        if (!temp_m.dangerous_pieces.empty())
        {
            it->second += 1;
        }
    }
}

template<typename T>
void Estimation::set_acceptable_rating(map< T, double>& options)
{
    // funkcja znajduje maksymalny rating wœród pionków który przyjmuje jako jedyny mo¿liwy
    for (auto it = options.begin(); it != options.end(); ++it)
    {
        if (it->second < acceptable_rating)
            acceptable_rating = it->second;
    }
    for (auto it = options.begin(); it != options.end(); ++it)
    {
        if (it->second > acceptable_rating)
            acceptable_rating = it->second;
    }

}

template<typename T>
void Estimation::sort(map< T, double>& options)
{
    // funckja usuwa pionki z niewystarczaj¹co wyokim rating

    set_acceptable_rating(options);

    for (auto it = options.begin(); it != options.end(); )
    {
        if (it->second < acceptable_rating)
            it = options.erase(it);
        else
        {
            ++it;
        }
    }
}

void Estimation::test_piece(Piece* piece, Moves& m, ProtoBoard& pb)
{
    // funkcja testuje mo¿liwe ruchy ka¿dego pionka, i w zale¿noœci od efektów tych ruchów zmienia rating pionka i zapisuje (lub nie) ruch jako preferowany 
    pieces_with_moves[piece] = {};

    Moves temp_m = m;

    temp_m.create_possibilities(piece->coordinate_r, piece->coordinate_c, piece->Color, pb.board);

    for (int i = 0; i < temp_m.possible_moves.size(); i++)
    {


        if (good_move(piece, temp_m.possible_moves[i], pb))
        {

            // Je¿eli zagro¿enia nie ma, zapisujemy do pionka ten ruch jako preferowany.
            //piece->first->preferable_moves.push_back(temp_m.possible_moves[i]);
            pieces_with_moves[piece].push_back(temp_m.possible_moves[i]);
        }
        else
        {
            double size = temp_m.possible_moves.size();
            pieces_with_rating[piece] -= (1 / size);
        }
    }


}

bool Estimation::good_move(Piece* piece, vector<int>& move, ProtoBoard& pb)
{
    Moves temp_m;
    ProtoBoard temp_pb; // Dla danego ruchu stwarzamy nowe ProtoBoard w którym testujemy ruch.
    temp_pb = pb; // Kopiujemy zawartoœæ pb do temp_pb wykorzystaj¹c przeci¹¿ony operator = .
    Piece* temp_piece = temp_pb.Vector[piece->coordinate_r][piece->coordinate_c]; // Stwarzamy pointer na objekt Piece, do krórego przypisujemy adres TYMCZASOWEGO ODPOWIEDNIKA AKTUALNEGO PIONKA NA TYMCZASOWEJ PLANSZY.
    temp_piece->move(move, temp_pb.Vector); // Przesuwamy tymczasowy pionek w tymczasowym ProtoBoard.
    temp_pb.get_board();
    temp_m.get_dangerous_pieces(temp_piece->coordinate_r, temp_piece->coordinate_c, temp_piece->Color, temp_pb.board); // Sprawdzamy czy pojawi³o siê jakieœ zagro¿enie.

    // "Oceniamy" aktualny pionek w zale¿noœci od tego czy pojawi³o siê jakieœ zagro¿enie.
    if (!temp_m.dangerous_pieces.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

vector<Piece*> Estimation::best_pieces(Moves& m, ProtoBoard* pb)
{
    pieces_with_rating.clear();
    pieces_with_moves.clear();
    get_pieces(m, pb);
    rate_endangered_pieces(*pb);
    sort(pieces_with_rating);
    for (auto it = pieces_with_rating.begin(); it != pieces_with_rating.end(); ++it)
        test_piece(it->first, m, *pb);
    sort(pieces_with_rating);
    vector<Piece*> best_pieces;
    for (auto it = pieces_with_rating.begin(); it != pieces_with_rating.end(); ++it)
        best_pieces.push_back(it->first);
    return best_pieces;
}