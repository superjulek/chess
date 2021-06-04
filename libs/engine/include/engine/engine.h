#include <chess/board/board.h>

class Engine
{
public:
    static Engine &get_instance();
    Move get_move(const Board &board);

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;
};
