#include "pieces/queen.h"

#include <algorithm>

using namespace Pieces;

Queen::Queen(PieceColor color)
    : Piece(color, PieceID::Queen), Rook(color), Bishop(color) {}

std::vector<PossibleMove> Queen::get_possible_moves(const Coordinates &coords) {

  std::vector<PossibleMove> possible_moves = Rook::get_possible_moves(coords);
  std::vector<PossibleMove> bishop_moves = Bishop::get_possible_moves(coords);
  std::move(bishop_moves.begin(), bishop_moves.end(),
            std::back_inserter(possible_moves));
  return possible_moves;
}

std::unique_ptr<Piece> Queen::clone()
{
  return std::make_unique<Queen> (*this);
}
