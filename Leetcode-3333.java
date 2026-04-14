import java.util.*;

class Solution {
    private static final long MOD = 1000000007;
    
    public int possibleStringCount(String word, int k) {
        int n = word.length();
        int cnt = 1;
        List<Integer> freq = new ArrayList<>();
        
        for (int i = 1; i < n; i++) {
            if (word.charAt(i) == word.charAt(i - 1)) {
                cnt++;
            } else {
                freq.add(cnt);
                cnt = 1;
            }
        }
        freq.add(cnt);
        
        long ans = 1;
        for (int o : freq) {
            ans = (ans * o) % MOD;
        }
        
        if (freq.size() >= k) {
            return (int) ans;
        }
        
        long[] f = new long[k];
        long[] g = new long[k];
        f[0] = 1;
        for (int i = 0; i < k; i++) {
            g[i] = 1;
        }
        
        for (int i = 0; i < freq.size(); i++) {
            long[] f_new = new long[k];
            long[] g_new = new long[k];
            
            for (int j = 1; j < k; j++) {
                f_new[j] = g[j - 1];
                if (j - freq.get(i) - 1 >= 0) {
                    f_new[j] = (f_new[j] - g[j - freq.get(i) - 1] + MOD) % MOD;
                }
            }
            
            g_new[0] = f_new[0];
            for (int j = 1; j < k; j++) {
                g_new[j] = (g_new[j - 1] + f_new[j]) % MOD;
            }
            
            f = f_new;
            g = g_new;
        }
        
        return (int) ((ans - g[k - 1] + MOD) % MOD);
    }
}

public class Main {
    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println(sol.possibleStringCount("aabbccdd", 7));  // Output: 5
        System.out.println(sol.possibleStringCount("aabbccdd", 8));  // Output: 1
    }
}