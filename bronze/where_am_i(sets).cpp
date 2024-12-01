#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    freopen("whereami.in","r",stdin);
    freopen("whereami.out","w",stdout);
	int n;
	cin>> n;
	string s;
	cin >> s;
	
	// Basically find the minimum k such that there are no two or more equal
	// substrings of length k. Binary search could be even better.
	int min = n + 1;
	for (int k = 1; k < n; k++) {
		set<string> substrings_of_size_k;
		for (int i = 0; i <= n - k; i++) {
			string substring = s.substr(i, k);
			if (substrings_of_size_k.count(substring)) {
				break;
			}
			substrings_of_size_k.insert(substring);
		}
		// The set has every substring of length k, thus all were unique (because we never broke out of the loop)
		if (substrings_of_size_k.size() == n - k + 1) {
			min = k;
			break;
		}
	}
    
    if (min == n + 1) {
        cout << n << endl;
    } else {
        cout << min << endl;
    }
	return 0;
}
