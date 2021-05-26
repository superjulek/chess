#include <chess/board/board.h>
#include <chess/board/coordinates.h>

#include <gtest/gtest.h>

#include <iostream>

// Coordinates

TEST(CoordinatesTests, OutputTest) {
  std::ostringstream local;
  auto *cout_buff = std::cout.rdbuf();
  std::cout.rdbuf(local.rdbuf());

  Coordinates coords{1, 2};
  std::cout << coords;
  ASSERT_STREQ(local.str().c_str(), "b3");

  local.str("");
  local.clear();

  coords = {0, 7}; // NOLINT
  std::cout << coords;
  ASSERT_STREQ(local.str().c_str(), "a8");

  std::cout.rdbuf(cout_buff);
}

TEST(CoordinatesTests, CharConstruct) {
  Coordinates c1('a', '1');
  Coordinates c2('h', '8');
  ASSERT_EQ(c1.file, 0);
  ASSERT_EQ(c1.rank, 0);
  ASSERT_EQ(c2.file, 7);
  ASSERT_EQ(c2.rank, 7);
}

TEST(CoordinatesTests, Comparison) {
  Coordinates c1('a', '1');
  Coordinates c2(0, 0);
  Coordinates c3('a', '2');
  ASSERT_EQ(c1, c2);
  ASSERT_NE(c1, c3);
  ASSERT_NE(c2, c3);
}

// Pawn Piece

TEST(PawnTests, IDColorTest) {
  Pieces::Pawn pawn1(Piece::PieceColor::Black);
  Pieces::Pawn pawn2(Piece::PieceColor::White);
  ASSERT_TRUE(pawn1.get_piece_id() == Piece::PieceID::Pawn);
  ASSERT_TRUE(pawn1.get_piece_color() == Piece::PieceColor::Black);
  ASSERT_TRUE(pawn2.get_piece_id() == Piece::PieceID::Pawn);
  ASSERT_TRUE(pawn2.get_piece_color() == Piece::PieceColor::White);
}

TEST(PawnTests, PossibleMoveTestA2w) {
  Pieces::Pawn pawn(Piece::PieceColor::White);
  auto posible_moves = pawn.get_possible_moves(Coordinates('a', '2'));

  ASSERT_EQ(posible_moves.size(), 3);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('a', '3')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('a', '3'));
    } else if (move.to == Coordinates('a', '4')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('a', '3'));
      ASSERT_TRUE(move.constrains.at(1).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(1).coords == Coordinates('a', '4'));
    } else if (move.to == Coordinates('b', '3')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::TakenByOpponent);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('b', '3'));
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

TEST(PawnTests, PossibleMoveTestH7b) {
  Pieces::Pawn pawn(Piece::PieceColor::Black);
  auto posible_moves = pawn.get_possible_moves(Coordinates('h', '7'));

  ASSERT_EQ(posible_moves.size(), 3);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('h', '6')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('h', '6'));
    } else if (move.to == Coordinates('h', '5')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('h', '6'));
      ASSERT_TRUE(move.constrains.at(1).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(1).coords == Coordinates('h', '5'));
    } else if (move.to == Coordinates('g', '6')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::TakenByOpponent);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('g', '6'));
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

TEST(PawnTests, PossibleMoveTestC2w) {
  Pieces::Pawn pawn(Piece::PieceColor::White);
  auto posible_moves = pawn.get_possible_moves(Coordinates('c', '2'));

  ASSERT_EQ(posible_moves.size(), 4);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('c', '3')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('c', '3'));
    } else if (move.to == Coordinates('c', '4')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('c', '3'));
      ASSERT_TRUE(move.constrains.at(1).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(1).coords == Coordinates('c', '4'));
    } else if (move.to == Coordinates('b', '3')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::TakenByOpponent);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('b', '3'));
    } else if (move.to == Coordinates('d', '3')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::TakenByOpponent);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('d', '3'));
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
  ASSERT_EQ(c4, 1);
}

TEST(PawnTests, PossibleMoveTestD8w) {
  Pieces::Pawn pawn(Piece::PieceColor::White);
  auto posible_moves = pawn.get_possible_moves(Coordinates('d', '8'));

  ASSERT_EQ(posible_moves.size(), 0);
}

