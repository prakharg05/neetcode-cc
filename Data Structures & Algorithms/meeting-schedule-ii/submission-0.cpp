/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
    struct Event {
        int start;
        int end;
        bool isEnd;
    };
    struct sortCompare {
        bool operator()(const Event &a, const Event &b) const {
            int pa=a.isEnd?a.end:a.start;
            int pb=b.isEnd?b.end:b.start;

            if (pa==pb) {
                return a.isEnd;
            }

            return pa<pb;
        }
    };


public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<Event> events;
        for(int x=0;x<intervals.size();x++) {
            auto i = intervals[x];
            events.push_back(Event{i.start, i.end, true});
            events.push_back(Event{i.start, i.end, false});
        }
        sort(events.begin(), events.end(), sortCompare());
        int activeEvents = 0;
        int maxActive = 0;
        for(int x=0;x<events.size();x++) {
            auto e=events[x];

            if(!e.isEnd) {
                activeEvents++;
                maxActive = max(maxActive, activeEvents);
            } else {
                activeEvents--;
            }
        }
        return maxActive;
    }
};
