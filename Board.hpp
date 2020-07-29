// // // // // // // // // // // // //
//                                  //
//     Board.hpp                    //
//     Dominika Zając               //
//                                  //
// // // // // // // // // // // // //

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Pieces.h"
#include "GUI_Piece.hpp"


class Board
{
    public:
            Board();  //constructor of board
        
            vector<vector<GUI_Piece*>>   GuiPiece;
            
            sf::Vector2f                 XY_positions[8];

            void                         loadTextures();
    
            int                          square_size = 135;
            int                          pos_zero_x = 442;
            int                          pos_zero_y = 61;    

            void                         CreateXYPositions();
            void                         CreateGuiPieceVector(vector<vector<Piece*>> PieceVector);
            void                         SetPieceTextures();
    
            vector<vector<GUI_Piece*>>   KingVector;
            void                         ChangeToKing();

            void                         UpdatePieceSprites(int p_x, int p_y, int s_x, int s_y);            
    
            sf::RectangleShape           square[64];
            sf::Sprite                   piece_sprite[8][8];
            sf::Sprite                   border[2];
            sf::Sprite                   checkerboard;
    
            sf::RectangleShape           menu;
    
            sf::Texture                  w_piece_tex;
            sf::Texture                  b_piece_tex;
            sf::Texture                  w_king_tex;
            sf::Texture                  b_king_tex;
            sf::Texture                  checkerboard_tex;
            sf::Texture                  border_tex;
            sf::Image                    border_image;
    
            sf::Font                     font;
            sf::Text                     scoretext_white;
            sf::Text                     scoretext_black;
            sf::Text                     scoretext1;
            sf::Text                     scoretext2;
    
            sf::Text                     CenterText;
    
            sf::RectangleShape           disable_instr_button;
            sf::Text                     InstrButtonText;
    
            sf::Text                     WhoWonText;
            sf::String                   WhoWonString;
    
            sf::RectangleShape           ExitButton;
            sf::Text                     Exit;
    

    
};


#endif /* Board_hpp */
