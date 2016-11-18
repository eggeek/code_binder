#include <iostream>
#include <utility>
#include <vector>
using namespace std;
#define MAX_P 100010
typedef pair<int, int> pii;
typedef vector<int> vi;

// solve a*x + b*y = gcd(a, b), if a < 0,
// transform to |a|*(-x) + b*y = gcd(|a|, b)
int extgcd(int a, int b, int& x, int& y) {
  int d = a;
  if (b != 0) {
    d = extgcd(b, a%b, y, x);
    y -= (a/b) * x;
  } else {
    x = 1; y = 0;
  }
  return d;
}

int mod_inverse(int a, int m) {
  int x, y;
  extgcd(a, m, x, y);
  return (m + x % m) % m;
}

// it's CRT when A = {1,...1}
pii linear_congruence(const vi& A, const vi& B, const vi& M) {
  int x = 0, m = 1;
  for (int i=0; i<(int)A.size(); i++) {
    int a = A[i] * m, b = B[i] - A[i] * x, d = __gcd(M[i], a);
    if (b % d != 0) return {0, -1}; // no solution
    int t = b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d);
    x = x + m * t;
    m *= M[i] / d;
  }
  return {x % m, m};
}

int fact[MAX_P];
// factorize n! => a * p^e, return a % p. O(log_p(n))
int mod_fact(int n, int p, int& e) {
  e = 0;
  if (n == 0) return 1;
  // calculate p, 2p, 3p, ...
  int res = mod_fact(n / p, p , e);
  e += n / p;

  // (p-1)! = -1 % mod p
  if (n / p % 2 != 0) return res * (p - fact[n % p]) % p;
  return res * fact[n % p] % p;
}

int mod_comb(int n, int k, int p) {
  if (n < 0 || k < 0 || n < k) return 0;
  int e1, e2, e3;
  int a1 = mod_fact(n, p, e1);
  int a2 = mod_fact(k, p, e2);
  int a3 = mod_fact(n-k, p, e3);
  if (e1 > e2 + e3) return 0;
  return a1 * mod_inverse(a2 * a3 % p, p) % p;
}

int main() {
  return 0;
}
