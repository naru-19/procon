#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define Sort(a) sort(a.begin(), a.end())
using ll = long long;
#define DEBUG_ON
#define INF 100100100100100
ll dx[] = {-1, 1, 0, 0};
ll dy[] = {0, 0, -1, 1};

vector<vector<ll>> seen(17, vector<ll>(17));
ll dfs(ll sx, ll sy, ll x, ll y, vector<string>& g, ll h, ll w) {
  if (x == sx && y == sy && seen[y][x] == 1) return 0;
  seen[y][x] = 1;
  ll ret = -INF;
  rep(i, 4) {
    ll nx = x + dx[i], ny = y + dy[i];
    if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
    if (seen[ny][nx] == 1) {
      if (nx != sx || ny != sy) continue;
    }
    if (g[ny][nx] == '#') continue;
    ll v = dfs(sx, sy, nx, ny, g, h, w);
    ret = max(ret, v + 1);
  }
  seen[y][x] = 0;
  return ret;
}

int main() {
  ll h, w;
  cin >> h >> w;
  vector<string> g(h);
  rep(i, h) { cin >> g[i]; }
  ll ans = -1;
  rep(i, h) {
    rep(j, w) {
      if (g[i][j] == '#') continue;
      ans = max(ans, dfs(j, i, j, i, g, h, w));
    }
  }
  if (ans <= 3)
    ans = -1;  // ans<=2で良い(行って帰るだけの2or4以上or-1しか取り得ない)
  cout << ans << endl;
}