TEST(PawnTests, PossibleMoveTestE5b) {
  Pieces::Pawn pawn(Piece::PieceColor::Black);
  auto posible_moves = pawn.get_possible_moves(Coordinates('e', '5'));

  ASSERT_EQ(posible_moves.size(), 3);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('e', '4')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('e', '4'));
    } else if (move.to == Coordinates('f', '4')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::TakenByOpponent);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('f', '4'));
    } else if (move.to == Coordinates('d', '4')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 1);
      ASSERT_TRUE(move.constrains.at(0).type ==
                  PossibleMove::Constrain::ConstrainType::TakenByOpponent);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('d', '4'));
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

// Empty Piece

TEST(EmptyPieceTests, IDTest) {
  Pieces::Empty empty;
  ASSERT_TRUE(empty.get_piece_id() == Piece::PieceID::Empty);
}

// Rook piece

TEST(RookTests, PossibleMoveTestRe4) {
  Pieces::Rook rook(Piece::PieceColor::Black);
  auto posible_moves = rook.get_possible_moves(Coordinates('e', '4'));
  ASSERT_EQ(posible_moves.size(), 14);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('a', '4')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 3);
      ASSERT_TRUE(move.constrains.at(2).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(2).coords == Coordinates('b', '4'));
    } else if (move.to == Coordinates('f', '4')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);

    } else if (move.to == Coordinates('e', '1')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(1).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(1).coords == Coordinates('e', '2'));
    } else if (move.to == Coordinates('e', '8')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 3);
      ASSERT_TRUE(move.constrains.at(2).type ==
                  PossibleMove::Constrain::ConstrainType::Free);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('e', '5'));
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
  ASSERT_EQ(c4, 1);
}

TEST(RookTests, PossibleMoveTestRh8) {
  Pieces::Rook rook(Piece::PieceColor::Black);
  auto posible_moves = rook.get_possible_moves(Coordinates('h', '8'));
  ASSERT_EQ(posible_moves.size(), 14);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('h', '2')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 5);
    } else if (move.to == Coordinates('h', '1')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 6);
      ASSERT_TRUE(move.constrains.at(5).coords == Coordinates('h', '2'));
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('h', '7'));

    } else if (move.to == Coordinates('a', '8')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 6);
      ASSERT_TRUE(move.constrains.at(3).coords == Coordinates('d', '8'));
    } else if (move.to == Coordinates('e', '8')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('g', '8'));
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
  ASSERT_EQ(c4, 1);
}

TEST(RookTests, IDColorTest) {
  Pieces::Rook rook1(Piece::PieceColor::Black);
  Pieces::Rook rook2(Piece::PieceColor::White);
  ASSERT_TRUE(rook1.get_piece_id() == Piece::PieceID::Rook);
  ASSERT_TRUE(rook1.get_piece_color() == Piece::PieceColor::Black);
  ASSERT_TRUE(rook2.get_piece_id() == Piece::PieceID::Rook);
  ASSERT_TRUE(rook2.get_piece_color() == Piece::PieceColor::White);
}

// Bishop piece

TEST(BishopTests, IDColorTest) {
  Pieces::Bishop bishop1(Piece::PieceColor::Black);
  Pieces::Bishop bishop2(Piece::PieceColor::White);
  ASSERT_TRUE(bishop1.get_piece_id() == Piece::PieceID::Bishop);
  ASSERT_TRUE(bishop1.get_piece_color() == Piece::PieceColor::Black);
  ASSERT_TRUE(bishop2.get_piece_id() == Piece::PieceID::Bishop);
  ASSERT_TRUE(bishop2.get_piece_color() == Piece::PieceColor::White);
}

TEST(BishopTests, PossibleMoveTestBb1) {
  Pieces::Bishop rook(Piece::PieceColor::White);
  auto posible_moves = rook.get_possible_moves(Coordinates('b', '1'));
  ASSERT_EQ(posible_moves.size(), 7);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('c', '2')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('a', '2')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);

    } else if (move.to == Coordinates('h', '7')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 5);
      ASSERT_TRUE(move.constrains.at(4).coords == Coordinates('g', '6'));
    } else if (move.to == Coordinates('e', '4')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('c', '2'));
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
  ASSERT_EQ(c4, 1);
}

TEST(BishopTests, PossibleMoveTestBd4) {
  Pieces::Bishop rook(Piece::PieceColor::White);
  auto posible_moves = rook.get_possible_moves(Coordinates('d', '4'));
  ASSERT_EQ(posible_moves.size(), 13);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('a', '1')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('c', '3'));
    } else if (move.to == Coordinates('h', '8')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 3);
      ASSERT_TRUE(move.constrains.at(2).coords == Coordinates('g', '7'));

    } else if (move.to == Coordinates('a', '7')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(1).coords == Coordinates('b', '6'));
    } else if (move.to == Coordinates('g', '1')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 2);
      ASSERT_TRUE(move.constrains.at(0).coords == Coordinates('e', '3'));
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
  ASSERT_EQ(c4, 1);
}

