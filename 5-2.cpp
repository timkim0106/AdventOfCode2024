#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
using namespace std;


void readLine2(vector<pair<int, int>>& rules, string& s)
{
    int n1 = stoi(s.substr(0, 2));
    int n2 = stoi(s.substr(3, 2));
    pair<int, int> p = make_pair(n1, n2);
    rules.push_back(p);

}

vector<int> parseNumbers(const string& input) {
    vector<int> result;
    stringstream ss(input);
    string token;

    while (getline(ss, token, ',')) {
        result.push_back(stoi(token));
    }

    return result;
}

void readLine(unordered_map<int, unordered_set<int>>& graph, unordered_map<int, int>& inDegree, string& s, vector<pair<int, int>>& rules) {
    int n1 = stoi(s.substr(0, 2));
    int n2 = stoi(s.substr(3, 2));
    pair<int, int> p = make_pair(n1, n2);
    rules.push_back(p);

    graph[n1].insert(n2);
    inDegree[n2]++;
    if (inDegree.find(n1) == inDegree.end()) {
        inDegree[n1] = 0; // Ensure all nodes are in the in-degree map
    }

    // Debug output for graph construction
    cout << "Edge added: " << n1 << " -> " << n2 << endl;
}

vector<int> topologicalSort(unordered_map<int, unordered_set<int>>& graph, unordered_map<int, int>& inDegree) {
    unordered_map<int, int> localInDegree = inDegree;
    queue<int> zeroInDegree;
    vector<int> sortedOrder;

    // Collect all nodes with zero in-degree
    for (const auto& pair : localInDegree) {
        if (pair.second == 0) {
            zeroInDegree.push(pair.first);
        }
    }

    // Perform topological sort
    while (!zeroInDegree.empty()) {
        int node = zeroInDegree.front();
        zeroInDegree.pop();
        sortedOrder.push_back(node);

        if (graph.find(node) != graph.end()) {
            for (int neighbor : graph[node]) {
                localInDegree[neighbor]--;
                if (localInDegree[neighbor] == 0) {
                    zeroInDegree.push(neighbor);
                }
            }
        }
    }

    // Handle cycles
    if (sortedOrder.size() != localInDegree.size()) {
        cerr << "Cycle detected! Proceeding with partial order." << endl;

        // Remove one edge from the cycle
        for (const auto& pair : graph) {
            for (int neighbor : pair.second) {
                if (localInDegree[neighbor] > 0) {
                    cerr << "Removing edge: " << pair.first << " -> " << neighbor << endl;
                    graph[pair.first].erase(neighbor);
                    localInDegree[neighbor]--;
                    if (localInDegree[neighbor] == 0) {
                        zeroInDegree.push(neighbor);
                    }
                    break; // Break only one edge per iteration
                }
            }
            if (!zeroInDegree.empty()) break;
        }

        // Recursively attempt topological sort again
        return topologicalSort(graph, localInDegree);
    }

    return sortedOrder;
}

void reorderVector(vector<int>& v, const vector<int>& sortedOrder) {
    unordered_map<int, int> position;
    for (size_t i = 0; i < sortedOrder.size(); ++i) {
        position[sortedOrder[i]] = i;
    }

    // Sort the vector based on the positions in the sortedOrder
    sort(v.begin(), v.end(), [&position](int a, int b) {
        auto posA = position.find(a);
        auto posB = position.find(b);

        // If one or both elements are missing from the sortedOrder, retain natural order
        if (posA == position.end() && posB == position.end()) return a < b;
        if (posA == position.end()) return false;
        if (posB == position.end()) return true;

        return posA->second < posB->second;
    });

    // Debug output for sorted vector
    cout << "Reordered vector: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
}

int checkLine(vector<int>& v, vector<pair<int, int>>& rules) {
    for (const auto& rule : rules) {
        auto it1 = find(v.begin(), v.end(), rule.first);
        auto it2 = find(v.begin(), v.end(), rule.second);

        if (it1 != v.end() && it2 != v.end()) {
            int idx1 = distance(v.begin(), it1);
            int idx2 = distance(v.begin(), it2);
            if (idx1 >= idx2) {
                return 0; // Invalid line
            }
        }
    }
    return v[v.size() / 2];
}


void swap(vector<int>& v, vector<pair<int, int>>& rules)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            int n1 = v[i];
            int n2 = v[j];
            for (const auto& p : rules)
            {
                if (p.first == n2 && p.second == n1)
                {
                    int temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
                    cout << "we had to swap" << endl;
                }
            }
        }
    }
}

int main() {
    ifstream MyFile("input.txt");
    string my_string;
    int total = 0, m = 0, n = 0, o = 0;

    unordered_map<int, unordered_set<int>> graph;
    unordered_map<int, int> inDegree;
    vector<pair<int, int>> rules;

    while (getline(MyFile, my_string)) {
        if (my_string.empty()) continue;

        if (my_string.size() <= 5) {
            readLine2(rules, my_string);
            //readLine(graph, inDegree, my_string, rules);
        } else {

            vector<int> v;
            v = parseNumbers(my_string);
            
            int middle = checkLine(v, rules);
            if (middle == 0)
            {
                // swap
                swap(v, rules);
                middle = checkLine(v, rules);
                total+= middle;
            }
            //total += middle;
        

            cout << "Middle element: " << middle << endl;
        }
    }


/*
            vector<int> sortedOrder = topologicalSort(graph, inDegree);
            if (sortedOrder.empty()) {
                cerr << "Aborting due to a cycle in the graph!" << endl;
                return 1;
            }

            stringstream ss(my_string);
            vector<int> v;
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                v.push_back(stoi(substr));
            }

            // Debug output for the initial vector
            cout << "Initial vector: ";
            for (int x : v) {
                cout << x << " ";
            }
            cout << endl;

            

           
    }
    */

    cout << "Total: " << total << endl;
    cout << "Valid lines: " << m << endl;
    cout << "Invalid lines: " << n << endl;
    cout << "Total lines: " << o << endl;

    MyFile.close();
    return 0;
}
