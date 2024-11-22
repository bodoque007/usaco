#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int shellLocation[3] = {0, 1, 2};
    int n;
    vector<int> counter(3);

    freopen ("shell.in","r",stdin);
    freopen ("shell.out","w",stdout);
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--; c--;
        int tmp = shellLocation[a];
        shellLocation[a] = shellLocation[b];
        shellLocation[b] = tmp;
        counter[shellLocation[c]]++;
    }
    cout << max(max(counter[0], counter[1]), counter[2]);
    return 0;
}