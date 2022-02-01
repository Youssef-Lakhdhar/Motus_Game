#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>  // std::invalid_argument
#include <math.h>
#include <cctype>
#include <cstring>
#include <codecvt>

#include "Button.hh"
#include "Image.hh"
#include "Text.hh"
#include "TextEntry.hh"
#include "Rectangular_Button.hh"
#include "Motus.hh"
#include "Grid.hh"

#define X_WINDOW 800
#define Y_WINDOW 750
#define NB_TRIES 10
#define NB_DIFFICULT_WORDS_7_LETTERS 16597
#define NB_DIFFICULT_WORDS_8_LETTERS 21446
#define NB_DIFFICULT_WORDS_9_LETTERS 22509
#define NB_DIFFICULT_WORDS_10_LETTERS 20056
#define NB_EASY_WORDS_7_LETTERS 138
#define NB_EASY_WORDS_8_LETTERS 65
#define NB_EASY_WORDS_9_LETTERS 52
#define NB_EASY_WORDS_10_LETTERS 51
#define SQUARE_SIZE 50
#define BUTTON_SIZE 6
#define BUTTON_WIDTH 130
#define BUTTON_HEIGHT 30
#define MENU_CHARACTER_SIZE 40
#define NB_BUTTONS_LETTERS 4
#define NB_BUTTONS_DIFFICULTY 2
#define DELAY_BETWEEN_SOUNDS 10
#define DELAY 500
#define BOLD true
#define NON_BOLD false
#define ITALIC true
#define NON_ITALIC false
#define UNDERLINED true 
#define NON_UNDERLINED false
#define RED 1
#define YELLOW -1
#define WHITE 0
#define LOGO_PATH "../images/Motus_Logo.jpg"
#define GENERIC_PATH "../sounds/generique.wav"
#define LATEX_FONT "../fonts/cmunss.ttf"
#define LAKESHORE_FONT "../fonts/lakeshore.ttf"

using namespace std;

Motus :: Motus() {

    word = "";
    word_length = 0;
    play_again = false;
    win = false;
    difficulty = false;
    submitted_word = "";
    user_entry = "";
    error_message = L" ";
}


