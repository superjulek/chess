#include <view/i_view.h>
#include <view/viewers/console_viewer.h>

#include <gtest/gtest.h>

TEST(ConsoleViewerTests, Viewer_display_board)
{
  std::string expected_text = "  A  B  C  D  E  F  G  H\n8\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m8\n7\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m7\n6\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m6\n5\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m5\n4\x1B[43;37m   \x1B[0m\x1B[41;37m R \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m4\n3\x1B[41;37m   \x1B[0m\x1B[43;37m R \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m3\n2\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m2\n1\x1B[41;37m K \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m1\n  A  B  C  D  E  F  G  H\n";
  std::ostringstream local;
  auto *cout_buff = std::cout.rdbuf();
  std::cout.rdbuf(local.rdbuf());
  ConsoleViewer csview;
  Board board1("w a1wK b3wR b4wR");
  Board::BoardLayout blayout1 = board1.get_layout();
  csview.display_board(blayout1);
  ASSERT_STREQ(local.str().c_str(), expected_text.c_str());
  std::cout.rdbuf(cout_buff);
}

TEST(ConsoleViewerTests, Viewer_display_board2)
{
  std::string expected_text = "  A  B  C  D  E  F  G  H\n8\x1B[43;30m R \x1B[0m\x1B[41;30m N \x1B[0m\x1B[43;30m B \x1B[0m\x1B[41;30m Q \x1B[0m\x1B[43;30m K \x1B[0m\x1B[41;30m B \x1B[0m\x1B[43;30m N \x1B[0m\x1B[41;30m R \x1B[0m8\n7\x1B[41;30m P \x1B[0m\x1B[43;30m P \x1B[0m\x1B[41;30m P \x1B[0m\x1B[43;30m P \x1B[0m\x1B[41;30m P \x1B[0m\x1B[43;30m P \x1B[0m\x1B[41;30m P \x1B[0m\x1B[43;30m P \x1B[0m7\n6\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m6\n5\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m5\n4\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m4\n3\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m3\n2\x1B[43;37m P \x1B[0m\x1B[41;37m P \x1B[0m\x1B[43;37m P \x1B[0m\x1B[41;37m P \x1B[0m\x1B[43;37m P \x1B[0m\x1B[41;37m P \x1B[0m\x1B[43;37m P \x1B[0m\x1B[41;37m P \x1B[0m2\n1\x1B[41;37m R \x1B[0m\x1B[43;37m N \x1B[0m\x1B[41;37m B \x1B[0m\x1B[43;37m Q \x1B[0m\x1B[41;37m K \x1B[0m\x1B[43;37m B \x1B[0m\x1B[41;37m N \x1B[0m\x1B[43;37m R \x1B[0m1\n  A  B  C  D  E  F  G  H\n";
  std::ostringstream local;
  auto *cout_buff = std::cout.rdbuf();
  std::cout.rdbuf(local.rdbuf());
  ConsoleViewer csview;
  Board board1;
  Board::BoardLayout blayout1 = board1.get_layout();
  csview.display_board(blayout1);
  ASSERT_STREQ(local.str().c_str(), expected_text.c_str());
  std::cout.rdbuf(cout_buff);
}

TEST(ConsoleViewerTests, Viewer_display_board3)
{
  std::string expected_text = "  A  B  C  D  E  F  G  H\n8\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;30m K \x1B[0m\x1B[41;37m   \x1B[0m8\n7\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m7\n6\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m6\n5\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m5\n4\x1B[43;37m   \x1B[0m\x1B[41;37m R \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m4\n3\x1B[41;30m Q \x1B[0m\x1B[43;37m R \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m3\n2\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m2\n1\x1B[41;37m K \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m\x1B[41;37m   \x1B[0m\x1B[43;37m   \x1B[0m1\n  A  B  C  D  E  F  G  H\n";

  std::ostringstream local;
  auto *cout_buff = std::cout.rdbuf();
  std::cout.rdbuf(local.rdbuf());
  ConsoleViewer csview;
  Board board1("w a1wK b3wR b4wR a3bQ g8bK");
  Board::BoardLayout blayout1 = board1.get_layout();
  csview.display_board(blayout1);
  ASSERT_STREQ(local.str().c_str(), expected_text.c_str());
  std::cout.rdbuf(cout_buff);
}
