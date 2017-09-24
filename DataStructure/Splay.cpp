#include <bits/stdc++.h>
using namespace std;
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define LOWB(x) (x & (-x))
#define UNIQUE(a) sort(ALL(a)), (a).erase(unique(ALL(a)), (a).end())
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

struct Node {
  Node *lhs, *rhs, *pre;
  int v;
  public:
  void print_node() {
    printf("lhs: %lld, rhs: %lld, pre: %lld, v:%d\n", (ll)lhs, (ll)rhs, (ll)pre, v);
  }
};

Node* newNode(int v) {
  Node *ptr = (Node*)malloc(sizeof(Node));
  ptr->lhs = nullptr;
  ptr->rhs = nullptr;
  ptr->pre = nullptr;
  ptr->v = v;
  return ptr;
}

class Splay {
  public:
  Node* root;
  void rightRotate(Node* c) {
    Node *t = c->lhs;
    Node *b = t->rhs;
    Node *d = c->pre;

    if (d) {
      if (d->rhs == c) d->rhs = t;
      else d->lhs = t;
    }
    if (b) b->pre = c;
    t->pre = d;
    t->rhs = c;
    c->pre = t;
    c->lhs = b;
  }

  void leftRotate(Node* c) {
    Node *t = c->rhs;
    Node *b = t->lhs;
    Node *d = c->pre;

    if (d) {
      if (d->rhs == c) d->rhs = t;
      else d->lhs = t;
    }
    if (b) b->pre = c;
    t->pre = d;
    t->lhs = c;
    c->pre = t;
    c->rhs = b;
  }

  public: void insert(int v) {
    if (root == nullptr) {
      root = newNode(v);
      return;
    }
    Node *p = root;
    while (true) {
      if (p->v == v) break;
      if (v < (p->v)) {
        if (p->lhs) p = p->lhs;
        else {
          p->lhs = newNode(v);
          p->lhs->pre = p;
          p = p->lhs;
          break;
        }
      } else {
        if (p->rhs) p = p->rhs;
        else {
          p->rhs = newNode(v);
          p->rhs->pre = p;
          p = p->rhs;
          break;
        }
      }
    }
    splay(p);
  }

  public: Node* find(int v) {
    if (root == nullptr) return nullptr;
    Node *p = root;
    while (p != nullptr) {
      if ((p->v) == v) break;
      else if ((p->v) > v) {
        if (p->lhs) p = p->lhs;
        else break;
      } else {
        if (p->rhs) p = p->rhs;
        else break;
      }
    }
    splay(p);
    if ((p->v) == v) return p;
    else return nullptr;
  }

  public:
  void inorder(Node* p) {
    if (p->lhs) inorder(p->lhs);
    printf("%d ", p->v);
    if (p->rhs) inorder(p->rhs);
    if (p == root) printf("\n");
  }

  void splay(Node *t) { // splay t to root
      while (true) {
        Node *p = t->pre;
        if (p == nullptr) break;
        Node *pp = p->pre;
        if (pp == nullptr) {
          if (p->lhs == t) this->rightRotate(p);
          else leftRotate(p);
          break;
        }
        if (pp->lhs == p) {
          if (p->lhs == t) { // ZigZig
            rightRotate(pp);
            rightRotate(p);
          } else { // ZigZag
            leftRotate(p);
            rightRotate(pp);
          }
        } else {
          if (p->lhs == t) { // ZigZag
            rightRotate(p);
            leftRotate(pp);
          } else { // ZigZig
            leftRotate(pp);
            leftRotate(p);
          }
        }
      }
      this->root = t;
    }
};


void test() {
  Splay s1;
  int maxn = 10000;
  clock_t begin = clock();
  vi data;
  data.resize(maxn);
  for (int i=0; i<maxn; i++) data[i] = random();
  sort(ALL(data), less<int>());

  for (int i=0; i<maxn; i++) {
    s1.insert(data[i]);
  }

  for (int i=0; i<maxn; i++) {
    assert(s1.find(data[i]) != nullptr);
  }
  clock_t end = clock();
  printf("s1 time: %.6lf s\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

int main() {
  test();
  return 0;
}
