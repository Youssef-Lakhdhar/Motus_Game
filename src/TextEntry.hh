#pragma once 
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class TextEntry{
 
 public:

  TextEntry(sf::RenderWindow& window, const std::size_t x, const std::size_t y);
  ~TextEntry();
  
  void init_rectangle(sf::RenderWindow& window,const size_t width, const size_t height, const size_t x, const size_t y)const;
  void display_playertext(sf::RenderWindow& window,const std::wstring tmp,const size_t pos_x,const size_t pos_y);
  void check_events(sf::RenderWindow& window,sf::Event& event);
  void display (sf::RenderWindow& window);
  std::string wstring_to_string(const std::wstring& Str);
  std::wstring string_to_wstring(const std::string& Str); 

  /* Getters & Setters */
  std::wstring get_playerInput() const { return _playerInput; }
  void set_playerInput(const std::wstring tmp){ _playerInput = tmp; }

  std::wstring get_finalInput() const { return _final; }
  std::string get_finalInput_to_string() { return wstring_to_string(_final); }
  void set_finalInput(const std::wstring tmp){ _final = tmp; }

  std::size_t get_entrysize() const { return _entrysize; }
  void set_entrysize(const std::size_t tmp){ _entrysize = tmp; }

  std::size_t get_xsize() const { return _xsize; }
  std::size_t get_ysize() const { return _ysize; }

  private :
  sf::Font _font;
  std::wstring _playerInput; //entrée de l'utilisateur
  std::size_t _entrysize; // Taille de l'entrée utilisateur
  std::size_t _xsize; 
  std::size_t _ysize; 
  std::wstring _final; //choix final
};  

