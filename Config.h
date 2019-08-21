#ifndef TETRIS__CONFIG_H_
#define TETRIS__CONFIG_H_
#include <map>
#include <SFML/Graphics.hpp>

// Config class for colors
class Config {
 public:
  static const sf::Color GetColor(char piece);
  static const sf::Color GetGhostColor(char piece);
 private:
  static std::map<char, sf::Color> piece_color;
  static std::map<char, sf::Color> ghost_piece_color;
};
#endif //TETRIS__CONFIG_H_
