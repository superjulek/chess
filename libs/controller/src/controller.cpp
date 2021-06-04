#include "controller.h"

#include <view/viewers/console_viewer.h>

Controller::Controller(std::unique_ptr<IView> concrete_viewer)
    : viewer(std::move(concrete_viewer)) {}

void Controller::start_game(std::unique_ptr<IPlayer> white,
                            std::unique_ptr<IPlayer> black) {
  loader.create_new_game(std::move(white), std::move(black));
}

void Controller::display_board() {
  viewer->display_board(loader.get_game_ptr()->get_board_layout());
}
