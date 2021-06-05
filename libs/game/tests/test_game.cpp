#include <game/game.h>
#include <game/player/ai_player.h>
#include <gtest/gtest.h>

#include <iostream>

// Game

TEST(GameTests, DepthPreviewTest) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  Board::BoardLayout layout0 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 0);
  ASSERT_EQ(game.get_current_depth(), 0);

  game.make_move(Move{{'a', '2'}, {'a', '3'}});
  Board::BoardLayout layout1 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 1);
  ASSERT_EQ(game.get_current_depth(), 0);

  game.make_move(Move{{'b', '7'}, {'b', '5'}});
  Board::BoardLayout layout2 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 0);

  game.enter_preview();
  game.step_back(2);
  Board::BoardLayout layout3 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 2);
  ASSERT_EQ(layout0, layout3);

  game.step_forward(1);
  Board::BoardLayout layout4 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 1);
  ASSERT_EQ(layout1, layout4);

  game.leave_preview();
  Board::BoardLayout layout5 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 0);
  ASSERT_EQ(layout2, layout5);
}

TEST(GameTests, GetStateNormalTest) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>("w a1wK h8bK d2bQ"));

  ASSERT_EQ(game.get_state(), Game::GameState::Normal);
}

TEST(GameTests, GetStatePatTest) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>("w a1wK h8bK b2bR c3bP"));

  ASSERT_EQ(game.get_state(), Game::GameState::Pat);
}
TEST(GameTests, GetStatePatTest1) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>("w a1wK a3wK b6wB"));

  ASSERT_EQ(game.get_state(), Game::GameState::Pat);
}

TEST(GameTests, GetStateCheckTest) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>("w a1wK h8bK b1bR"));

  ASSERT_EQ(game.get_state(), Game::GameState::Check);
}

TEST(GameTests, GetStateCheckmateTest) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>("w a1wK h8bK b2bR c3bP a8bR"));

  ASSERT_EQ(game.get_state(), Game::GameState::Checkmate);
}

TEST(GameTests, PastMoves) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>());
  Move mv = move_from_string("e2e4");
  game.make_move(mv);
  mv = move_from_string("c7c6");
  game.make_move(mv);
  mv = move_from_string("d2d4");
  game.make_move(mv);
  mv = move_from_string("d7d5");
  game.make_move(mv);
  mv = move_from_string("b1c3");
  game.make_move(mv);
  mv = move_from_string("d5e4");
  game.make_move(mv);
  mv = move_from_string("c3e4");
  game.make_move(mv);
  ASSERT_EQ(game.get_past_moves().size(), 7);
}

TEST(GameTests, GameString) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black),
                   std::make_unique<Board>());
  Move mv = move_from_string("e2e4");
  game.make_move(mv);
  mv = move_from_string("c7c6");
  game.make_move(mv);
  mv = move_from_string("d2d4");
  game.make_move(mv);
  mv = move_from_string("d7d5");
  game.make_move(mv);
  mv = move_from_string("b1c3");
  game.make_move(mv);
  mv = move_from_string("d5e4");
  game.make_move(mv);
  mv = move_from_string("c3e4");
  game.make_move(mv);
  ASSERT_EQ(game.game_string(), "e2e4c7c6d2d4d7d5b1c3d5e4c3e4");
}

// AI player

TEST(GameTests, Create_AI) {
  AIPlayer AI(Piece::PieceColor::Black);
  ASSERT_EQ(AI.get_color(), Piece::PieceColor::Black);
}

TEST(GameTests, GetMoveAI) {
  AIPlayer AI(Piece::PieceColor::Black);
  Board b("w a1wK b8bR c6bK");
  Move mv = AI.get_move(b, false);
  ASSERT_EQ(mv.to.file, 0);
  ASSERT_EQ(mv.to.rank, 1);
}
