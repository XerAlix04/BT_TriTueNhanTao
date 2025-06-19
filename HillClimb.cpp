#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream> 
#include <algorithm>
#include <deque>

using namespace std;

struct Node
{
    char id;
    int cost;
    bool operator==(const Node& other) const {
        return id == other.id && cost == other.cost;
    }
};

namespace std {
    template<>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            return hash<char>()(node.id) ^ hash<int>()(node.cost);
        }
    };
}

int n, m;
unordered_map<Node, vector<Node>> adj;
deque<Node> L, Li;
Node start, target;

bool compareNodes(const Node& a, const Node& b) {
    return a.cost > b.cost;
}

void inp(ifstream& input) {
    input >> n >> m;
    input >> start.id >> start.cost >> target.id >> target.cost;
    for (int i = 0; i < m; i++) {
        Node A, B;
        char a, b;
        int x, y;
        input >> a >> x >> b >> y;
        A.id = a;
        A.cost = x;
        B.id = b;
        B.cost = y;
        adj[A].push_back(B);
    }
}

void printSteps(Node u, deque<Node> L, deque<Node> Li, ofstream& outSteps){
    outSteps << "Node: " << u.id << "-" << u.cost << " ++++ Li: ";

    deque<Node> tempL = L;
    deque<Node> tempLi = Li;
    
    while(!tempLi.empty()){
        Node z = tempLi.front();
        tempLi.pop_front();
        outSteps << z.id << "-" << z.cost;
        if(!tempLi.empty()){
            outSteps << ", ";
        }
    }

    outSteps << " ++++ L: ";

    while(!tempL.empty()){
        Node v = tempL.front();
        tempL.pop_front();
        outSteps << v.id << "-" << v.cost;
        if (!tempL.empty()) {
            outSteps << ", ";
        }
    }

    outSteps << endl;
}

void HillClimb(Node u, Node target, ofstream& output, ofstream& outSteps){
    output << "Node ID: " << u.id << ", Cost: " << u.cost << endl;

    if(u==target){
        return;
    }

    vector<Node>& adjacentNodes = adj[u];
    sort(adjacentNodes.begin(), adjacentNodes.end(), compareNodes);
    for(const auto& x : adjacentNodes){
        L.push_front(x);
        Li.push_front(x);
    }

    printSteps(u, L, Li,  outSteps);

    while(!Li.empty()){
        Li.pop_front();
    }

    Node v = L.front();
    L.pop_front();
    HillClimb(v, target, output, outSteps);
}



int main() {
    ifstream input("inHC.txt");
    ofstream output("outHC.txt");
    ofstream outSteps("outStepsHC.txt");

    if (!input.is_open()) {
        cerr << "Không thể mở tệp!" << endl;
        return 1;
    }

    inp(input);
    
    HillClimb(start, target, output, outSteps);

    input.close();
    output.close();
    outSteps.close();

    return 0;
}