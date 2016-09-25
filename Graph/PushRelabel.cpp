#include <queue>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;
#define N 10010
#define M 2000200
const ll INF = 1e10;

class MaxFlow {
    public:

    struct Edge {
        int to, c, f, rev;
    } e[M << 1];

    vector<int> g[N];
    queue<int> q;
    ll ex[N];
    bool inq[N];
    int n, m, s, t, tote, h[N];
    int cnth[N<<1];

    void initialize(int n, int m, int s, int t) {
        this->n = n; this->m = m;
        this->s = s; this->t = t; tote = 0;
        for (int i=0; i<n; i++) ex[i] = 0;
        for (int i=0; i<n; i++) h[i] = 0;
        for (int i=0; i<n; i++) g[i].clear();
        for (int i=0; i<=2*n; i++) cnth[i] = 0;
        for (int i=0; i<n; i++) inq[i] = 0;
        while (!q.empty()) q.pop();
    }

    void add_edge(int from, int to, int cap) {
        g[from].push_back(tote);
        e[tote] = Edge{to, cap, 0, tote^1};
        tote++;
    }

    void push(int from, Edge& edge) {
        int flow = min(ex[from], (ll)(edge.c - edge.f));
        ex[from] -= flow;
        ex[edge.to] += flow;
        edge.f += flow;
        e[edge.rev].f -= flow;
    }

    void gap_heuristic(int gap) {
        for (int u=0; u<n; u++) {
            if (u == s || u == t || h[u] < gap) continue;
            cnth[h[u]]--;
            h[u] = 2 * n;
            cnth[h[u]]++;
        }
    }

    void discharge(int u) {
        while (ex[u]) {
            int nexth = 2 * n;
            for (auto eid: g[u]) {
                if (e[eid].c - e[eid].f == 0) continue;
                int v = e[eid].to;
                if (h[u] == h[v] + 1) {
                    push(u, e[eid]);
                    if (v != s && v != t && !inq[v]) {
                        inq[v] = true;
                        q.push(v);
                    }
                }
                if (h[u] < h[v] + 1) nexth = min(nexth, h[v] + 1);
                if (!ex[u]) break;
            }
            if (ex[u]) {
                if (cnth[h[u]] == 1) gap_heuristic(h[u]);
                else {
                    cnth[h[u]] --;
                    h[u] = nexth;
                    cnth[h[u]] ++;
                }
            }
            if (h[u] >= n) break;
        }
        inq[u] = false;
    }

    ll run() {
        h[s] = n;
        cnth[0] = n - 1;
        cnth[n] = 1;
        for (auto eid: g[s]) {
            ex[s] = INF;
            if (!e[eid].c) continue;
            push(s, e[eid]);
            if (e[eid].to != t && !inq[e[eid].to]) {
                inq[e[eid].to] = true;
                q.push(e[eid].to);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            discharge(u);
        }
        return ex[t];
    }
} mf;

int main() {
//    freopen("test.in", "r", stdin);
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);

    mf.initialize(n, m, s-1, t-1);
    for (int i=0; i<m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        mf.add_edge(u-1, v-1, c);
        mf.add_edge(v-1, u-1, 0);
    }
    cout << mf.run() << endl;
    return 0;
}
