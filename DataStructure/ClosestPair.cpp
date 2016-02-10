#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long llong;
const int maxn = 200010;
const double INF = 4e18;

struct Point {
    double x, y;
};
Point s[maxn];
Point tmp[maxn];

bool cmpY(Point a, Point b) { return a.y < b.y; }

void merge(int l, int m, int r) {
    int tm = m, tl = l, idx = 0;
    while (l < tm  && m < r) {
        if (s[l].y <= s[m].y) tmp[idx++] = s[l++];
        else tmp[idx++] = s[m++];
    }
    while (l < tm) tmp[idx++] = s[l++];
    while (m < r) tmp[idx++] = s[m++];
    for (int i=0; i<idx; i++) s[i+tl] = tmp[i];
}

double ClosestPair(int l, int r) {
    double d = INF;
    if (r == l) return d;
    int mid = (l + r) >> 1;
    double X = s[mid].x; // store X before recursive process, cuz they will rearrange Points.
    d = min(ClosestPair(l, mid), ClosestPair(mid+1, r));
    merge(l, mid+1, r+1);

    int idx = 0;
    for (int i=l; i<=r; i++) {
        if (fabs(s[i].x - X) >= d) continue;
        for (int j=0; j<idx; j++) {
            double dx = s[i].x - tmp[idx - 1 - j].x;
            double dy = s[i].y - tmp[idx - 1 - j].y;
            if (dy >= d) break;
            d = min(d, sqrt(dx*dx + dy*dy));
        }
        tmp[idx++] = s[i];
    }
    return d;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        s[i] = Point{x, y};
    }
    auto cmpx = [](Point a, Point b) { return a.x < b.x; };
    sort(s, s + n, cmpx);
    printf("%lf\n",ClosestPair(0, n-1));
    return 0;
}
