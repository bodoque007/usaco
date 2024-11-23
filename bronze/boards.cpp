#include <iostream>
#include <vector>
#include <iterator>

// Statement = https://usaco.org/index.php?page=viewproblem2&cpid=664

using namespace std;
int main()
{   
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("blocks.in","r",stdin);
    freopen("blocks.out","w",stdout);

    int n;
    cin >> n;
    vector<int> max_freq(26, 0);

    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        vector<int> freq_a(26, 0);
        vector<int> freq_b(26, 0);

        for (char& c : a) {
            freq_a[c - 'a']++;
        }

        for (char& c : b) {
            freq_b[c - 'a']++;
        }

        for (int j = 0; j < 26; j++) {
            max_freq[j] += max(freq_a[j], freq_b[j]);
        }
    }
    
    copy(max_freq.begin(), max_freq.end(), ostream_iterator<int>(cout, "\n"));
    return 0;
}
