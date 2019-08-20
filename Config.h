#ifndef TETRIS__CONFIG_H_
#define TETRIS__CONFIG_H_
#include <map>
#include <SFML/Graphics.hpp>

class Config {
 public:
  static const sf::Color GetColor(char piece);
 private:
  static std::map<char, sf::Color> piece_color;
};
#endif //TETRIS__CONFIG_H_
