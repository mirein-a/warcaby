// // // // // // // // // // // // //
//                                  //
//     Game.cpp                     //
//     Dominika Zając               //
//                                  //
// // // // // // // // // // // // //

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Board.hpp"


Game::Game():

  aspect_ratio()
, screen_height()
, window_h()
, window_w()
, view(sf::Vector2f(980.0f, 600.0f), sf::Vector2f(1960.0f, 1200.0f))  // center and size of the view
, myBoard()
{
}

vector<int> Game::processEvents(char what_do, Moves& mo, char current_color)
{
    // funkcja analizuje dane wejściowe gracza, takie jak kliknięcie myszki czy przycisku klawiatury
    // funkcja analizuje owe dane w zależności od zmiennej what_do:
    
    // what_do == c - cancel or switch (anuluj lub zmień kolejkę)
    // what_do == a - pause or switch (zatrzymaj grę lub zmień kolejkę)
    // what_do == p - pick piece (wybierz pionek)
    // what_do == f - pick field (wybierz pole)
    
    vector<int> dummy_vector = {440};
    
     while (sth_changed==888)
    {
        while (window.pollEvent(event))
        {
            if (what_do == 'c')  // cancel or switch
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                    {
                        window.close();
                        render();
                        break;
                    }
                    
                    case sf::Event::MouseButtonReleased:
                    {
                        sf::Vector2i mouse_pix = sf::Mouse::getPosition(window);
                        sf::Vector2f mouse_coords = window.mapPixelToCoords(mouse_pix);
                        
                        mouse_x = mouse_coords.x;
                        mouse_y = mouse_coords.y;
                        
                        // guzik do wyłączania instrukcji
                        
                        if (myBoard.disable_instr_button.getGlobalBounds().contains(mouse_x, mouse_y))
                        {
                            if (disable_instructions == false)
                                disable_instructions = true;
                            else
                                disable_instructions = false;
                            render();
                        }
                    }
                        
                    case sf::Event::KeyReleased:
                    {
                        vector<int> return_key = {0};
                        switch(event.key.code)
                        {
                            case sf::Keyboard::S:  // switch
                            
                                return_key[0] = 115; // s in ASCII
                                sth_changed = 1;
                                return return_key;
                                break;
                            
                            case sf::Keyboard::C:  // cancel
                            
                                return_key[0] = 99; // c in ASCII
                                sth_changed = 1;
                                Message = "To cancel chosen piece, pick a different one, \nTo continue, pick a field.";
                                return return_key;
                                break;
                        }
                        break;
                    }
                }
                
            }
            
            if (what_do == 'a') // pause or switch
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                    {
                        window.close();
                        render();
                        break;
                    }
                        
                    case sf::Event::KeyReleased:
                    {
                        vector<int> return_key = {0};
                        switch(event.key.code)
                        {
                            case sf::Keyboard::P:  // pause
                            
                                return_key[0] = 112; // p in ASCII
                                sth_changed = 1;
                                Message = "";
                                return return_key;
                                break;
                                
                            case sf::Keyboard::S:  // switch
                            
                                return_key[0] = 115; // s in ASCII
                                sth_changed = 1;
                                Message = "";

                                return return_key;
                                break;
                        }
                        break;
                    }
                        
                    case sf::Event::MouseButtonReleased:
                    {
                        sf::Vector2i mouse_pix = sf::Mouse::getPosition(window);
                        sf::Vector2f mouse_coords = window.mapPixelToCoords(mouse_pix);
                        
                        mouse_x = mouse_coords.x;
                        mouse_y = mouse_coords.y;
                        
                        // guzik do wyłączania instrukcji
                        
                        if (myBoard.disable_instr_button.getGlobalBounds().contains(mouse_x, mouse_y))
                        {
                            if (disable_instructions == false)
                                disable_instructions = true;
                            else
                                disable_instructions = false;
                            render();
                        }
                    }
                }
            }
            
            if (what_do == 'p' or what_do == 'f') // pick piece or field
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                    {
                        window.close();
                        render();
                        break;
                    }
                        
                    case sf::Event::MouseButtonReleased:
                    {
                        
                        sf::Vector2i mouse_pix = sf::Mouse::getPosition(window);
                        sf::Vector2f mouse_coords = window.mapPixelToCoords(mouse_pix);
                        
                        mouse_x = mouse_coords.x;
                        mouse_y = mouse_coords.y;
                        
                        std::cout << endl << "mouse_x: " << mouse_x << ", mouse_y: " << mouse_y << endl;
                        
                        if (what_do == 'p') // pick piece
                        {
                            bool chosen = false;
                            bool correct_piece = false;
                            for (int i = 0; i < 8; i++)
                            {
                                for (int j = 0; j < 8; j++)
                                {
                                    if (myBoard.GuiPiece[i][j] != nullptr)
                                    {
                                        // jeśli myszka znajduje się na pionku o współrzędnych [i][j]
                                        if (myBoard.GuiPiece[i][j]->piece_sprite.getGlobalBounds().contains(mouse_x, mouse_y))
                                        {
                                            chosen = true;
                                            if (myBoard.GuiPiece[i][j]->piece_color == current_color)
                                            {
                                                for (int n = 0; n < mo.possible_pieces.size(); ++n)
                                                {
                                                    // jeśli możemy się tym pionkiem ruszyć
                                                    if (mo.possible_pieces[n][0] == i && mo.possible_pieces[n][1] == j)
                                                    {
                                                        correct_piece = true;
                                                        selected_piece_coords.first = i;
                                                        selected_piece_coords.second = j;
                                                        
                                                        vector<int> return_coords = {0,0};
                                                        return_coords[0] = i;
                                                        return_coords[1] = j; // zwracamy współrzędne pionka
                                                        
                                                        sth_changed = 1;
                                                        return return_coords;
                                                        break;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                cout << "Not your turn"<< endl;
                                                sth_changed = 888;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    else
                                    {
                                        sth_changed = 888;
                                    }
                                }
                            }
                            if (chosen == false)
                                cout << "No piece has been chosen "<<endl;
                            
                            else if (correct_piece == false)
                                cout << "No moves possible for this piece"<< endl;
                            sth_changed = 888;
                        }
                        
                        if (what_do == 'f') // pick field
                        {
                            if (!(mouse_x < 442 || mouse_x > 1522 || mouse_y < 61 || mouse_y > 1141))
                            {
                                // iterujemy, by znaleźć kwadrat, w którym znajduje się myszka
                                for (int v = 0; v < 8; v++)
                                {
                                    if (mouse_x >= myBoard.XY_positions[v].x and mouse_x < myBoard.XY_positions[v].x + 135)
                                    {
                                        mouse_x = myBoard.XY_positions[v].x + 67.5;
                                        chosen_square_coords.first = 7 - v;
                                    }
                                    
                                    if (mouse_y >= myBoard.XY_positions[v].y and mouse_y < myBoard.XY_positions[v].y + 135)
                                    {
                                        mouse_y = myBoard.XY_positions[v].y + 67.5;
                                        chosen_square_coords.second = v;
                                    }
                                }
                                
                                std::cout << endl << "chosen row: " << chosen_square_coords.first << ", chosen column: " << chosen_square_coords.second << endl;
                                
                                if (myBoard.GuiPiece[chosen_square_coords.first][chosen_square_coords.second]!=nullptr)
                                {
                                    // jeśli po wybraniu pionka chcemy zmienić wybór i wybrać inny, klikamy na inny pionek
                                    // tego samego koloru
                                    
                                    if (myBoard.GuiPiece[chosen_square_coords.first][chosen_square_coords.second]->piece_color == current_color)
                                    {
                                        cout << "Piece changed"<<endl;
                                        return dummy_vector;
                                    }
                                }
                                
                                if (not ((chosen_square_coords.first == selected_piece_coords.first) and (chosen_square_coords.second == selected_piece_coords.second)))
                                {
                                    bool correct_move = false;
                                    int num = 0;
                                    
                                    for (int i = 0; i < mo.possible_moves.size(); ++i)
                                    {
                                        int the_final_field_x = 0;
                                        int the_final_field_y = 0;
                                        
                                        if (mo.possible_moves[i].size() >= 4)
                                        {
                                            // w przypadku wielokrotnych bić, podświetlamy i wybieramy jedynie
                                            // ostatnie pole, na którym znajdzie się pionek
                                            
                                            the_final_field_x = mo.possible_moves[i].size() - 4;
                                            the_final_field_y = mo.possible_moves[i].size() - 3;
                                        }
                                        else
                                        {
                                            the_final_field_x = 0;
                                            the_final_field_y = 1;
                                        }
                                        
                                        // jeśli wybrane pole jest jednym z ostatnich pól, na które może ruszyć się pionek
                                        if ((mo.possible_moves[i][the_final_field_x] == chosen_square_coords.first) && (mo.possible_moves[i][the_final_field_y] == chosen_square_coords.second))
                                        {
                                            correct_move = true;
                                            num = i;
                                            
                                            if (myBoard.GuiPiece[selected_piece_coords.first] [selected_piece_coords.second] != nullptr)
                                            {
                                                new_position.x = mouse_x;
                                                new_position.y = mouse_y;
                                                
                                                // previous_position pobierane, by móc ewentualnie anulować ruch
                                                previous_position = myBoard.GuiPiece[selected_piece_coords.first][selected_piece_coords.second]->piece_sprite.getPosition();
                                                
                                                // ustawienie nowej pozycji pionka w GUI
                                                myBoard.GuiPiece[selected_piece_coords.first] [selected_piece_coords.second]->piece_sprite.setPosition(new_position);
                                                
                                                if (mo.possible_moves[i].size() >= 4)
                                                {
                                                    for (int t = 0; t < mo.possible_moves[i].size(); t +=4)
                                                    {
                                                        int a = mo.possible_moves[i][t+2]; // współrzędna x zbitego pionka
                                                        int b = mo.possible_moves[i][t+3]; // współrzędna y zbitego pionka
                                                        
                                                        if (myBoard.GuiPiece[a][b] != nullptr)
                                                            RemovePiece(a, b, current_color);  // usunięcie pionka z planszy GUI
                                                    }
                                                }
                                                
                                                myBoard.GuiPiece[selected_piece_coords.first][selected_piece_coords.second]->UpdateGuiPiece(selected_piece_coords.first, selected_piece_coords.second, chosen_square_coords.first, chosen_square_coords.second, myBoard.GuiPiece);
                                            }
                                        }
                                    }
                                    
                                    if (correct_move)
                                    {
                                        return mo.possible_moves[num];
                                    }
                                    else
                                    {
                                        cout << endl<<"This move is not possible "<< endl;
                                        sth_changed = 888;
                                    }
                                    
                                }
                            }
                        }
                        
                        if (myBoard.disable_instr_button.getGlobalBounds().contains(mouse_x, mouse_y)) // guzik do wyłączania instrukcji
                        {
                            if (disable_instructions == false)
                                disable_instructions = true;
                            else
                                disable_instructions = false;
                            sth_changed = 888;
                            render();
                        }

                        break;
                    }
                }
            }
        }
        sth_changed = 888;
    }
    sth_changed = 888;
    return dummy_vector;

                
}

