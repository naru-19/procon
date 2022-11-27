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

/*https://algo-logic.info/dijkstra/を参考に実装*/
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
void abc035() {
  ll n, m, t;
  cin >> n >> m >> t;
  graph iki(n, true);
  graph kaeri(n, true);
  vector<ll> a(n);
  rep(i, n) { cin >> a[i]; }
  rep(i, m) {
    ll _a, _b, _c;
    cin >> _a >> _b >> _c;
    _a--;
    _b--;
    iki.add_edge(_a, _b, _c);
    kaeri.add_edge(_b, _a, _c);
  }
  iki.dij(0);
  kaeri.dij(0);
  ll ans = 0;
  rep(i, n) {
    if (i == 0) continue;
    ll cost = iki.d[i] + kaeri.d[i];
    if (cost > t) continue;
    ans = max(ans, (t - cost) * a[i]);
  }
  ans = max(ans, a[0] * t);
  cout << ans << endl;
}
void testPath() {
  /*無向グラフ*/
  ll n = 5;
  graph g(n);
  g.add_edge(0, 1, 2);
  g.add_edge(1, 3, 1);
  g.add_edge(0, 3, 4);
  g.add_edge(2, 4, 1);
  g.add_edge(0, 2, 1);
  g.add_edge(2, 3, 1);
  g.dij(0);
  cout << "0->3までの最短距離=" << g.d[3] << endl;
  cout << "経路3<-";
  ll tmp = 3;
  while (g.prev[tmp] != 0) {
    cout << g.prev[tmp] << "<-";
    tmp = g.prev[tmp];
  }
  cout << "0" << endl;
}

int main() {
  // abc035();
  testPath();
}