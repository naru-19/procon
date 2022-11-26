#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
template <class M /*l,rの型*/, class R /*関数fの返り値型*/,
          class F = std::function<R(M)>,
          class J = std::function<bool(M, M)> /*継続条件*/>
class TernarySearchSolver {
 private:
  F f;
  J judge;

 public:
  TernarySearchSolver(F &f, J &judge) : f(f), judge(judge) {}
  pair<M, M> solveminimum(M l, M r) {
    while (judge(l, r)) {
      M c1 = l + (r - l) / M(3);
      M c2 = r - (r - l) / M(3);
      if (f(c1) > f(c2))
        l = c1;
      else
        r = c2;
    }
    return {l, r};
  }
  pair<M, M> solvemaximum(M l, M r) {
    while (judge(l, r)) {
      M c1 = l + (r - l) / M(3);
      M c2 = r - (r - l) / M(3);
      if (f(c1) < f(c2))
        l = c1;
      else
        r = c2;
    }
    return {l, r};
  }
};

void testMin() {
  ll a = 2, b = 3;
  auto f = [&](long double x) { return (x - a) * (x - b); };
  auto judge = [](long double l, long double r) {
    /* もしl,rがlong longなら終了条件はr-l>2->true,else falseになる
      if(r-l>2)return true;
      else reutrn false;
    */
    if (l + pow(10, -8) < r) return true;
    return false;
  };
  // fを最小にするのはx=2.5
  TernarySearchSolver<long double, long double, decltype(f), decltype(judge)>
      ts(f, judge);
  auto [l, r] = ts.solveminimum(-5, 100);
  cout << l << "," << r << ": ←2.5ならokでminは," << f(l) << endl;
}
void testMax() {
  ll a = 2, b = 3;
  auto f = [&](long double x) { return -(x - a) * (x - b); };
  auto judge = [](long double l, long double r) {
    /* もしl,rがlong longなら終了条件はr-l>2->true,else falseになる
      if(r-l>2)return true;
      else reutrn false;
    */
    if (l + pow(10, -8) < r) return true;
    return false;
  };
  // fを最小にするのはx=2.5
  TernarySearchSolver<long double, long double, decltype(f), decltype(judge)>
      ts(f, judge);
  auto [l, r] = ts.solvemaximum(-5, 100);
  cout << l << "," << r << ": ←2.5ならokでmaxは," << f(l) << endl;
}
void testMax2() {
  auto f = [&](long double x) { return -pow(2.5, x) * (x - 3) * 10; };
  auto judge = [](long double l, long double r) {
    /* もしl,rがlong longなら終了条件はr-l>2->true,else falseになる↓
      if(r-l>2)return true;
      else reutrn false;
    */
    if (l + pow(10, -8) < r) return true;
    return false;
  };
  // fを最小にするのはx=2.5
  TernarySearchSolver<long double, long double, decltype(f), decltype(judge)>
      ts(f, judge);
  auto [l, r] = ts.solvemaximum(-5, 100);
  cout << l << "," << r << ": ←1.90864ならokでmaxは," << f(l) << endl;
}

void arc054() {
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
}
int main() {
  testMin();
  testMax();
  testMax2();
}