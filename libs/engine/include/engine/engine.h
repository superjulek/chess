#include <chess/board/board.h>

class Engine {
public:
  static Engine &get_instance();
  static Move get_move(const Board &board) {
    return get_instance().I_get_move(board);
  };

private:
  Engine() = default;
  ~Engine() = default;
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  Move I_get_move(const Board &board);
};
