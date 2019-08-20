#include "Config.h"
std::map<char, sf::Color> Config::piece_color;

const sf::Color Config::GetColor(char piece) {
  piece_color.insert(std::pair<char, sf::Color>('I', sf::Color::Cyan));
  piece_color.insert(std::pair<char, sf::Color>('J', sf::Color::Blue));
  piece_color.insert(std::pair<char, sf::Color>('O', sf::Color::Yellow));
  piece_color.insert(std::pair<char, sf::Color>('S', sf::Color::Green));
  piece_color.insert(std::pair<char, sf::Color>('T', sf::Color::Magenta));
  piece_color.insert(std::pair<char, sf::Color>('Z', sf::Color::Red));
  piece_color.insert(std::pair<char, sf::Color>('L', sf::Color(255, 144, 0)));
  return piece_color[piece];
}
