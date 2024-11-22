#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>


// Statement = https://usaco.guide/bronze/simulation
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("shuffle.in","r", stdin);
    freopen("shuffle.out","w", stdout);

    int n;
    cin >> n;
    vector<int> shuffles(n);
    vector<int> cows(n);
    vector<int> cows_aux(n);

    for (size_t i = 0; i < n; i++)
    {
        cin >> shuffles[i];
        shuffles[i]--;
    }
    

    for(int i = 0; i < cows.size(); i++){
        cin >> cows[i];
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cows_aux[j] = cows[shuffles[j]];
        }
        swap(cows, cows_aux);
    }
    copy(cows.begin(), cows.end(), ostream_iterator<int>(cout, "\n"));


    return 0;
}
