#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; ++i)
#define Sort(a) sort(a.begin(), a.end())
using ll = unsigned long long;

#define DEBUG_ON

int main() {
  ll a, b;
  cin >> a >> b;
  ll g = gcd(a, b);
  ll lim = pow(10, 18);
  if (a / g > lim / b) {
    cout << "Large" << endl;
  } else {
    cout << (a / g) * b << endl;
  }
}