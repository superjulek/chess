#include "game.h"

Game::Game(std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black)
    : current_depth(0), preview(false), board(std::make_unique<Board>()),
      player_white(std::move(white)), player_black(std::move(black)) {}

Board::BoardLayout Game::get_board_layout() { return board->get_layout(); }

void Game::enter_preview() {
  if (!preview) {
    preview = true;
  } else {
    throw std::runtime_error("Preview mode already entered");
  }
}

void Game::leave_preview() {
  if (preview) {
    step_forward(current_depth);
    preview = false;
  } else {
    throw std::runtime_error("Already not in preview mode");
  }
}

void Game::step_back(size_t steps) {
  size_t total_depth = get_max_depth();

  if (current_depth + steps <= total_depth) {
    for (size_t step = 0; step < steps; ++step) {
      board->apply_move(past_moves.at(total_depth - (current_depth + step + 1)),
                        false);
    }
    current_depth += steps;
  } else {
    throw std::runtime_error("Stepping back too far");
  }
}

void Game::step_forward(size_t steps) {
  size_t total_depth = get_max_depth();
  if (current_depth >= steps) {
    for (size_t step = 0; step < steps; ++step) {
      board->apply_move(past_moves.at(total_depth - current_depth + step),
                        true);
    }
    current_depth -= steps;
  } else {
    throw std::runtime_error("Stepping forward too far");
  }
}

void Game::next_move() {
  if (preview) {
    throw std::runtime_error("Cannot move in preview mode");
  }
  Move move;

  while (true) {
    if (board->get_current_player() == Piece::PieceColor::White) {
      player_white->get_move(*board);
    } else {
      player_black->get_move(*board);
    }
    if (board->is_move_possible(move)) {
      Piece::PieceID captured_piece =
          board->get_layout().layout.at(move.to.file).at(move.to.rank).piece_id;
      board->apply_move(move);
      past_moves.push_back({move, captured_piece});
      break;
    }
  }
}

void Game::make_move(Move move) {
  if (preview) {
    throw std::runtime_error("Cannot move in preview mode");
  }
  if (board->is_move_possible(move)) {
    Piece::PieceID captured_piece =
        board->get_layout().layout.at(move.to.file).at(move.to.rank).piece_id;
    board->apply_move(move);
    past_moves.push_back({move, captured_piece});
  } else {
    throw std::runtime_error("Applied wrong move");
  }
}
