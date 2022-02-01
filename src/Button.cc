#include <iostream>
#include "Button.hh"
using namespace std; 

#define SPACE_WITH_BORDER 3
#define TEXT_WIDTH 200
#define CHARACTER_SIZE 17
#define SPACE_BETWEEN_BUTTON_AND_TEXT 17
#define WHITE 255
#define BLACK 0
#define BORDER_THICKNESS 2

using namespace std;

Button :: Button (sf::RenderWindow& window, const size_t x, const size_t y, const size_t size, const string text) {
  
	x_button = x;
	y_button = y;
	radius_button = size;
	is_clicked = false;
	button_text = text;	
}

void Button :: draw_circle(sf::RenderWindow& window, int radius, int x, int y, int color) const{

	sf::CircleShape button(radius);
    button.setPosition(x - radius ,y - radius);
    button.setFillColor(sf::Color(color,color,color));
    button.setOutlineThickness(BORDER_THICKNESS); 
    button.setOutlineColor(sf::Color(BLACK, BLACK, BLACK));
    window.draw(button);
}

void Button :: set_button_text(sf::RenderWindow& window, string text, int x, int y) {

	sf::Font font;
	if (! font.loadFromFile("../fonts/cmunss.ttf") ){
        cout << "Error ! Cannot find cmunss.ttf"<<endl;
    }

	sf::Text Text(text,font,TEXT_WIDTH);
    Text.setCharacterSize(CHARACTER_SIZE);
    Text.setFillColor(sf::Color(BLACK, BLACK, BLACK));
    Text.setString(text);
    Text.setStyle(sf::Text::Italic);
    Text.setPosition(x - Text.getLocalBounds().width/2,y);
    window.draw(Text);	
}

void Button :: display (sf::RenderWindow& window) {

	draw_circle(window, radius_button, x_button, y_button, WHITE);
	set_button_text(window, button_text, x_button, y_button + SPACE_BETWEEN_BUTTON_AND_TEXT);

	if(is_clicked) {
		draw_circle(window, radius_button - SPACE_WITH_BORDER, x_button, y_button, BLACK);
	}
} 

void Button :: check_events(sf::RenderWindow& window, size_t x_click, size_t y_click){

	if ( (x_click >= x_button - radius_button) && (x_click <= x_button + radius_button) ) {
		if ( (y_click >= y_button - radius_button) && (y_click <= y_button + radius_button) ) {

			if( !is_clicked ){
				is_clicked = true;
			}
			else{	
				is_clicked = false;
			}
		}       
    }
}