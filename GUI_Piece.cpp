// // // // // // // // // // // // //
//                                  //
//     GUI_Piece.hpp                //
//     Dominika Zając               //
//                                  //
// // // // // // // // // // // // //

#include "GUI_Piece.hpp"

#include <SFML/Graphics.hpp>
#include <vector>



GUI_Piece::GUI_Piece(int x_coord, int y_coord, char color) 
{
    coordinates.x = x_coord;
    coordinates.y = y_coord;
    piece_color = color;
    piece_status = 'm';
    
    if (piece_color == 'c')
    {
        piece_sprite.scale(sf::Vector2f(0.22, 0.22));
        piece_sprite.setOrigin(305, 305);
    }
    
    if (piece_color == 'b')
    {
        piece_sprite.setOrigin(510, 510);
        piece_sprite.scale(sf::Vector2f(0.13, 0.13));
    }
};


void GUI_Piece::UpdateGuiPiece(int p_x, int p_y, int s_x, int s_y, std::vector<std::vector<GUI_Piece*>>& GuiPieceVector)
{
    // Zmiana pozycji pionka w GUI (przy wybraniu dla niego nowego pola)
    
    std::swap(GuiPieceVector[p_x][p_y], GuiPieceVector[s_x][s_y]);
    coordinates.x = s_x;
    coordinates.y = s_y;
}
