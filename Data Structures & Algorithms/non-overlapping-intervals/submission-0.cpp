class Solution {
    struct Event{
        int start;
        int end;
        bool isEnd;
    };


    struct sortCompare {
        bool operator()(const Event &a, const Event &b) const {
            int pa = a.isEnd? a.end:a.start;
            int pb = b.isEnd? b.end:b.start;
            if (pa==pb) {
                return a.isEnd? true: false;
            }
            return pa<pb;

        }
    };
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        vector<Event> events;
        for(auto v: intervals) {
            events.push_back({v[0], v[1], false});
            events.push_back({v[0], v[1], true});
        }
        sort(events.begin(), events.end(), sortCompare());
        multiset<Event, sortCompare> activeEvents;
        int ans = 0;
        for(int x=0;x<events.size();x++) {
            auto e = events[x];
            if (!e.isEnd) {
                activeEvents.insert(e);
            } else {
                auto i = activeEvents.find(Event{e.start, e.end, false});
                if (i != activeEvents.end()) { // event found
                    activeEvents.erase(i);
                } else {
                    cout<<"missingcounterpart "<<e.start<< " "<<e.end<<" "<<e.isEnd<<endl; 
                    // counter part must have been removed
                    continue;
                }
                if (!activeEvents.empty()) {
                    // this means, theres an ongoing interval that overlapped the recently ended event, better to delete it
                    // better to loop and remove
                    while(!activeEvents.empty()) {
                        auto eventToRemove = activeEvents.begin();
                        activeEvents.erase(eventToRemove);
                        ans++;
                    }
                }
            }
        }
        return ans;

    }
};
