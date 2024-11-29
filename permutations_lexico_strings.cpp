#include <iostream>
#include <vector>


using namespace std;
vector<int> count(26);
string curr_perm = "";
int n;

void print_permutations() {
    if (curr_perm.size() == n) {
        cout << curr_perm << endl;
    } else {
        for (int i = 0; i < n; i++) {
            if (count[i] == 0) {
                continue;
            }
            count[i]--;
            curr_perm.push_back('a' + i);
            print_permutations();
            count[i]++;
            curr_perm.pop_back();
        }
    }
}

int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    n = s.size();
    for (auto& c : s) {
        count[c - 'a']++;
    }
    
    int perms = factorial(n);
    
    int unique_chars_factorials = 1;
    for (auto& c : count) {
        unique_chars_factorials *= factorial(c);
    }
    cout << perms / unique_chars_factorials << endl;
    print_permutations();
    return 0;
}