void Game::render()
{
    window.clear(sf::Color(255, 254, 238)); // oczyszczanie wszystkich niepotrzebnych elementów, które zostały z poprzedniego załadowania
    
    window.setView(view);

    if (game_over == false)
    {
        window.draw(myBoard.checkerboard);
        myBoard.border[0].setPosition(sf::Vector2f(50, 58));
        myBoard.border[1].setPosition(sf::Vector2f(1610, 58));
        
        string number_string1 = to_string(white_player_score);
        string number_string2 = to_string(black_player_score);

        myBoard.scoretext_white.setString(number_string1);
        myBoard.scoretext_black.setString(number_string2);
        
        window.draw(myBoard.border[0]);
        window.draw(myBoard.border[1]);

        window.draw(myBoard.scoretext1);
        window.draw(myBoard.scoretext2);
        window.draw(myBoard.scoretext_white);
        window.draw(myBoard.scoretext_black);

        
        for (int s = 0; s < highlight.size(); s++)
        {
            window.draw(myBoard.square[highlight[s]]);
        }

        myBoard.ChangeToKing();
      
        
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (myBoard.GuiPiece[i][j] != nullptr)
                {
                    window.draw(myBoard.GuiPiece[i][j]->piece_sprite);
                }
            }
        }
                
        if (disable_instructions)
            myBoard.disable_instr_button.setFillColor(sf::Color(240,239,223));
        else
            myBoard.disable_instr_button.setFillColor(sf::Color(255,255,250));

        window.draw(myBoard.disable_instr_button);
        
        myBoard.InstrButtonText.setString("Instructions");
        window.draw(myBoard.InstrButtonText);
        Shout();
            
    }
    
    else
    {
        window.draw(myBoard.menu);
        myBoard.WhoWonText.setString(myBoard.WhoWonString);
        window.draw(myBoard.WhoWonText);
        myBoard.Exit.setString("Exit Game");
        window.draw(myBoard.ExitButton);
        window.draw(myBoard.Exit);
        
        while (window.pollEvent(event))
                {
                    switch(event.type)
                    {
        
                        case sf::Event::MouseButtonReleased:
                        {
                            sf::Vector2i mouse_pix = sf::Mouse::getPosition(window);
                            sf::Vector2f mouse_coords = window.mapPixelToCoords(mouse_pix);
        
                            mouse_x = mouse_coords.x;
                            mouse_y = mouse_coords.y;
        
                            if (myBoard.ExitButton.getGlobalBounds().contains(mouse_x, mouse_y))
                            {
                                window.close();
                            }
                        }
                    }
                }
    }
    
    

    window.display();
}

