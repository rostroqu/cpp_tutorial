#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print(const vector<int>& vec) {
    cout << "vec = ";
    for (auto v: vec) {
        cout << v << ", ";
    }
    cout << "\n";
}

using IntMatrix = vector<vector<int>>;

int main() {
    const int x{7};
    const string s{"Let us begin"};

    cout << "x = " << x << "\n";
    cout << "s = \"" <<  s << "\"\n";

    const vector<int> vec{1, 2, 8, 4, 7, 0};
    const IntMatrix matrix;

    print(vec);
}