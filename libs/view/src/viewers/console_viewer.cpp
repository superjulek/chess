#include "viewers/console_viewer.h"

#include <iostream>

const std::map<Piece::PieceID, std::string> ConsoleViewer::white_map = {
    {Piece::PieceID::Pawn, "♙"}, {Piece::PieceID::Bishop, "♗"},
    {Piece::PieceID::King, "♔"}, {Piece::PieceID::Queen, "♕"},
    {Piece::PieceID::Rook, "♖"}, {Piece::PieceID::Knight, "♘"},
    {Piece::PieceID::Empty, "□"}};

const std::map<Piece::PieceID, std::string> ConsoleViewer::black_map = {
    {Piece::PieceID::Pawn, "♟"}, {Piece::PieceID::Bishop, "♝"},
    {Piece::PieceID::King, "♚"}, {Piece::PieceID::Queen, "♛"},
    {Piece::PieceID::Rook, "♜"}, {Piece::PieceID::Knight, "♞"},
    {Piece::PieceID::Empty, "■"}};

void ConsoleViewer::display_board(const Board::BoardLayout &board_layout) {
  for (int rank = chess_size - 1; rank >= 0; --rank) {
    for (int file = 0; file < static_cast<int>(chess_size); ++file) {
      std::cout << white_map.at(board_layout.layout.at(file).at(rank).piece_id)
                << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void ConsoleViewer::display_text(const std::string &text
                                 __attribute__((unused))) {}
void ConsoleViewer::clear_board() {}
