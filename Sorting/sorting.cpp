#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <random>
#include <cmath>
#include <ctime>
#include <functional>
#include <algorithm>
#include <complex>
#include <numeric>
#include <limits>
#include <bitset>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <map>
#include <set>
using namespace std;
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define MP(x, y) make_pair((x),(y))
#define FI first
#define SE second
#define LOWB(x) (x & (-x))
#define UNIQUE(a) sort(ALL(a)), (a).erase(unique(ALL(a)), (a).end())
#define HEIGHT(n) (sizeof(int) * 8 - __builtin_clz(n)) //height of range n segment tree
#define INF 1e9
#define INF_LL 4e18
#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
/*-----------------------------------*/
int n;
vi a;

void print_arr(vi x) {
  for (int i=0; i<SZ(x); i++) printf("%d%c", x[i], i+1<SZ(x)?' ': '\n');
}

class MergeSort {

  public:
  vi arr, tmp;
  int n;

  MergeSort(vi nums) {
    arr = nums;
    n = SZ(nums);
    tmp.resize(n);
  }

  void merge(int l, int r) {
    int mid = (l + r) >> 1;
    int idxl=l, idxr=mid+1, idx=l;
    while (idxl<=mid && idxr<=r) {
      if (arr[idxl] <= arr[idxr]) {
        tmp[idx++] = arr[idxl++];
      } else {
        tmp[idx++] = arr[idxr++];
      }
    }
    while (idxl <= mid) tmp[idx++] = arr[idxl++];
    while (idxr <= r) tmp[idx++] = arr[idxr++];
    assert(idx - l == r - l + 1);
    for (int i=l; i<=r; i++) arr[i] = tmp[i];
  }

  void merge_sort(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid+1, r);
    merge(l, r);
  }

  void run() {
    merge_sort(0, this->n-1);
  }
};

class QuickSort {
  public:

  vi arr;
  int n;

  QuickSort(vi nums) {
    arr = nums;
    n = SZ(nums);
  }

  void run() {
    quick_sort(0, n-1);
  }

  int partial(int l, int r) {
    int var = arr[r];
    int idx = l;
    for (int i=l; i<=r; i++) {
      if (arr[i] < var) {
        swap(arr[idx++], arr[i]);
      }
    }
    swap(arr[idx], arr[r]);
    return idx;
  }

  void quick_sort(int l, int r) {
    if (l >= r) return;
    int pivot = partial(l, r);
    quick_sort(l, pivot-1);
    quick_sort(pivot+1, r);
  }
};

class Heap {
  public:
  vi arr;
  int n;

  Heap() {
    arr.resize(1);
    n = 0;
  }

  void push(int v) {
    arr.push_back(v);
    ++n;
    siftup(n);
  }

  int top() { return arr[1]; }

  void pop() {
    swap(arr[1], arr[n]);
    arr.pop_back();
    n--;
    siftdown(1);
  }

  void siftup(int pos) {
    while ((pos >> 1)> 0) {
      int pa = pos >> 1;
      if (arr[pos] < arr[pa]) {
        swap(arr[pos], arr[pa]);
        pos = pa;
      } else break;
    }
  }

  void siftdown(int pos) {
    int ls = pos << 1;
    int rs = pos << 1 | 1;
    int nxt = pos;
    if (rs <= n) nxt = arr[ls] < arr[rs]? ls: rs;
    else if (ls <= n) nxt = ls;
    if (arr[nxt] < arr[pos]) {
      swap(arr[nxt], arr[pos]);
      siftdown(nxt);
    }
  }

  void heapfy(vi a) {
    arr = vi(1, 0);
    arr.insert(arr.end(), a.begin(), a.end());
    n = SZ(a);
    for (int i=n/2; i>=1; i--) siftdown(i);
  }

  vi heap_sort(vi a) {
    heapfy(a);
    vi res;
    while (n) {
      res.push_back(top());
      pop();
    }
    return res;
  }
};

bool eq(vi u, vi v) {
  if (SZ(u) != SZ(v)) return false;
  for (int i=0; i<SZ(u); i++) {
    if (u[i] != v[i]) return false;
  }
  return true;
}

struct cmp {
  bool operator() (int x, int y) {
    return x > y;
  }
};

priority_queue<int, vi, cmp> q;

vi heap_sort() {
  for (int i=0; i<n; i++) q.push(a[i]);
  vi res;
  while (!q.empty()) {
    res.push_back(q.top());
    q.pop();
  }
  return res;
}

int main() {
  scanf("%d", &n);
  a.resize(n);
  for (int i=0; i<n; i++) scanf("%d", &a[i]);
  MergeSort sol = MergeSort(a);
  QuickSort sol2 = QuickSort(a);
  vi sol3 = heap_sort();
  Heap h = Heap();
  sol.run();
  sol2.run();

  vi sol4 = h.heap_sort(a);
  assert(eq(sol.arr, sol2.arr));
  assert(eq(sol.arr, sol3));

  assert(eq(sol.arr, sol4));
  print_arr(sol4);
  return 0;
}
