#include "engine.h"
#include <time.h>

Engine &Engine::get_instance()
{
    static Engine instance;
    return instance;
}
Move Engine::get_move(const Board &board)
{
    board.get_possible_moves();
    std::vector<PossibleMove> moves = board.get_possible_moves();
    srand (time(NULL));
    int move_num =  rand()%int(moves.size());
    return moves.at(size_t(move_num));
}
