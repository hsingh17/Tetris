#ifndef TETRIS__O_H_
#define TETRIS__O_H_
#include "Tetrominoe.h"

class O : public Tetromino {
 public:
  O();
  const std::vector<std::pair<int, int>> Rotate() override;
};
#endif //TETRIS__O_H_
