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
int main() {
  ll n, m;
  cin >> n >> m;
  graph tok(n);
  graph ntok(n);
  rep(i, m) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    tok.add_edge(a, b, c);
    ntok.add_edge(a, b, c);
  }
  tok.dij(0);
  ntok.dij(n - 1);

  rep(i, n) { cout << tok.d[i] + ntok.d[i] << endl; }
}