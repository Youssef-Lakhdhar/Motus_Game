#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <codecvt>
#include <vector>
#include <stdexcept>  // std::invalid_argument
#include <math.h>
extern "C"{
    #include <unistd.h>
}

#include "Grid.hh"
#include "Text.hh"

#define BORDER_THICKNESS 2
#define X_WINDOW 800
#define Y_WINDOW 750
#define SPACE_BETWEEN_SQUARES 8
#define TEXTBAR_HEIGHT 30
#define LATEX_FONT "../fonts/cmunss.ttf"
#define MENU_CHARACTER_SIZE 40
#define BOLD true
#define NON_BOLD false
#define ITALIC true
#define NON_ITALIC false
#define UNDERLINED true 
#define NON_UNDERLINED false

using namespace std;

Grid :: Grid(size_t nb_x, size_t nb_y, size_t square_size) {

	Square_Size = square_size;
	nb_squares_x = nb_x;
	nb_squares_y = nb_y;
	height = nb_y * square_size + (nb_y - 1) * SPACE_BETWEEN_SQUARES + BORDER_THICKNESS;
	length = nb_x * square_size + (nb_x - 1) * SPACE_BETWEEN_SQUARES + BORDER_THICKNESS;
	cpt_words = 0;
	x_grid = 0;
	y_grid = 0;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j){
			words_array[i][j] = ' ';
			colors_array[i][j] = 0;
		}
	}
}	

void Grid :: draw_square(sf::RenderWindow& window, const size_t x, const size_t y, const size_t size, const sf::Color& color) {

	sf::RectangleShape square;
	square.setSize(sf::Vector2f(size, size));
	square.setOutlineColor(sf::Color::Black);
	square.setFillColor(color);
	square.setOutlineThickness(BORDER_THICKNESS);
	square.setPosition(x, y);
	rectangles_array[x_grid][y_grid] = square;
	window.draw(square);
}

void Grid :: submit_new_word(wstring word){

	for (long unsigned int i = 0; i < word.length(); ++i) {
		words_array[i][cpt_words] = word[i];
	}

	if(cpt_words < nb_squares_y - 1){
		cpt_words ++;
	}
}

void Grid :: write_character (sf::RenderWindow& window, int index, int j) {

	size_t x_init = (X_WINDOW - length) / 2; 
	size_t y_init = (0.95*Y_WINDOW - height - TEXTBAR_HEIGHT) / 2;
	string sound_path;

	for (int i = 0; i <= index; ++i) {

		sf::Color color;
		switch(colors_array[i][j]){

			case 1:
				color = sf::Color::Red;
				sound_path = "../sounds/son_rouge.wav";
				break;
			case -1:
				color = sf::Color::Yellow;
				sound_path = "../sounds/son_jaune.wav";
				break;
			default:
				color = sf::Color::White;
				sound_path = "../sounds/son_blanc.wav";
				break;		
		}

		draw_square(window, x_init + i * (Square_Size + SPACE_BETWEEN_SQUARES), y_init + j * (Square_Size + SPACE_BETWEEN_SQUARES), Square_Size, color);
	}	
}

void Grid :: play_sound( int index, int j ) {

	string sound_path;

	for (int i = 0; i <= index; ++i) {

		sf::Color color;
		switch(colors_array[i][j]){

			case 1:
				sound_path = "../sounds/son_rouge.wav";
				break;
			case -1:
				sound_path = "../sounds/son_jaune.wav";
				break;
			default:
				sound_path = "../sounds/son_blanc.wav";
				break;		
		}
	}	

	sf::SoundBuffer Buffer;
    Buffer.loadFromFile(sound_path);
    sf::Sound sound;
   	sound.setBuffer(Buffer);
    sound.play();
    while( sound.getStatus() != sf::SoundSource::Stopped ){
    }
}

