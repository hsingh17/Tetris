#ifndef TETRIS__TETROMINOE_H_
#define TETRIS__TETROMINOE_H_
#include <vector>
#include <SFML/Graphics.hpp>

class Tetromino : public sf::Drawable {
 public:
  Tetromino() = default;
  virtual const std::vector<std::pair<int, int>> Rotate();
  void Move(int dx, int dy);
  char& Piece();
  std::vector<std::pair<int, int>>& Coords();
  void SetCoords(std::vector<std::pair<int,int>> new_coords);
  void Reset();
 protected:
  char piece;
  std::vector<std::pair<int, int>> cur_coords;
  std::vector<std::pair<int, int>> init_coords;

 private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
#endif //TETRIS__TETROMINOE_H_
