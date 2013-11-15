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

#define N 36*36*36*36
int dist[N];

class CornersGame {
public:
	int encode(vector<string> & board) {
		int state = 0;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (board[i][j] != 'x') continue;
				state *= 36;
				state += (i*6+j);
			}
		}
		return state;
	}

	void decode(int state, vector<string> & board) {
		for (int i = 0; i < 4; i++) {
			board[state%36/6][state%36%6] = 'x';
			state /= 36;
		}
	}

	int countMoves(vector <string> board) {
		for (int i = 0; i < N; i++) dist[i] = -1;
		vector<string> tmp = board;
		tmp[4][4] = 'x';
		tmp[4][5] = 'x';
		tmp[5][4] = 'x';
		tmp[5][5] = 'x';
		int src = encode(tmp);

		tmp = board;
		tmp[0][0] = 'x';
		tmp[0][1] = 'x';
		tmp[1][0] = 'x';
		tmp[1][1] = 'x';
		int des = encode(tmp);

		queue<int> qs;
		qs.push(src);
		dist[src] = 0;
		while (!qs.empty()) {
			int node = qs.front();
			qs.pop();

			if (node == des) return dist[node];

			tmp = board;
			decode(node, tmp);

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					if (tmp[i][j] != 'x') continue;
					for (int di = -1; di <= 1; di++) {
						for (int dj = -1; dj <= 1 ; dj++) {
							if (abs(di) == abs(dj)) continue;
							int ni = i+di, nj = j+dj;
							if ((ni < 0 || ni > 5 || nj < 0 || nj > 5 || tmp[ni][nj] == 'r')) continue;
							if (tmp[ni][nj] == 'x' || tmp[ni][nj] == 's') {
								ni += di, nj += dj;
								if ((ni < 0 || ni > 5 || nj < 0 || nj > 5 || tmp[ni][nj] != '.')) continue;
							}
							swap(tmp[i][j], tmp[ni][nj]);
							int next = encode(tmp);
							swap(tmp[i][j], tmp[ni][nj]);
							if (dist[next] != -1) continue;
							dist[next] = dist[node]+1;
							qs.push(next);
						}
					}
				}
			}
		}
		return -1;
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
	CornersGame *obj;
	int answer;
	obj = new CornersGame();
	clock_t startTime = clock();
	answer = obj->countMoves(p0);
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
	string t0[] = {"......","......","......","......","......","......"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 16;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {".....s","..s.r.","r.....",".srs..","..r...","......"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 19;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"......","......","....ss","....ss","...r..","...r.."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = -1;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"...s.r","..r.s.","rr.s..","..s.rr","s.rr..",".s.s.."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 54;
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
