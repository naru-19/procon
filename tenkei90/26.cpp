#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep2(i, j, n) for (ll i = j; i < n; ++i)
#define Sort(a) sort(a.begin(), a.end())
#define Sortr(a) sort(a.rbegin(), a.rend())
using ll = long long;
#define INF 1001001001001001000

/*
できること:無向木において、2点間の距離をO(NlogN)で求めることができる。
また、任意の2点の最近共通祖先(lca)をO(NlogN)で求めることができる
*/
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
  ll n;
  cin >> n;
  Tree tree(n);
  rep(i, n - 1) {
    ll a, b;
    cin >> a >> b, a--, b--;
    tree.add_edge(a, b);
  }
  tree.build(0);
  map<ll, ll> depth2count;
  ll max_depth = 0;
  rep(i, n) {
    depth2count[tree.depth[i]]++;
    max_depth = max(max_depth, tree.depth[i]);
  }
  vector<vector<ll>> dp(n + 1, vector<ll>(2));
  // 深さ０を取るか取らないか
  dp[0][0] = 0;
  dp[0][1] = 1;
  ll d;  //深さdは必ずとる
  rep2(i, 1, max_depth + 1) {
    dp[i][1] = dp[i - 1][0] + depth2count[i];
    if (dp[i][1] >= n / 2) {
      d = i;
    }
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
  }
  set<ll> ans;
  ll tmp = dp[d][1];
  ll tmp_depth = d;
  for (ll depth = d; depth >= 0; depth--) {
    if (depth == d) {
      ans.insert(depth);
    } else {
      if (tmp - depth2count[tmp_depth] == dp[depth][1] &&
          tmp_depth - depth > 1) {
        ans.insert(depth);
        tmp -= depth2count[tmp_depth];
        tmp_depth = depth;
      }
    }
  }
  ll c = 0;
  rep(i, n) {
    if (ans.count(tree.depth[i]) > 0 && c < n / 2) {
      cout << i + 1 << " ";
      c++;
    }
  }
}