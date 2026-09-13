#pragma once
#include <vector>
#include <cstddef>

namespace life {
    using Cell_t = bool;
    using Grid_t = std::vector<std::vector<Cell_t>>;

    Cell_t nextState(Cell_t cell, int noOfNeighbors) {
        if (cell) {
            return noOfNeighbors == 2 || noOfNeighbors == 3;
        }
        return noOfNeighbors == 3;
    }

    bool alive(const Grid_t& grid, std::size_t row, std::size_t col) {
        if (row >= grid.size() || col >= grid[row].size()) {
            return false;
        }
        return grid[row][col];
    }

    int liveNeighbours(const Grid_t& grid, std::size_t row, std::size_t col) {
        const std::size_t r0 = (row == 0) ? 0 : row - 1;
        const std::size_t c0 = (col == 0) ? 0 : col - 1;

        int count = 0;
        for (std::size_t r = r0; r <= row + 1; ++r) {
            for (std::size_t c = c0; c <= col + 1; ++c) {
                if ((r != row || c != col) && alive(grid, r, c)) {
                    count++;
                }
            }
        }
        return count;
    }

    Grid_t step(const Grid_t& grid) {
        Grid_t next(grid.size(), std::vector<Cell_t>(grid[0].size(), false));

        for (std::size_t r = 0; r < grid.size(); ++r) {
            for (std::size_t c = 0; c < grid[r].size(); ++c) {
                next[r][c] = nextState(grid[r][c], liveNeighbours(grid, r, c));
            }
        }
        return next;
    }
}
