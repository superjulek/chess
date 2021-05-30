#pragma once

#include "../pieces/empty.h"
#include "../pieces/pawn.h"
#include "../pieces/rook.h"
#include "../pieces/bishop.h"
#include "../pieces/knight.h"
#include "../pieces/king.h"
#include "../pieces/queen.h"
#include "../pieces/piece.h"

#include <exception>

// Dirty solution, should be improved
namespace Pieces {
inline std::unique_ptr<Piece> get_piece_by_id(Piece::PieceID id,
                                              Piece::PieceColor color) {
  switch (id) {
  case Piece::PieceID::Pawn:
    return std::make_unique<Pawn>(Pawn(color));
  case Piece::PieceID::Bishop:
    return std::make_unique<Bishop>(Bishop(color));
  case Piece::PieceID::Knight:
    return std::make_unique<Knight>(Knight(color));
  case Piece::PieceID::Queen:
    return std::make_unique<Queen>(Queen(color));
  case Piece::PieceID::Rook:
    return std::make_unique<Rook>(Rook(color));
  case Piece::PieceID::King:
    return std::make_unique<King>(King(color));
  default:
    throw std::runtime_error("Attempt to create unimplemented piece");
  }
}
} // namespace Pieces
