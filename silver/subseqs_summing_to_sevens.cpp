#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> prefix_sum(n + 1);
    for (int i = 1; i < n + 1; i++) {
        int ID;
        cin >> ID;
        prefix_sum[i] = prefix_sum[i - 1] + ID % 7;
    }
    int max_length = 0;
    for (int i = 1; i < prefix_sum.size(); i++) {
        for (int j = i; j < prefix_sum.size(); j++) {
            if ((prefix_sum[j] - prefix_sum[i - 1]) % 7 == 0 && max_length < j - i + 1) {
                max_length = j - i + 1;
            }
        }
    }
    
    cout << max_length << endl;
    return 0;
}
