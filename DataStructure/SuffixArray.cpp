#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
using namespace std;
#define maxn 2500001
class SuffixArray {
    private:
        int cnt[maxn], tmp[maxn], sa2nd_key[maxn], l;
        struct cmp {
            int* rank, len;
            cmp(int* R, int L) { rank = R, len = L; };
            bool operator() (int i, int j) {
                if (rank[i] == rank[j]) return rank[i + len] < rank[j + len];
                return rank[i] < rank[j];
            }
        };

        void radixSort(int* rk) {
            int* sa2 = sa2nd_key, idx=0;
            for (int i=n-l+1; i<=n; i++) sa2[idx++] = i;
            for (int i=0; i<=n; i++) if (sa[i] >= l) sa2[idx++] = sa[i] - l;
            for (int i=0; i<=m; i++) cnt[i] = 0;
            for (int i=0; i<=n; i++) cnt[rk[sa2[i]]]++;
            for (int i=1; i<=m; i++) cnt[i] += cnt[i-1];
            for (int i=n; i>=0; i--) sa[--cnt[rk[sa2[i]]]] = sa2[i];
        }

    public:
        string s;
        int sa[maxn], rank[maxn], m, n;

        SuffixArray() {}
        SuffixArray(string S, int M) { init(s); }

        void init(string S) {
            s = S;
            n = (int)s.size();
            for (int i=0; i<n; i++) sa[i] = i, rank[i] = s[i] - 'a' + 1;
            sa[n] = n, rank[n] = 0; // terminate symbol
            radixConstructSa();
        }

        // radix sort
        void radixConstructSa() {
            int *x = rank;
            int *y = tmp;
            sort(sa, sa+1+n, cmp(x, l));
            m = x[sa[n]];
            for (l=1; l<=n; l<<=1) {
                radixSort(x);
                y[sa[0]] = 0;
                for (int i=1; i<=n; i++) {
                    y[sa[i]] = y[sa[i-1]] + (cmp(x, l)(sa[i-1], sa[i]) ? 1 : 0);
                }
                swap(x, y);
                if (x[sa[n]] == n) break;
                m = x[sa[n]];
            }
            for (int i=0; i<=n; i++) rank[sa[i]] = i;
        }

        // quick sort
        void qsortConstructSa() {
            int* x = rank;
            int* y = tmp;
            for (l=1; l<=n; l<<=1) {
                sort(sa, sa+n+1, cmp(x, l));
                y[sa[0]] = 0;
                for (int i=1; i<=n; i++) {
                    y[sa[i]] = y[sa[i-1]] + (cmp(x, l)(sa[i-1], sa[i]) ? 1 : 0);
                }
                swap(x, y);
                if (x[sa[n]] == n) break;
            }
            for (int i=0; i<=n; i++) rank[sa[i]] = i;
        }

        void printSA() {
            for (int i=1; i<=n; i++) printf("%d%c", sa[i], i<n?' ': '\n');
        }

};
SuffixArray A;

int main() {
//    freopen("test.in", "r", stdin);
    string s;
    cin >> s;
    A.init(s);
    A.radixConstructSa();
    A.printSA();
}
