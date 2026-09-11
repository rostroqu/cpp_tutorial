#include <iostream>

using namespace std;

int main() {
    int grid[2][4] = {
        {1, 5, 7, 3},
        {9, 6, 2, 0}
    };

    cout << grid[1][2] << "\n";

    for (const auto& row : grid) {
        for (const int element : row) {
            cout << element << ", ";
        }
        cout << "\n";
    }
}