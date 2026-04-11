class Solution {
    struct Compare {
        bool operator()(vector<int> a, vector<int> b) {
            // min heap
            return a[2]>b[2];
            
        }
    };
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int r = 0;
        for (int x = 0 ; x<n ;x++) {
            for (int y=0;y<n;y++) {
                r = max(r, grid[x][y]);
            }
        }
        r++;
        int l =0;

        while(l<=r) {
            int m = l+ (r-l)/2.0;
            if (canReach(grid, m)) {
                r = m-1;
            } else {
                l = m+1;
            }

        } 
        return l;
    }

    bool canReach(vector<vector<int>> &grid, int time) {
         if (grid[0][0]> time ) {
            return false;
         }
        queue<pair<int,int>> q;
        int n=grid.size();
        vector<vector<bool>> visited(n, vector<bool> (n, false));

        q.push({0,0});
        visited[0][0] = true;
        while(!q.empty()) {
            int k = q.size();
            for(int i=0;i<k;i++) {
                auto node = q.front();
                q.pop();
                if (grid[node.first][node.second] > time) {
                    continue;
                }
                if (node.first == n-1 && node.second == n-1) {
                    return true;
                }
                for(auto v : getNeighbours(node.first, node.second, n)) {
                    if (!visited[v.first][v.second]) {
                        visited[v.first][v.second] = true;
                        q.push({v.first, v.second});
                    }
                }
            }
        }
        return false;
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
