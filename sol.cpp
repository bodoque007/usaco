#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> apples_set(n);

    for (int i = 0; i < n; i++) {
        cin >> apples_set[i];
    }
    long long total_weight = accumulate(apples_set.begin(), apples_set.end(), 0LL);
    long long min_difference = LLONG_MAX;

    for (int mask = 0; mask < (1 << n); mask++) {
        long long subset_sum = 0;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset_sum += apples_set[i];
            }
        }

        long long other_sum = total_weight - subset_sum;
        min_difference = min(min_difference, abs(subset_sum - other_sum));
    }

    cout << min_difference << endl;

    return 0;
}