// King piece

TEST(KingTests, IDColorTest) {
  Pieces::King King1(Piece::PieceColor::Black);
  Pieces::King King2(Piece::PieceColor::White);
  ASSERT_TRUE(King1.get_piece_id() == Piece::PieceID::King);
  ASSERT_TRUE(King1.get_piece_color() == Piece::PieceColor::Black);
  ASSERT_TRUE(King2.get_piece_id() == Piece::PieceID::King);
  ASSERT_TRUE(King2.get_piece_color() == Piece::PieceColor::White);
}

TEST(KingTests, PossibleMoveTestKa1) {
  Pieces::King king(Piece::PieceColor::White);
  auto posible_moves = king.get_possible_moves(Coordinates('a', '1'));
  ASSERT_EQ(posible_moves.size(), 3);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('a', '2')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('b', '2')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);

    } else if (move.to == Coordinates('b', '1')) {
      c3++;
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

TEST(KingTests, PossibleMoveTestKh8) {
  Pieces::King king(Piece::PieceColor::White);
  auto posible_moves = king.get_possible_moves(Coordinates('h', '8'));
  ASSERT_EQ(posible_moves.size(), 3);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('h', '7')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('g', '8')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);

    } else if (move.to == Coordinates('g', '7')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

TEST(KingTests, PossibleMoveTestKd5) {
  Pieces::King king(Piece::PieceColor::White);
  auto posible_moves = king.get_possible_moves(Coordinates('d', '5'));
  ASSERT_EQ(posible_moves.size(), 8);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;
  int c5 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('e', '6')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('c', '4')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);

    } else if (move.to == Coordinates('d', '4')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('e', '5')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('c', '5')) {
      c5++;
      ASSERT_EQ(move.constrains.size(), 0);
    }
  }

  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

// Knight piece

TEST(KnightTests, PossibleMoveTestNa1) {
  Pieces::Knight knight(Piece::PieceColor::White);
  auto posible_moves = knight.get_possible_moves(Coordinates('a', '1'));
  ASSERT_EQ(posible_moves.size(), 2);

  int c1 = 0;
  int c2 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('c', '2')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('b', '3')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
}

TEST(KnightTests, PossibleMoveTestNe4) {
  Pieces::Knight knight(Piece::PieceColor::White);
  auto posible_moves = knight.get_possible_moves(Coordinates('e', '4'));
  ASSERT_EQ(posible_moves.size(), 8);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;
  int c5 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('f', '6')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
      ASSERT_TRUE(move.from == Coordinates('e', '4'));
    } else if (move.to == Coordinates('d', '6')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('g', '5')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 0);
      ASSERT_TRUE(move.from == Coordinates('e', '4'));
    } else if (move.to == Coordinates('c', '3')) {
      c4++;
      ASSERT_EQ(move.constrains.size(), 0);
      ASSERT_TRUE(move.from == Coordinates('e', '4'));
    } else if (move.to == Coordinates('d', '2')) {
      c5++;
      ASSERT_EQ(move.constrains.size(), 0);
      ASSERT_TRUE(move.from == Coordinates('e', '4'));
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
  ASSERT_EQ(c4, 1);
  ASSERT_EQ(c5, 1);
}

