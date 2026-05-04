class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<vector<int>> packed(n);
        for(int x=0;x<n;x++) {
            packed[x] = {position[x], speed[x]};
        }
        sort(packed.begin(), packed.end());
        vector<double> timeTaken(n, -1.0);
        timeTaken[n-1] = (1.0*target-packed[n-1][0]*1.0)/packed[n-1][1]*1.0;

        int ans = 1;
        for(int x=n-2;x>=0;x--) {
            double independently = (1.0*target -packed[x][0])/(packed[x][1]*1.0);

            timeTaken[x]= max(timeTaken[x+1], independently);
            if (timeTaken[x]!=timeTaken[x+1]) {
                ans++;
            }
        }
        return ans;
    }
};
