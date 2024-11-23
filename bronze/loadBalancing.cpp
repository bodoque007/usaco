#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

// Statement = https://usaco.org/index.php?page=viewproblem2&cpid=617


using namespace std;
int main()
{   
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("balancing.in","r",stdin);
    freopen("balancing.out","w",stdout);

    int n, b;
    cin >> n >> b;

    set<int> x_fence_positions;
    set<int> y_fence_positions;

    vector<pair<int, int>> cows(n);

    int x, y;

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        cows[i] = make_pair(x, y);
        x_fence_positions.insert(x + 1);
        y_fence_positions.insert(y + 1);
    }

    int minimum_imbalance = n;

    for (auto a : x_fence_positions) {
        for (auto b : y_fence_positions) {
            int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
            for (auto& [x, y] : cows) {
                if (x > a && y > b) q1++;
                if (x < a && y > b) q2++;
                if (x < a && y < b) q3++;
                if (x > a && y < b) q4++;
            }
            int max_imbalance = max({q1, q2, q3, q4});
            minimum_imbalance = min(minimum_imbalance, max_imbalance);
        }
    }

    cout << minimum_imbalance << endl;
    return 0;
}
