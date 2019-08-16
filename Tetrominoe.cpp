#include <map>
#include "Tetrominoe.h"
const std::vector<std::pair<int, int>> Tetromino::Rotate() {
  std::vector<std::pair<int, int>> rotation_matrix = {
      std::make_pair(0, 1),
      std::make_pair(-1, 0)
  };
  std::vector<std::pair<int, int>> rotated_cords;
  std::pair<int, int> shift_amt = cur_coords.back();

  for (auto coord : cur_coords) {
    // Shift all coords, so that origin is at the center
    coord.first -= shift_amt.first;
    coord.second -= shift_amt.second;

    // Apply rotation
    int new_x = (coord.first * rotation_matrix[0].first + coord.second * rotation_matrix[0].second) + shift_amt.first;
    int new_y = (coord.first * rotation_matrix[1].first + coord.second * rotation_matrix[1].second) + shift_amt.second;

   rotated_cords.emplace_back(new_x, new_y);
  }
  return rotated_cords;
}

void Tetromino::Move(int dx, int dy) {
  for (auto& coord : cur_coords) {
    coord.first += dy;
    coord.second += dx;
  }
}

char& Tetromino::Piece() {
  return piece;
}

std::vector<std::pair<int, int>>& Tetromino::Coords() {
  return cur_coords;
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  std::map<char, sf::Color> piece_color = {
      {'I', sf::Color::Cyan},
      {'J', sf::Color::Blue},
      {'O', sf::Color::Yellow},
      {'S', sf::Color::Green},
      {'T', sf::Color::Magenta},
      {'Z', sf::Color::Red},
      {'L', sf::Color(255, 140, 0)}
  };

  for (const auto& coord : cur_coords) {
    sf::RectangleShape sq(sf::Vector2f(40.f, 40.f));
    sq.setFillColor(piece_color[piece]);
    sq.setPosition(coord.second * 40, coord.first * 40);
    target.draw(sq, states);
  }
}

void Tetromino::SetCoords(std::vector<std::pair<int, int>> new_coords) {
  cur_coords = std::move(new_coords);
}

void Tetromino::Reset() {
  // By setting the piece's coordinates back to its original coords we give illusion of endless pieces
  cur_coords = init_coords;
}

