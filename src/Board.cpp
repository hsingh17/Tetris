#include <algorithm>
#include "Board.h"

Board::Board() : row(20), col(10), game_over(false), board(row, std::vector<char>(col, '*')) {}

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
  // Check if all coordinates can be moved to where the user wants to go
  for (const auto& coord : coords) {
    int new_x = coord.second + dx;
    int new_y = coord.first + dy;
    if (!(new_y >= 0 && new_y <= Row() - 1 && new_x >= 0 && new_x <= Col() - 1 && At(new_y, new_x) == '*'))
      return false;
  }
  return true;
}

bool Board::Bottom(Tetromino& piece) {
  // A piece has fallen as low as it can if:
  // 1. Reaches the bottom of the board
  // 2. Collides with another block
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
  // Used for when tetromino can no longer go lower
  for (const auto& coord : piece.Coords())
    board[coord.first][coord.second] = piece.Piece();
}

void Board::ClearLines() {
  // Clear line works as follows::
  // 1. Start from the top of the board
  // 2. Check if there are no empty positions in the row (indicating a line clear)
  // 3. From this ith position, push down the rows above ith row
  for (int i = 0; i < Row(); i++) {
    if (std::find(board[i].begin(), board[i].end(), '*') == board[i].end())
      PushDown(i);
  }
}

void Board::PushDown(int i) {
  // PushDown works as follows:
  // 1. Set ith row to be empty position
  // 2. Start from ith position and decrementing down
  // 3. Each iteration set current row to be the row above
  // 4. 0th row is set to be empty position
  board[i] = std::vector<char>(Col(), '*');
  for (int j = i; j > 0; j--)
    board[j] = board[j - 1];
  board[0] = std::vector<char>(Col(), '*');
}

void Board::HardDrop(Tetromino& piece) {
  // HardDrop is used for when user presses spacebar
  // Keep moving tetromino down 1 space until it hits the furthest it can
  while (!Bottom(piece))
    piece.Move(0, 1);
}

bool Board::GameOver(Tetromino& piece) {
  // Game is over if piece is the furthest down it can go and it is at the top of the board
  for (const auto& coord : piece.Coords())
    if (coord.first == 0 && Bottom(piece))
      game_over = true;

  return game_over;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (int i = 0; i < Row(); i++) {
    for (int j = 0; j < Col(); j++) {
      if (board[i][j] != '*') {
        sf::RectangleShape sq(sf::Vector2f(40.f, 40.f));
        if (game_over)
          sq.setFillColor(sf::Color(128, 128, 128));
        else
          sq.setFillColor(Config::GetColor(board[i][j]));
        sq.setPosition(j * 40, i * 40);
        target.draw(sq, states);
      }
    }
  }
}




