class Solution {
    struct Event {
        int start;
        int end;
        bool isEnd;
        bool isPoint;
    };
    struct sortCompare {
        bool operator()(const Event  &a, const Event &b) const {
            // first determine, if you are interval-point or query-point
            int pa = -1;
            int pb = -1;
            if (a.isPoint) {
                pa = a.start;
            } else {
                pa = !a.isEnd? a.start: a.end;
            }

            if (b.isPoint) {
                pb = b.start;
            } else {
                pb = !b.isEnd?b.start:b.end;
            }

            if (pa == pb) {
                // handle precedence
                // then start (0),points(1), end(2) among lines
                int aVal = a.isPoint?1 : (a.isEnd? 2:0);
                int bVal = b.isPoint?1 : (b.isEnd? 2:0);
                return aVal<bVal;
            }
            return pa <pb;

        }
    };

    struct setCompare {
        bool operator() (const Event &a, const Event &b) const {
            // sort by length, but if legnth equal, still define a precendece so it's deterministic and comp(a,b) !=comp(b,a) generally
            int lenA = (a.end - a.start +1 );
            int lenB = (b.end - b.start +1);
            if (lenA != lenB) {
                return lenA < lenB;
            }

            if (a.start!=b.start) return a.start<b.start;
            return a.end<b.end;
        }
    };
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<Event> events;
        for(auto i: intervals) {
            events.push_back(Event{i[0], i[1], false, false});
            events.push_back(Event{i[0], i[1], true, false});
        }
        for(auto p: queries) {
            events.push_back(Event{p,p,false, true});
        }
        multiset<Event, setCompare> activeEvents;
        sort(events.begin(), events.end(), sortCompare());
        map<int, int> ans;
        for(int x=0;x<events.size();x++) {
            auto e = events[x];
            if(e.isPoint) {
                // answer the query
                // this is a query, check the active events, and choose the the short length

                if(activeEvents.empty()) {
                    ans[e.start] = -1;
                } else {
                    auto interval = activeEvents.begin();
                    ans[e.start] = (*interval).end - (*interval).start +1;
                }
            } else {
                // activate and deactivate events lol

                if (!e.isEnd) {
                    activeEvents.insert(e);
                } else {
                    // now we must end the interval, and remove it for active intervals

                    auto foundEvent = activeEvents.find(Event{e.start, e.end, false, false});
                    if(foundEvent !=activeEvents.end()) {
                        activeEvents.erase(foundEvent);
                    }
                }
            }
        }
        for(int x=0;x<queries.size();x++) {
            queries[x] = ans[queries[x]];
        }
        return queries;

    }
};