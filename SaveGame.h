#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "ProtoBoard.h"
#include "Player.h"
#include <stdlib.h>

using namespace std;

class SaveGame
{
	/*
	elementy do zapisania:
	(1) imiona graczy, ilosc pionkow, kolory
	(2) czyja kolejka teraz
	(3) ulozeniee pionkow na planszy (zapisanie wspolrzednych pionkow z ManVectora i stworzenie nowego Vectora)
	(4) damki czy zwykle pionki (chyba wystarczy tyle linijek ile jest pionkow i dla kazdego pionka w tym miejscu te same dane)

	maksymalna liczba gier do zapisania: 5
	*/
public:
	vector<vector<int> > coords;
	vector<char> colors;

	string player_type;
	char current_color;
	string name1;
	string name2;
	int num_pieces_1;
	int num_pieces_2;


	void save_game(ProtoBoard* pb);
	void get_coords(int i, int j);
	void get_colors(char color);
};

