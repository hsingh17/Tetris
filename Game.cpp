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

  generator = std::mt19937(rd());
  dist = std::uniform_int_distribution<int>(0, 6);
}

void Game::Start() {

  cur_piece = pieces[dist(generator)].get();

  while (window.isOpen()) {
    Gravity();
    GetInput();
    board.ClearLines();
    CheckBottom();

    sf::Event event;
    if (board.GameOver(*cur_piece))
      while (window.waitEvent(event))
        if (event.type == sf::Event::Closed)
          window.close();


  }
}

bool Game::GetInput() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
      board.HardDrop(*cur_piece);
      PlacePiece();
      return false;
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Left && board.Movable(cur_piece->Coords(), -1, 0))
        cur_piece->Move(-1, 0);
      else if (event.key.code == sf::Keyboard::Right && board.Movable(cur_piece->Coords(), 1, 0))
        cur_piece->Move(1, 0);
      else if (event.key.code == sf::Keyboard::Down && board.Movable(cur_piece->Coords(), 0, 1))
        cur_piece->Move(0, 1);
      else if (event.key.code == sf::Keyboard::Up && board.Movable(cur_piece->Rotate(), 0, 0))
        cur_piece->SetCoords(cur_piece->Rotate());
      return true;
    }
  }
  UpdateWindow();
  return false;
}

void Game::Gravity() {
  if (gravity_clock.getElapsedTime().asMilliseconds() >= 500 && board.Movable(cur_piece->Coords(), 0, 1)) {
    gravity_clock.restart();
    cur_piece->Move(0, 1);
  }
  UpdateWindow();
}

void Game::CheckBottom() {
  sf::Clock lock_delay;
  if (board.Bottom(*cur_piece)) {
    do {
      if (GetInput())
        lock_delay.restart();
      if (!board.Bottom(*cur_piece))
        return;
    } while (lock_delay.getElapsedTime().asMilliseconds() <= 500);
    PlacePiece();
  }
}

int Game::Width() {
  return width;
}

int Game::Height() {
  return height;
}
void Game::UpdateWindow() {
  window.clear();
  window.draw(*cur_piece);
  window.draw(board);
  window.display();
}

void Game::PlacePiece() {
  board.UpdateBoard(*cur_piece);
  cur_piece->Reset();
  auto new_piece = pieces[dist(generator)].get();
  while (new_piece == cur_piece)
    new_piece = pieces[dist(generator)].get();
  cur_piece = new_piece;
}
