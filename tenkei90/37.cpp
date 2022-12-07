#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep2(i, j, n) for (ll i = j; i < n; ++i)
#define Sort(a) sort(a.begin(), a.end())
#define Sortr(a) sort(a.rbegin(), a.rend())
using ll = long long;
#define tobit(x, i) (((x) >> (i)) & 1)
#define INF 1001001001001001000
#define yes "Yes"
#define no "No"

int main() {
  ll w, n;
  cin >> w >> n;
  vector<vector<ll>> spice(n, vector<ll>(3));
  rep(i, n) { cin >> spice[i][0] >> spice[i][1] >> spice[i][2]; }

  // まずは下限を使ってdpを行う。
  vector<vector<ll>> dp(n + 1, vector<ll>(w + 1, -INF));
  dp[0][0] = 0;
  rep2(i, 1, n + 1) {
    rep(_w, w + 1) {
      dp[i][_w] = max(dp[i - 1][_w], dp[i][_w]);
      if (_w + spice[i - 1][0] > w) continue;
      if (dp[i - 1][_w] == -INF) continue;
      dp[i][_w + spice[i - 1][0]] =
          max(dp[i][_w + spice[i - 1][0]], dp[i - 1][_w] + spice[i - 1][2]);
    }
  }
  // V、下限をVでソート
  vector<vector<ll>> lowerlimit(w + 1, vector<ll>(2));
  rep(i, w + 1) {
    lowerlimit[i][0] = dp[n][i];
    lowerlimit[i][1] = i;
  }
  Sortr(lowerlimit);
  ll ans = -1;
  rep(i, w + 1) {
    // 復元
    ll tmp = lowerlimit[i][0];
    if (tmp == -INF) continue;
    ll l = lowerlimit[i][1];
    ll r = 0;
    for (ll j = n - 1; j >= 0; j--) {
      if (dp[j][l - spice[j][0]] == tmp - spice[j][2]) {
        r += spice[j][1];
        tmp -= spice[j][2];
        l -= spice[j][0];
      }
    }
    if (r >= w) {
      cout << lowerlimit[i][0] << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}