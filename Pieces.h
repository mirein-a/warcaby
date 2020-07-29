#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Piece
{
public:

    char Status; // m(Man) lub k(King)
    char Color;  // b lub c
    int coordinate_r; //pionowa wspó³rzedna na planszy (od 0 do 7)
    int coordinate_c; //pozioma wspó³rzedna na planszy (od 0 do 7)

    Piece(char color, int coord_r, int coord_c);

    //    ~Piece();

    virtual char GetStatus() const = 0; // Klasa bazowa Piece nie posiada statusa

    void move(vector<int> new_coords, vector<vector<Piece*>>& men_vector);

    void beat(vector<int>& coords_of_beaten, vector<vector<Piece*>>& V);

};

class Man : public Piece // Zwyk³y pionek
{
public:

    Man(char color, int coord_r, int coord_c) : Piece(color, coord_r, coord_c) { Status = 'm'; };

    char GetStatus() const override;

};

class King : public Piece // Damka
{
public:

    King(char color, int coord_r, int coord_c) : Piece(color, coord_r, coord_c) { Status = 'k'; };

    char GetStatus() const override;
};
