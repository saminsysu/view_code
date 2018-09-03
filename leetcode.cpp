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

/* There are N children standing in a line. Each child is assigned a rating value.
You are giving candies to these children subjected to the following requirements:
Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/

// 三次遍历

int candy(vector<int> &ratings) {
    int n = ratings.size();
    if (n == 0) {
        return 0;
    }
    vector<int> cnt(n, 1);
    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) {
            cnt[i] = cnt[i - 1] + 1;
        }
    }
    for (int i = n - 1; i > 0; --i) {
        if (ratings[i] < ratings[i - 1]) {
            cnt[i - 1] = max(cnt[i] + 1, cnt[i - 1]);
        }
    }
    int count = 0;
    for (int i = 0; i < n; ++i) {
        count += cnt[i];
    }
    return count;
}

// 一次遍历

int candy(vector<int> &ratings) {
    int n = ratings.size();
    if (n == 0) {
        return 0;
    }
    int pre = 1, cnt = 1, len = 0;
    for (int i = 1; i < n; ++i) {
        if (ratings[i] >= ratings[i - 1]) {
            if (len > 0) {
                cnt += (1 + len) * len / 2;
                if (len >= pre) {
                    cnt += len - pre + 1;
                }
                pre = 1;
                len = 0;
            }
            pre = (ratings[i] == ratings[i - 1]) ? 1 : pre + 1;
            cnt += pre;
        } else {
            len++;
        }
    }
    if (len > 0) {
        cnt += (1 + len) * len / 2;
        if (len >= pre) {
            cnt += len - pre + 1;
        }
    }
    return cnt;
}

/* Given a triangle, find the minimum path sum from top to bottom. 
Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is11(i.e., 2 + 3 + 5 + 1 = 11).

*/

// 自顶向下

int minimumTotal(vector<vector<int> > &triangle) {
    int n = triangle.size();
    if (n == 0) {
        return 0;
    }
    vector<int> dp1(n, 0), dp2(n, 0);
    vector<int> *ptr1 = &dp1, *ptr2 = &dp2;
    (*ptr1)[0] = triangle[0][0];
    for (int i = 1; i < n; i++) {
        swap(ptr1, ptr2);
        for (int j = 0; j < triangle[i].size(); j++) {
            if (j == 0) {
                (*ptr1)[0] = (*ptr2)[0] + triangle[i][0];
            } else if (j == triangle[i].size() - 1) {
                (*ptr1)[j] = (*ptr2)[j-1] + triangle[i][j];
            } else {
                (*ptr1)[j] = (triangle[i][j] + (*ptr2)[j-1] > triangle[i][j] + (*ptr2)[j]) ? 
                triangle[i][j] + (*ptr2)[j] : triangle[i][j] + (*ptr2)[j-1];
            }
        }
    }
    int minimum = INT_MAX;
    for (int i = 0; i < n; i++) {
        minimum = min(minimum, (*ptr1)[i]);
    }
    return minimum;
}

// 自底向上

int minimumTotal(vector<vector<int> > &triangle) {
    int n = triangle.size();
    if (n == 0) {
        return 0;
    }
    vector<int> dp(triangle[n - 1]);
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < triangle[i].size(); j++) {
            dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
        }
    }
    return dp[0];
}
