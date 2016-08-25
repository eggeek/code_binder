#include <vector>
#include <cstring>
using namespace std;
#define N 1010
typedef vector<int> vi;
vi e[N];
int match[N], n;
bool vis[N];

int dfs(int cur) {
  vis[cur] = true;
  for (int i: e[cur]) if (match[i] == -1 || (!vis[match[i]] && dfs(match[i]))) {
    match[cur] = i;
    match[i] = cur;
    return true;
  }
  return false;
}

int hungary() {
  memset(match, -1, sizeof(match));
  int res = 0;
  for (int i=0; i<n; i++) if (match[i] == -1) {
    memset(vis, false, sizeof(vis));
    res += dfs(i);
  }
  return res;
}

int main() {
  return 0;
}