int Motus :: init_menu(sf::RenderWindow &window){

    sf::SoundBuffer Buffer;
    Buffer.loadFromFile(GENERIC_PATH);
    sf::Sound generic;
    generic.setBuffer(Buffer);
    generic.setLoop(true);
    generic.play();

    Button Bouton7l(window, X_WINDOW/5, 0.55*Y_WINDOW, BUTTON_SIZE, "7 lettres");
    Button Bouton8l(window, 2*X_WINDOW/5, 0.55*Y_WINDOW, BUTTON_SIZE, "8 lettres");
    Button Bouton9l(window, 3*X_WINDOW/5, 0.55*Y_WINDOW, BUTTON_SIZE, "9 lettres");
    Button Bouton10l(window, 4*X_WINDOW/5, 0.55*Y_WINDOW, BUTTON_SIZE, "10 lettres");
    Button Button_Letters[4] = { Bouton7l, Bouton8l, Bouton9l, Bouton10l };

    Image logo(window, X_WINDOW/2 , Y_WINDOW/8 , X_WINDOW, Y_WINDOW/4, LOGO_PATH);
    Text text(window, (wstring)(L"Sélectionnez vos paramètres") , X_WINDOW/2 - 15, ( Bouton7l.get_y() + logo.get_height() )/2 - 2*BUTTON_SIZE, MENU_CHARACTER_SIZE, sf::Color(0,0,139), LATEX_FONT, BOLD, NON_ITALIC, NON_UNDERLINED);
    Text signature(window, (wstring)(L"Clément Roger ®") , 0.94*X_WINDOW, 0.97*Y_WINDOW , 10, sf::Color::Black, LATEX_FONT, NON_BOLD, ITALIC, NON_UNDERLINED); 

    Button BoutonFacile(window, X_WINDOW/3, 0.7*Y_WINDOW, BUTTON_SIZE, "Facile");
    Button BoutonDifficile(window, 2*X_WINDOW/3, 0.7*Y_WINDOW, BUTTON_SIZE, "Difficile");
    Button Button_Difficulty[2] = {BoutonFacile, BoutonDifficile};

    Rectangular_Button BoutonStart(window, X_WINDOW/2, 0.9*Y_WINDOW, BUTTON_WIDTH, BUTTON_HEIGHT, "Start", sf::Color(220,220,220));

	while(window.isOpen()){

		sf::Event event;
        while( window.pollEvent(event) ){

        	if(event.type == sf::Event::Closed){

                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {

                float x = sf::Mouse::getPosition(window).x;
                float y = sf::Mouse::getPosition(window).y;

                if(y > 0.4*Y_WINDOW){

                    if(y < 0.6*Y_WINDOW){

                        for (int i = 0; i < NB_BUTTONS_LETTERS; ++i) {
                            Button_Letters[i].set_is_clicked(false);
                        }
                        for (int i = 0; i < NB_BUTTONS_LETTERS; ++i) {
                            Button_Letters[i].check_events(window, x, y);
                            if( Button_Letters[i].get_is_clicked() ){
                                word_length = i + 7;
                            }
                        }
                    }    
                    else if(y < 0.8*Y_WINDOW){

                        for (int i = 0; i < NB_BUTTONS_DIFFICULTY; ++i){
                            Button_Difficulty[i].set_is_clicked(false);
                        }
                        for (int i = 0; i < NB_BUTTONS_DIFFICULTY; ++i) {
                            Button_Difficulty[i].check_events(window, x, y);
                        }
                        difficulty = Button_Difficulty[0].get_is_clicked();
                    }
                    else{

                        if(BoutonStart.is_clicked(x,y)){
                            for (int i = 0; i < NB_BUTTONS_LETTERS; ++i) {
                                if( Button_Letters[i].get_is_clicked() ) {
                                    for (int i = 0; i < NB_BUTTONS_DIFFICULTY; ++i) {
                                        if( Button_Difficulty[i].get_is_clicked() ) {
                                            return 0;
                                        }    
                                    }
                                }
                            }
                        }
                    } 
                }                       
            }
        }

    	window.clear(sf::Color::White);
        for (int i = 0; i < NB_BUTTONS_LETTERS; ++i){
            Button_Letters[i].display(window);
        }
        for (int i = 0; i < NB_BUTTONS_DIFFICULTY; ++i){
            Button_Difficulty[i].display(window);
        }
        logo.display(window);
        BoutonStart.display(window);
        text.display(window);
        signature.display(window);
   		window.display();    
	}

	return 0;
}

std::wstring Motus :: string_to_wstring(const std::string& Str) {

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(Str);
}

bool Motus :: check_word(string str){

    if(str.length() != word_length){
        error_message = L"Veuillez entrer un mot de " + string_to_wstring( to_string(word_length) ) + L" lettres";
        return false;
    }
    if(str[0] != word[0]){
        error_message = L"Veuillez entrer un mot commençant par " + wchar_t( word[0] );
        return false;
    }
    for (long unsigned int i = 0; i < word_length; ++i) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            continue;
        }
        error_message = L"Veuillez entrer un mot ne contenant que des lettres entre A et Z";
        return false;
    }
    error_message = L" ";
    return true;
}

