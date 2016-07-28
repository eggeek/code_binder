#include<stdio.h>
#include<string.h>
#define max(a,b) (a)>(b)?(a):(b)
#define maxn 100010
char str[maxn<<1];
int next[maxn<<1];
int len,ans[3];
void getNext()
{
//    kmp解决了求所有主串的前缀pre[i] (0<=i<n)的后缀与模式串前缀的最大匹配长度问题;
//    拓展kmp解决了所有主串的后缀suf[i]的前缀,与模式串前缀的最大匹配长度问题.
//    str[ l , l+next[l]-1 ] == str[ 0 , next[l]-1 ]
    int i,j,l,r;
    l=1,r=-1;
    next[0]=0;
    for(i=1;i<2*len;i++){
        if(next[i-l]<r-i+1)next[i]=next[i-l];
        else{
                j=max(r-i+1,0);
                while(i+j<2*len && str[i+j] == str[j])
                    j++;
                l=i;r=i+j-1;next[i]=j;
            }
    }
    next[0]=i;
//    for(i=0;i<2*len;i++)printf(" %d",next[i]);
}
void statis()
{
    int i;
    memset(ans,0,sizeof(ans));
    for(i=1;i<len*2;i++){
        if(next[i]>=len)ans[1]++;
        else if(str[i+next[i]] > str[next[i]])ans[2]++;
        else if(str[i+next[i]] < str[next[i]])ans[0]++;
        if(len*2%i==0 && i+next[i]==len*2)break;
    }
    printf("%d %d %d\n",ans[0],ans[1],ans[2]);
}
int main()
{
    int cas,t;
    scanf("%d",&cas);
    for(t=1;t<=cas;t++){
        printf("Case %d: ",t);
        scanf("%s",str);
        len=strlen(str);
        memcpy(str+len,str,len);
        getNext();
        statis();
    }
    return 0;
}
