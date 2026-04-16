class Solution {
public:
    int trap(vector<int> &height) {
        // we must calculate the lower envelop https://www.thealgorists.com/Algo/TrappingRain with some smartness to save on space
        // with 2 pointers, when ever we move them, atleast one sided values is known
        // meaning, height[i] & leftMaxSoFar and height[j] & rightMaxSoFar
        // helpmin calculating the lower envelop for for either i or j with certabniity
        int n = height.size();
        int i=0;
        int j=n-1;
        int ans = 0;
        int leftMaxSoFar = height[i];
        int rightMaxSoFar = height[j];
        while(i<=j) {
            leftMaxSoFar = max(leftMaxSoFar, height[i]);
            rightMaxSoFar = max(rightMaxSoFar, height[j]);

            // for either i or j, we need to answer min(left[i], right[i]) or min(left[j], right[j]) 

            // consider i (left)
            // rightMaxSoFar is the min of right[n...j] till now
            // so if leftMaxSoFar < min(right[n...j]), we can say leftMaxSoFar wins
            // as right[k] is monotonically decreasing (so moving from right -> left always increases the val)
            if (leftMaxSoFar< rightMaxSoFar) {
                ans += max(0, leftMaxSoFar - height[i]);
                i++;
            } else { //(leftMaxSoFar>=rightMaxSoFar)
                ans += max(0, rightMaxSoFar - height[j]);
                j--;
            }



        }
        return ans;
        



    }
    int trapWithSpace(vector<int>& height) {
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
        // space complexity is O(n);
        // we can't optimize time complexity. 
        // but do we need to store leftMax and rightMax;
        // can't we compute it on the fly , and keep adding.
        // lower envelop of the leftMax(monotonically increasing ) and rightMax (monotonically decreasing) curve.

        int ans = 0;
        for(int x= 0;x<n;x++) {
            int mini = min(leftMax[x], rightMax[x]);
            ans += max(mini-height[x], 0);
        }

        return ans;
    }
};
