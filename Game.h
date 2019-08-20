#ifndef TETRIS__GAME_H_
#define TETRIS__GAME_H_
#include <memory>
#include<random>
#include <SFML/Graphics.hpp>
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
  Tetromino ghost_piece;
  Board board;
  int width, height;
  sf::RenderWindow window;
  std::array<std::unique_ptr<Tetromino>, 7> pieces;
  sf::Clock gravity_clock;
  std::random_device rd;
  std::mt19937 generator;
  std::uniform_int_distribution<int> dist;

  bool GetInput();
  void Gravity();
  void CheckBottom();
  void UpdateWindow();
  void PlacePiece();
  void GameOver();
  void AdjustGhostPiece();
};
#endif //TETRIS__GAME_H_
