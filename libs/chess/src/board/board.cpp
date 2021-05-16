#include "board/board.h"

Board::Board() {

  const int first_rank = 0;
  const int last_rank = 7;
  const int second_rank = 1;
  const int penultimate_rank = 6;
  const int first_empty_rank = 2;
  const int last_empty_rank = 5;
  const int first_file = 0;

  /* Set rank of white Figures */
  /* TODO: FIX!!!*/
  for (size_t file = first_file; file < chess_size; ++file) {
    fields.at(file).at(first_rank) =
        std::make_unique<Pieces::Empty>(Pieces::Empty());
  }

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

  /* Set rank of black Figures */
  /* TODO: FIX!!!*/
  for (size_t file = first_file; file < chess_size; ++file) {
    fields.at(file).at(last_rank) =
        std::make_unique<Pieces::Empty>(Pieces::Empty());
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
