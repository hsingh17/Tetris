#include <iostream>
#include "Game.h"
int main() {
  std::cout << "Hello, World!" << std::endl;
  bool retry;
  do {
    Game game;
    retry = game.Start();
  } while (retry);

  return 0;
}