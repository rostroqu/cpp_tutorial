#include <string>
#include "life.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <thread>

namespace {
    const std::string HOME = "\x1b[H";
    const std::string ALIVE = "\u2588";
    const std::string DEAD = " ";

    std::string render(const life::Grid_t& grid) {
        std::string out = HOME;
        for (const auto& row: grid) {
            for (life::Cell_t cell : row) {
                out += cell ? ALIVE : DEAD;
            }
            out += "\n";
        }
        return out;
    }
}

static const std::size_t rows = 35;
static const std::size_t cols = 100;

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5);

    life::Grid_t grid(rows, std::vector<life::Cell_t>(cols));
    for (auto& row : grid) {
        std::generate(row.begin(), row.end(), [&]() { return dist(gen); });
    }

    while (true)
    {
        std::cout << render(grid) << std::flush; 
        grid = life::step(grid);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }
    
}