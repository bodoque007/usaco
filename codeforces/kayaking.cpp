#include <bits/stdc++.h>
#include <vector>

using namespace std;
vector<int> excluded;
vector<int> weights;


int calc_instability() {
    int curr_instability = 0;
    int i = 0;
    while (i < weights.size() - 1) {
        if (excluded[i]) {
            i++;
        } else if (excluded[i + 1]) {
            curr_instability += abs(weights[i] - weights[i + 2]);
            i += 3;
        } else {
            curr_instability += abs(weights[i] - weights[i + 1]);
            i += 2;
        }
    }
    return curr_instability;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    n *= 2;
    weights.resize(n);
    
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    
    sort(weights.begin(), weights.end());
    excluded.resize(n, 0);
    
    int min_instability = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            excluded[i] = excluded[j] = 1;
            min_instability = min(min_instability, calc_instability());
            excluded[i] = excluded[j] = 0;
        }
    }
    cout << min_instability << endl;
    return 0;
}
