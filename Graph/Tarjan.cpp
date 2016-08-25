#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 10000
stack<int> S;
int disc = 0;
int in_stack[MAX];
void tarjan(int u,vector< vector<int> > g,int index[],int low_index[]){
  index[u] = low_index[u] = ++disc;
  in_stack[u] = 1;
  S.push(u);
  for(int i = 0;i < g[u].size();i++) {
  int v = g[u][i];
  if(index[v] == -1) {
      tarjan(v,g,index,low_index);
      low_index[u] = min(low_index[v],low_index[u]);
    }
    else if(in_stack[v] == 1)
      low_index[u] = min(low_index[u],index[v]);
  }
  if(index[u] == low_index[u]) {
    while(S.empty() == false && index[u] == low_index[S.top()] ) {
      cout<<S.top()<<" ";
      in_stack[S.top()] = 0;
      S.pop();
    }
    cout<<endl;
	}
}
