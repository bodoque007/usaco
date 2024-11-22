#include <iostream>
#include <vector>

using namespace std;
int main()
{   
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, n, m;
    cin >> t;

    while(t--)
    {
        int current_prefix_red = 0, max_prefix_red = 0;
        cin >> n;

        for(int i = 0; i < n; i++)
        {  
           int x;
           cin >> x;
           current_prefix_red += x;
           max_prefix_red = max(max_prefix_red, current_prefix_red);
        }

        cin >> m;
        int current_prefix_blue = 0, max_prefix_blue = 0;
        
        for (size_t i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            current_prefix_blue += x;
            max_prefix_blue = max(max_prefix_blue, current_prefix_blue);
        }
        cout << max(0, max_prefix_blue + max_prefix_red) << endl;
    }
    return 0;
}
