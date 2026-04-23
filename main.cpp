#include "vector.hpp"
#include <iostream>
#include <string>

using namespace std;
using sjtu::vector;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> v;
    
    for (int i = 0; i < n; ++i) {
        string op;
        cin >> op;
        
        if (op == "push_back") {
            int val;
            cin >> val;
            v.push_back(val);
        } else if (op == "pop_back") {
            v.pop_back();
        } else if (op == "size") {
            cout << v.size() << "\n";
        } else if (op == "get") {
            int idx;
            cin >> idx;
            cout << v[idx] << "\n";
        } else if (op == "clear") {
            v.clear();
        }
    }
    
    return 0;
}
