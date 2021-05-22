#include <view/i_view.h>
#include <view/viewers/console_viewer.h>

#include <gtest/gtest.h>

TEST(ConsoleViewerTests, CreateViewer) {
  Board board;
  Board::BoardLayout blayout = board.get_layout();
  ConsoleViewer csview;
  csview.display_board(blayout);
  // TODO
}
