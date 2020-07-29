// // // // // // // // // // // // //
//                                  //
//     GUI_Piece.hpp                //
//     Dominika Zając               //
//                                  //
// // // // // // // // // // // // //



#ifndef GUI_Piece_hpp
#define GUI_Piece_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>


class GUI_Piece
{
    public:
            GUI_Piece(int x_coord, int y_coord, char color);

            sf::Vector2f            coordinates;
            char                    piece_color;
            char                    piece_status = 'm';
            sf::Sprite              piece_sprite;
    
            void                    UpdateGuiPiece(int p_x, int p_y, int s_x, int s_y, std::vector<std::vector<GUI_Piece*>>&GuiPieceVector);


};

class GUI_King : public GUI_Piece
{
    public:
            GUI_King(int x_coord, int y_coord, char color) : GUI_Piece(x_coord, y_coord, color) { piece_status = 'k'; };
};


#endif /* GUI_Piece_hpp */
