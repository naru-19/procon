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
typedef pair<ll, ll> P;
struct graph {
  ll V;
  vector<vector<edge>> G;
  vector<ll> d;
  graph(ll n) { init(n); }
  void init(ll n) {
    V = n;
    G.resize(V);
    d.resize(V);
    rep(i, V) { d[i] = INF; }
  }
  void add_edge(ll s, ll t, ll cost) {
    edge e;
    e.to = t, e.cost = cost;
    G[s].push_back(e);
  }

  void dij(ll s) {
    rep(i, V) { d[i] = INF; }
    d[s] = 0;
    priority_queue<P, vector<P>, greater<P>> que;
    que.push(P(0, s));
    while (!que.empty()) {
      P p = que.top();
      que.pop();
      ll v = p.second;
      if (d[v] < p.first) continue;
      for (auto e : G[v]) {
        if (d[e.to] > d[v] + e.cost) {
          d[e.to] = d[v] + e.cost;
          que.push(P(d[e.to], e.to));
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
      ret = ret * x % MOD;  // n ????????????bit??? 1 ????????? x^(2^i) ????????????
    x = x * x % MOD;
    n >>= 1;  // n ???1bit ???????????????
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
// ????????????????????????????????????????????????????????????????????????

void solve1(ll n, ll q) {
  vector<ll> px(n), py(n);

  vector<ll> corners(4);
  vector<ll> idx(4);
  rep(i, n) {
    cin >> px[i] >> py[i];
    if (px[i] >= 0 && py[i] >= 0) {
      if (corners[0] < abs(px[i]) + abs(py[i])) {
        idx[0] = i;
      }
      corners[0] = max(corners[0], abs(px[i]) + abs(py[i]));
    }
    if (px[i] <= 0 && py[i] >= 0) {
      if (corners[1] < abs(px[i]) + abs(py[i])) {
        idx[1] = i;
      }
      corners[1] = max(corners[1], abs(px[i]) + abs(py[i]));
    }
    if (px[i] <= 0 && py[i] <= 0) {
      if (corners[2] < abs(px[i]) + abs(py[i])) {
        idx[2] = i;
      }
      corners[2] = max(corners[2], abs(px[i]) + abs(py[i]));
    }
    if (px[i] >= 0 && py[i] <= 0) {
      if (corners[3] < abs(px[i]) + abs(py[i])) {
        idx[3] = i;
      }
      corners[3] = max(corners[3], abs(px[i]) + abs(py[i]));
    }
  }
  rep(i, q) {
    ll x;
    cin >> x;
    x--;

    ll ans = -1;
    rep(j, 4) {
      ans = max(ans, abs(px[x] - px[idx[j]]) + abs(py[x] - py[idx[j]]));
    }
    cout << ans << endl;
  }
}

void solve2(ll n, ll q) {
  vector<vector<ll>> px(n, vector<ll>(2));
  rep(i, n) { cin >> px[i][0] >> px[i][1]; }
  vector<vector<ll>> px_rotated(n, vector<ll>(2));
  ll xmin = INF, xmax = -INF, ymin = INF, ymax = -INF;
  rep(i, n) {
    px_rotated[i][0] = (px[i][0] - px[i][1]);
    px_rotated[i][1] = (px[i][0] + px[i][1]);
    xmin = min(xmin, px_rotated[i][0]);
    xmax = max(xmax, px_rotated[i][0]);
    ymin = min(ymin, px_rotated[i][1]);
    ymax = max(ymax, px_rotated[i][1]);
  }
  rep(i, q) {
    ll j;
    cin >> j;
    j--;
    ll ans = max({abs(px_rotated[j][0] - xmin), abs(px_rotated[j][0] - xmax),
                  abs(px_rotated[j][1] - ymin), abs(px_rotated[j][1] - ymax)

    });
    cout << ans << endl;
  }
}

int main() {
  ll n, q;
  cin >> n >> q;
  solve2(n, q);
}