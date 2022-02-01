#pragma once 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Grid{

	public:

		Grid(size_t nb_x, size_t nb_y, size_t square_size);
		void draw_square(sf::RenderWindow& window, const size_t x, const size_t y, const size_t size, const sf::Color& color);
		void display(sf::RenderWindow& window);
		void submit_new_word(std::wstring word);
		void write_character (sf::RenderWindow& window, int i, int j);
		void play_sound( int index, int j );
		void print_text ( sf::RenderWindow& window, size_t jmax );
		void write_next_line (sf::RenderWindow& window, int j);
		void print_colors(sf::RenderWindow& window, size_t jmax); 

		void set_word_case(int i, int j, wchar_t c) { words_array[i][j] = c; }
		void set_color_case(int i, int j, int val) { colors_array[i][j] = val; }
		int get_color_case(int i, int j) const { return colors_array[i][j]; }	

	private:	

		size_t Square_Size;
		size_t height;
		size_t length;
		size_t nb_squares_x;
		size_t nb_squares_y;
		wchar_t words_array[10][10];
		sf::RectangleShape rectangles_array[10][10];
		int colors_array[10][10];
		size_t cpt_words;
		size_t x_grid;
		size_t y_grid;
};		