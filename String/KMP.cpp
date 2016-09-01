#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef vector<int> vi;

// test on: uva455
class KMP {
public:
  string pattern;
  vi next;
  void init(string str) {
    pattern = str;
    next.resize((int)str.size()+1);
  }

  void getNext() {
    int lenp = (int)pattern.size();
    next[0] = -1;
    for (int i=0, j=-1; i<lenp;) {
      while (j != -1 && pattern[i] != pattern[j]) {
        j = next[j];
      }
      i++; j++;
      next[i] = j;
    }
  }

  int match(string text) { // return the number of pattern in text
    int i, j;
    int cnt = 0, lent = (int)text.size(), lenp = (int)pattern.size();
    for (i=0, j=0; i<lent; i++) {
      while (j != -1 && text[i] != pattern[j]) j = next[j];
      j++;
      if (j == lenp) cnt++;
    }
    return cnt;
  }
} sol;

int main() {
    bool flag = false;
    int cas;
    cin >> cas;
    while(cas--) {
        if (!flag) flag = true;
        else cout << endl;
        string p;
        cin >> p;
        sol.init(p);
        sol.getNext();
        int len = (int)p.size();
        int ans = len % (len - sol.next[len])? len: len - sol.next[len];
        cout << ans << endl;
    }
    return 0;
}
