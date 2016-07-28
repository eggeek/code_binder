#include<stdio.h>
#include<string.h>
#define maxn 1000010
char p[maxn],txt[maxn];
int next[maxn];
int lenp,lent;
void getNext()
{
    int i,j;
    next[0]=-1,j=-1;
    for(i=0;i<lenp;){
        while(j!=-1 && p[i]!=p[j])j=next[j];
        i++;j++;
        next[i]=j;
    }
}
void kmp()
{
    int i,j;
    int cnt=0;
    for(i=0,j=0;i<lent;i++){
        while(j!=-1 && txt[i]!=p[j])j=next[j];
        j++;
        if(j==lenp)cnt++;
    }
    printf("%d\n",cnt);
}
int main()
{
    int cas;
//    freopen("test.txt","r",stdin);
    scanf("%d",&cas);
    while(cas--){
        scanf("%s%s",p,txt);
        lenp=strlen(p);
        lent=strlen(txt);
        getNext();
        kmp();
    }
    return 0;
}
