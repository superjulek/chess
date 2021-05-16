#include "pieces/pawn.h"

using namespace Pieces;

Pawn::Pawn(PieceColor color) : Piece(color, PieceID::Pawn) {}

std::vector<PossibleMove> Pawn::get_possible_moves(const Coordinates &coords) {
  std::vector<PossibleMove> possible_moves;

  const int first_rank = 0;
  const int last_rank = 7;
  const int second_rank = 1;
  const int penultimate_rank = 6;
  const int first_file = 0;
  const int last_file = 7;

  int dir = (piece_color == PieceColor::White) ? 1 : -1;

  /* Single step */
  if (coords.rank != first_rank && coords.rank != last_rank) {
    PossibleMove short_move;

    short_move.from = coords;
    short_move.to = {coords.file, coords.rank + dir};
    short_move.constrains.push_back(
        {PossibleMove::Constrain::ConstrainType::Free,
         {coords.file, coords.rank + dir}});
    possible_moves.push_back(short_move);
  }

  /* Double step */
  if ((coords.rank == second_rank && piece_color == PieceColor::White) ||
      (coords.rank == penultimate_rank && piece_color == PieceColor::Black)) {
    PossibleMove long_move;

    long_move.from = coords;
    long_move.to = {coords.file, coords.rank + dir * 2};
    long_move.constrains.push_back(
        {PossibleMove::Constrain::ConstrainType::Free,
         {coords.file, coords.rank + dir}});
    long_move.constrains.push_back(
        {PossibleMove::Constrain::ConstrainType::Free,
         {coords.file, coords.rank + dir * 2}});
    possible_moves.push_back(long_move);
  }

  /* Captures */
  if (coords.rank != first_rank && coords.rank != last_rank) {
    if (coords.file != last_file) {
      PossibleMove capture_right;

      capture_right.from = coords;
      capture_right.to = {coords.file + 1, coords.rank + dir};
      capture_right.constrains.push_back(
          {PossibleMove::Constrain::ConstrainType::TakenByOpponent,
           capture_right.to});
      possible_moves.push_back(capture_right);
    }

    if (coords.file != first_file) {
      PossibleMove capture_left;

      capture_left.from = coords;
      capture_left.to = {coords.file - 1, coords.rank + dir};
      capture_left.constrains.push_back(
          {PossibleMove::Constrain::ConstrainType::TakenByOpponent,
           capture_left.to});
      possible_moves.push_back(capture_left);
    }
  }
  return possible_moves;
}
