#include <random>
#include <cmath>
#include <iostream>
#include "Game.h"
#include "T.h"
#include "O.h"
#include "J.h"
#include "L.h"
#include "S.h"
#include "Z.h"
#include "I.h"


Game::Game() : width(400), height(800), window(sf::VideoMode(width, height), "Tetris"){
  pieces[0] = (std::unique_ptr<T>(new T()));
  pieces[1] = std::unique_ptr<O>(new O());
  pieces[2] = std::unique_ptr<J>(new J());
  pieces[3] = std::unique_ptr<L>(new L());
  pieces[4] = std::unique_ptr<S>(new S());
  pieces[5] = std::unique_ptr<Z>(new Z());
  pieces[6] = std::unique_ptr<I>(new I());
}

void Game::Start() {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> dist(0, 6);
  sf::Clock clock;
  cur_piece = pieces[dist(generator)].get();

  while (window.isOpen()) {
    // Move the block down every 500ms
    if (clock.getElapsedTime().asMilliseconds() >= 500 && board.Movable(cur_piece->Coords(), 0, 1)) {
      clock.restart();
      cur_piece->Move(0, 1);
    }
    GetInput();
    board.ClearLines();

    bool movingleft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool movingright = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if (board.Bottom(*cur_piece) && !movingleft && !movingright) {
      board.UpdateBoard(*cur_piece);
      cur_piece->Reset();
      cur_piece = pieces[dist(generator)].get();
    }

    window.clear();
    window.draw(*cur_piece);
    window.draw(board);
    window.display();
  }
}

void Game::GetInput() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed || board.GameOver(*cur_piece))
      window.close();

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Left && board.Movable(cur_piece->Coords(), -1, 0))
        cur_piece->Move(-1, 0);
      else if (event.key.code == sf::Keyboard::Right && board.Movable(cur_piece->Coords(), 1, 0))
        cur_piece->Move(1, 0);
      else if (event.key.code == sf::Keyboard::Down && board.Movable(cur_piece->Coords(), 0, 1))
        cur_piece->Move(0, 1);
      else if (event.key.code == sf::Keyboard::Up && board.Movable(cur_piece->Rotate(), 0, 0))
        cur_piece->SetCoords(cur_piece->Rotate());
      else if (event.key.code == sf::Keyboard::Space)
        board.HardDrop(*cur_piece);
    }
  }
}

int Game::Width() {
  return width;
}

int Game::Height() {
  return height;
}
