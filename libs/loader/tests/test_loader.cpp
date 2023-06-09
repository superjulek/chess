#include <gtest/gtest.h>
#include <loader/loader.h>

#include <fstream>
#include <iostream>
// Loader

TEST(LoaderTests, TestStartingGame) {
  Loader my_loader;
  Board start_board;
  my_loader.create_new_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  ASSERT_EQ(my_loader.get_game_ptr()->get_board_layout(),
            start_board.get_layout());
  ASSERT_EQ(my_loader.get_game_ptr()->get_current_player_color(),
            Piece::PieceColor::White);
  ASSERT_EQ(my_loader.get_game_ptr()->get_state(), Game::GameState::Normal);
}

TEST(LoaderTests, DropGame) {
  Loader my_loader;
  my_loader.create_new_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  my_loader.drop_game();
  ASSERT_FALSE(my_loader.is_game_loaded());
}
TEST(LoaderTests, TestSavingGame) {
  Loader my_loader;
  Board start_board;
  my_loader.create_new_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  Game *game = my_loader.get_game_ptr();
  Move mv = move_from_string("e2e4");
  game->make_move(mv);
  mv = move_from_string("c7c6");
  game->make_move(mv);
  mv = move_from_string("d2d4");
  game->make_move(mv);
  mv = move_from_string("d7d5");
  game->make_move(mv);
  mv = move_from_string("b1c3");
  game->make_move(mv);
  mv = move_from_string("d5e4");
  game->make_move(mv);
  mv = move_from_string("c3e4");
  game->make_move(mv);
  my_loader.store_game_to_file("./plik.txt");
  bool file_exists = false;
  std::ifstream isfile;
  isfile.open("./plik.txt");
  if (isfile) {
    file_exists = true;
    isfile.close();
  }
  ASSERT_TRUE(file_exists);
}

TEST(LoaderTests, TestLoadingGame) {
  Loader my_loader;
  Board start_board;
  my_loader.load_game_from_file(
      "./plik.txt", std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  std::ifstream isfile;
  isfile.open("./plik.txt");
  isfile.close();
  if (isfile) {
    remove("./plik.txt");
  }

  Game *game1 = my_loader.get_game_ptr();
  ASSERT_EQ(game1->get_past_moves().size(), 7);
  ASSERT_EQ(game1->get_past_moves().at(0).from.rank, 1);
}

TEST(LoaderTests, TestCloneGame) {
  Loader my_loader;
  Board start_board;
  my_loader.create_new_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  Game *game = my_loader.get_game_ptr();
  Move mv = move_from_string("e2e4");
  game->make_move(mv);
  mv = move_from_string("c7c6");
  game->make_move(mv);
  mv = move_from_string("d2d4");
  game->make_move(mv);
  mv = move_from_string("d7d5");
  game->make_move(mv);
  mv = move_from_string("b1c3");
  game->make_move(mv);
  mv = move_from_string("d5e4");
  game->make_move(mv);
  mv = move_from_string("c3e4");
  game->make_move(mv);

  game->step_back(2);
  my_loader.start_from_current_preview(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  Game *clone_game = my_loader.get_game_ptr();
  ASSERT_TRUE(my_loader.is_game_loaded());
  ASSERT_EQ(clone_game->get_max_depth(), 5);
  ASSERT_EQ(clone_game->get_current_depth(), 0);
  ASSERT_FALSE(clone_game->is_preview());
}
