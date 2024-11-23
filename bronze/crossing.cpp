#include <iostream>
#include <vector>
#include <iterator>

// Statement = https://usaco.org/index.php?page=viewproblem2&cpid=712

using namespace std;
int main()
{   
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("circlecross.in","r",stdin);
    freopen("circlecross.out","w",stdout);

    int count = 0;
    vector<pair<int, int>> cows(26, {-1, -1}); 

    string circle_path;

    cin >> circle_path;

    for (int i = 0; i < circle_path.size(); i++) {
        if (cows[circle_path[i] - 'A'].first == -1) {
            cows[circle_path[i] - 'A'].first = i;
        } else {
            cows[circle_path[i] - 'A'].second = i;
        }
    }

    for (int i = 0; i < cows.size(); i++) {
        for (int j = i + 1; j < cows.size(); j++) {
            if ((cows[i].first < cows[j].first && cows[i].second > cows[j].first && cows[i].second < cows[j].second) 
            || (cows[j].first < cows[i].first && cows[j].second > cows[i].first && cows[j].second < cows[i].second)) {
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}
