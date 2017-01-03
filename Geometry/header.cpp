#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const double EPS = 1e-10;

struct P {
    double x, y;
    P() {};
    P(double a, double b) : x(a), y(b) {}

    double add(double a, double b) { // add operation consider eps
        if (fabs(a + b) < EPS * (abs(a) + abs(b))) return 0;
        return a + b;
    }
    P operator + (P p) { return P(add(x, p.x), add(y, p.y)); }
    P operator - (P p) { return P(add(x, -p.x), add(y, -p.y)); }
    P operator * (double d) { return P(x * d, y * d); }
    double dot(P p) { return add(x * p.x, y * p.y); }
    double det(P p) { return add(x * p.y, -y * p.x); }
};

bool on_seg(P p1, P p2, P q) { // detect whether q is on segment p1-p2
    return (p1 - q).det(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

P intersection(P p1, P p2, P q1, P q2) {
    return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
}

bool is_intersect(P p1, P p2, P q1, P q2) {
  return (p1 - p2).det(q1 - q2) != 0;
}

class ConvexHull {
  public:

  static bool cmp_x(const P& p, const P& q) {
    if (p.x != q.x) return p.x < q.x;
    return p.y < q.y;
  }

  vector<P> convex_hull(vector<P> ps, int n) {
    sort(ps.begin(), ps.end(), cmp_x);
    int k = 0;
    vector<P> qs(n*2);
    // construct upside
    for (int i=0; i<n; i++) {
      while (k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
      qs[k++] = ps[i];
    }

    // custruct downside
    for (int i=n-2, t=k; i>=0; i--) {
      while (k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
      qs[k++] = ps[i];
    }
    qs.resize(k-1);
    return qs;
  }
};
