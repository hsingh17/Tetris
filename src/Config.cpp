#include "Config.h"
std::map<char, sf::Color> Config::piece_color;
std::map<char, sf::Color> Config::ghost_piece_color;

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

const sf::Color Config::GetGhostColor(char piece) {
  ghost_piece_color.insert(std::pair<char, sf::Color>('I', sf::Color(224, 255, 255)));
  ghost_piece_color.insert(std::pair<char, sf::Color>('J', sf::Color(173, 216, 230)));
  ghost_piece_color.insert(std::pair<char, sf::Color>('O', sf::Color(240, 230, 140)));
  ghost_piece_color.insert(std::pair<char, sf::Color>('S', sf::Color(144, 238, 144)));
  ghost_piece_color.insert(std::pair<char, sf::Color>('T', sf::Color(255, 128, 255)));
  ghost_piece_color.insert(std::pair<char, sf::Color>('Z', sf::Color(250, 128, 114)));
  ghost_piece_color.insert(std::pair<char, sf::Color>('L', sf::Color(244, 164, 96)));
  return ghost_piece_color[piece];
}
