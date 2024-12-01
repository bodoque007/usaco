#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("notlast.in", "r", stdin);
    freopen("notlast.out", "w", stdout);

    int n;
    cin >> n;

    map<string, int> cows_milking_amount = {
        {"Bessie", 0}, {"Elsie", 0}, {"Daisy", 0}, 
        {"Gertie", 0}, {"Annabelle", 0}, {"Maggie", 0}, 
        {"Henrietta", 0}
    };

    while (n--) {
        string cow_name;
        int amount;
        cin >> cow_name >> amount;
        cows_milking_amount[cow_name] += amount;
    }

    string smallest_key = "";
    string second_smallest_key = "";
    int smallest_value = INT_MAX;
    int second_smallest_value = INT_MAX;

    for (const auto& [key, value] : cows_milking_amount) {
        if (value < smallest_value) {
            second_smallest_value = smallest_value;
            second_smallest_key = smallest_key;
            smallest_value = value;
            smallest_key = key;
        } else if (value > smallest_value && value < second_smallest_value) {
            second_smallest_value = value;
            second_smallest_key = key;
        }
    }

    int countSecondSmallest = 0;
    for (const auto& [key, value] : cows_milking_amount) {
        if (value == second_smallest_value) {
            countSecondSmallest++;
            if (countSecondSmallest > 1) break;
        }
    }

    if (countSecondSmallest > 1 || second_smallest_key == "") {
        cout << "Tie" << endl;
    } else {
        cout << second_smallest_key << endl;
    }

    return 0;
}
