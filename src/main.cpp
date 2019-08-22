#include "Game.h"
int main() {
  bool retry;
  do {
    Game game;
    retry = game.Start();
  } while (retry);

  return 0;
}