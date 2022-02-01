#pragma once 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Rectangular_Button{

    public :
        Rectangular_Button (sf::RenderWindow& window, const size_t x, const size_t y, const size_t width, const size_t heigth, const std::string text, const sf::Color& color);
        void draw_recangle(sf::RenderWindow& window, size_t x, size_t y, size_t width, size_t heigth, sf::Color& color) const;
        void set_button_text(sf::RenderWindow& window, std::string text, int x, int y);
        void display (sf::RenderWindow& window);
        bool is_clicked(size_t x_click, size_t y_click);
        std::size_t get_x() {return x_button;}
        std::size_t get_y() {return y_button;}
        std::size_t get_width() {return width_button;}
        std::size_t get_heigth() {return height_button;}

    private :
        std::size_t x_button;
        std::size_t y_button;
        std::size_t width_button;
        std::size_t height_button;
        std::string button_text;
        sf::Color Color;
};          