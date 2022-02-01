#pragma once 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Grid.hh"

class Motus{

	public:

		Motus();
		int init_menu(sf::RenderWindow &window);
		void run();
		bool check_word(std::string word);
		void init_word();
		int generate_random_number(const int min, const int max) const; 
		void fill_colors_array(Grid& grille);
		bool is_letter_yellow (int i, Grid& grille);
		void transition(sf::RenderWindow& window);
		void check_victory();

		std::wstring string_to_wstring(const std::string& Str);
		std::string get_user_entry() { return user_entry; }

	private:	

		std::string word;
		std::string submitted_word;
		std::string user_entry;
		size_t word_length;
		size_t word_counter;
		bool play_again;
		bool win;
		bool difficulty; //True if easy, false if difficult
		std::wstring error_message;
};		