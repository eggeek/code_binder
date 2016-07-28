#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int dict = 26;
const int root = 0;
const int maxn = 3000000;
struct node
{
	int son[dict],fail,idx;
//	int fa;
};node tree[maxn];
int sz,n;
queue<int>q;
bool vis[maxn],ok[maxn],apr[3000];
char pat[3000][3000];
char txt[5000010],str[5000010];
void trans(char *s)
{
	int i,num;
	for ( i=0 ; str[i] ; i++ )
	{
		if ( str[i]=='[')
		{
			for ( i++,num=0 ; str[i] ; i++ )
			if ('0'<=str[i] && str[i]<='9')num = num*10 + str[i]-'0';
			else	break;
			while (num--)*s++ = str[i];
			i++;
		}
		else	*s++ = str[i];
	}
	*s='\0';
}
int initNode(int idx)
{
	memset(tree[idx].son,0,sizeof(tree[idx]));
	tree[idx].fail=tree[idx].idx=0;
	return idx;
}
void ins(char* s,int idx)
{
	int cur=root,t;
	while (*s)
	{
		t = *s -'A';
		if (!tree[cur].son[t]) tree[cur].son[t] = initNode(++sz);
		cur = tree[cur].son[t];
		s++;
	}tree[cur].idx = idx;
}
void buildac()
{
	int i,cur,nxt,f;
	for ( i=0 ; i<dict ; i++ )
	if (tree[root].son[i])	q.push(tree[root].son[i]);

	while (!q.empty())
	{
		cur = q.front(); q.pop();
		f = tree[cur].fail;
		for ( i=0 ; i<dict ; i++ )
		if (tree[cur].son[i])
		{
			nxt  = tree[cur].son[i];
			tree[nxt].fail = tree[f].son[i];
			q.push(nxt);
		}else	tree[cur].son[i] = tree[f].son[i];
	}
}
void search(char *s)
{
	int i,cur=0;
	for (i=0 ; i<=sz ; i++ )vis[i]=0;
	for ( ; *s ; s++ )
	{
		cur = tree[cur].son[*s-'A'];
		for ( i=cur ; i && !vis[i]; i=tree[i].fail )
		{
			vis[i]=1;
			apr[tree[i].idx]=1;
		}
	}
}
int main()
{
	int cas,i;
//	freopen("test.txt","r",stdin);
	scanf("%d",&cas);
	while (cas--)
	{
		sz = initNode(0);
		scanf("%d",&n);
		for ( i=1 ; i<=n ; i++ ){
			apr[i]=0;
			scanf("%s",str);
			trans(pat[i]);
			ins(pat[i],i);
		}
		buildac();
		scanf("%s",str);
		trans(txt);
		search(txt);
		for ( i=0 ; i<=sz ; i++ )vis[i]=0;
		for ( i=1 ; i<=n ; i++ )
		if (apr[i])
		{
			int j,k,len = strlen(pat[i]),cur=root;
//			printf("i=%d\n",i);
			for ( j=0 ; j<len ; j++ )
			{
				cur = tree[cur].son[pat[i][j]-'A'];
				for ( k=cur ; k && !vis[k] ;  k=tree[k].fail )
				if(tree[k].idx != i){
					apr[tree[k].idx]=0;
					vis[k]=1;
				}
			}
		}
		int ans=0;
		for ( i=1 ; i<=n ; i++ )
		if (apr[i]) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
