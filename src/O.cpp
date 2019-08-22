#include "O.h"
O::O() {
  Tetromino::init_coords = {
      std::make_pair(0, 4),
      std::make_pair(0, 5),
      std::make_pair(1, 4),
      std::make_pair(1, 5)
  };
  Tetromino::cur_coords = Tetromino::init_coords;
  Tetromino::piece = 'O';
}

const std::vector<std::pair<int, int>> O::Rotate() {
  // No need to rotate a square
  return Tetromino::cur_coords;
}