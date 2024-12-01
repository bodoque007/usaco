#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("breedflip.in", "r", stdin);
    freopen("breedflip.out", "w", stdout);

    int n;
    cin >> n;

    string A, B;
    cin >> A;
    cin >> B;

    int i = 0;
    int count_differing_contiguous_segments = 0;
    while (i < n) {
        int j = i;
        while(A[j] != B[j]) j++;
        if (j != i) {
            count_differing_contiguous_segments++;
        }
        i = j + 1;
    }
    
    cout << count_differing_contiguous_segments << endl;
    
    return 0;
}
