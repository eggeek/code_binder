#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <iostream>
using namespace std;

class Treap {
    private: struct node {
        int l, r, prior, value;
    };
    const int nil = -1;
    int root, _size;
    vector<node> t;

    /*
     *           u                   v
     *          / \                 / \
     *         A   v   <======>    u   C
     *            / \             / \
     *           B   C           A   B
     * */
    void rotateR(int& rt) {
        int newrt = t[rt].r;
        t[rt].r = t[newrt].l;
        t[newrt].l = rt;
        rt = newrt;
    }

    void rotateL(int& rt) {
        int newrt = t[rt].l;
        t[rt].l = t[newrt].r;
        t[newrt].r = rt;
        rt = newrt;
    }

    int newNode(int value) {
        node x = node{-1, -1, rand(), value};
        t.push_back(x);
        _size++;
        return t.size() - 1;
    }

    public:

    Treap() {
        root = -1;
        _size = 0;
        srand(time(0));
    }

    int size() {
        return _size;
    }

    void insert(int& rt, int value) {
        if (rt == nil) {
            rt = newNode(value);
            return;
        }
        if (value < t[rt].value) {
            insert(t[rt].l, value);
            if (t[t[rt].l].prior < t[rt].prior) rotateL(rt);
        } else {
            insert(t[rt].r, value);
            if (t[t[rt].r].prior < t[rt].prior) rotateR(rt);
        }
    }

    void remove(int& rt, int value) {
        if (rt == -1) return;
        if (value < t[rt].value) {
            remove(t[rt].l, value);
        }
        else if (value > t[rt].value){
            remove(t[rt].r, value);
        }
        else if (t[rt].value == value) {
            if (t[rt].l == nil && t[rt].r == nil) rt = -1;
            else if (t[rt].l == nil) rt = t[rt].r;
            else if (t[rt].r == nil) rt = t[rt].l;
            else {

            }
        }
    }
};

int main() {
    return 0;
}
