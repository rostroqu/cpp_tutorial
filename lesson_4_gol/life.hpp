#pragma once
#include <vector>
#include <cstddef>

namespace life {
    using Cell_t = bool;
    using Grid_t = std::vector<std::vector<Cell_t>>;

    class World {
        public:
        explicit World(Grid_t initial);
        void step();
        [[nodiscard]] const Grid_t& current() const;
    
        private:
        Grid_t curr;
        Grid_t next;
    };

    [[nodiscard]] Cell_t nextState(Cell_t cell, int noOfNeighbors);
    [[nodiscard]] bool alive(const Grid_t& grid, std::size_t row, std::size_t col);
    [[nodiscard]] int liveNeighbours(const Grid_t& grid, std::size_t row, std::size_t col);

    Grid_t step(const Grid_t& grid);
}
