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
  // Put possible pieces into an array
  pieces[0] = (std::unique_ptr<T>(new T()));
  pieces[1] = std::unique_ptr<O>(new O());
  pieces[2] = std::unique_ptr<J>(new J());
  pieces[3] = std::unique_ptr<L>(new L());
  pieces[4] = std::unique_ptr<S>(new S());
  pieces[5] = std::unique_ptr<Z>(new Z());
  pieces[6] = std::unique_ptr<I>(new I());

  // Initialize the generator, seeded with pseudo-random number from random device.
  // NOTE: On my device rd.entropy() returns 0.
  // Meaning random device returns the same number every time for the seed.
  generator = std::mt19937(rd());
  dist = std::uniform_int_distribution<int>(0, 6);

  // Initialize the current piece and ghost piece.
  // NOTE: Ghost piece is the "shadow" of where a block would land
  cur_piece = pieces[dist(generator)].get();
  ghost_piece = Tetromino(*cur_piece, true);
}

void Game::Start() {
  while (window.isOpen() && !board.GameOver(*cur_piece)) {
    // Game loop is as follows:
    // 1. Push block down due to gravity
    // 2. Get user's input
    // 3. Fix the ghost piece accordingly
    // 4. Clear any lines
    // 5. Check if piece has reached the bottom
    // 6. Update window and display
    // 7. Go to game over if game is done
    Gravity();
    GetInput();
    AdjustGhostPiece();
    board.ClearLines();
    CheckBottom();
    UpdateWindow();
  }
  GameOver();
}

bool Game::GetInput() {
  // Generic SFML Code to get input
  // This function returns bool because we need to know
  // if any of the arrow keys are pressed so that lock delay can be reset
  sf::Event event;
  while (window.pollEvent(event) && !board.GameOver(*cur_piece)) {
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
  // We push the tetromino down 1 row if the clock reads anything above 500ms
  if (gravity_clock.getElapsedTime().asMilliseconds() >= 500 && board.Movable(cur_piece->Coords(), 0, 1)) {
    gravity_clock.restart();
    cur_piece->Move(0, 1);
  }
}

void Game::CheckBottom() {
  // This function looks strange because I wanted to create an authentic Tetris experience.
  // Lock delay is simply the time before a piece is finalized onto the board.
  // For this implementation and according to the wiki, lock delay is 500ms
  // Lock delay can be reset if the user moves left, right, or rotates the tetromino.
  // NOTE: Spamming any of the aformentioned keys will cause piece to be stuck at the bottom.
  //       This is not a bug, this is a feature known as "Infinity."
  sf::Clock lock_delay;
  if (board.Bottom(*cur_piece)) {
    do {
      if (GetInput())
        lock_delay.restart();

      // This is needed because a block can shift left or right, causing it to no longer be at the bottom most position
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
  if (!board.GameOver(*cur_piece)) {
    window.draw(ghost_piece);
    window.draw(*cur_piece);
  }
  window.draw(board);
  window.display();
}

void Game::PlacePiece() {
  // We update the internal represenation of our board
  // Then reset the current piece, this gives the illusion of multiple pieces
  // Then we select a new piece different from current piece
  board.UpdateBoard(*cur_piece);
  cur_piece->Reset();
  auto new_piece = pieces[dist(generator)].get();
  while (new_piece->Piece() == cur_piece->Piece())
    new_piece = pieces[dist(generator)].get();
  cur_piece = new_piece;
  ghost_piece = Tetromino(*cur_piece, true);
}

void Game::GameOver() {
  sf::Event event;
  while (window.waitEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
    UpdateWindow();
  }
}

void Game::AdjustGhostPiece() {
  ghost_piece.SetCoords(cur_piece->Coords());
  board.HardDrop(ghost_piece);
}
