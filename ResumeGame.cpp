#include "ResumeGame.h"


void ResumeGame::resume_game()
{
	fstream saved_game;
	string game_name = "game1.txt";
	string datum;

	saved_game.open(game_name.c_str(), ios::in);
	if (saved_game.good() == false)
		cout << "no game has been saved" << endl;
	else
	{
		int i = 0;
		while ((getline(saved_game, datum)) && (i < 5))
		{
			if (i == 0) { datum.c_str(); current_color = datum[0]; }
			else if (i == 1) name1 = datum;
			else if (i == 2) name2 = datum;
			else if (i == 3) num_pieces_1 = atoi(datum.c_str());
			else if (i == 4) num_pieces_2 = atoi(datum.c_str());
			++i;
		}
		while ((getline(saved_game, datum)) && (i < 134))
		{
			if (i % 2 == 0)
			{
				int temp_coords = atoi(datum.c_str());
				get_coords(temp_coords / 10, (temp_coords - temp_coords / 10));
			}
			else { datum.c_str(); get_colors(datum[0]); }
			if (i == 132)
			{
				if (datum == "computer") player_type = "computer";
				else player_type = "user";
			}
			i++;
		}

		saved_game.close();

		if (player_type == "computer")
		{
			PlayGameNew<ComputerPlayer> pg(true, coords, colors, current_color, name1, name2, num_pieces_1, num_pieces_2);
			pg.lets_play();
		}
		else
		{
			PlayGameNew<UserPlayer> pg(true, coords, colors, current_color, name1, name2, num_pieces_1, num_pieces_2);
			pg.lets_play();
		}
	}
}

void ResumeGame::get_coords(int i, int j)
{
	coords.push_back({ i, j });
}

void ResumeGame::get_colors(char color)
{
	colors.push_back(color);
}