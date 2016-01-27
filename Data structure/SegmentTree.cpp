#include <algorithm>
using namespace std;
#define maxn 100000
class SegmentTree {
    private:

        int t[maxn<<1], size, height;

        void push_up(int l, int r) {// [l, r)
            for (l += size, r += size-1; l > 1;) {
                l >>= 1, r >>= 1;
                for (int i=l; i<=r; i++) t[i] = max(t[i<<1], t[i<<1|1]);
            }
        }

        void push_down(int l, int r) {// [l, r)
            int s = height;
            for (l += size, r += size-1; s > 0; --s) {
                for (int i = (l>>s); i <= (r>>s); i++) {
                    // update
                }
            }
        }

    public:
        SegmentTree(int N) { init(N); }
        void init(int N) {
            size = N;
            // height of range n segment tree
            height = sizeof(int) * 8 - __builtin_clz(N);
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

int main() {
    /*
        1. if it is a segment tree of a sorts of indexs, care about Index Out Of Bounds.
        2. non-recursive segment tree is a sorts of balanced trees, not 1.
    */
    int n = 100;
    SegmentTree t(n);
    t.modify(1, 10);
    printf("%d\n", t.query(0, n));
}
