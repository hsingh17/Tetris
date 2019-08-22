#include "S.h"
S::S() {
  Tetromino::init_coords = {
      std::make_pair(0, 4),
      std::make_pair(0, 5),
      std::make_pair(1, 3),
      std::make_pair(1, 4)
  };
  Tetromino::cur_coords = Tetromino::init_coords;
  Tetromino::piece = 'S';
}
