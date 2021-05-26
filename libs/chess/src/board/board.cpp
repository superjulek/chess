#include "board/board.h"

Board::Board() {

  const int first_rank = 0;
  const int last_rank = 7;
  const int second_rank = 1;
  const int penultimate_rank = 6;
  const int first_empty_rank = 2;
  const int last_empty_rank = 5;
  const int first_file = 0;

  /* Rank in chess notation goes for rows, files for vertical columns*/

  /* Set ranks of Figures */

  auto set_figures_rank = [&](size_t rank, Piece::PieceColor color) {
    fields.at(0).at(rank) = std::make_unique<Pieces::Rook>(Pieces::Rook(color));
    fields.at(chess_size - 1).at(rank) =
        std::make_unique<Pieces::Rook>(Pieces::Rook(color));
    fields.at(1).at(rank) =
        std::make_unique<Pieces::Knight>(Pieces::Knight(color));
    fields.at(chess_size - 2).at(rank) =
        std::make_unique<Pieces::Knight>(Pieces::Knight(color));
    fields.at(2).at(rank) =
        std::make_unique<Pieces::Bishop>(Pieces::Bishop(color));
    fields.at(chess_size - 3).at(rank) =
        std::make_unique<Pieces::Bishop>(Pieces::Bishop(color));
    fields.at(3).at(rank) = std::make_unique<Pieces::Queen>(Pieces::Queen(color));
    fields.at(4).at(rank) = std::make_unique<Pieces::King>(Pieces::King(color));
  };

  set_figures_rank(first_rank, Piece::PieceColor::White);
  set_figures_rank(last_rank, Piece::PieceColor::Black);

  /* Set rank of white Pawns */
  for (size_t file = first_file; file < chess_size; ++file) {
    fields.at(file).at(second_rank) =
        std::make_unique<Pieces::Pawn>(Pieces::Pawn(Piece::PieceColor::White));
  }

  /* Set ranks of empty fields */
  for (size_t rank = first_empty_rank; rank <= last_empty_rank; ++rank) {
    for (size_t file = first_file; file < chess_size; ++file) {
      fields.at(file).at(rank) =
          std::make_unique<Pieces::Empty>(Pieces::Empty());
    }
  }

  /* Set rank of black Pawns */
  for (size_t file = first_file; file < chess_size; ++file) {
    fields.at(file).at(penultimate_rank) =
        std::make_unique<Pieces::Pawn>(Pieces::Pawn(Piece::PieceColor::Black));
  }
}

Board::BoardLayout Board::get_layout() {
  Board::BoardLayout ret_layout;
  for (size_t file = 0; file < chess_size; ++file) {
    for (size_t rank = 0; rank < chess_size; ++rank) {
      ret_layout.layout.at(file).at(rank) = {
          fields.at(file).at(rank)->get_piece_id(),
          fields.at(file).at(rank)->get_piece_color()};
    }
  }
  return ret_layout;
}