TEST(KnightTests, PossibleMoveTestNh7) {
  Pieces::Knight knight(Piece::PieceColor::White);
  auto posible_moves = knight.get_possible_moves(Coordinates('h', '7'));
  ASSERT_EQ(posible_moves.size(), 3);

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;

  for (const auto &move : posible_moves) {
    if (move.to == Coordinates('f', '8')) {
      c1++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('f', '6')) {
      c2++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else if (move.to == Coordinates('g', '5')) {
      c3++;
      ASSERT_EQ(move.constrains.size(), 0);
    } else {
      FAIL();
    }
  }
  ASSERT_EQ(c1, 1);
  ASSERT_EQ(c2, 1);
  ASSERT_EQ(c3, 1);
}

// Queen piece

TEST(QueenTests, IDColorTest) {
  Pieces::Queen Queen1(Piece::PieceColor::Black);
  Pieces::Queen Queen2(Piece::PieceColor::White);
  ASSERT_TRUE(Queen1.get_piece_id() == Piece::PieceID::Queen);
  ASSERT_TRUE(Queen1.get_piece_color() == Piece::PieceColor::Black);
  ASSERT_TRUE(Queen2.get_piece_id() == Piece::PieceID::Queen);
  ASSERT_TRUE(Queen2.get_piece_color() == Piece::PieceColor::White);
}

TEST(QueenTests, PossibleMoveTestQb3) {
  Pieces::Queen queen(Piece::PieceColor::White);
  auto posible_moves = queen.get_possible_moves(Coordinates('b', '3'));
  ASSERT_EQ(posible_moves.size(), 23);
}

// Board

TEST(BoardTests, CreateBoard) {
  Board board;
  ASSERT_TRUE(true);
}

TEST(BoardTests, CreateBoardLayout) {
  Board board;
  Board::BoardLayout blayout = board.get_layout();

  ASSERT_TRUE(blayout.layout.at(0).at(0).piece_id == Piece::PieceID::Rook);
  ASSERT_TRUE(blayout.layout.at(1).at(0).piece_id == Piece::PieceID::Knight);
  ASSERT_TRUE(blayout.layout.at(2).at(0).piece_id == Piece::PieceID::Bishop);
  ASSERT_TRUE(blayout.layout.at(3).at(0).piece_id == Piece::PieceID::Queen);
  ASSERT_TRUE(blayout.layout.at(4).at(0).piece_id == Piece::PieceID::King);
  ASSERT_TRUE(blayout.layout.at(5).at(0).piece_id == Piece::PieceID::Bishop);
  ASSERT_TRUE(blayout.layout.at(6).at(0).piece_id == Piece::PieceID::Knight);
  ASSERT_TRUE(blayout.layout.at(7).at(0).piece_id == Piece::PieceID::Rook);

  ASSERT_TRUE(blayout.layout.at(0).at(1).color == Piece::PieceColor::White);
  ASSERT_TRUE(blayout.layout.at(0).at(1).piece_id == Piece::PieceID::Pawn);
  ASSERT_TRUE(blayout.layout.at(7).at(1).color == Piece::PieceColor::White);
  ASSERT_TRUE(blayout.layout.at(7).at(1).piece_id == Piece::PieceID::Pawn);

  ASSERT_TRUE(blayout.layout.at(0).at(2).piece_id == Piece::PieceID::Empty);
  ASSERT_TRUE(blayout.layout.at(7).at(2).piece_id == Piece::PieceID::Empty);
  ASSERT_TRUE(blayout.layout.at(0).at(5).piece_id == Piece::PieceID::Empty);
  ASSERT_TRUE(blayout.layout.at(7).at(5).piece_id == Piece::PieceID::Empty);

  ASSERT_TRUE(blayout.layout.at(0).at(6).color == Piece::PieceColor::Black);
  ASSERT_TRUE(blayout.layout.at(0).at(6).piece_id == Piece::PieceID::Pawn);
  ASSERT_TRUE(blayout.layout.at(7).at(6).color == Piece::PieceColor::Black);
  ASSERT_TRUE(blayout.layout.at(7).at(6).piece_id == Piece::PieceID::Pawn);

  ASSERT_TRUE(blayout.layout.at(0).at(7).piece_id == Piece::PieceID::Rook);
  ASSERT_TRUE(blayout.layout.at(1).at(7).piece_id == Piece::PieceID::Knight);
  ASSERT_TRUE(blayout.layout.at(2).at(7).piece_id == Piece::PieceID::Bishop);
  ASSERT_TRUE(blayout.layout.at(3).at(7).piece_id == Piece::PieceID::Queen);
  ASSERT_TRUE(blayout.layout.at(4).at(7).piece_id == Piece::PieceID::King);
  ASSERT_TRUE(blayout.layout.at(5).at(7).piece_id == Piece::PieceID::Bishop);
  ASSERT_TRUE(blayout.layout.at(6).at(7).piece_id == Piece::PieceID::Knight);
  ASSERT_TRUE(blayout.layout.at(7).at(7).piece_id == Piece::PieceID::Rook);

  ASSERT_TRUE(blayout.layout.at(2).at(0).color == Piece::PieceColor::White);
  ASSERT_TRUE(blayout.layout.at(6).at(0).color == Piece::PieceColor::White);

  ASSERT_TRUE(blayout.layout.at(4).at(7).color == Piece::PieceColor::Black);
  ASSERT_TRUE(blayout.layout.at(0).at(7).color == Piece::PieceColor::Black);
}
