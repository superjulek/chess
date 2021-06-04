#pragma once

#include <view/i_view.h>
#include <loader/loader.h>

#include <memory>

class Controller {
public:
  Controller(std::unique_ptr<IView> concrete_viewer);
  void display_board();
  void start_game(std::unique_ptr<IPlayer> white,
                  std::unique_ptr<IPlayer> black);

private:
  Loader loader;
  std::unique_ptr<IView> viewer;
};
