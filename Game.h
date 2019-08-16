#ifndef TETRIS__GAME_H_
#define TETRIS__GAME_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tetrominoe.h"

class Game {
 public:
  Game();
  void Start();
  int Width();
  int Height();
 private:
  int width, height;
  sf::RenderWindow window;
  std::vector<std::unique_ptr<Tetromino>> pieces;

};
#endif //TETRIS__GAME_H_
