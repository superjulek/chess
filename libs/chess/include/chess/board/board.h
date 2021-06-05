#pragma once

#include <array>
#include <memory>
#include <vector>

#include "../pieces/bishop.h"
#include "../pieces/empty.h"
#include "../pieces/king.h"
#include "../pieces/knight.h"
#include "../pieces/pawn.h"
#include "../pieces/piece.h"
#include "../pieces/piece_factory.h"
#include "../pieces/queen.h"
#include "../pieces/rook.h"

class Board {
 public:
  Board();
  Board(const Board &other);
  /**
   * Notation is:
   * p xycf xycf ...
   * where:
   * p - current player [w, b]
   * xy - piece coordinates (e.g. a1)
   * c - piece color [w, b]
   * f - piece type [K, Q, R, B, N, P]
   */
  Board(const std::string &notation);
  struct BoardLayout {
    struct TileData {
      Piece::PieceID piece_id;
      Piece::PieceColor color;
    };
    /* .at(file).at(rank) */
    std::array<std::array<TileData, chess_size>, chess_size> layout;
    friend bool operator==(const Board::BoardLayout &bl1, const Board::BoardLayout &bl2);
  };
  BoardLayout get_layout();
  // For current player
  std::vector<PossibleMove> get_possible_moves() const;
  bool is_move_possible(const Move &move);
  /**
   * Apply history move
   * @param current   true for testing current player
   * */
  bool is_check(bool current);
  bool is_pat();
  bool is_checkmate();
  /**
   * Apply history move
   * @param forward   true for forward in history
   * */
  void apply_move(const StoredMove &move, bool forward);
  /* Move should be checked if is possible beforehand */
  void apply_move(const Move &move);

 private:
  /* .at(file).at(rank) */
  std::array<std::array<std::unique_ptr<Piece>, chess_size>, chess_size> fields;
  Piece::PieceColor current_player;
  bool is_constrain_ok(const PossibleMove::Constrain &constrain) const;

 public:
  inline Piece::PieceColor get_current_player() { return current_player; }
};

std::string move_to_str(Move mv);

Move move_from_string(std::string mv_string);
