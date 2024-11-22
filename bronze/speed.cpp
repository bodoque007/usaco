#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

#define dbg(v)                                                                 \
	cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << endl;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    int n, m;
    freopen ("speeding.in","r",stdin);
    freopen ("speeding.out","w",stdout);
    cin >> n >> m;
    vector<int> roadLimit(100);
    int fragmentLength, fragmentSpeed, pos = 0, maxSpeed = 0;
    
    for (size_t i = 0; i < n; i++)
    {
        cin >> fragmentLength >> fragmentSpeed;
        for (int j = pos; j < pos + fragmentLength; j++) {
            roadLimit[j] = fragmentSpeed;
        }
        pos += fragmentLength;
    }

    pos = 0;
    for (size_t i = 0; i < m; i++)
    {
        cin >> fragmentLength >> fragmentSpeed;
        for (int j = pos; j < pos + fragmentLength; j++) {
            maxSpeed = max(maxSpeed, fragmentSpeed - roadLimit[j]);
        }
        pos += fragmentLength;
    }   
    cout << maxSpeed << endl;
    return 0;
}