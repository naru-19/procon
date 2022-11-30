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
template <class T>
inline bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T>
inline bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
struct edge {
  ll to, cost;
};
struct graph {
  ll V;
  vector<vector<edge>> G;
  vector<ll> d;
  vector<ll> prev;
  bool directed = false;
  graph(ll n) { init(n); }
  graph(ll n, bool directed) : directed(directed) { init(n); }
  void init(ll n) {
    V = n;
    G.resize(V);
    prev.resize(V);
    d.resize(V);
    rep(i, V) { d[i] = INF; }
  }
  void add_edge(ll s, ll t, ll cost) {
    edge e;
    e.to = t, e.cost = cost;
    G[s].push_back(e);
    if (!directed) {
      edge e;
      e.to = s, e.cost = cost;
      G[t].push_back(e);
    }
  }

  void dij(ll s) {
    rep(i, V) { d[i] = INF; }
    d[s] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
        que;
    que.push(pair<ll, ll>(0, s));
    while (!que.empty()) {
      pair<ll, ll> p = que.top();
      que.pop();
      ll v = p.second;
      if (d[v] < p.first) continue;
      for (auto e : G[v]) {
        if (d[e.to] > d[v] + e.cost) {
          d[e.to] = d[v] + e.cost;
          prev[e.to] = v;
          que.push({d[e.to], e.to});
        }
      }
    }
  }
};
void keta(double x) { cout << fixed << setprecision(10) << x; }
string num2str(ll x) {
  string s;
  ostringstream oss;
  oss << x << flush;
  s = oss.str();
  return s;
}
#define DEBUG_ON

ll modinv(ll a, ll MOD) {
  ll m = MOD;
  ll b = m, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    a -= t * b;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  u %= m;
  if (u < 0) u += m;
  return u;
}
class UnionFind {
 private:
  //   int* data;
  vector<ll> data;

 public:
  UnionFind(int n = 0) : data(n, -1) {}

  int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
      return false;
    else {
      if (data[x] > data[y]) swap(x, y);
      data[x] += data[y];
      data[y] = x;
      return true;
    }
  }

  bool is_same(int x, int y) { return find(x) == find(y); }

  int size(int x) { return -data[find(x)]; }
};
ll MOD = 1000000007;
// ll MOD=998244353;
long long pow2(long long x, long long n) {
  long long ret = 1;
  while (n > 0) {
    if (n & 1)
      ret = ret * x % MOD;  // n の最下位bitが 1 ならば x^(2^i) をかける
    x = x * x % MOD;
    n >>= 1;  // n を1bit 左にずらす
  }
  return ret;
}

ll ncr(ll n, ll r) {
  ll ans = 1;
  rep(i, r) {
    ans = ans * (n - i);
    ans *= pow2(i + 1, MOD - 2);
    ans %= MOD;
  }
  return ans;
}
// ll h, w;
// ll n;
// ll n;
// cin>>n;
// string s(n,'');
ll dx[] = {1, -1, 0, 0};
ll dy[] = {0, 0, -1, 1};
int main() {
  ll h, w;
  cin >> h >> w;
  ll rs, cs, rt, ct;
  cin >> rs >> cs >> rt >> ct;
  rs--, cs--, rt--, ct--;
  vector<string> g(h);
  rep(i, h) { cin >> g[i]; }
  vector<vector<vector<ll>>> dp(h, vector<vector<ll>>(w, vector<ll>(5, INF)));
  rep(i, 5) { dp[rs][cs][i] = 0; }
  deque<pair<pair<ll, ll>, ll>> q;
  q.push_back({{rs, cs}, 4});
  while (q.size()) {
    auto [pos, dir] = q.front();
    auto [y, x] = pos;
    q.pop_front();
    rep(i, 4) {
      ll nx = x + dx[i];
      ll ny = y + dy[i];
      if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
      if (g[ny][nx] == '#') continue;
      if (dir == i || dir == 4) {
        if (dp[ny][nx][i] > dp[y][x][dir]) {
          dp[ny][nx][i] = dp[y][x][dir];
          q.push_front({{ny, nx}, i});
        }
      } else {
        if (dp[ny][nx][i] > dp[y][x][dir] + 1) {
          dp[ny][nx][i] = dp[y][x][dir] + 1;
          q.push_back({{ny, nx}, i});
        }
      }
    }
  }
  ll ans = INF;
  rep(i, 4) { ans = min(ans, dp[rt][ct][i]); }
  cout << ans << endl;
}