void Game::WindowSetUp()
{
    // Ustawienia okna aplikacji
    
    screen_height =sf::VideoMode::getDesktopMode().height;
    std::cout << endl << "Desktop Resolution:";
    std::cout << endl << sf::VideoMode::getDesktopMode().height << ", " << sf::VideoMode::getDesktopMode().width;

    aspect_ratio = screen_height / 1600.0f;
    window_h = 1200 * aspect_ratio;
    window_w = 1960 * aspect_ratio;
    cout << endl << "aspect ratio " << aspect_ratio << ", new height: " << window_h << ", new width: " << window_w;
    
    videomode.height = window_h;
    videomode.width = window_w;
    window.create(videomode, "Checkers", sf::Style::Titlebar | sf::Style::Close);
    
    view.zoom(1);
}

void Game::SetUp(vector<vector<Piece*>> v)
{
    // Przygotowanie elementów i ich tekstur do wyświetlenia
    
    myBoard.CreateXYPositions();
    myBoard.loadTextures();

    myBoard.CreateGuiPieceVector(v);
    myBoard.SetPieceTextures();
    
    selected_piece_coords.first = 30;
    selected_piece_coords.second = 30;
    
    myBoard.ChangeToKing();
        
}

void Game::HighlightPieces(Moves& mo)
{
    // Tworzenie wektora z współrzędnymi pionków, którymi gracz może się ruszyć
    
    highlight.clear();
    for (int i = 0; i < mo.possible_pieces.size(); ++i)
    {
        int highlight_number = mo.possible_pieces[i][0] * 8 + mo.possible_pieces[i][1];
        highlight.push_back(highlight_number);
    }
    render();
}

