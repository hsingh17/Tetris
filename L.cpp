#include "L.h"
L::L() {
  Tetromino::init_coords = {
      std::make_pair(0, 3),
      std::make_pair(1, 5),
      std::make_pair(1, 3),
      std::make_pair(1, 4)
  };
  Tetromino::cur_coords = Tetromino::init_coords;  Tetromino::piece = 'L';
}
