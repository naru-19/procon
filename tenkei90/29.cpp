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
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T>
inline bool chmax(T& a, T b) {
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
template <class M, class E, class F = std::function<M(M, M)>,
          class A = std::function<M(M, E)>, class G = std::function<E(E, E)>>
class LazySegmentTree {
 private:
  std::vector<M> data;
  std::vector<E> lazy;
  F op;
  G cp;
  A act;
  M e;
  E id;
  int sz;

  void propagate(int index) {
    if (lazy[index] == id) return;
    lazy[index << 1] = cp(lazy[index << 1], lazy[index]);
    lazy[(index << 1) | 1] = cp(lazy[(index << 1) | 1], lazy[index]);
    data[index] = act(data[index], lazy[index]);
    lazy[index] = id;
  }

  void propagate_topdown(int index) {
    int h = 0;
    for (int i = 1; i < index; i <<= 1) ++h;
    for (int i = h; i; i--) propagate(index >> i);
  }

  void recalc(int index) {
    while (index >>= 1)
      data[index] = op(act(data[index << 1], lazy[index << 1]),
                       act(data[(index << 1) | 1], lazy[(index << 1) | 1]));
  }

 public:
  LazySegmentTree(int sz, const F& op, const A& act, const G& cp, const M& e,
                  const E& id)
      : op(op),
        act(act),
        cp(cp),
        e(e),
        id(id),
        sz(sz),
        data(sz << 1, e),
        lazy(sz << 1, id) {}

  LazySegmentTree(const std::vector<M>& v, const F& op, const A& act,
                  const G& cp, const M& e, const E& id)
      : op(op),
        act(act),
        cp(cp),
        e(e),
        id(id),
        sz(v.size()),
        data(v.size() << 1, e),
        lazy(v.size() << 1, id) {
    for (int i = 0; i < sz; i++) {
      data[i + sz] = v[i];
    }

    for (int i = (int)sz - 1; i > 0; i--) {
      data[i] = op(data[i << 1], data[(i << 1) | 1]);
    }
  }

  bool update(int index, const M& x) {
    if (index < 0 || index >= sz) return false;

    index += sz;

    propagate_topdown(index);

    data[index] = x;
    lazy[index] = id;

    recalc(index);

    return true;
  }

  void update(int left, int right, const E& g) {
    if (left < 0) left = 0;
    if (right > sz) right = sz;
    left += sz;
    right += sz;

    propagate_topdown(left);
    propagate_topdown(right - 1);

    for (int l = left, r = right; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        lazy[l] = cp(lazy[l], g);
        ++l;
      }
      if (r & 1) {
        --r;
        lazy[r] = cp(lazy[r], g);
      }
    }

    recalc(left);
    recalc(right - 1);
  }

  M fold(int left, int right) {
    if (left < 0) left = 0;
    if (right > sz) right = sz;
    left += sz;
    right += sz;

    propagate_topdown(left);
    propagate_topdown(right - 1);

    M l = e, r = e;

    for (; left < right; left >>= 1, right >>= 1) {
      if (left & 1) {
        l = op(l, act(data[left], lazy[left]));
        ++left;
      }
      if (right & 1) {
        --right;
        r = op(act(data[right], lazy[right]), r);
      }
    }

    return op(l, r);
  }

  M fold() { return fold(0, sz); }
};
using M = long long;
using E = optional<long long>;

auto op = [](const M& x, const M& y) { return max(x, y); };

auto cp = [](const E& f, const E& g) {
  if (g)
    return g;
  else
    return f;
};

auto act = [](const M& x, const E& f) {
  if (f) return f.value();
  return x;
};
const M e = -INF;      // queryの単位元
const E id = nullopt;  // rangeに適用するものの単位元

int main() {
  ll w, n;
  cin >> w >> n;
  LazySegmentTree<M, E, decltype(op), decltype(act), decltype(cp)> segtree(
      w, op, act, cp, e, id);
  segtree.update(0, w, 0);
  rep(i, n) {
    ll l, r;
    cin >> l >> r;
    l--, r--;
    ll maxv = segtree.fold(l, r + 1);
    segtree.update(l, r + 1, maxv + 1);
    cout << maxv + 1 << endl;
  }
}