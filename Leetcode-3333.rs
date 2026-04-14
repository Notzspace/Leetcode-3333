const MOD: i64 = 1_000_000_007;

impl Solution {
    pub fn possible_string_count(word: String, k: i32) -> i32 {
        let k = k as usize;
        let bytes = word.as_bytes();
        let n = bytes.len();
        let mut cnt = 1;
        let mut freq = Vec::new();
        
        for i in 1..n {
            if bytes[i] == bytes[i - 1] {
                cnt += 1;
            } else {
                freq.push(cnt);
                cnt = 1;
            }
        }
        freq.push(cnt);
        
        let mut ans: i64 = 1;
        for &o in &freq {
            ans = (ans * o as i64) % MOD;
        }
        
        if freq.len() >= k {
            return ans as i32;
        }
        
        let mut f = vec![0i64; k];
        let mut g = vec![1i64; k];
        f[0] = 1;
        
        for &freq_val in &freq {
            let freq_val = freq_val as usize;
            let mut f_new = vec![0i64; k];
            let mut g_new = vec![0i64; k];
            
            for j in 1..k {
                f_new[j] = g[j - 1];
                if j > freq_val {
                    f_new[j] = (f_new[j] - g[j - freq_val - 1] + MOD) % MOD;
                }
            }
            
            g_new[0] = f_new[0];
            for j in 1..k {
                g_new[j] = (g_new[j - 1] + f_new[j]) % MOD;
            }
            
            f = f_new;
            g = g_new;
        }
        
        ((ans - g[k - 1] + MOD) % MOD) as i32
    }
}

struct Solution;

fn main() {
    let sol = Solution;
    println!("{}", Solution::possible_string_count("aabbccdd".to_string(), 7));  // Output: 5
    println!("{}", Solution::possible_string_count("aabbccdd".to_string(), 8));  // Output: 1
}