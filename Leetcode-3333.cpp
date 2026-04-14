#include <iostream>
#include <vector>
#include <string>
using namespace std;

const long long MOD = 1e9 + 7;

class Solution {
public:
    int possibleStringCount(string word, int k) {
        int n = word.length();
        int cnt = 1;
        vector<int> freq;
        
        for (int i = 1; i < n; i++) {
            if (word[i] == word[i - 1]) {
                cnt++;
            } else {
                freq.push_back(cnt);
                cnt = 1;
            }
        }
        freq.push_back(cnt);
        
        long long ans = 1;
        for (int o : freq) {
            ans = (ans * o) % MOD;
        }
        
        if ((int)freq.size() >= k) {
            return (int)ans;
        }
        
        vector<long long> f(k, 0), g(k, 1);
        f[0] = 1;
        
        for (int i = 0; i < (int)freq.size(); i++) {
            vector<long long> f_new(k, 0);
            for (int j = 1; j < k; j++) {
                f_new[j] = g[j - 1];
                if (j - freq[i] - 1 >= 0) {
                    f_new[j] = (f_new[j] - g[j - freq[i] - 1] + MOD) % MOD;
                }
            }
            vector<long long> g_new(k, 0);
            g_new[0] = f_new[0];
            for (int j = 1; j < k; j++) {
                g_new[j] = (g_new[j - 1] + f_new[j]) % MOD;
            }
            f = f_new;
            g = g_new;
        }
        
        return (int)((ans - g[k - 1] + MOD) % MOD);
    }
};

int main() {
    Solution sol;
    cout << sol.possibleStringCount("aabbccdd", 7) << endl;  // Output: 5
    cout << sol.possibleStringCount("aabbccdd", 8) << endl;  // Output: 1
    return 0;
}