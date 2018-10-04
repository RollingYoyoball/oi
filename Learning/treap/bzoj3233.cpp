#include<iostream>
#include<cstdio>
#include<cstring>
#define Pr pair<int,int>
using namespace std;
const int MAXN=1e5+10;
int n,m;
struct xxx
{
    int ch[2][MAXN],sz[MAXN],tag[MAXN],fix[MAXN],val[MAXN];
    int tot,rt;
    int newnode(int v)
    {
        val[++tot]=v;
        ch[0][tot]=ch[1][tot]=0;
        tag[tot]=0;
        sz[tot]=1;
        fix[tot]=rand();//remeber to change it back
        return tot;
    }
    int pushup(int x)
    {
        sz[x]=sz[ch[0][x]]+sz[ch[1][x]]+1;
    }
    int downtag(int x)
    {
        tag[x]=0;
        swap(ch[0][x],ch[1][x]);
        if (ch[0][x]) tag[ch[0][x]]^=1;
        if (ch[1][x]) tag[ch[1][x]]^=1;
    }
    int merge(int x,int y)
    {
        if (!x||!y) return x+y;
        if (tag[x]) downtag(x);
        if (tag[y]) downtag(y);
        if (fix[x]<fix[y])
        {
            ch[1][x]=merge(ch[1][x],y);
            pushup(x);
            return x;
        }
        ch[0][y]=merge(x,ch[0][y]);
        pushup(y);
        return y;
    }
    Pr split(int x,int k)
    {
        if (k<=0) return Pr(0,x);
        if (tag[x]) downtag(x);
        int lch=ch[0][x],rch=ch[1][x];
        int flag=k-sz[lch]-1;
        Pr a;
        if (flag>=0)
        {
            a=split(rch,flag);
            ch[1][x]=a.first; pushup(x);
            return Pr(x,a.second);
        }
        else
        {
            a=split(lch,k);
            ch[0][x]=a.second; pushup(x);
            return Pr(a.first,x);
        }
    }
    int print() {dfs(rt);}
    int dfs(int x)
    {
        if (!x) return 0;
        if (tag[x]) downtag(x);
        dfs(ch[0][x]);
        printf("%d ",val[x]);
        dfs(ch[1][x]);
    }
    int reverse(int l,int r)
    {
        Pr tmp=split(rt,l-1),tmp1=split(tmp.second,r-l+1);
        tag[tmp1.first]^=1;
        rt=merge(merge(tmp.first,tmp1.first),tmp1.second);
    }
    int insert(int pos,int v)
    {
        int x=newnode(v);
        rt=merge(rt,x);
    }
}tr;
 
int main()
{
//  freopen("a.in","r",stdin);
 
    scanf("%d%d",&n,&m);
    int x,y;
    for (int i=1;i<=n;++i) 
        tr.insert(i,i);
    for (int i=1;i<=m;++i)
    {
        scanf("%d%d",&x,&y);
        tr.reverse(x,y);
    }
    tr.print(); 
}
