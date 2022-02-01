#pragma once 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Button{

	public :
		Button (sf::RenderWindow& window, const size_t x, const size_t y, const size_t size, const std::string text);
		void draw_circle(sf::RenderWindow& window, int radius, int x, int y, int color) const;
		void set_button_text(sf::RenderWindow& window, std::string text, int x, int y);
		void display (sf::RenderWindow& window);
		void check_events(sf::RenderWindow& window, size_t x_click, size_t y_click);
		void set_is_clicked(bool const new_val) {is_clicked = new_val;}
		bool get_is_clicked() const {return is_clicked; }
		std::size_t get_x() {return x_button;}
		std::size_t get_y() {return y_button;}

	private :
		std::size_t x_button;
		std::size_t y_button;
		bool is_clicked;
		std::size_t radius_button;
		std::string button_text;
};			