#include "Pieces.h"


Piece::Piece(char color, int coord_r, int coord_c)
{
    Color = color;
    coordinate_r = coord_r;
    coordinate_c = coord_c;
};

//Piece::~Piece() // Destruktor z powiadomieniem o destrukcji.
//{
    // cout << "Destroyed piece!\n" << endl;
//}

char Man::GetStatus() const
{
    return Status;
}

char King::GetStatus() const
{
    return Status;
}

void Piece::move(vector<int> new_coords, vector<vector<Piece*>>& V)// argumenty to wspó³rzêdne wolnego pola na planszy ( i w wektorze MenVector)
{
    int new_r = new_coords[0];
    int new_c = new_coords[1];
    new_coords.erase(new_coords.begin(), new_coords.begin() + 2);
    swap(V[coordinate_r][coordinate_c], V[new_r][new_c]);
    //w wektorze MenVector w miejscach gdzie nie ma ¿adnych pionów znajduje siê nullptr,
    //a w miejscach gdzie na planszy musi byæ pion znajduje siê pointer na objekt Man
    // wiêc je¿eli chcemy przesunšæ pion na wolne miejsce, to w wektorze zamianiamy miejscami nullptr i Man*
    coordinate_r = new_r;
    coordinate_c = new_c;
    if (!new_coords.empty()) // W przypaku gdy ruchy zawiera w sobie bicie innego piona, wektor z nowymi wspolrzednymi
        beat(new_coords, V);    // jest wektorem 4-elementowym : 2 wspolrzedne na ktore sie ruszy i 2 wspolrzedne pobitego piona
    if (!new_coords.empty())
        move(new_coords, V);

};

void Piece::beat(vector<int>& coords_of_beaten, vector<vector<Piece*>>& V)
{
    int coord_r = coords_of_beaten[0];
    int coord_c = coords_of_beaten[1];
    coords_of_beaten.erase(coords_of_beaten.begin(), coords_of_beaten.begin() + 2);
    delete V[coord_r][coord_c]; // usuwamy pobityy pionek z pamiÊci
    V[coord_r][coord_c] = nullptr; // w wektorze na jego miejscu pozostaje nullptr
};