#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
#define maxn 10010

struct Edge { int u, v, c; } es[maxn];

class SegmentTree {
// need test on https://www.codechef.com/problems/QTREE
    private:
        int t[maxn<<1], size, height;
    public:

        void init(int N) {
            // height of range n segment tree
            height = sizeof(int) * 8 - __builtin_clz(N);
            size = N;
            memset(t, 0, sizeof(t));
        }

        void modify(int p, int val) {
            for ( t[p += size] = val; p > 1; p >>= 1) {
                t[p >> 1] = max(t[p], t[p^1]);
            }
        }

        int query(int l, int r) {// [l, r)
            int ans = 0;
            for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
                if (l & 1) ans = max(ans, t[l++]);
                if (r & 1) ans = max(ans, t[--r]);
            }
            return ans;
        }
};

class HLD {
    #define INF 1000000
    public:
        SegmentTree t;
        // heavy light decomposition
        int dep[maxn], heavy[maxn], fa[maxn], sz[maxn],
            top[maxn], pos[maxn], pCnt, n;
        // tree
        vector<int> g[maxn];

        void init(int N, Edge (&es)[maxn]) {
            pCnt = 0;
            n = N;
            for (int i=1; i<=n; i++) g[i].clear();
            t.init(n);
            memset(dep, 0, sizeof(dep));
            memset(heavy, 0, sizeof(heavy));
            for (int i=1; i<n; i++) {
                g[es[i].u].push_back(es[i].v);
                g[es[i].v].push_back(es[i].u);
            }
            int root = 1;
            dfs1(root);
            dfs2(root, root);
            for (int i=1; i<n; i++) {
                int& u = es[i].u;
                int& v = es[i].v;
                if (dep[u] > dep[v]) swap(u, v);
                t.modify(pos[v], es[i].c);
            }
        }

        void dfs1(int rt) {
            sz[rt] = 1;
            for (auto v: g[rt]) if (v != fa[rt]) {
                fa[v] = rt;
                dep[v] = dep[rt] + 1;
                dfs1(v);
                sz[rt] += sz[v];
                if (sz[v] > sz[heavy[rt]]) heavy[rt] = v;
            }
        }

        void dfs2(int rt, int head) {
            pos[rt] = pCnt++;
            top[rt] = head;
            if (heavy[rt]) dfs2(heavy[rt], head);
            for (auto v: g[rt]) {
                if (v != fa[rt] && v != heavy[rt]) dfs2(v, v);
            }
        }

        void changeEdgeCost(int eid, int c) { t.modify(pos[es[eid].v], c); }

        int maxLenEdge(int u, int v) {
            int ans = -INF;
            while (top[u] != top[v]) {
                if (dep[top[u]] > dep[top[v]]) swap(u, v);
                ans = max(ans, t.query(pos[top[v]], pos[v]+1));
                v = fa[top[v]];
            }
            if (u == v) return ans;
            if (dep[u] > dep[v]) swap(u, v);
            ans = max(ans, t.query(pos[heavy[u]], pos[v]+1));
            return ans;
        }
} hld;

int main() {
    int cas;
//    freopen("test.in", "r", stdin);
    for (scanf("%d", &cas); cas; cas--) {
        int n;
        scanf("%d", &n);
        for (int i=1; i<n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            es[i].u = a, es[i].v = b, es[i].c = c;
        }
        hld.init(n, es);
        char op[10];
        int x, y;
        while (scanf("%s", op) && *op != 'D') {
            scanf("%d%d", &x, &y);
            if (*op == 'C')  hld.changeEdgeCost(x, y);
            else printf("%d\n", hld.maxLenEdge(x, y));
        }
    }
    return 0;
}
