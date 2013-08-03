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

using namespace std;

double ps[5120];

class RockSkipping {
public:
    double probability(string rs, int m) {
        for (int i = 0; i < 5120; i++)
            ps[i] = 0.0;

        int N = rs.size();
        int start = 0;
        int end = 0;
        ps[0] = 100.0;

        while (m > 0) {
            for (int i = end; i >= start; i--) {
                if (rs[i%N] == 'X')
                    continue;
                for(int j = 1; j <= m; j++) {
                    int k = i+j;
                    ps[k] += ps[i]/m;
                }
                ps[i] = 0.0;
            }
            start = start+1;
            end = end+m;
            m--;
            //cout << "ps" << endl;
            //for (int i = 0; i < N; i++)
            //    cout << ps[i] << " ";
            //cout << endl;
        }

        double res = 0.0;
        for (int i = 0; i < 5120; i++)
            if (rs[i%N] == 'X')
                res += ps[i];

        return 100.0-res;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, string p0, int p1, bool hasAnswer, double p2) {
    cout << "Test " << testNum << ": [" << "\"" << p0 << "\"" << "," << p1;
    cout << "]" << endl;
    RockSkipping *obj;
    double answer;
    obj = new RockSkipping();
    clock_t startTime = clock();
    answer = obj->probability(p0, p1);
    clock_t endTime = clock();
    delete obj;
    bool res;
    res = true;
    cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    if (hasAnswer) {
        cout << "Desired answer:" << endl;
        cout << "\t" << p2 << endl;
    }
    cout << "Your answer:" << endl;
    cout << "\t" << answer << endl;
    if (hasAnswer) {
        res = answer == answer && fabs(p2 - answer) <= 1e-9 * max(1.0, fabs(p2));
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

    string p0;
    int p1;
    double p2;

    {
        // ----- test 0 -----
        p0 = ".";
        p1 = 100;
        p2 = 100.0;
        all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 1 -----
        p0 = "...X";
        p1 = 2;
        p2 = 50.0;
        all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 2 -----
        p0 = "........................X";
        p1 = 50;
        p2 = 11.60725450562586;
        all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 3 -----
        p0 = "...X......XXXX...XX.X..X...XX...";
        p1 = 48;
        p2 = 5.408479511004734E-8;
        all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
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
