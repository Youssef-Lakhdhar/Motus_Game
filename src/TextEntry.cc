#include <iostream>
#include "TextEntry.hh"
#include <codecvt>
#include <string>

#define SIZE 200
#define HEIGHT 30

using namespace std; 

TextEntry :: TextEntry (sf::RenderWindow& window,const size_t x, const size_t y) {

	if (!_font.loadFromFile("../fonts/cmunss.ttf")) {
        cout<<"Font ERROR. Don't find ccmuns.ttf"<<endl;
    }
    
    string str = "";
    _playerInput = string_to_wstring(str);
    _entrysize = 0;
    _xsize = x - SIZE/2;
    _ysize = y - HEIGHT/2;
    _final = string_to_wstring(str);
}

TextEntry :: ~TextEntry() {} 

void TextEntry :: init_rectangle(sf::RenderWindow& window,const size_t width, const size_t height, const size_t x, const size_t y)const{

	sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x,y);

    rectangle.setFillColor(sf::Color(255,255,255)); //Fill with white
    rectangle.setOutlineThickness(2); //Border of two pixels ...
    rectangle.setOutlineColor(sf::Color(0, 0, 0)); // ... in black
    window.draw(rectangle);

}  

void TextEntry :: display_playertext(sf::RenderWindow& window,const wstring tmp,const size_t pos_x,const size_t pos_y){

	sf::Text playerText(tmp,_font,SIZE);
    playerText.setCharacterSize(24);
    playerText.setPosition(pos_x,pos_y);
    playerText.setFillColor(sf::Color(0, 0, 0));
    playerText.setString(tmp);
    set_entrysize(playerText.getLocalBounds().width);
    window.draw(playerText);
}

void TextEntry :: check_events(sf::RenderWindow& window,sf::Event& event){
	
    wstring Tmp = get_playerInput();
    string tmp = wstring_to_string(Tmp);
	std::size_t cpt = 0;

	if ((event.key.code == sf::Keyboard::Enter)){
    	if(!cpt){
    		set_finalInput(Tmp);
	    	Tmp.clear();
	    	cpt++;
    	}
    }
	else if (event.type == sf::Event::TextEntered) {

		//Si efface un charactère
        if(event.text.unicode == '\b'){

            if(tmp != ""){

                Tmp.erase(Tmp.size() -1, 1);
            }
        }
        else if (get_entrysize() < SIZE - 20){
        	
        	Tmp += event.text.unicode;
        }
    }

    set_playerInput(Tmp);
    cpt = 0;

}

void TextEntry :: display (sf::RenderWindow& window){

    init_rectangle(window,SIZE,30,get_xsize(),get_ysize());
    display_playertext(window,get_playerInput(),get_xsize()+ SIZE/2 - get_entrysize()/2, get_ysize());

}

std::wstring TextEntry :: string_to_wstring(const std::string& Str) {

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(Str);
}

std::string TextEntry :: wstring_to_string(const std::wstring& Str){

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(Str);
}
