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
      if (x > y) swap(x, y);
      data[x] += data[y];
      data[y] = x;
      return true;
    }
  }

  bool is_same(int x, int y) { return find(x) == find(y); }

  int size(int x) { return -data[find(x)]; }
};
void process1(UnionFind &uf, vector<vector<pair<ll, ll>>> &g) {
  ll x, y, v;
  cin >> x >> y >> v;
  x--, y--;
  if (y != x + 1) {
    cout << "error" << endl;
    return;
  }
  if (x % 2 == 0) {
    g[x].push_back({y, -v});
  } else {
    g[x].push_back({y, v});
  }
  uf.unite(x, y);
}
void process2(vector<pair<ll, pair<ll, ll>>> &ans, UnionFind &uf) {
  ll x, y, v;
  cin >> x >> y >> v;
  x--, y--;
  if (uf.is_same(x, y)) {
    ans.push_back({x, {y, v}});
  } else
    ans.push_back({-1, {-1, v}});
}

int main() {
  ll n, q;
  cin >> n >> q;
  string amb = "Ambiguous";
  vector<pair<ll, pair<ll, ll>>> ans;
  vector<ll> a(n);
  UnionFind uf(n);
  vector<vector<pair<ll, ll>>> g(n);
  for (ll i = 0; i < q; i++) {
    ll t;
    cin >> t;
    if (t == 0) {
      process1(uf, g);
    } else {
      process2(ans, uf);
    }
  }
  set<ll> roots;
  rep(i, n) { roots.insert(uf.find(i)); }
  // 連結じゃないパターンもある。
  vector<ll> d(n);
  set<ll> seen;
  for (auto root : roots) {
    deque<ll> dq;
    dq.push_back(root);
    seen.insert(root);
    while (dq.size()) {
      ll tmp = dq.front();
      dq.pop_front();
      for (auto x : g[tmp]) {
        auto [next, cost] = x;
        if (seen.count(next) > 0) continue;
        seen.insert(next);
        d[next] = cost + d[tmp];
        dq.push_back(next);
      }
    }
  }
  for (auto p : ans) {
    if (p.first == -1) {
      cout << amb << endl;
    } else {
      ll x = p.first;
      auto [y, v] = p.second;
      ll _ans;
      if (x % 2 == 0) {
        ll diff = d[x] - d[y];
        _ans = v - diff;
      } else {
        ll diff = d[x] - d[y];
        _ans = -v - diff;
      }
      if (y % 2 == 1) _ans *= -1;
      cout << _ans << endl;
    }
  }
  return 0;
}
