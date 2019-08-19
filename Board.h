#ifndef TETRIS__BOARD_H_
#define TETRIS__BOARD_H_
#include <vector>
#include "Tetrominoe.h"

class Board : public sf::Drawable{
 public:
  Board();
  const int Row() const;
  const int Col() const;
  const std::vector<std::vector<char>>& GetBoard() const;
  void UpdateBoard(Tetromino& piece);
  bool Movable(const std::vector<std::pair<int, int>>& coords, int dx, int dy);
  bool Bottom(Tetromino& piece);
  void ClearLines();
  void HardDrop(Tetromino& piece);
  bool GameOver(Tetromino& piece);

 private:
  int row, col;
  bool game_over;
  std::vector<std::vector<char>> board;
  char At(int row, int col);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void PushDown(int i);
};
#endif //TETRIS__BOARD_H_
