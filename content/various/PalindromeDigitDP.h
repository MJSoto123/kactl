/**
 * Author: Juanma
 * Description: Counts palindromic integers in [0, X] using Digit DP.
 * Builds the number digit by digit and checks symmetric positions
 * using curr[]. Leading zeros are ignored, and memoized results
 * are reused only when the current number is smaller than X.
 * Usage: solve(R) - solve(L - 1)
 * Time: O(D^2 * 10), where D is the number of digits.
 */

const int max_num_digits = 20;
int high[20], curr[20];
ll dp[20][20][2][2];

void init() {
    memset(dp, -1, sizeof(dp));
}

ll dfs(int start, int cur, int palin, int smaller) {
    if(cur < 0) {
        return palin;
    }

    if(smaller && dp[start][cur][palin][smaller] != -1) {
        return dp[start][cur][palin][smaller];
    }

    int mx_digit = 9;
    if(!smaller) mx_digit = high[cur];

    ll ans = 0;
    for(int xth_digit = 0; xth_digit <= mx_digit; xth_digit++) {
        curr[cur] = xth_digit;

        if(start == cur && xth_digit == 0) {
            ans += dfs(
                start - 1,
                cur - 1,
                palin,
                smaller || high[cur] > xth_digit
            );
        }
        else if(palin && cur < (start + 1) / 2) {
            ans += dfs(
                start,
                cur - 1,
                curr[start - cur] == xth_digit,
                smaller || high[cur] > xth_digit
            );
        }
        else {
            ans += dfs(
                start,
                cur - 1,
                palin,
                smaller || high[cur] > xth_digit
            );
        }
    }

    return dp[start][cur][palin][smaller] = ans;
}

ll solve(ll val) {
    if(val < 0) return 0;

    init();
    int i = 0;
    while(val) {
        high[i++] = val % 10;
        val /= 10;
    }
    return dfs(i - 1, i - 1, 1, 0);
}
