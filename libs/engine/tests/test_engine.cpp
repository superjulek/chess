#include <gtest/gtest.h>
#include <engine/engine.h>

TEST(EngineTest, CreateEngine)
{
    Board b("b a1bK b3wR");
    ASSERT_EQ(Engine::get_instance().get_move(b).to.file, 0);
    ASSERT_EQ(Engine::get_instance().get_move(b).to.rank, 1);
}

