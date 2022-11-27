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
struct _edge {
  ll next;
  ll cost;
};
/*無向木*/
struct Tree {
  /*
  参考にした実装:https://algo-logic.info/lca/
  */
  ll v; /*頂点数*/
  vector<vector<ll>> parent;
  vector<vector<_edge>> edges;
  vector<ll> depth;
  ll root;
  ll cost = 1;
  void init(ll n) {
    edges.resize(n);
    depth.resize(n);
  }
  Tree(ll n) {
    v = n;
    init(n);
  }
  void add_edge(ll u, ll v) {
    _edge e;
    e.next = v;
    e.cost = cost;
    edges[u].push_back(e);
    e.next = u;
    e.cost = cost;
    edges[v].push_back(e);
  }
  void build(ll _root
             /*各頂点の2^k個先の親とdepthを計算する,
             計算量はO(NlogN),
             頂点のdepth=0,parent=-1*/
  ) {
    root = _root;
    ll k = 1;
    while ((1 << k) < v) k++;
    parent.assign(k, vector<ll>(v, -1));
    // 前処理
    // 根からの深さと1つ親の頂点を求める
    // prents[k][v]:= vの2^k個先の親,k=0で一個上に注意
    parent[0][root] = -1;
    depth[root] = 0;
    deque<ll> q;
    q.push_back(root);
    while (q.size()) {
      ll tmp = q.front();
      q.pop_front();
      for (auto e : edges[tmp]) {
        ll child = e.next;
        if (child == parent[0][tmp]) continue;
        parent[0][child] = tmp;
        depth[child] = depth[tmp] + 1;
        q.push_back(child);
      }
    }
    for (ll _k = 0; _k + 1 < k; _k++) {
      for (ll i = 0; i < v; i++) {
        if (parent[_k][i] < 0) {
          parent[_k + 1][i] = -1;
        } else {
          parent[_k + 1][i] = parent[_k][parent[_k][i]];
        }
      }
    }
  }
  ll lca(ll u, ll v) {
    if (depth[u] < depth[v]) swap(u, v);
    ll k = parent.size();
    // LCAまでの距離
    for (ll _k = 0; _k < k; _k++) {
      if ((depth[u] - depth[v]) >> _k & 1) {
        u = parent[_k][u];
      }
    }
    if (u == v) return u;
    for (ll _k = k - 1; _k >= 0; _k--) {
      if (parent[_k][u] != parent[_k][v]) {
        u = parent[_k][u];
        v = parent[_k][v];
      }
    }
    return parent[0][u];
  }
  ll dist(ll u, ll v) {
    ll _lca = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[_lca];
  }
  pair<ll, pair<ll, ll>> get_diameter() {
    /*
    木の直径を求めるプログラムでO(N)
    戻り値は [直径,[端点1,端点2]]
    */
    vector<ll> seen(v);
    deque<pair<ll, ll>> q;
    //  端点1を見つける
    ll edge_node1 = 0, max_depth = 0;
    for (ll i = 0; i < v; i++) {
      if (max_depth < depth[i]) {
        max_depth = depth[i];
        edge_node1 = i;
      }
    }
    ll diameter = 0;
    ll edge_node2 = edge_node1;
    q.push_back({edge_node1, 0});
    while (q.size()) {
      auto [tmp, d] = q.front();
      q.pop_front();
      for (auto e : edges[tmp]) {
        if (seen[e.next] == 1) continue;
        seen[e.next] = 1;
        if (diameter < d + 1) {
          diameter = d + 1;
          edge_node2 = e.next;
        }
        q.push_back({e.next, d + 1});
      }
    }
    return {diameter, {edge_node1, edge_node2}};
  }
};

int main() {
  // treeである
  ll n;
  cin >> n;
  Tree tree(n);
  rep(i, n - 1) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;
    tree.add_edge(u, v);
  }
  tree.build(0);
  ll ans = tree.get_diameter().first;
  cout << ans + 1 << endl;
}