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
int main() {
  ll n, k, p;
  cin >> n >> k >> p;
  vector<ll> g1(n / 2);
  vector<ll> g2(n - n / 2);
  rep(i, n) {
    if (i < n / 2) {
      cin >> g1[i];
    } else {
      cin >> g2[i - n / 2];
    }
  }
  map<ll, vector<ll>> sum1, sum2;
  ll ans = 0;
  for (ll bit = 0; bit < (1 << ll(n / 2)); bit++) {
    ll counter = 0;
    ll tmp_value = 0;
    rep(i, n / 2) {
      if (bit & (1 << i)) {
        counter++;
        tmp_value += g1[i];
      }
    }
    if (tmp_value <= p) {
      sum1[counter].push_back(tmp_value);
    }
  }
  for (ll bit = 0; bit < (1 << ll(n - n / 2)); bit++) {
    ll counter = 0;
    ll tmp_value = 0;
    rep(i, n - n / 2) {
      if (bit & (1 << i)) {
        counter++;
        tmp_value += g2[i];
      }
    }
    if (tmp_value <= p) {
      sum2[counter].push_back(tmp_value);
    }
  }
  rep(i, k + 1) {
    Sort(sum1[i]);
    Sort(sum2[i]);
  }
  rep(c1, k + 1) {
    ll c2 = k - c1;
    for (auto sum : sum1[c1]) {
      ll nokori = p - sum;
      auto itr = upper_bound(sum2[c2].begin(), sum2[c2].end(), nokori);
      ll idx;
      if (itr == sum2[c2].begin()) continue;
      if (itr == sum2[c2].end()) {
        idx = sum2[c2].size();
      } else {
        idx = distance(sum2[c2].begin(), itr);
      }
      ans += idx;
    }
  }

  cout << ans << endl;
}