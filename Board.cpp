// // // // // // // // // // // // //
//                                  //
//     Board.cpp                     //
//     Dominika Zając               //
//                                  //
// // // // // // // // // // // // //

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <iostream>

#include "Board.hpp"
#include "Pieces.h"
#include "GUI_Piece.hpp"

Board::Board():
 w_piece_tex()
, b_piece_tex()
, piece_sprite()
, font()
{
}

void Board::loadTextures()
{
    // Załadowanie wszystkich tekstur, ustawienie wielkości elementów, przypisanie czcionki, koloru itp.
    
    if (!w_piece_tex.loadFromFile("board_and_pieces/white_piece.png"))
    {
        std::cout << "White piece load failed \n";
        system("pause");
    }
    
    if (!b_piece_tex.loadFromFile("board_and_pieces/black_piece.png"))
    {
        std::cout << "Black piece load failed \n";
        system("pause");
    }
    
    if (!w_king_tex.loadFromFile("board_and_pieces/white_king.png"))
    {
        std::cout << "White king load failed \n";
        system("pause");
    }
    
    if (!b_king_tex.loadFromFile("board_and_pieces/black_king.png"))
    {
        std::cout << "Black king load failed \n";
        system("pause");
    }
    
    if (!font.loadFromFile("board_and_pieces/calibri.ttf"))
    {
        std::cout << "Font load failed \n";
        system("pause");
    }
    
    if (!checkerboard_tex.loadFromFile("board_and_pieces/checkerboard_left_right.png"))
    {
        std::cout << "Checkerboard load failed \n";
        system("pause");
    }

    menu.setSize(sf::Vector2f(1960,1200));
    menu.setFillColor(sf::Color::Blue);
    menu.setPosition(0, 0);
    
    checkerboard.setPosition(380, 0);
    checkerboard.setTexture(checkerboard_tex);

    border_image.create(300, 1082, sf::Color(0, 0, 0, 15));
    border_tex.loadFromImage(border_image);
    border[0].setTexture(border_tex);
    border[1].setTexture(border_tex);
    
    w_piece_tex.setSmooth(true);
    b_piece_tex.setSmooth(true);
    w_king_tex.setSmooth(true);
    b_king_tex.setSmooth(true);
    
    scoretext1.setFont(font);
    scoretext1.setCharacterSize(50);
    scoretext1.setFillColor(sf::Color::Black);
    scoretext1.setString("Black Score: ");

    scoretext2.setFont(font);
    scoretext2.setCharacterSize(50);
    scoretext2.setFillColor(sf::Color::Black);
    scoretext2.setString("White Score: ");

    scoretext_white.setFont(font);
    scoretext_white.setCharacterSize(100);
    scoretext_white.setFillColor(sf::Color::Black);

    scoretext_black.setFont(font);
    scoretext_black.setCharacterSize(100);
    scoretext_black.setFillColor(sf::Color::Black);
    
    scoretext1.setPosition(75, 58);
    scoretext2.setPosition(1635, 58);
    scoretext_white.setPosition(1730, 100);
    scoretext_black.setPosition(170, 100);
    
    CenterText.setFont(font);
    CenterText.setCharacterSize(80);
    CenterText.setPosition(160, 500);
    CenterText.setFillColor(sf::Color::Black);
    CenterText.setOutlineColor(sf::Color::White);
    CenterText.setOutlineThickness(3);
    
    disable_instr_button.setPosition(1625, 990);
    disable_instr_button.setSize(sf::Vector2f(270,90));
    disable_instr_button.setOutlineColor(sf::Color(39, 45, 45));
    disable_instr_button.setOutlineThickness(7);
        
    InstrButtonText.setPosition(1638, 1000);
    InstrButtonText.setFont(font);
    InstrButtonText.setCharacterSize(50);
    InstrButtonText.setFillColor(sf::Color::Black);
    
    WhoWonText.setFont(font);
    WhoWonText.setCharacterSize(80);
    WhoWonText.setPosition(450, 500);
    WhoWonText.setFillColor(sf::Color::Red);
    WhoWonText.setOutlineColor(sf::Color::White);
    WhoWonText.setOutlineThickness(3);
    
    ExitButton.setPosition(850, 900);
    ExitButton.setSize(sf::Vector2f(270, 90));
    ExitButton.setFillColor(sf::Color::Red);
    ExitButton.setOutlineColor(sf::Color::White);
    ExitButton.setOutlineThickness(7);
    
    Exit.setFont(font);
    Exit.setCharacterSize(50);
    Exit.setPosition(882, 910);
    Exit.setFillColor(sf::Color::Black);


    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            int num = i*8 + j;
            
            square[num].setSize(sf::Vector2f(135, 135));
            square[num].setFillColor(sf::Color::Red);
            square[num].setPosition(XY_positions[7 - i].x, XY_positions[j].y);
        }
    }
}


