#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

struct Constraint {
    int i, j, e;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<Constraint> constraints;
        vector<int> variables;
        
        for (int k = 0; k < n; k++) {
            int i, j, e;
            cin >> i >> j >> e;
            constraints.push_back({i, j, e});
            variables.push_back(i);
            variables.push_back(j);
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        variables.erase(unique(variables.begin(), variables.end()), variables.end());
        
        unordered_map<int, int> compress;
        for (size_t idx = 0; idx < variables.size(); idx++) {
            compress[variables[idx]] = static_cast<int>(idx);
        }
        
        DSU dsu(variables.size());
        
        // Process equality constraints first
        for (const auto& constraint : constraints) {
            if (constraint.e == 1) {
                int compressed_i = compress[constraint.i];
                int compressed_j = compress[constraint.j];
                dsu.unite(compressed_i, compressed_j);
            }
        }
        
        // Check inequality constraints
        bool possible = true;
        for (const auto& constraint : constraints) {
            if (constraint.e == 0) {
                int compressed_i = compress[constraint.i];
                int compressed_j = compress[constraint.j];
                if (dsu.connected(compressed_i, compressed_j)) {
                    possible = false;
                    break;
                }
            }
        }
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    
    return 0;
}