#include <utility>
#include <vector>
#include <queue>
using namespace std;
#define MAX_V 100010
#define INF 1e8
typedef pair<int, int> pii;

class MinCostMaxFlow {
  struct edge {int to, cap, cost, rev; };
  vector<edge> G[MAX_V];
  int V;
  int h[MAX_V];
  int dist[MAX_V];
  int prevv[MAX_V], preve[MAX_V];

  void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
    G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
  }

  int min_cost_flow(int s, int t, int f) {
    int res = 0;
    fill(h, h + V, 0);
    while (f > 0) {
      priority_queue<pii, vector<pii>, greater<pii> > que;
      fill(dist, dist + V, INF);
      dist[s] = 0;
      que.push(pii(0, s));
      while (!que.empty()) {
        pii p = que.top(); que.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < G[v].size(); i++) {
          edge &e = G[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            que.push({dist[e.to], e.to});
          }
        }
      }
      if (dist[t] == INF) return -1;
      for (int v=0; v<V; v++) h[v] += dist[v];
      int d = f;
      for (int v=t; v!=s; v=prevv[v]) {
        d = min(d, G[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (int v=t; v!=s; v=prevv[v]) {
        edge &e = G[prevv[v]][preve[v]];
        e.cap -=d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};

void solve() {
  /*
   * int flow = max_flow(s, t);
   * int cost = min_cost_flow(s, t, flow);
   */
}
