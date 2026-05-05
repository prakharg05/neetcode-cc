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
    struct sortCompare{
        bool operator()(const Interval &a, const Interval &b) const {
            return a.start <b.start;
        }
    };
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        if (intervals.size() == 0) {
            return true;
        }
        sort(intervals.begin(), intervals.end(), sortCompare());
        for(int x=0;x<intervals.size()-1;x++) {
            auto i=intervals[x];
            auto j=intervals[x+1];
            if (doOverlap(i, j)) {
                return false;
            }

        }
        return true;
    }
    bool doOverlap(Interval &i, Interval &j) {
        return i.end>j.start;
    }
};