void Board::CreateGuiPieceVector(vector<vector<Piece*>> PieceVector)
{
    // Stworzenie wektora GUI_Piece (pionków GUI) na podstawie wektora pionków logicznych (Piece)
    
    for (int i = 0; i < 8; i++)
    {
        vector<GUI_Piece*> row;
        for (int j = 0; j < 8; j++)
        {
            if (PieceVector[i][j] == nullptr)
                row.push_back(nullptr);
            else
            {
                if ((PieceVector[i][j]->Color == 'B') or (PieceVector[i][j]->Color == 'b'))
                {
                    if (PieceVector[i][j]->Status == 'm')
                        row.push_back(new GUI_Piece(i, j, 'b'));
                    else if (PieceVector[i][j]->Status == 'k')
                        row.push_back(new GUI_King(i, j, 'b'));
                }
                
                if ((PieceVector[i][j]->Color == 'C') or (PieceVector[i][j]->Color == 'c'))
                {
                    if (PieceVector[i][j]->Status == 'm')
                        row.push_back(new GUI_Piece(i, j, 'c'));
                    else if (PieceVector[i][j]->Status == 'k')
                        row.push_back(new GUI_King(i, j, 'c'));
                }
            }
        }
        GuiPiece.push_back(row);
    }
}


void Board::SetPieceTextures()
{
    // Ustawienie tekstur i pozycji pionków na początku rozgrywki lub po ponownym załadowaniu gry
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (GuiPiece[i][j] == nullptr)
                continue;
            else
            {
                GuiPiece[i][j]->piece_sprite.setPosition(XY_positions[7-i].x + 67.5, XY_positions[j].y + 67.5);

                if (GuiPiece[i][j]->piece_color == 'c') // 'c' tam gdzie stoi czarny pionek
                {
                    if ( GuiPiece[i][j]->piece_status == 'm')
                        GuiPiece[i][j]->piece_sprite.setTexture(b_piece_tex);
                    else if (GuiPiece[i][j]->piece_status == 'k')
                        GuiPiece[i][j]->piece_sprite.setTexture(b_king_tex);
                    
                }
                else if (GuiPiece[i][j]->piece_color == 'b') // 'b' tam gdzie stoi bialy pionek
                {
                    if ( GuiPiece[i][j]->piece_status == 'm')
                        GuiPiece[i][j]->piece_sprite.setTexture(w_piece_tex);
                    else if (GuiPiece[i][j]->piece_status == 'k')
                        GuiPiece[i][j]->piece_sprite.setTexture(w_king_tex);
                }
            }
        }
    }
}


void Board:: CreateXYPositions()
{
    // Stworzenie wektora pozycji, na których mogą znaleźć się pionki czy czerwone kwadraty podświetlenia pól
    
    for (int i = 0; i < 8; i++)
    {
        XY_positions[i].x = pos_zero_x + i * square_size;
        XY_positions[i].y = pos_zero_y + i * square_size;
    }
}


void Board::ChangeToKing()
{
    // Zmiana tekstury pionka z tekstury zwykłego piona (bez kropki w środku) na teksturę króla (z kropką w środku)
    
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (GuiPiece[r][c] != nullptr)
                if (GuiPiece[r][c]->piece_status == 'k')
                {
                    if (GuiPiece[r][c]->piece_color == 'b')
                        GuiPiece[r][c]->piece_sprite.setTexture(w_king_tex);
                    else if (GuiPiece[r][c]->piece_color == 'c')
                        GuiPiece[r][c]->piece_sprite.setTexture(b_king_tex);
                }
        }
    }
}
