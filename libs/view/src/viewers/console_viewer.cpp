#include "viewers/console_viewer.h"

#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

const std::map<Piece::PieceID, std::string> ConsoleViewer::text_map = {
    {Piece::PieceID::Pawn, " P "}, {Piece::PieceID::Bishop, " B "},
    {Piece::PieceID::King, " K "}, {Piece::PieceID::Queen, " Q "},
    {Piece::PieceID::Rook, " R "}, {Piece::PieceID::Knight, " N "},
    {Piece::PieceID::Empty, "   "}};

static std::string print(bool first_color, Piece::PieceColor color) {
  std::string res;
  if (first_color) {
    if (color == Piece::PieceColor::White) {
      res = "\033[43;37m";
    } else {
      res = "\033[43;30m";
    }
  } else {
    if (color == Piece::PieceColor::White) {
      res = "\033[41;37m";
    } else {
      res = "\033[41;30m";
    }
  }
  return res;
}

void ConsoleViewer::display_board(const Board::BoardLayout &board_layout) {

  const std::string rank_symbols = "  A  B  C  D  E  F  G  H\n";
  std::string board_to_print;
  board_to_print = rank_symbols;
  bool first_color = true;
  for (int rank = chess_size - 1; rank >= 0; --rank) {
    board_to_print += std::to_string(rank + 1);
    for (int file = 0; file < static_cast<int>(chess_size); ++file) {
      Piece::PieceID piece_id = board_layout.layout.at(file).at(rank).piece_id;
      Piece::PieceColor piece_color =
          board_layout.layout.at(file).at(rank).color;
      board_to_print += print(first_color, piece_color);
      board_to_print += text_map.at(piece_id);
      board_to_print += "\033[0m";
      first_color = !first_color;
    }
    board_to_print += std::to_string(rank + 1);
    board_to_print += "\n";
    first_color = !first_color;
  }
  board_to_print += rank_symbols;
  std::cout << board_to_print;
}

void ConsoleViewer::display_text(const std::string &text
                                 __attribute__((unused))) {
  // TODO
}

void ConsoleViewer::clear_board() {
#ifdef __linux__
  try {
    if (std::system("clear") != 0) {
      throw std::runtime_error("Cleaning screen failed");
    };
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
#elif _WIN32
  try {
    if (std::system("CLS") != 0) {
      throw std::runtime_error("Cleaning screen failed");
    };
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
#endif
}
