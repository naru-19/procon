#include <bits/stdc++.h>
using ll = long long;
using namespace std;

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

void testTree() {
  ll n = 5;
  /*
  0[1[2,3],4]
  ↓こんな感じの木
    2-1-0-4
      |
      3
  */
  Tree tree(n);
  tree.add_edge(0, 1);
  tree.add_edge(2, 1);
  tree.add_edge(0, 4);
  tree.add_edge(1, 3);
  // root=0
  tree.build(0);
  cout << tree.lca(0, 3) << ": ans=0" << endl;
  cout << tree.lca(2, 4) << ": ans=0" << endl;
  cout << tree.lca(2, 3) << ": ans=1" << endl;
  cout << tree.dist(2, 4) << ": ans=3" << endl;
  ll diameter = tree.get_diameter().first;
  cout << "tree diameter is " << diameter << "(ans=3)" << endl;
}

int main() { testTree(); }
