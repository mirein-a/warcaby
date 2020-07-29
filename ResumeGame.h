#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "PlayGameNew.h"

using namespace std;


class ResumeGame
{
public:
	vector<vector<int> > coords;
	vector<char> colors;

	string player_type;
	char current_color;
	string name1;
	string name2;
	int num_pieces_1;
	int num_pieces_2;

	void resume_game();
	void get_coords(int i, int j);
	void get_colors(char color);
};

