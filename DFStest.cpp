#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <sstream>
using namespace std;

struct Node {
    string name;
    vector<string> neighbors;
};

void readGraph(const string& filename, vector<Node>& graph, string& startNode, string& goalNode) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open input file." << endl;
        exit(1);
    }

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        // Parse the line (e.g., "A B C" means node A has neighbors B and C)
        stringstream ss(line);
        string nodeName;
        ss >> nodeName;

        Node node;
        node.name = nodeName;

        string neighbor;
        while (ss >> neighbor) {
            node.neighbors.push_back(neighbor);
        }

        graph.push_back(node);

        if(startNode.empty()){
            startNode = nodeName;
        }
    }

    if(!graph.empty()){
        goalNode = graph.back().name;
    }

    infile.close();
}

// Function to find the index of a node in the graph vector
int findNodeIndex(const vector<Node>& graph, const string& nodeName) {
    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[i].name == nodeName) {
            return i;
        }
    }
    return -1; // Node not found
}

// Function to perform DFS and write the output to a file
void dfs(const vector<Node>& graph, const string& startNode, const string& goalNode, const string& outputFilename) {
    ofstream outfile(outputFilename);
    if (!outfile) {
        cerr << "Error: Could not open output file." << endl;
        exit(1);
    }

    stack<string> s;
    set<string> visited;
    vector<string> path;
    s.push(startNode);

    outfile << "Node\tAdjacent Nodes\tStack\tVisited Nodes\n";

    while (!s.empty()) {
        string current = s.top();
        s.pop();

        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            path.push_back(current);

            outfile << current << "\t";
            for (const string& neighbor : graph[findNodeIndex(graph, current)].neighbors) { 
                outfile << neighbor << " ";
            }
            outfile << "\t";

            // Print stack
            stack<string> tempStack = s;
            while (!tempStack.empty()) {
                outfile << tempStack.top() << " ";
                tempStack.pop();
            }
            outfile << "\t";

            // Print visited nodes
            for (const string& node : visited) {
                outfile << node << " ";
            }
            outfile << endl;

            if (current == goalNode) {
                outfile << "\nPath to goal: ";
                for (const string& node : path) {
                    outfile << node << " ";
                }
                outfile << endl;
                break;
            }

            // Push unvisited neighbors onto the stack
            for (const string& neighbor : graph[findNodeIndex(graph, current)].neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    s.push(neighbor);
                }
            }
        }
    }

    outfile.close();
}

int main() {
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";
    vector<Node> graph;
    string startNode, goalNode;

    readGraph(inputFilename, graph, startNode, goalNode);

    for(int i = 0; i<graph.size(); i++){
        cout << graph[i].name << "\n";
        for(int j = 0; j<graph[i].neighbors.size(); j++){
            cout << graph[i].neighbors[j] << " ";
        }
        cout << "\n";
    }
    cout << startNode << " " << goalNode;

    dfs(graph, startNode, goalNode, outputFilename);

    cout << "DFS completed. Output written to " << outputFilename << endl;

    return 0;
}
