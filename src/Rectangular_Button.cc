#include <iostream>
#include "Rectangular_Button.hh"
using namespace std; 

#define TEXT_WIDTH 200
#define CHARACTER_SIZE 17
#define BORDER_THICKNESS 2

using namespace std;

Rectangular_Button :: Rectangular_Button (sf::RenderWindow& window, const size_t x, const size_t y, const size_t width, const size_t height, const string text, const sf::Color& color) {
  
	x_button = x - width/2;
	y_button = y - height/2;
	width_button = width;
	height_button = height;
	button_text = text;
	Color = color;	
}

void Rectangular_Button :: draw_recangle(sf::RenderWindow& window, size_t x, size_t y, size_t width, size_t height, sf::Color& color) const {

	sf::RectangleShape button;
	button.setSize(sf::Vector2f(width, height));
	button.setOutlineColor(sf::Color::Black);
	button.setFillColor(color);
	button.setOutlineThickness(BORDER_THICKNESS);
	button.setPosition(x, y);
	window.draw(button);
}

void Rectangular_Button :: set_button_text(sf::RenderWindow& window, string text, int x, int y) {

	sf::Font font;
	if (! font.loadFromFile("../fonts/cmunss.ttf") ){
        cout << "Error ! Cannot find cmunss.ttf"<<endl;
    }

	sf::Text Text(text,font,TEXT_WIDTH);
    Text.setCharacterSize(CHARACTER_SIZE);
    Text.setFillColor(sf::Color::Black);
    Text.setString(text);
    Text.setStyle(sf::Text::Italic);
    Text.setPosition(x - Text.getLocalBounds().width/2 , y - Text.getLocalBounds().height);
    window.draw(Text);	
}

void Rectangular_Button :: display (sf::RenderWindow& window) {

	draw_recangle(window, x_button, y_button, width_button, height_button, Color);
	set_button_text(window, button_text, x_button + width_button/2, y_button + height_button/2);
} 

bool Rectangular_Button :: is_clicked(size_t x_click, size_t y_click){

	if ( (x_click >= x_button) && (x_click <= x_button + width_button) ) {
		if ( (y_click >= y_button) && (y_click <= y_button + height_button) ) {
			return true;
		}       
    }
    return false;
}