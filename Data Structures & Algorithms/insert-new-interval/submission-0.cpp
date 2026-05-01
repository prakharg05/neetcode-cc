class Solution {


    struct Event {
        int start;
        int end;
        bool isEnd;
    };
    struct sortCompare {
        bool operator()(const Event &a, const Event &b) {
            int pa = a.isEnd ? a.end:a.start;
            int pb = b.isEnd? b.end: b.start;

            if (pa==pb) {
                return a.isEnd ? false: true;
            }

            return pa<pb;

        }
    };

    
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<Event> events;
        for (auto i: intervals) {
            events.push_back(Event{i[0], i[1], false});
            events.push_back(Event{i[0], i[1], true});
        }
        events.push_back(Event{newInterval[0], newInterval[1], false});
events.push_back(Event{newInterval[0], newInterval[1], true});
        sort(events.begin(), events.end(), sortCompare());

        vector<vector<int>> ans;
        int activeEvents = 0;
        int start = -1;
        for(int x=0;x<events.size();x++) {
            auto e = events[x];

            if(!e.isEnd) {

                if (activeEvents ==0) {
                    start = e.start;
                }
                activeEvents++;

            } else {
                activeEvents--;
                if (activeEvents == 0) {
                    ans.push_back({start, e.end});
                }
            }
        }
        return ans;
        
        
    }
};
