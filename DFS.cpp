#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream> // Để sử dụng ifstream và ofstream

// 9 12
// A B
// A C
// A D
// B I
// B G
// I G
// C E
// C F
// E G
// E K
// D F
// F K
// D C



using namespace std;

int n, m;
unordered_map<char, vector<char>> adj; // Dùng map để lưu danh sách kề
unordered_map<char, bool> visited;     // Dùng map để lưu trạng thái thăm

void inp(ifstream& input) {
    input >> n >> m; // Số đỉnh và số cạnh
    for (int i = 0; i < m; i++) {
        char x, y;
        input >> x >> y;
        adj[x].push_back(y); // Chỉ thêm cạnh từ x đến y
    }
    for (char c = 'A'; c < 'A' + n; c++) {
        visited[c] = false; // Đánh dấu tất cả các đỉnh là chưa thăm
    }
}

void dfs(char u, char target, ofstream& output) {
    output << u << " ";
    visited[u] = true;

    if (u == target) {
        
        return;
    }

    for (char v : adj[u]) {
        if (!visited[v]) {
            dfs(v, target, output);
        }
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Không thể mở tệp!" << endl;
        return 1;
    }

    inp(input);
    dfs('A', 'D', output); // Giả sử đỉnh bắt đầu là 'A'

    input.close();
    output.close();

    return 0;
}