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

// Board

TEST(BoardTests, CreateBoard) {
  Board board;
  ASSERT_TRUE(true);
}

TEST(BoardTests, CreateBoardLayout) {
  Board board;
  Board::BoardLayout blayout = board.get_layout();
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
}
