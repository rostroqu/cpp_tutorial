#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
    cout << "vec = ";
    for (auto v: vec) {
        cout << v << ", ";
    }
    cout << endl;
}

using IntMatrix = vector<vector<int>>;

int main() {
    int x{7};
    string s{"Let us begin"};

    cout << "x = " << x << endl;
    cout << "s = \"" <<  s << "\"" << endl;

    vector<int> vec{1, 2, 8, 4, 7, 0};
    IntMatrix matrix;

    print(vec);
}