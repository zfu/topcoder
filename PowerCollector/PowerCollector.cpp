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
#include <limits>

using namespace std;

#define MAX 1400000
bool prime[MAX];

class PowerCollector {
public:
	string countPowers(string N) {
        for (int i = 2; i < MAX; i++) prime[i] = true;
        for (int i = 2; i*i < MAX; i++)
            if (prime[i])
                for (int j = i*i; j < MAX; j += i)
                    prime[j] = false;
        istringstream is(N);
        long long n;
        is >> n;
        ostringstream os;
        os << go(n, MAX);
        return os.str();
	}

    int go(long long n, int e) {
        int res = 1;
        for (int i = 2; i < e; i++) {
            if (!prime[i]) continue;
            int p = root(n, i);
            if (p <= 1) break;
            res += p-go(p, i);
        }
        return res;
    }

    long long root(long long n, int e) {
        long long l = 1, u = n;
        while (l < u) {
            long long m = l+(u-l+1)/2;
            long long t = n;
            for (int i = 0; i < e; i++) t /= m;
            if (t < 1) u = m-1;
            else l = m;
        }
        return l;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, string p0, bool hasAnswer, string p1) {
	cout << "Test " << testNum << ": [" << "\"" << p0 << "\"";
	cout << "]" << endl;
	PowerCollector *obj;
	string answer;
	obj = new PowerCollector();
	clock_t startTime = clock();
	answer = obj->countPowers(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p1 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
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
	
	string p0;
	string p1;
	
    {
    // ----- test 0 -----
    p0 = "10";
    p1 = "4";
    all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
    // ------------------
    }
    
    {
    // ----- test 1 -----
    p0 = "36";
    p1 = "9";
    all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
    // ------------------
    }

    {
        // ----- test 2 -----
        p0 = "1000000000000000000";
        p1 = "1001003332";
        all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
        // ------------------
    }

    {
        // ----- test 3 -----
        p0 = "1000";
        p1 = "41";
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
