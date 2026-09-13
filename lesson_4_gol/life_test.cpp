#include "life.hpp"
#include <gtest/gtest.h>

//------------------------------------------------------------------------ Cell rules
TEST(GridRules, CellDiesIfLessThanTwoOrMoreThan3NeighborsAreAlive) {
    EXPECT_TRUE(life::nextState(true, 2));
    EXPECT_TRUE(life::nextState(true, 3));
    EXPECT_FALSE(life::nextState(true, 1));
    EXPECT_FALSE(life::nextState(true, 4));
}

TEST(GridRules, CellComesAliveIfThereIsThreeNeighbors) {
    EXPECT_FALSE(life::nextState(false, 2));
    EXPECT_TRUE(life::nextState(false, 3));
    EXPECT_FALSE(life::nextState(false, 4));
}

//------------------------------------------------------------------------ Grid rules
TEST(NeighborsCalculation, CellAtMiddleGetsRightNumberOfNeighbors) {
    life::Grid_t grid = {
        { false,  true,  true },
        { true,  false, false },     // Our target in the middle
        { false, false,  true },
    };

    int liveNeighbors = life::liveNeighbours(grid, 1, 1);
    EXPECT_EQ(liveNeighbors, 4);
}

TEST(NeighborsCalculation, CellAtEdgesGetsFalseNeighborsAtLimit) {
    life::Grid_t grid = {
        { false,  true,   true },
        { true,   true,  false },
        { true,   true,   true },
    };

    EXPECT_EQ(life::liveNeighbours(grid, 0, 0), 3);
    EXPECT_EQ(life::liveNeighbours(grid, 1, 2), 5);
}

//-------------------------------------------------------------- The actual stepping
TEST(GridStep, GridChangesAccordingToRules) {
    life::Grid_t grid = {
        { false, true, true }, { true, true, false }, { true, true, true },
    };

    life::Grid_t gridStep1 = {
        { true, true, true }, { false, false, false }, { true, false, true }
    };
    EXPECT_EQ(life::step(grid), gridStep1);

    life::Grid_t gridStep2 = {
        { false, true, false }, { true, false, true }, { false, false, false }
    };
    EXPECT_EQ(life::step(gridStep1), gridStep2);
}

TEST(GridStep, NonSquareGridFollowsRules) {
    life::Grid_t grid = {
        { false, true, true, true }, { true, true, false, true }
    };
    life::Grid_t gridStep1 = {
         { true, true, false, true }, { true, true, false, true }
    };
    EXPECT_EQ(life::step(grid), gridStep1);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}