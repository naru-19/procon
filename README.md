# procon

- [データ構造](#データ構造)

# データ構造

- [1.Tree](#1.Tree)
- [2.Dijkstra](#2.Dijkstra) (データ構造ではないが...)
- [3.SCC](#3.SCC)

## 1.Tree

シンプルな木(n 頂点全てが連結で、無向グラフ、辺の重みは全て 1)<br>
↓ サンプルコード

```c++
  /*
  0[1[2,3],4]
  ↓こんな感じの木
    2-1-0-4
      |
      3
  */
  ll n = 5;
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
```

## 2.Dijkstra

無向グラフ、有向グラフどちらにも対応している。↓ サンプル

```c++
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
```

_output_

```
0->3までの最短距離=2
経路3<-2<-0
```

## 3.SCC

有向グラフを強連結成分分解する。また、その後にできた dag を取得可能。<br>
↓ サンプルコード

```cpp
int main(){
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
  solver.build();
  for (ll i = 0; i < solver.group.size(); i++) {
    printf("group%lldの構成要素", i);
    for (auto node : solver.group[i]) {
      cout << node + 1 << " ";
    }
    cout << "" << endl;
  }
  cout << "-----DAG-----" << endl;
  for (ll i = 0; i < solver.group.size(); i++) {
    for (auto next : solver.dag[i]) {
      cout << i << "->" << next << endl;
    }
  }
}
```

入力`8 10 1 2 2 3 3 1 3 4 4 5 5 6 6 4 7 8 8 7 8 7`に対して出力は

```
group0の構成要素7 8
group1の構成要素1 3 2
group2の構成要素4 6 5
-----DAG-----
1->2
```

[例題](https://atcoder.jp/contests/typical90/tasks/typical90_u)

# Others

- [1.TernarySearch](#1.TernarySearch)

## 1.TernarySearch

三分探索<br>
↓arc054 の例

```c++
  ld p;
  cin >> p;
  auto f = [&](ld x) { return x + p / (pow(2, x / 1.5)); };
  auto judge = [](ld l, ld r) {
    if (l + pow(10, -8) < r) return true;
    return false;
  };
  TernarySearchSolver<ld, ld, decltype(f), decltype(judge)> ts(f, judge);
  auto [l, r] = ts.solveminimum(0, p);
  cout << fixed << setprecision(10) << f(l);
```

> **Warning**<br>
> 探索範囲が整数の場合、judge 内 if の条件が(r-l>2)になることに注意する
