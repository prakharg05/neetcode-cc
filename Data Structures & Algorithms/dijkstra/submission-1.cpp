class Solution {
struct Compare {
    bool operator()(pair<int, int> a, pair<int,int> b) {
        // min heap comparator  for <node, weight> pair
        return a.second > b.second;
        
    }
};
public:

    unordered_map<int, int> shortestPath(int n, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int, int>>> a(n);

        for(int x=0;x<edges.size();x++) {
            auto edge = edges[x];
            a[edge[0]].push_back({edge[1], edge[2]});
        }

        vector<bool> visited(n, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minHeap;

        minHeap.push({src, 0});
        vector<int> dist(n, INT_MAX-99);
        dist[src] = 0;
        while(!minHeap.empty()) {
            auto node = minHeap.top();
            int u =node.first;
            minHeap.pop();

            for(auto pp: a[u]) {
                int v = pp.first;
                int w = pp.second;

                if (dist[v] > dist[u] + w ) {
                    dist[v] = dist[u] + w ;
                    minHeap.push({v, dist[v]});
                }
            }
        }
        unordered_map<int, int> ans;
        for(int x= 0; x<n;x++ ) {
            ans[x] = dist[x] != INT_MAX-99 ? dist[x] : -1;
        }
        return ans;
    }
};
