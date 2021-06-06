#include "runner.h"

#include <logger/channels/console_logger.h>
#include <logger/channels/file_logger.h>
#include <logger/logger.h>
#include <view/viewers/console_viewer.h>

#include <chrono>
#include <ctime>

Runner::Runner() : controller(std::make_unique<ConsoleViewer>()) {
  register_logger();
}

void Runner::register_logger() {
  /* Register loggers */
  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Debug, LogSev::Error)));
  Logger::get_instance().register_channel(std::make_unique<FileLogger>(
      FileLogger(LogSev::Trace, LogSev::Fatal,
                 getenv("HOME") + std::string("/chesslogs/logs.log"))));
  std::time_t now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  Logger::get_instance().log(LogSev::Info,
                             std::string("Starting at ") + std::ctime(&now));
  Logger::get_instance().log(LogSev::Info, "Program launched");
  Logger::get_instance().log(LogSev::Info, "Program terminating");
}

static Command get_exit_command() {
  Command exit_com{
      .name = "exit",
      .description = "Leave program.",
      .options = {},
      .options_map = {},
      .action = {[](const Command &cmd __attribute__((unused))) { exit(0); }},
  };
  return exit_com;
}

std::function<Move(const Board &, std::string name, bool retry)> Runner::get_user_prompting_fun() {
  return [&](const Board &board __attribute__((unused)), std::string name, bool retry) {
    Move mv;
    Communicator com;
    this->controller.display_text("Turn of player named: " + name + "\n");
    if (retry) {
      this->controller.display_text("Move not possible! Try once again: " + name + "\n");
    }
    retry = true;
    com.add_command({
        .name = "move",
        .description = "Give move coords. (e.g. move -from a2 -to a3)",
        .options =
            {
                {
                    .name = "-from",
                    .default_value = "",
                    .required = true,
                },
                {
                    .name = "-to",
                    .default_value = "",
                    .required = true,
                },
            },
        .options_map = {},
        .action = {[&](const Command &cmd) {
          std::string from = cmd.options_map.at("-from");
          std::string to = cmd.options_map.at("-to");
          mv.from = Coordinates(from.at(0), from.at(1));
          mv.to = Coordinates(to.at(0), to.at(1));
        }},
    });
    while (true) {
      controller.display_board();
      try {
        this->controller.display_text(com.get_prompt());
        com.communicate();
        break;
      } catch (const std::exception &exc) {
        retry = true;
        this->controller.display_text("Wrong coords, retry!\n");
      }
    }
    return mv;
  };
}

Communicator Runner::get_start_communicator() {
  Communicator com;
  com.add_command(get_exit_command());
  com.add_command({
      .name = "start-new",
      .description =
          "Starts new game. Set names for human players. AI otherwise.",
      .options =
          {
              {
                  .name = "-player1-name",
                  .default_value = "AI-1",
                  .required = false,
              },
              {
                  .name = "-player2-name",
                  .default_value = "AI-2",
                  .required = false,
              },
          },
      .options_map = {},
      .action = {[&](const Command &cmd) {
        std::unique_ptr<IPlayer> player_white;
        std::string white_name = cmd.options_map.at("-player1-name");
        if (white_name == "AI-1") {
          player_white = std::make_unique<AIPlayer>(Piece::PieceColor::White);
        } else {
          player_white = std::make_unique<HumanPlayer>(
              Piece::PieceColor::White, white_name, get_user_prompting_fun());
        }
        std::unique_ptr<IPlayer> player_black;
        std::string black_name = cmd.options_map.at("-player2-name");
        if (black_name == "AI-2") {
          player_black = std::make_unique<AIPlayer>(Piece::PieceColor::Black);
        } else {
          player_black = std::make_unique<HumanPlayer>(
              Piece::PieceColor::Black, black_name, get_user_prompting_fun());
        }
        this->controller.start_game(std::move(player_white),
                                    std::move(player_black));
      }},
  });
  com.add_command({
      .name = "load-from-file",
      .description = "Load game from file",
      .options = {
          {
              .name = "-path",
              .default_value = "",
              .required = true,
          },
          {
              .name = "-player1-name",
              .default_value = "AI-1",
              .required = false,
          },
          {
              .name = "-player2-name",
              .default_value = "AI-2",
              .required = false,
          },
      },
      .options_map = {},
      .action = {[&](const Command &cmd) {
        std::string path = cmd.options_map.at("-path");
        std::unique_ptr<IPlayer> player_white;
        std::string white_name = cmd.options_map.at("-player1-name");
        if (white_name == "AI-1") {
          player_white = std::make_unique<AIPlayer>(Piece::PieceColor::White);
        } else {
          player_white = std::make_unique<HumanPlayer>(
              Piece::PieceColor::White, white_name, get_user_prompting_fun());
        }
        std::unique_ptr<IPlayer> player_black;
        std::string black_name = cmd.options_map.at("-player2-name");
        if (black_name == "AI-2") {
          player_black = std::make_unique<AIPlayer>(Piece::PieceColor::Black);
        } else {
          player_black = std::make_unique<HumanPlayer>(
              Piece::PieceColor::Black, black_name, get_user_prompting_fun());
        }

        this->controller.load_game(path, std::move(player_white),
                                   std::move(player_black));
      }},
  });
  return com;
}

