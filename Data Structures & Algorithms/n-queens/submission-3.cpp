class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        string grid(n*n, '.');
        vector<vector<string>> ans;
        generateSolutions(0, n, n,grid, ans);
        return ans;


    }
    bool validSolution(string &grid, int n) {
        vector<pair<int,int>> points;
        for(int x=0;x<grid.size();x++) {
            if (grid[x] == 'Q') {
                points.push_back({x/n, x%n});
            } 
        }
        for(int x=0;x<points.size();x++) {
            for(int y=x+1;y<points.size();y++) {
                if ((points[x].first == points[y].first) || (points[x].second == points[y].second)) {
                    return false;
                }
                if (abs(float(points[x].first - points[y].first) / float(points[x].second - points[y].second)) == 1) {
                    return false;
                }
            }
        }
        return true;
    }
    vector<string> chunk(string &grid, int n) {
        vector<string> result;
        
        for (int i = 0; i < n; i++) {
            result.push_back(grid.substr(i * n, n));
        }

        return result;
    }
    int generateSolutions(int i, int n, int queensRemaning,string &grid, vector<vector<string>> &ans) {
        // throway bad boards as soons as possible
        if (!validSolution(grid, n)) {
            return 0;
        }
        if (i>=n*n) {
            // time to test the solutions
            // are queens chill?
            if (queensRemaning == 0 && validSolution(grid, n)) {
                ans.push_back(chunk(grid, n));
            }
            return 0;
        }

        char prevVal = grid[i];
        if (queensRemaning>0) {
        // I may place the queen here, and move forward
            grid[i] = 'Q';
            // if i place a queen, i can jump to next row
            generateSolutions(i+(n - (i%n)), n, queensRemaning-1, grid, ans);
        }

        // I may not place the queen here, and move forward
        grid[i] = prevVal;
        generateSolutions(i+1, n, queensRemaning, grid, ans);
    
        return 0;
    }
};
