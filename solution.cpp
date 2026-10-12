#include <cstdio>
#include <vector>
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

struct Constraint {
    int i, j, e;
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<Constraint> constraints;
        constraints.reserve(n);
        vector<int> variables;
        variables.reserve(n * 2);
        
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            constraints.push_back({i, j, e});
            variables.push_back(i);
            variables.push_back(j);
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        variables.erase(unique(variables.begin(), variables.end()), variables.end());
        
        DSU dsu(variables.size());
        
        // Process equality constraints first
        for (int k = 0; k < n; k++) {
            if (constraints[k].e == 1) {
                int compressed_i = lower_bound(variables.begin(), variables.end(), constraints[k].i) - variables.begin();
                int compressed_j = lower_bound(variables.begin(), variables.end(), constraints[k].j) - variables.begin();
                dsu.unite(compressed_i, compressed_j);
            }
        }
        
        // Check inequality constraints
        bool possible = true;
        for (int k = 0; k < n; k++) {
            if (constraints[k].e == 0) {
                int compressed_i = lower_bound(variables.begin(), variables.end(), constraints[k].i) - variables.begin();
                int compressed_j = lower_bound(variables.begin(), variables.end(), constraints[k].j) - variables.begin();
                if (dsu.connected(compressed_i, compressed_j)) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}