void Motus :: init_word() {

    string file_path; 
    int nb_words;

    if(difficulty) {
    	switch( word_length ){

    		case 7:
    			file_path = "../files/mots_faciles_7_lettres.txt";
    			nb_words = NB_EASY_WORDS_7_LETTERS;
    			break;
    		case 8:
    			file_path = "../files/mots_faciles_8_lettres.txt";
    			nb_words = NB_EASY_WORDS_8_LETTERS;
    			break;
    		case 9:
    			file_path = "../files/mots_faciles_9_lettres.txt";
    			nb_words = NB_EASY_WORDS_9_LETTERS;
    			break;
    		case 10:
    			file_path = "../files/mots_faciles_10_lettres.txt";
    			nb_words = NB_EASY_WORDS_10_LETTERS;
    			break;
    		default:
    			cout << "A problem occured ... Word length is incorrect" << endl;
    			break;
    	}        
    }
    else{
        switch( word_length ){

    		case 7:
    			file_path = "../files/mots_difficiles_7_lettres.txt";
    			nb_words = NB_DIFFICULT_WORDS_7_LETTERS;
    			break;
    		case 8:
    			file_path = "../files/mots_difficiles_8_lettres.txt";
    			nb_words = NB_DIFFICULT_WORDS_8_LETTERS;
    			break;
    		case 9:
    			file_path = "../files/mots_difficiles_9_lettres.txt";
    			nb_words = NB_DIFFICULT_WORDS_9_LETTERS;
    			break;
    		case 10:
    			file_path = "../files/mots_difficiles_10_lettres.txt";
    			nb_words = NB_DIFFICULT_WORDS_10_LETTERS;
    			break;
    		default:
    			cout << "A problem occured ... Word length is incorrect" << endl;
    			break;
    	}
    }

    int nb_line = generate_random_number(1,nb_words);
    //cout << "Mot n°" << nb_line << " du fichier " << file_path << endl;
    int i = 0;
    bool flag = false;
 
    ifstream file(file_path);
 
    if( file ) {
        std::string line;
 
        while( std::getline( file, line ) && !flag ) {
            
            if( i == nb_line && line.length() == word_length ) {
                flag = true;
                word = line;
            }
            else if (i > nb_line) {
                nb_line = generate_random_number(1,nb_words);
                file.clear();
                file.seekg(0,std::ios::beg);
                i = -1;
            }
            i++;
        }

        //cout << "Mot à deviner : " << word << endl;
    }
}

int Motus :: generate_random_number(const int min, const int max) const {

    std::srand(std::time(nullptr)); //Initialise le générateur de nombres aléatoires

    return rand()%(max - min + 1) + min;
}

void Motus :: fill_colors_array(Grid &grille) {

	for (long unsigned int i = 0; i < word_length; i++ ){
		
		if( submitted_word[i] == word[i] ){
            for (int j = word_counter; j < NB_TRIES; ++j){

                grille.set_color_case(i, j, RED);
                grille.set_word_case(i, j, (wchar_t)word[i]);
            }
		}	
		else if( is_letter_yellow(i , grille) ) {
			
			grille.set_color_case(i,word_counter, YELLOW);
		}
		else{
			
			grille.set_color_case(i,word_counter, WHITE);
		}	
	}

    if(win){
        if(word_counter < NB_TRIES - 1){
            for (long unsigned int i = 1; i < word_length; ++i) {
                for (long unsigned int j = word_counter + 1; j < NB_TRIES; ++j) {

                    grille.set_color_case(i, j, WHITE);
                    grille.set_word_case(i, j, (wchar_t)' ');
                }                
            }
        }    
    }		
}

bool Motus :: is_letter_yellow (int i, Grid& grille) {

	if( word.find(submitted_word[i],0) != string::npos ){
		for (long unsigned int x = 0; x < word_length; ++x) {
			if(word[x] == submitted_word[i] && grille.get_color_case(x,word_counter) != RED) {
				return true;
			}
		}
	}
	return false;
}

void Motus :: check_victory() {

	if( submitted_word == word ) {

		win = true;	
        
        string sound_path = "../sounds/son_fin.wav";
        sf::SoundBuffer Buffer;
        Buffer.loadFromFile(sound_path);
        sf::Sound sound;
        sound.setBuffer(Buffer);
        sound.play();
        while( sound.getStatus() != sf::SoundSource::Stopped ){
        }
	}
}

void Motus :: transition(sf::RenderWindow& window) {

	wstring victory_string;
	if(win){
		victory_string = L"Félicitations, vous avez trouvé le mot !";
	}
	else{
		victory_string = L"Vous avez perdu. Le mot était " + string_to_wstring( word );
	}

	wstring replay_string = L"Souhaitez vous rejouer ?";

	Text text1(window, victory_string , X_WINDOW/2 - 20, 0.4*Y_WINDOW, MENU_CHARACTER_SIZE, sf::Color(0,0,139), LATEX_FONT, BOLD, NON_ITALIC, NON_UNDERLINED);
	Text text2(window, replay_string , X_WINDOW/2 - 20, 0.5*Y_WINDOW, MENU_CHARACTER_SIZE, sf::Color(0,0,139), LATEX_FONT, BOLD, NON_ITALIC, NON_UNDERLINED);
	Rectangular_Button BoutonRejouer(window, X_WINDOW/3, 0.8*Y_WINDOW, BUTTON_WIDTH, BUTTON_HEIGHT, "Recommencer", sf::Color(220,220,220));
	Rectangular_Button BoutonTerminer(window, 2*X_WINDOW/3, 0.8*Y_WINDOW, BUTTON_WIDTH, BUTTON_HEIGHT, "Terminer", sf::Color(220,220,220));

	bool flag = false;
		
	while(window.isOpen() && !flag) {

		sf::Event event;
  		while (window.pollEvent(event)) {

           	if (event.type == sf::Event::Closed){
           	   window.close();                
           	}
           	else if(event.type == sf::Event::MouseButtonPressed) {

           		float x = sf::Mouse::getPosition(window).x;
                float y = sf::Mouse::getPosition(window).y;

                if( BoutonTerminer.is_clicked(x,y) ){
                	window.close();
                }
                else if ( BoutonRejouer.is_clicked(x,y) ){
                	flag = true;
                	play_again = true;
                } 
            } 
       	}

		window.clear(sf::Color::White);
		text1.display(window);
		text2.display(window);
		BoutonRejouer.display(window);
		BoutonTerminer.display(window);
	    window.display();
	}    
}