void Game::HighlightFields(Moves& mo) 
{
    // Tworzenie wektora z współrzędnymi pól, na które gracz może się ruszyć wybranym pionkiem
    
    highlight.clear();
    for (int x = 0; x < mo.possible_moves.size(); ++x)
    {
        if (mo.possible_moves[x].size() > 4)
        {
            for (int k = 0; k < mo.possible_moves[x].size(); k += 4)
            {
                highlight.clear();

                int highlight_number = mo.possible_moves[x][k] * 8 + mo.possible_moves[x][k+1];
                highlight.push_back(highlight_number);
            }
        }
        
        else
        {
            int highlight_number = mo.possible_moves[x][0] * 8 + mo.possible_moves[x][1];
            highlight.push_back(highlight_number);
        }
    }
    
    render();
}


void Game::BringThePastBack()
{
    // Przywrócenie informacji o wybranym i pobitych pionkach po anulowaniu
    
    swap(myBoard.GuiPiece[chosen_square_coords.first][chosen_square_coords.second], myBoard.GuiPiece[selected_piece_coords.first][selected_piece_coords.second]);
    myBoard.GuiPiece[selected_piece_coords.first][selected_piece_coords.second]->coordinates = sf::Vector2f(selected_piece_coords.first, selected_piece_coords.second);
    
    myBoard.GuiPiece[selected_piece_coords.first] [selected_piece_coords.second]->piece_sprite.setPosition(previous_position);
    
    
    for (int t=0; t< beat_coords.size(); t++)
    {
        
        int a = beat_coords[t][0];
        int b = beat_coords[t][1];
        
        if (a != 30 && b != 30)  // jesli w tym ruchu nie został zbity żaden pion, a = 30 i b = 30
        {
            myBoard.GuiPiece[a][b]->piece_sprite.setPosition(beat_previous_positions[t].x, beat_previous_positions[t].y);
            myBoard.GuiPiece[a][b]->coordinates = sf::Vector2f(a,b);
            myBoard.GuiPiece[a][b]->piece_color = beat_color;
            
        }
    }
}


