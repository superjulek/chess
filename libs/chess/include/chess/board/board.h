#pragma once

#include "../pieces/empty.h"
#include "../pieces/piece.h"
#include "../pieces/pawn.h"

#include <array>
#include <memory>
#include <vector>

class Board {
public:
  Board();
  unsigned static const chess_size = 8;
  struct BoardLayout {
    struct TileData {
      Piece::PieceID piece_id;
      Piece::PieceColor color;
    };
    /* .at(file).at(rank) */
    std::array<std::array<TileData, chess_size>, chess_size> layout;
  };
  BoardLayout get_layout();
  std::vector<Move> get_possible_moves();
  bool is_move_possible(const Move &move);
  bool is_chech();
  /**
   * Apply history move
   * @param forward   true for forward in history
   * */
  void apply_move(const StoredMove &move, bool forward);
  void apply_move(const Move &move);

private:
  /* .at(file).at(rank) */
  std::array<std::array<std::unique_ptr<Piece>, chess_size>, chess_size> fields;
};
