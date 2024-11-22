#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 7;
    vector<int> place(n);
    while(n--) {
        cin >> place[n];
    }
    sort(place.begin(), place.end());
    int a = place[0];
    int b = place[1];
    int c = place[place.size() - 1] - a - b;
    cout << a << " " << b << " " << c << endl;
    return 0;
}