class Solution {
    struct Compare {
        bool operator()(vector<int> a, vector<int> b) {
            
            return a[2]>b[2];
            
        }
    };
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> distance(n, vector<int>(n, INT_MAX));

        priority_queue<vector<int>, vector<vector<int>>, Compare> heap;
        distance[0][0] = grid[0][0];
        heap.push({0,0,grid[0][0]});

        while(!heap.empty()) {
            auto node = heap.top();
            int x = node[0];
            int y = node[1];
            heap.pop();
            if (x==n-1 && y==n-1) {
                return distance[x][y];
            }
            for (auto i:getNeighbours(node[0], node[1], n)) {
                int vx = i.first;
                int vy = i.second;
                int incrementalCost = max( distance[x][y], grid[vx][vy]);
                if (distance[vx][vy] >  incrementalCost ) {
                    distance[vx][vy] = incrementalCost;
                    heap.push({vx, vy, incrementalCost});
                }
            }
        }
        return distance[n-1][n-1];

    }
    bool isSafe(int x, int y, int n) {
        return x<n&&y<n&&x>=0&&y>=0;
    }
    vector<pair<int,int>> getNeighbours(int x, int y, int n) {
        vector<pair<int, int>> ans;
        vector<int> dx = {-1, 0, 1, 0};
        vector<int> dy = {0, 1, 0 , -1};
        for(int k = 0;k<4;k++) {
            if(isSafe(x+dx[k], y+dy[k], n)) {
                ans.push_back({x+dx[k], y+dy[k]});
            }
        }
        return ans;
    }
};
