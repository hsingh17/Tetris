#ifndef TETRIS__GAME_H_
#define TETRIS__GAME_H_
#include <SFML/Graphics.hpp>
#include <memory>
#include "Tetrominoe.h"
#include "Board.h"

class Game {
 public:
  Game();
  void Start();
  int Width();
  int Height();
 private:
  Tetromino* cur_piece;
  Board board;
  int width, height;
  sf::RenderWindow window;
  std::array<std::unique_ptr<Tetromino>, 7> pieces;

  void GetInput();

};
#endif //TETRIS__GAME_H_
