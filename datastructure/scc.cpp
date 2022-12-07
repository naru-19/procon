#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rep2(i, x, n) for (int i = x; i < n; ++i)
#define Sort(a) sort(a.begin(), a.end())
using ll = long long;

#define DEBUG_ON

struct SccSolver {
  ll n;
  vector<vector<ll> > g, rev;
  vector<ll> _seen1, _seen2;
  vector<ll> nodeId;  //  帰りがけの順番 -> 頂点番号
  vector<vector<ll> > group;
  vector<set<ll> > dag;
  SccSolver(ll _n, vector<vector<ll> >& _g, vector<vector<ll> >& _rev) {
    n = _n;
    g = _g;
    rev = _rev;
    _seen1.resize(n);
    _seen2.resize(n);
    nodeId.resize(n);
  }
  // 帰りがけ順dfs
  void _postdfs(ll& id, ll tmp) {
    _seen1[tmp] = 1;
    for (auto next : g[tmp]) {
      if (_seen1[next]) continue;
      _postdfs(id, next);
    }
    nodeId[id] = tmp;
    id++;
  }
  void _dfs(vector<ll>& scc, ll tmp) {
    _seen2[tmp] = 1;
    scc.push_back(tmp);
    for (auto next : rev[tmp]) {
      if (_seen2[next]) continue;
      _dfs(scc, next);
    }
  }
  void solve() {
    // 1回目のdfs
    ll id = 0;
    for (ll i = 0; i < n; i++) {
      if (_seen1[i]) continue;
      _postdfs(id, i);
    }
    // 2回目のdfs
    for (ll i = n - 1; i >= 0; i--) {
      ll node = nodeId[i];
      if (_seen2[node]) continue;
      vector<ll> scc;
      _dfs(scc, node);
      group.push_back(scc);
    }
  }
  // groupからdagを形成, dagはsetであることに注意
  void build() {
    if (group.size() == 0) {
      cout << "please run SccSolver.solve() before build." << endl;
      return;
    }
    dag.resize(group.size());
    vector<ll> mapping(n);  // 頂点番号 -> group番号
    for (ll i = 0; i < group.size(); i++) {
      for (auto node : group[i]) {
        mapping[node] = i;
      }
    }
    for (ll i = 0; i < n; i++) {
      for (auto next : g[i]) {
        if (mapping[i] != mapping[next]) {
          dag[mapping[i]].insert(mapping[next]);
        }
      }
    }
    mapping.clear();
  }
};

void tenkei21() {
  ll n, m;
  cin >> n >> m;
  vector<vector<ll> > g(n);
  vector<vector<ll> > rev(n);
  rep(i, m) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    g[a].push_back(b);
    rev[b].push_back(a);
  }
  SccSolver solver = SccSolver(n, g, rev);
  solver.solve();
  ll ans = 0;
  for (auto scc : solver.group) {
    ll size = scc.size();
    ans += (size - 1) * size / 2;
  }
  cout << ans << endl;
  cout << "-----↓おまけ-----" << endl;
  solver.build();
  for (ll i = 0; i < solver.group.size(); i++) {
    for (auto next : solver.dag[i]) {
      cout << i << " " << next << endl;
    }
  }
  //入力:8 10 1 2 2 3 3 1 3 4 4 5 5 6 6 4 7 8 8 7 8 7
  //出力が[1 2]であればok,(0は今日連結成分分解をすると頂点だけ(7,8)になる)
}

int main() { tenkei21(); }