void Motus :: run() {

    sf::RenderWindow window(sf::VideoMode(X_WINDOW, Y_WINDOW), "Motus");
    jeu:
    init_menu(window);
    init_word();
    word_counter = 0;

    TextEntry TextBar(window, X_WINDOW/2 , 0.90*Y_WINDOW );
    Grid grille(word_length, NB_TRIES, SQUARE_SIZE);
    for (int i = 0; i < 10; ++i) {
        grille.set_color_case( 0 , i , RED );
        grille.set_word_case(0 , i , (wchar_t)word[0]);
    }
    std::string entry = "";

    while (window.isOpen() && !win && word_counter < NB_TRIES) {

        sf::Event event;
        while (window.pollEvent(event)) {

            TextBar.check_events(window,event);
            if (event.type == sf::Event::Closed){
                window.close();                
            } 
        }
        entry = get_user_entry(); 

        if ( TextBar.get_finalInput_to_string() != "" && TextBar.get_finalInput_to_string() != "\r" && entry != TextBar.get_finalInput_to_string() ){
                
            submitted_word = TextBar.get_finalInput_to_string();
            for(long unsigned int i = 0; i < submitted_word.length(); i++){
                submitted_word[i] = toupper(submitted_word[i]);
            }
            user_entry = TextBar.get_finalInput_to_string();
            if( check_word(submitted_word) ){
         		fill_colors_array(grille);
                grille.submit_new_word( string_to_wstring( submitted_word ) );
                sf::sleep(sf::milliseconds(DELAY));
                for (long unsigned int i = 0; i < word_length; ++i) {
                    window.clear(sf::Color::White);
                    TextBar.display(window);
                    grille.display(window);
                    grille.print_colors(window,word_counter);
                    grille.print_text(window, word_counter + 1);
                    grille.write_character(window,i,word_counter);
                    grille.print_text(window, word_counter + 1);
                    sf::sleep(sf::milliseconds(DELAY_BETWEEN_SOUNDS));
                    window.display();
                    grille.play_sound(i,word_counter);
                }
                word_counter++;
            }
            check_victory();
        }
        Text text(window, error_message , X_WINDOW/2, 0.95*Y_WINDOW , 20, sf::Color(0,0,139), LATEX_FONT, BOLD, NON_ITALIC, NON_UNDERLINED);

        window.clear(sf::Color::White);
        TextBar.display(window);
        grille.display(window);
        grille.print_colors(window,word_counter);
        grille.print_text(window, word_counter);
        if(!win && word_counter != NB_TRIES){
            grille.write_next_line(window, word_counter);    
        }
        text.display(window);
        window.display();
    }

    if(!win){
        string sound_path = "../sounds/son_defaite.wav";
        sf::SoundBuffer Buffer;
        Buffer.loadFromFile(sound_path);
        sf::Sound sound;
        sound.setBuffer(Buffer);
        sound.play();
        while( sound.getStatus() != sf::SoundSource::Stopped ){
        }
    }
    sf::sleep(sf::milliseconds(DELAY));
    transition(window);

    if(play_again) {

	    word = "";
	    word_length = 0;
	    play_again = false;
	    win = false;
	    difficulty = false;
	    submitted_word = "";
	    user_entry = "";
    	goto jeu;
    }    
}