void Grid :: write_next_line (sf::RenderWindow& window, int j) {

	size_t x_init = (X_WINDOW - length) / 2; 
	size_t y_init = (0.95*Y_WINDOW - height - TEXTBAR_HEIGHT) / 2;

	for (size_t i = 0; i < nb_squares_x; ++i) {

		sf::Color color;
		switch(colors_array[i][j]){

			case 1:
				color = sf::Color::Red;
				break;
			case -1:
				color = sf::Color::Yellow;
				break;
			default:
				color = sf::Color::White;
				break;		
		}
		wstring s(1,words_array[i][j]);
		draw_square(window, x_init + i * (Square_Size + SPACE_BETWEEN_SQUARES), y_init + j * (Square_Size + SPACE_BETWEEN_SQUARES), Square_Size, color);
		Text text(window, s , x_init + Square_Size / 2 + i * (Square_Size + SPACE_BETWEEN_SQUARES) - rectangles_array[i][j].getLocalBounds().left, y_init + Square_Size / 2 + j * (Square_Size + SPACE_BETWEEN_SQUARES) - rectangles_array[i][j].getLocalBounds().top, MENU_CHARACTER_SIZE, sf::Color::Black, LATEX_FONT, NON_BOLD, NON_ITALIC, NON_UNDERLINED);	
		text.display(window);
	}
}

void Grid :: print_text ( sf::RenderWindow& window, size_t jmax ) {

	size_t x_init = (X_WINDOW - length) / 2; 
	size_t y_init = (0.95*Y_WINDOW - height - TEXTBAR_HEIGHT) / 2;

	
	for (size_t i = 0; i < nb_squares_x; ++i) {
		for (size_t j = 0; j < jmax; ++j) {

			sf::Color color;
			switch(colors_array[i][j]){

				case 1:
					color = sf::Color::Red;
					break;
				case -1:
					color = sf::Color::Yellow;
					break;
				default:
					color = sf::Color::White;
					break;		
			}
			wstring s(1,words_array[i][j]);
			Text text(window, s , x_init + Square_Size / 2 + i * (Square_Size + SPACE_BETWEEN_SQUARES) - rectangles_array[i][j].getLocalBounds().left, y_init + Square_Size / 2 + j * (Square_Size + SPACE_BETWEEN_SQUARES) - rectangles_array[i][j].getLocalBounds().top, MENU_CHARACTER_SIZE, sf::Color::Black, LATEX_FONT, NON_BOLD, NON_ITALIC, NON_UNDERLINED);	
			text.display(window);
		}	
	}
	const size_t i = 0;
	for (size_t j = 0; j < nb_squares_y; ++j) {

		sf::Color color;
		switch(colors_array[i][j]){

			case 1:
				color = sf::Color::Red;
				break;
			case -1:
				color = sf::Color::Yellow;
				break;
			default:
				color = sf::Color::White;
				break;		
		}
		wstring s(1,words_array[i][j]);
		draw_square(window, x_init + i * (Square_Size + SPACE_BETWEEN_SQUARES), y_init + j * (Square_Size + SPACE_BETWEEN_SQUARES), Square_Size, color);
		Text text(window, s , x_init + Square_Size / 2 + i * (Square_Size + SPACE_BETWEEN_SQUARES) - rectangles_array[i][j].getLocalBounds().left, y_init + Square_Size / 2 + j * (Square_Size + SPACE_BETWEEN_SQUARES) - rectangles_array[i][j].getLocalBounds().top, MENU_CHARACTER_SIZE, sf::Color::Black, LATEX_FONT, NON_BOLD, NON_ITALIC, NON_UNDERLINED);	
		text.display(window);	
	}
}

void Grid :: print_colors(sf::RenderWindow& window, size_t jmax) {

	size_t x_init = (X_WINDOW - length) / 2; 
	size_t y_init = (0.95*Y_WINDOW - height - TEXTBAR_HEIGHT) / 2;

	
	for (size_t i = 0; i < nb_squares_x; ++i) {
		for (size_t j = 0; j < jmax; ++j) {

			sf::Color color;
			switch(colors_array[i][j]){

				case 1:
					color = sf::Color::Red;
					break;
				case -1:
					color = sf::Color::Yellow;
					break;
				default:
					color = sf::Color::White;
					break;		
			}
			draw_square(window, x_init + i * (Square_Size + SPACE_BETWEEN_SQUARES), y_init + j * (Square_Size + SPACE_BETWEEN_SQUARES), Square_Size, color);
		}	
	}

}

void Grid :: display(sf::RenderWindow& window) {

	size_t x_init = (X_WINDOW - length) / 2; 
	size_t y_init = (0.95*Y_WINDOW - height - TEXTBAR_HEIGHT) / 2;
	
	for (size_t i = 0; i < nb_squares_x; ++i) {
		for (size_t j = 0; j < nb_squares_y; ++j){

			draw_square(window, x_init + i * (Square_Size + SPACE_BETWEEN_SQUARES), y_init + j * (Square_Size + SPACE_BETWEEN_SQUARES), Square_Size, sf::Color::Transparent);	
		}
	}
}