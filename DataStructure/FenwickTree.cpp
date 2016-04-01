#include <cstdio>
using namespace std;
#define N 1000010
#define lowb(x) (x & (-x))
int a[N], n, m;

class FenwickTree {
    private:
        int t[N];

    public:
        void add(int p, int v) {
            while (p <= n) {
                t[p] += v;
                p += lowb(p);
            }
        }

        int prefix(int p) {
            int ans = 0;
            while (p) {
                ans += t[p];
                p -= lowb(p);
            }
            return ans;
        }

        int range(int l, int r) {
            return prefix(r) - prefix(l-1);
        }
}t;


int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) scanf("%d", a+i);
    for (int i=1; i<=n; i++) t.add(i, a[i]);

    scanf("%d", &m);
    for (int i=1; i<=m; i++) {
        int o, x, y;
        scanf("%d%d%d", &o, &x, &y);
        if (o == 1) {
            printf("%d\n", i);
            t.add(x, y);
        } else {
            int ans = t.range(x, y);
            printf("%d %d\n", i, ans);
        }
    }
    return 0;
}