Communicator Runner::get_preview_communicator() {
  Communicator com;
  com.add_command(get_exit_command());
  // TODO
  // TODO comm: Leave preview
  return com;
}

Communicator Runner::get_gaming_communicator(Game::GameState state) {
  Communicator com;
  com.add_command(get_exit_command());
  com.add_command({.name = "display-board",
                   .description = "Displays current state of board.",
                   .options = {},
                   .options_map = {},
                   .action = {[&](const Command &cmd __attribute__((unused))) {
                     this->controller.display_board();
                   }}});
  com.add_command({
      .name = "save-game",
      .description = "It saves your game in given location",
      .options = {{
          .name = "-path",
          .default_value = "",
          .required = true,
      }},
      .options_map = {},
      .action = {[&](const Command &cmd __attribute__((unused))) {
        std::string path = cmd.options_map.at("-path");
        this->controller.save_game(path);
      }},
  });
  if (state != Game::GameState::Checkmate && state != Game::GameState::Pat) {
    com.add_command({
        .name = "next-move",
        .description = "Invokes next move.",
        .options = {},
        .options_map = {},
        .action = {[&](const Command &cmd __attribute__((unused))) {
          this->controller.next_move();
        }},
    });
    com.add_command({
        .name = "resign",
        .description = "I want to resign",
        .options = {},
        .options_map = {},
        .action = {[&](const Command &cmd __attribute__((unused))) {
          this->controller.abandon_game();
        }},
    });
    if (state == Game::GameState::Check) {
      controller.display_text("Check!\n");
    }
  } else {
    com.add_command({
        .name = "preview-game",
        .description = "It lets you look through moves, entering preview mode.",
        .options = {},
        .options_map = {},
        .action = {[&](const Command &cmd __attribute__((unused))) {
          this->controller.enter_preview();
        }},
    });
    com.add_command({
        .name = "start-new",
        .description =
            "Starts new game. Set names for human players. AI otherwise.",
        .options =
            {
                {
                    .name = "-player1-name",
                    .default_value = "AI-1",
                    .required = false,
                },
                {
                    .name = "-player2-name",
                    .default_value = "AI-2",
                    .required = false,
                },
            },
        .options_map = {},
        .action = {[&](const Command &cmd) {
          std::unique_ptr<IPlayer> player_white;
          std::string white_name = cmd.options_map.at("-player1-name");
          if (white_name == "AI-1") {
            player_white = std::make_unique<AIPlayer>(Piece::PieceColor::White);
          } else {
            player_white = std::make_unique<HumanPlayer>(
                Piece::PieceColor::White, white_name, get_user_prompting_fun());
          }
          std::unique_ptr<IPlayer> player_black;
          std::string black_name = cmd.options_map.at("-player2-name");
          if (black_name == "AI-2") {
            player_black = std::make_unique<AIPlayer>(Piece::PieceColor::Black);
          } else {
            player_black = std::make_unique<HumanPlayer>(
                Piece::PieceColor::Black, black_name, get_user_prompting_fun());
          }
          this->controller.start_game(std::move(player_white),
                                      std::move(player_black));
        }},
    });
  }
  if (state == Game::GameState::Pat) {
    this->controller.display_text("\033[1;4mPat!\nIt's a tie! \033[0m\n");
  }
  if (state == Game::GameState::Checkmate) {
    if (this->controller.get_current_player() == Piece::PieceColor::White) {
      this->controller.display_text("\033[1;4mCheckmate!\nBlack won!\033[0m\n");
    } else {
      this->controller.display_text("\033[1;4mCheckmate!\nWhite won!\033[0m\n");
    }
  }
  return com;
}

void Runner::run() {
  while (true) {
    try {
      Communicator comm;
      if (!controller.is_game_loaded()) {
        comm = get_start_communicator();
      } else if (!controller.is_preview()) {
        comm = get_gaming_communicator(controller.get_game_state());
      } else {
        comm = get_preview_communicator();
      }
      controller.display_text(std::string("\033[1;33m") + comm.get_prompt() +
                              "\033[0m");
      comm.communicate();
    }

    catch (const std::exception &exc) {
      controller.display_text(std::string("\033[1;31;47mError: ") + exc.what() +
                              "\033[0m\n");
    }
  }
}
