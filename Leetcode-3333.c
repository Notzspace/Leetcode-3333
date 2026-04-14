#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int possibleStringCount(char* word, int k) {
    int n = strlen(word);
    int cnt = 1;
    int* freq = (int*)malloc(n * sizeof(int));
    int freq_size = 0;
    
    for (int i = 1; i < n; i++) {
        if (word[i] == word[i - 1]) {
            cnt++;
        } else {
            freq[freq_size++] = cnt;
            cnt = 1;
        }
    }
    freq[freq_size++] = cnt;
    
    long long ans = 1;
    for (int i = 0; i < freq_size; i++) {
        ans = (ans * freq[i]) % MOD;
    }
    
    if (freq_size >= k) {
        free(freq);
        return (int)ans;
    }
    
    long long* f = (long long*)calloc(k, sizeof(long long));
    long long* g = (long long*)malloc(k * sizeof(long long));
    f[0] = 1;
    for (int i = 0; i < k; i++) {
        g[i] = 1;
    }
    
    for (int i = 0; i < freq_size; i++) {
        long long* f_new = (long long*)calloc(k, sizeof(long long));
        long long* g_new = (long long*)calloc(k, sizeof(long long));
        
        for (int j = 1; j < k; j++) {
            f_new[j] = g[j - 1];
            if (j - freq[i] - 1 >= 0) {
                f_new[j] = (f_new[j] - g[j - freq[i] - 1] + MOD) % MOD;
            }
        }
        
        g_new[0] = f_new[0];
        for (int j = 1; j < k; j++) {
            g_new[j] = (g_new[j - 1] + f_new[j]) % MOD;
        }
        
        free(f);
        free(g);
        f = f_new;
        g = g_new;
    }
    
    long long result = (ans - g[k - 1] + MOD) % MOD;
    
    free(freq);
    free(f);
    free(g);
    
    return (int)result;
}

int main() {
    printf("%d\n", possibleStringCount("aabbccdd", 7));  // Output: 5
    printf("%d\n", possibleStringCount("aabbccdd", 8));  // Output: 1
    return 0;
}