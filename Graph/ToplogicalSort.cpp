#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 200010
int n, m, ind[N], vis[N], stk[N], top;
vector<int> g[N], ans;
priority_queue<int, vector<int>, greater<int> > q;

bool dfs0(int p, int flag) {
    vis[p] = flag;
    for (auto i: g[p]) {
        if (!vis[i]) {
            bool ans = dfs0(i, flag);
            if (ans) return ans;
        }
        else {
            if (vis[i] == flag) return true;
            else return false;
        }
    }
    return false;
}

bool checkCyc() {
    int flag = 0;
    for (int i=0; i<n; i++) if (!vis[i]) {
        if (dfs0(i, ++flag)) return true;
    }
    return false;
}

void sol1() {
    for (int i=0; i<n; i++) if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int cur = q.top();
        q.pop();
        ans.push_back(cur);
        for (auto i: g[cur]) {
            ind[i]--;
            if (!ind[i]) {
                q.push(i);
            }
        }
    }
    if ((int)ans.size() != n) {
        assert(checkCyc() == true);
        printf("-1\n");
    }
    else {
        assert((int)ans.size() == n);
        for (int i=0; i<n; i++) printf("%d%c", ans[i], i==n-1?'\n': ' ');
    }
}

void dfs(int p) {
    vis[p] = 1;
    for (auto i: g[p]) {
        if (!vis[i]) dfs(i);
    }
    stk[top++] = p;
}

bool cmp(int a, int b) { return a > b; }

int idx[N];
bool checkValid() {
    for (int i=top-1; i>=0; i--) idx[stk[i]] = top-1-i;
    for (int i=0; i<n; i++) {
        for (auto j: g[i]) if (idx[j] <= idx[i]) return false;
    }
    return true;
}

void sol2() {
    /*
    if (checkCyc()) {
        printf("-1\n");
        return;
    }*/
    memset(vis, 0, sizeof(vis));
    for (int i=0; i<n; i++) sort(g[i].begin(), g[i].end(), cmp);
    for (int i=n-1; i>=0; i--) if (!vis[i]) {
        dfs(i);
    }
    if(checkValid()) {
        for (int i=top-1; i>=0; i--) printf("%d%c", stk[i], i==0?'\n':' ');
    } else printf("-1\n");
}

int main() {
//    freopen("test.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i=0; i<m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        ind[v]++;
    }
    sol1();
}
