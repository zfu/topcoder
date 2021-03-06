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

int memo[20];

class EncodingTrees {
public:
	string getCode(int N, int index) {
        for (int i = 0; i <= N; i++) memo[i] = -1;
        memo[0] = memo[1] = 1;
	    if (calc(N) < index) return "";
        //for (int i = 0; i <= N; i++) cout << memo[i] << " ";
        //cout << endl;
        string s;
        for (int i = 0; i < N; i++) s.push_back('a'+i);
        return go(s, index);
    }

    int calc(int n) {
        if (memo[n] != -1) return memo[n];
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += calc(i)*calc(n-i-1);
        return memo[n] = sum;
    }
    
    string go(string s, int i) {
        int n = s.size();
        if (n == 0) return "";
        if (n == 1) return s;
        int j = 0;
        for (; j < n; j++) {
            int e = memo[j]*memo[n-j-1];
            if (i <= e) break;
            i -= e;
        }
        string res;
        res.push_back(s[j]);
        int k = memo[n-j-1];
        int l = i%k;
        res += go(s.substr(0, j), 1+(i-1)/k);
        res += go(s.substr(j+1, n-j-1), l?l:k);
        return res;
    }
};
// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, int p0, int p1, bool hasAnswer, string p2) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1;
	cout << "]" << endl;
	EncodingTrees *obj;
	string answer;
	obj = new EncodingTrees();
	clock_t startTime = clock();
	answer = obj->getCode(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p2 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
	if (hasAnswer) {
		res = answer == p2;
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
	
	int p0;
	int p1;
	string p2;
	
    {
    // ----- test 0 -----
        p0 = 2;
        p1 = 1;
        p2 = "ab";
        all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 1 -----
        p0 = 2;
        p1 = 2;
        p2 = "ba";
        all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 2 -----
        p0 = 2;
        p1 = 3;
        p2 = "";
        all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 3 -----
        p0 = 4;
        p1 = 9;
        p2 = "cbad";
        all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 4 -----
        p0 = 15;
        p1 = 14023;
        p2 = "abcdeohgfniljkm";
        all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
        // ------------------
    }

    {
        // ----- test 5 -----
        p0 = 3;
        p1 = 2;
        p2 = "acb";
        all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
        // ------------------
    }
    
    {
        // ----- test 6 -----
        p0 = 6;
        p1 = 66;
        p2 = "cbafed";
        all_right = KawigiEdit_RunTest(6, p0, p1, true, p2) && all_right;
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
