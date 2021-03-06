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

int fs[16];
int dist[32768][16];

struct Order {
    bool operator() (const int x, const int y) const {
        return make_pair(dist[x/16][x%16], x) < make_pair(dist[y/16][y%16], y);
    }
};

class TurntableService {
public:
    int calculateTime(vector <string> favorites) {
        int N = favorites.size();
        for (int i = 0; i < N; i++) {
            int f = 0;
            istringstream is(favorites[i]);
            int s;
            while (is >> s) 
                f |= (1 << s);
            fs[i] = f;
        }

        for (int i = 0; i < 32768; i++)
            for (int j = 0; j < 16; j++)
                dist[i][j] = INT_MAX;
        dist[0][0] = 0;

        int res = INT_MAX;

        set<int, Order> qs;
        qs.insert(0);
        while (!qs.empty()) {
            int w = *qs.begin();
            qs.erase(qs.begin());
            int d = w/16;
            int p = w%16;
            int t = dist[d][p];

            //cout << "where " << p << endl;
            //cout << "time " << t << endl;
            //bitset<15> bs(d);
            //cout << "done " << bs << endl;

            if (d == (1<<N)-1) {
                if (t < res) res = t;
                continue;
            }

            for (int r = 0; r < N; r++) {
                int np = (p+r)%N;
                //cout << "next pos " << np << endl;
                int nt = t;
                if (r > 0) nt = t+((r<N-r)?r:(N-r))+1;
                int nd = d;
                for (int i = 0; i < N; i++) {
                    int f = (i>=np)?(i-np):(N-np+i);
                    if ((fs[i]>>f)&1) {
                        //cout << "eat " << f << endl;
                        nd |= 1<<i;
                    }
                }
                //bitset<15> bs(nd);
                //cout << "next done " << bs << endl;
                if (nd == d) continue;
                nt += 15;
                if (nt < dist[nd][np]) {
                    int nw = nd*16+np;
                    if (qs.count(nw)) qs.erase(nw);
                    dist[nd][np] = nt;
                    qs.insert(nw);
                }
            } 
        }

        return res;
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
    TurntableService *obj;
    int answer;
    obj = new TurntableService();
    clock_t startTime = clock();
    answer = obj->calculateTime(p0);
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
        string t0[] = {"0 2","1","0 1"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 32;
        all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 1 -----
        string t0[] = {"0","0","0"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 49;
        all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 2 -----
        string t0[] = {"4","1","2","3","0"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 50;
        all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 3 -----
        string t0[] = {"0 004","2 3","0 01","1 2 3 4","1 1"};
        p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
        p1 = 35;
        all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
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
