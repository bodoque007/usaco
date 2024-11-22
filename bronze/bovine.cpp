#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>



#define dbg(v)                                                                 \
	cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << endl;

using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;

    freopen ("cownomics.in","r",stdin);
    freopen ("cownomics.out","w",stdout);

    cin >> n >> m;
    vector<string> spottedCows(n);
    vector<string> nonSpottedCows(n);
    int count = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> spottedCows[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        cin >> nonSpottedCows[i];
    }
    int poss_positions = 0;
	for (int i = 0; i < m; i++) {
		unordered_set<char> seen;

		for (int j = 0; j < n; j++) { seen.insert(nonSpottedCows[j][i]); }

		bool dupe = false;

		for (int j = 0; j < n; j++) {
			if (seen.count(spottedCows[j][i]) > 0) {
				dupe = true;
				break;
			}
		}
		if (!dupe) { poss_positions++; }
    }

    cout << poss_positions << endl;
    return 0;
}