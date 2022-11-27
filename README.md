# procon

- [データ構造](#データ構造)

# データ構造

- [1.Tree](#1.Tree)

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
