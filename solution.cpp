#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DSU {
private:
    vector<int> parent;
    
public:
    DSU(int n) : parent(n) {
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
        
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<int, int>> equal_constraints;
        vector<pair<int, int>> unequal_constraints;
        equal_constraints.reserve(n);
        unequal_constraints.reserve(n);
        
        unordered_map<int, int> id_map;
        vector<int> variables;
        variables.reserve(n * 2);
        
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            
            if (e == 1) {
                equal_constraints.push_back({i, j});
            } else {
                unequal_constraints.push_back({i, j});
            }
            
            if (id_map.find(i) == id_map.end()) {
                id_map[i] = variables.size();
                variables.push_back(i);
            }
            if (id_map.find(j) == id_map.end()) {
                id_map[j] = variables.size();
                variables.push_back(j);
            }
        }
        
        DSU dsu(variables.size());
        
        // Process equality constraints
        for (const auto& constraint : equal_constraints) {
            int id_i = id_map[constraint.first];
            int id_j = id_map[constraint.second];
            dsu.unite(id_i, id_j);
        }
        
        // Check inequality constraints
        bool possible = true;
        for (const auto& constraint : unequal_constraints) {
            int id_i = id_map[constraint.first];
            int id_j = id_map[constraint.second];
            if (dsu.connected(id_i, id_j)) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}