void Game::ResetThePast()
{
    // Reset zmiennych potrzebnych do przywracania informacji po anulowaniu

    for (int t=0; t< beat_coords.size(); t++)
    {
        beat_previous_positions[t] = sf::Vector2f(3000,3000);
        
        beat_coords[t][0] = 30;
        beat_coords[t][1] = 30;

        beat_color = 'n';
    }
}

void Game::RemovePiece(int a,int b, char current_color) 
{
    // Usuwanie pionka z planszy GUI
    
    // zapisywanie informacji o pionku, w razie ewentualnej przyszłej anulacji bieżącego bicia
    beat_previous_positions.push_back(myBoard.GuiPiece[a][b]->piece_sprite.getPosition());
    vector<int> one_beat;
    one_beat.push_back(myBoard.GuiPiece[a][b]->coordinates.x);
    one_beat.push_back(myBoard.GuiPiece[a][b]->coordinates.y);
    beat_coords.push_back(one_beat);
    if (current_color == 'b') beat_color = 'c';
    if (current_color == 'c') beat_color = 'b';
    
    // usunięcie pionka z okna aplikacji
    
    myBoard.GuiPiece[a][b]->piece_sprite.setPosition(sf::Vector2f(3000, 3000));
    myBoard.GuiPiece[a][b]->piece_color = 'n'; // non-existant
    myBoard.GuiPiece[a][b]->coordinates = sf::Vector2f(30,30);

}

void Game::Shout()
{
    // Ustawianie treści wiadomości (instrukcji) wyświetlanej na ekran
    
    if (disable_instructions == false)
    {
        myBoard.CenterText.setString(Message);

        window.draw(myBoard.CenterText);
    }
}
