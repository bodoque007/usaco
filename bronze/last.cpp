#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> capacities(3);
    vector<int> currentMilk(3);

    freopen ("mixmilk.in","r",stdin);
    freopen ("mixmilk.out","w",stdout);

    for (int i = 0; i < 3; i++) {
        cin >> capacities[i];
        cin >> currentMilk[i];
    }
    
    for (int i = 0; i < 100; i++) {
        int from = i % 3;               // Current bucket index
        int to = (i + 1) % 3;           // Next bucket index

        int milk_to_add = capacities[to] - currentMilk[to];
        if (milk_to_add > currentMilk[from]) {
            milk_to_add = currentMilk[from];
        }
        currentMilk[from] -= milk_to_add;
        currentMilk[to] += milk_to_add;
    }
    for (auto val : currentMilk) {
        cout << val << "\n";
    }
    return 0;
}

// 10 4 
// 8 3