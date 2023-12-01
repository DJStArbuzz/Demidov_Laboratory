#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> A(n + 2);
    vector<long long> Pref_l(n + 2);
    vector<long long> Pref_r(n + 2);

    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for (int i = 1; i <= n; i++) {
        Pref_l[i] = Pref_l[i - 1] + max(-(A[i] - A[i - 1]), (long long)0);
    }

    for (int i = 1; i <= n; i++) {
        cout << Pref_l[i] << endl;
    }

    for (int i = n; i >= 1; i--) {
        Pref_r[i] = Pref_r[i + 1] + max(-(A[i] - A[i + 1]), (long long)0);
    }
    
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (a < b) {
            cout << Pref_l[b] - Pref_l[a] << endl;
        }

        else {
            cout << Pref_r[b] - Pref_r[a] << endl;
        }
    }

}
