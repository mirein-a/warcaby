// // // // // // // // // // // // //
//                                  //
//     Game.hpp                     //
//     Dominika Zając               //
//                                  //
// // // // // // // // // // // // //

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Pieces.h"
#include "Moves.h"
#include "Board.hpp"
#include "ProtoBoard.h"

class Game
{
    public:
        Game();

        sf::View            view;
        sf::RenderWindow    window;
        sf::VideoMode       videomode;
    
        Board               myBoard;
        
        ProtoBoard*         pb; 
        
        int                 mouse_x;
        int                 mouse_y;
    
        sf::Vector2f        new_position;
        sf::Vector2f        chosen_position;

        pair<int, int>      chosen_square_coords;
        pair<int, int>      selected_piece_coords;
    
        float               screen_height;
        float               aspect_ratio;
        float               window_h;
        float               window_w;
            
        void                ResetThePast();
        void                BringThePastBack();
    
        sf::Vector2f        previous_position;
        vector<sf::Vector2f>beat_previous_positions;
        vector<vector<int>> beat_coords;
        char                beat_color = 'n';
        void                RemovePiece(int a, int b, char current_color);

        int                 black_player_score = 0;
        int                 white_player_score = 0;

        void                WindowSetUp();
        void                SetUp(vector<vector<Piece*>> v);
    
        vector<int>         highlight;
        void                HighlightPieces(Moves& mo);
        void                HighlightFields(Moves& mo);
    
        sf::Event           event;
        vector<int>         processEvents(char what_do, Moves& mo, char current_color);
        int                 sth_changed = 888;
        void                render();
    
        void                Shout();
        sf::String          Message;
        bool                disable_instructions = false;
    
        bool                game_over = false;



};

#endif /* Game_hpp */
