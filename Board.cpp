#include <algorithm>
#include "Board.h"

Board::Board() : row(20), col(10), board(row, std::vector<char>(col, '*')) {}

const int Board::Row() const {
  return row;
}

const int Board::Col() const {
  return col;
}

const std::vector<std::vector<char>>& Board::GetBoard() const {
  return board;
}

bool Board::Movable(const std::vector<std::pair<int, int>>& coords, int dx, int dy) {
  for (const auto& coord : coords) {
    int new_x = coord.second + dx;
    int new_y = coord.first + dy;
    if (!(new_y >= 0 && new_y <= Row() - 1 && new_x >= 0 && new_x <= Col() - 1 && At(new_y, new_x) == '*'))
      return false;
  }
  return true;
}

bool Board::Bottom(Tetromino& piece) {
  for (const auto& coord : piece.Coords()) {
    // Reached the bottom of the screen
    if (coord.first == Row() - 1)
      return true;

    // Hit another block
    if (At(coord.first + 1, coord.second) != '*')
      return true;
  }
  return false;
}

char Board::At(int row, int col) {
  if (row < 0 || col < 0)
    return '*';
  return board[row][col];
}

void Board::UpdateBoard(Tetromino& piece) {
  for (const auto& coord : piece.Coords())
    board[coord.first][coord.second] = piece.Piece();
}

void Board::ClearLines() {
  for (int i = 0; i < Row(); i++) {
    if (std::find(board[i].begin(), board[i].end(), '*') == board[i].end())
      PushDown(i);
  }
}

void Board::PushDown(int i) {
  board[i] = std::vector<char>(Col(), '*');
  for (int j = i; j > 0; j--)
    board[j] = board[j - 1];
  board[0] = std::vector<char>(Col(), '*');
}

void Board::HardDrop(Tetromino& piece) {
  while (!Bottom(piece))
    piece.Move(0, 1);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  std::map<char, sf::Color> piece_color = {
      {'I', sf::Color::Cyan},
      {'J', sf::Color::Blue},
      {'O', sf::Color::Yellow},
      {'S', sf::Color::Green},
      {'T', sf::Color::Magenta},
      {'Z', sf::Color::Red},
      {'L', sf::Color(255, 140, 0)}
  };

  for (int i = 0; i < Row(); i++) {
    for (int j = 0; j < Col(); j++) {
      if (board[i][j] != '*') {
        sf::RectangleShape sq(sf::Vector2f(40.f, 40.f));
        sq.setFillColor(piece_color[board[i][j]]);
        sq.setPosition(j * 40, i * 40);
        target.draw(sq, states);
      }
    }
  }

}

bool Board::GameOver(Tetromino& piece) {
  for (const auto& coord : piece.Coords())
    if (board[coord.first][coord.second] != '*')
      return true;

  return false;
}




