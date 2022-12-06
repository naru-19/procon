#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rep2(i, j, n) for (ll i = j; i < n; ++i)
#define Sort(a) sort(a.begin(), a.end())
#define Sortr(a) sort(a.rbegin(), a.rend())
using ll = unsigned long long;
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
void solve1(ll l, ll r) {
  ll ans = 0;
  rep2(i, l, r + 1) {
    ans += i * (to_string(i).length());
    ans %= MOD;
  }
  cout << ans << endl;
}

void solve2(ll l, ll r) {
  ll ketal = log10(l);
  ll ketar = log10(r);
  // using mint = atcoder::modint1000000007;
  if (ketal != ketar) {
    ll ans = 0;
    ll rangel = (pow(10, ketal + 1) - l);
    rangel %= MOD;
    rangel *= (pow(10, ketal + 1) - 1 + l);
    rangel %= MOD;
    rangel *= modinv(2, MOD);
    rangel %= MOD;
    ll ranger = (r - pow(10, ketar) + 1);  // * (r + pow(10, ketar)) / 2;
    ranger %= MOD;
    ranger *= (r + pow(10, ketar));
    ranger %= MOD;
    ranger *= modinv(2, MOD);
    ranger %= MOD;
    ans += (rangel) * (ketal + 1);
    ans %= MOD;
    ans += (ranger) * (ketar + 1);
    ans %= MOD;
    // cout << ans << endl;
    rep2(i, ketal + 1, ketar) {
      ll tmp = (i + 1) * ((pow2(10, i + 1) + MOD - pow2(10, i)) + MOD);
      tmp += MOD;
      tmp %= MOD;
      tmp *= (pow2(10, i + 1) + MOD - 1 + pow2(10, i) + MOD);
      tmp %= MOD;
      tmp *= modinv(2, MOD);
      tmp %= MOD;
      ans += tmp;
      ans %= MOD;
      // cout << i << "," << ans << endl;
    }
    cout << ans << endl;
  } else {
    ll ans = (ketar + 1) * (r - l + 1);
    ans %= MOD;
    ans *= (r + l);
    ans %= MOD;
    ans *= modinv(2, MOD);
    ans %= MOD;
    cout << ans << endl;
  }
}
using mint = atcoder::modint1000000007;
void solve3(ll l, ll r) {
  ll ketal = to_string(l).length() - 1;
  ll ketar = to_string(r).length() - 1;
  if (ketal != ketar) {
    mint mr = r;
    mint ml = l;
    mint ten = 10;
    mint rangel = (ten.pow(ketal + 1) - ml) * (ten.pow(ketal + 1) - 1 + ml) / 2;
    mint ranger = (mr - ten.pow(ketar) + 1) * (mr + ten.pow(ketar)) / 2;
    mint ans = (rangel) * (ketal + 1);
    ans += (ranger) * (ketar + 1);

    rep2(i, ketal + 1, ketar) {
      mint mi = i;
      mint tmp = (mi + 1) * ((ten.pow(i + 1) - ten.pow(i))) *
                 (ten.pow(i + 1) - 1 + ten.pow(i)) / 2;

      ans += tmp;
      // cout << i << "," << ans << endl;
    }
    cout << ans.val() << endl;
  } else {
    mint mr = r;
    mint ml = l;
    mint ans = (ketar + 1) * (mr - ml + 1) * (mr + ml) / 2;
    cout << ans.val() << endl;
  }
}

int main() {
  ll l, r;
  cin >> l >> r;
  // solve1(l, r);
  solve3(l, r);
}
