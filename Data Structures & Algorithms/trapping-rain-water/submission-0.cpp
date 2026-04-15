class Solution {
public:
    int trap(vector<int>& height) {
        // solution is for each bar is
        // the water accumulated = min(maxHeight left of the bar (including it), maxheight right of bar inclusing it)
        int n = height.size();
        vector<int> leftMax(n, 0);
        vector<int> rightMax(n, 0);
        leftMax[0]=height[0];
        for(int x=1;x<n;x++) {
            leftMax[x] = max(leftMax[x-1], height[x]);
        }
        rightMax[n-1]= height[n-1];
        for(int x=n-2;x>=0;x--) {
            rightMax[x] = max(rightMax[x+1], height[x]);
        }
        int ans = 0;
        for(int x= 0;x<n;x++) {
            int mini = min(leftMax[x], rightMax[x]);
            ans += max(mini-height[x], 0);
        }
        return ans;
    }
};
