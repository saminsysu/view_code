/* Given a string s and a dictionary of words dict, 
determine if s can be segmented into a space-separated 
sequence of one or more dictionary words.
*/

// 使用动态规划，状态转移方程为 dp[i] = dp[j], dict.count(s.substr(j, i - j)) != 0

bool wordBreak(string s, unordered_set<string> &dict) {
    if (s.empty()) {
        return true;
    }
    vector<bool> dp(s.size() + 1, false); // 值为 l 长度时的字符串是否满足条件
    dp[0] = true;
    for (int i = 1; i <= s.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (dict.count(s.substr(j, i - j)) != 0 && dp[j]) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s.size()];


/* Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.
*/

// 使用动态规划，状态转移方程为 dp[i][j] = (s[i]==s[j] && (j - i <= 1 || DP[i+1][j-1] == 1))

int minCut(string s) {
    if (s.empty()) {
        return 0;
    }
    int len = s.size();
    vector<vector<bool> > dp(len, vector<bool>(len, false));
    vector<int> count(len+1, INT_MAX);
    count[len] = 0;
    for (int i = len - 1; i >= 0; i--) {
        for (int j = i; j < len; j++) {
            if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
                dp[i][j] = 1;
                count[i] = min(count[j + 1] + 1, count[i]);
            }
        }
    }
    return count[0] - 1;
}