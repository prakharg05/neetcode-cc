class Solution {
    struct Event {
        int start;
        int end;
        bool isEnd;
    };

    struct sortCompare {
        bool operator()(const Event &a , const Event &b) {
            int pa = a.isEnd? a.end:a.start;
            int pb = b.isEnd? b.end:b.start;

            if (pa==pb) {
                return a.isEnd? false:true;
            }
            return pa<pb;
        }
    };
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<Event> events;
        for(auto i: intervals) {
            events.push_back(Event{i[0], i[1], false});
            events.push_back(Event{i[0], i[1], true});
        }
        sort(events.begin(), events.end(), sortCompare());
        int mergeStart = -1;
        int activeEvents = 0;
        vector<vector<int>> ans;
        for(int x=0;x<events.size();x++) {
            auto i = events[x];

            if(!i.isEnd) {
                if (activeEvents ==0 ) {
                    mergeStart = i.start;
                }
                activeEvents ++;

            }else {

                activeEvents--;
                if (activeEvents ==0 ) {
                    ans.push_back({mergeStart, i.end});
                }

            }

        }
        return ans;
    }
};
