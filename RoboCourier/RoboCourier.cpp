#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

int dist[512][6];

struct order {
    bool operator() (const int x, const int y) const {
        return make_pair(dist[x/6][x%6], x) < make_pair(dist[y/6][y%6], y);
    }
};
set<int, order> qs;

class RoboCourier {
public:
    int timeToDeliver(vector <string> path) {
        vector<pair<int, int> > ts;
        ts.push_back(make_pair(1, 1));
        ts.push_back(make_pair(0, 1));
        ts.push_back(make_pair(-1, 0));
        ts.push_back(make_pair(-1, -1));
        ts.push_back(make_pair(0, -1));
        ts.push_back(make_pair(1, 0));

        int graph[512][6];
        for (int i = 0; i < 512; i++)
            for (int j = 0; j < 6; j++)
                graph[i][j] = -1;

        vector<pair<int, int> > ns;
        ns.push_back(make_pair(0, 0));
        int from = 0;
        int turn = 0;
        for (int i = 0; i < (int)path.size(); i++) {
            for (int j = 0; j < (int)path[i].size(); j++) {
                char c = path[i][j];
                if (c == 'F') {
                    pair<int, int> p = make_pair(ns[from].first + ts[turn].first, ns[from].second + ts[turn].second);
                    vector<pair<int, int> >::iterator it = find(ns.begin(), ns.end(), p);
                    int to;
                    if (it == ns.end()) { 
                        ns.push_back(p);
                        to = ns.size()-1;
                    }
                    else {
                        to = it-ns.begin();
                    }
                    //cout << "from " << from << " to " << to << " turn " << turn << endl;
                    graph[from][turn] = to;
                    graph[to][(turn+3)%6] = from;
                    from = to;
                }
                else if (c == 'R') {
                    turn = (turn+1)%6;
                }
                else if (c == 'L') {
                    turn = (turn+5)%6;
                }
            }
        }

        int end = from;
        for (int i = 0; i < 512; i++)
            for (int j = 0; j < 6; j++)
                dist[i][j] = INT_MAX;
        dist[0][0] = 0;

        qs.clear();
        qs.insert(0);
        while (!qs.empty()) {
            int w = *qs.begin();
            qs.erase(qs.begin());
            int p = w/6;
            int t = w%6;
            int d = dist[p][t];

            //cout << "where " << p << " turn " << t << " dist " << d << endl;
            if (p == end) return d;

            push(p, (t+1)%6, d+3);
            push(p, (t+5)%6, d+3);

            int s = 0;
            int np = p;
            while (graph[np][t] != -1) {
                s++;
                np = graph[np][t];
                int dd = (s==1)?4:(8+2*(s-2));
                push(np, t, d+dd);
            }
        }

        return -1;
    }

    void push(int np, int nt, int nd) {
        if (nd < dist[np][nt]) {
            int nw = np*6+nt;
            if (qs.count(nw)) qs.erase(nw);
            dist[np][nt] = nd;
            qs.insert(nw);
        }
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, int p1) {
    cout << "Test " << testNum << ": [" << "{";
    for (int i = 0; int(p0.size()) > i; ++i) {
        if (i > 0) {
            cout << ",";
        }
        cout << "\"" << p0[i] << "\"";
    }
    cout << "}";
    cout << "]" << endl;
    RoboCourier *obj;
    int answer;
    obj = new RoboCourier();
    clock_t startTime = clock();
    answer = obj->timeToDeliver(p0);
    clock_t endTime = clock();
    delete obj;
    bool res;
    res = true;
    cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    if (hasAnswer) {
        cout << "Desired answer:" << endl;
        cout << "\t" << p1 << endl;
    }
    cout << "Your answer:" << endl;
    cout << "\t" << answer << endl;
    if (hasAnswer) {
        res = answer == p1;
    }
    if (!res) {
        cout << "DOESN'T MATCH!!!!" << endl;
    } else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
        cout << "FAIL the timeout" << endl;
        res = false;
    } else if (hasAnswer) {
        cout << "Match :-)" << endl;
    } else {
        cout << "OK, but is it right?" << endl;
    }
    cout << "" << endl;
    return res;
}
int main() {
    bool all_right;
    all_right = true;

    vector <string> p0;
    int p1;

    {
        // ----- test 0 -----
        string t0[] = {"FRRFLLFLLFRRFLF"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 15;
        all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 1 -----
        string t0[] = {"RFLLF"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 17;
        all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 2 -----
        string t0[] = {"FLFRRFRFRRFLLFRRF"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 0;
        all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 4 -----
        string t0[] = {"RFLLFLFLFRFRRFFFRFFRFFRRFLFFRLRRFFLFFLFLLFRFLFLRFF","RFFLFLFFRFFLLFLLFRFRFLRLFLRRFLRFLFFLFFFLFLFFRLFRLF","LLFLFLRLRRFLFLFRLFRF"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 24;
        all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 5 -----
        string t0[] = {"LLFLFRLRRLRFFLRRRRFFFLRFFRRRLLFLFLLRLRFFLFRRFFFLFL","RLFFRRLRLRRFFFLLLRFRLLRFFLFRLFRRFRRRFRLRLRLFFLLFLF","FRFLRFRRLLLRFFRRRLRFLFRRFLFFRLFLFLFRLLLLFRLLRFLLLF","FFLFRFRRFLLFFLLLFFRLLFLRRFRLFFFRRFFFLLRFFLRFRRRLLR","FFFRRLLFLLRLFRRLRLLFFFLFLRFFRLRLLFLRLFFLLFFLLFFFRR","LRFRRFLRRLRRLRFFFLLLLRRLRFFLFRFFRLLRFLFRRFLFLFFLFR","RFRRLRRFLFFFLLRFLFRRFRFLRLRLLLLFLFFFLFRLLRFRLFRLFR","LLFLFRLFFFFFFFRRLRLRLLRFLRLRRRRRRRRLFLFLFLRFLFRLFF","RLFRRLLRRRRFFFRRRLLLLRRLFFLLLLLRFFFFRFRRLRRRFFFLLF","FFFFLRRLRFLLRRLRLRFRRRRLFLLRFLRRFFFRFRLFFRLLFFRRLL"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 169;
        all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
        // ------------------
    }

    if (all_right) {
        cout << "You're a stud (at least on the example cases)!" << endl;
    } else {
        cout << "Some of the test cases had errors." << endl;
    }
    return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
