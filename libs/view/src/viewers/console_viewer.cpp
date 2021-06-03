#include "viewers/console_viewer.h"

#include <iostream>
#include <string>
#include <stdlib.h>

const std::map<Piece::PieceID, std::string> ConsoleViewer::text_map = {
    {Piece::PieceID::Pawn, " P "}, {Piece::PieceID::Bishop, " B "},
    {Piece::PieceID::King, " K "}, {Piece::PieceID::Queen, " Q "},
    {Piece::PieceID::Rook, " R "}, {Piece::PieceID::Knight, " N "},
    {Piece::PieceID::Empty, "   "}};



void ConsoleViewer::display_board(const Board::BoardLayout &board_layout) {

  std::string board_to_print;
  board_to_print="  A  B  C  D  E  F  G  H\n";
  bool temp = true;
  for (int rank = chess_size - 1; rank >= 0; --rank) {
    board_to_print+=std::to_string(rank+1);
    for (int file = 0; file < static_cast<int>(chess_size); ++file) {
      Piece::PieceID piece_id = board_layout.layout.at(file).at(rank).piece_id;
      Piece::PieceColor piece_color = board_layout.layout.at(file).at(rank).color;
      board_to_print += print(temp, piece_color);
      board_to_print += text_map.at(piece_id);
      board_to_print+="\033[0m";
      temp =! temp;
    }
    board_to_print+=std::to_string(rank+1);
    board_to_print+="\n";
    temp=!temp;
  
  }
   board_to_print +="  A  B  C  D  E  F  G  H\n";
   std::cout<<board_to_print;
}

void ConsoleViewer::display_text(const std::string &text
                                 __attribute__((unused))) {}
void ConsoleViewer::clear_board() {
  /* Linux */
  try
  {
    std::system("clear");
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  /* Windows */
  try
  {
    std::system("CLS");
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}

std::string print(bool temp, Piece::PieceColor color)
{
  std::string res;
  if (temp)
  {
    if (color == Piece::PieceColor::White)
    {
      res="\033[43;37m";
    }
    else 
    {
      res="\033[43;30m";
    }
  }
  else 
  {
    if (color == Piece::PieceColor::White)
    {
      res="\033[41;37m";
    }
    else 
    {
      res="\033[41;30m";
    }
  }
  return res;
}
