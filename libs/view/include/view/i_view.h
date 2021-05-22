#pragma once

#include <chess/board/board.h>

#include <string>

class IView {
public:
  virtual void display_board(const Board::BoardLayout &board_layout) = 0;
  virtual void display_text(const std::string &text) = 0;
  virtual void clear_board() = 0;
  virtual ~IView() {}
};
