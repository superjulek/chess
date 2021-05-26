#pragma once

#include "../board/coordinates.h"

#include <vector>

inline unsigned const chess_size = 8;

struct PossibleMove; // Forward declaration to avoid circular dependencies

class Piece {
public:
  enum class PieceColor : bool {
    White = true,  // White going forward
    Black = false, // Black going backward
  };
  enum class PieceID : int {
    Empty,
    King,   // krol
    Queen,  // hetman
    Bishop, // goniec
    Rook,   // wieza
    Knight, // skoczek
    Pawn,   // pion
  };

protected:
  PieceColor piece_color;
  PieceID piece_id;

public:
  inline Piece(PieceColor color, PieceID id)
      : piece_color(color), piece_id(id){};
  virtual std::vector<PossibleMove>
  get_possible_moves(const Coordinates &coords) = 0;
  inline PieceColor get_piece_color() { return piece_color; }
  inline PieceID get_piece_id() { return piece_id; }
  virtual ~Piece(){};
};

#include "../board/move.h" // Make sure we aways have move.h included as well
