#pragma once

#include "../i_view.h"

#include <map>

class ConsoleViewer : public IView {
public:
  void display_board(const Board::BoardLayout &board_layout) override;
  void display_text(const std::string &text) override;
  void clear_board() override;

private:
  static const std::map<Piece::PieceID, std::string> text_map;
};

std::string print(bool temp, Piece::PieceColor color);
