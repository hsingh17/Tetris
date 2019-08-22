#include "I.h"
I::I() {
  Tetromino::init_coords = {
      std::make_pair(0, 3),
      std::make_pair(0, 5),
      std::make_pair(0, 6),
      std::make_pair(0, 4)
  };
  Tetromino::cur_coords = Tetromino::init_coords;
  Tetromino::piece = 'I';
}
