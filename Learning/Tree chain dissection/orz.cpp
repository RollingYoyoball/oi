#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int read()
{
    char c=getchar();int s=0;bool f=0;
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=1;
    for(;'0'<=c&&c<='9';c=getchar()) s=s*10+c-48;
    return f?-s:s;
}
inline int min(int x,int y){return x<y?x:y;}
const int M=32768;
const int N=131072;
const int INF=2147483647;
int n,S,T,yy;
struct node{int y,next,f;}a[16777216];
struct tree{int y,next;}e[M];
int g[N],q[N],tt,tot;
int fa[M],k[M],v[M],p[M];
int top[M],tid[M],pid[M],id[M];
int size[M],son[M],dep[M];
int lc[M<<2],rc[M<<2],step[N];
void add(int x,int y,int f)
{
//	printf("%d %d\n",x,y);
    a[++tt].y=y;a[tt].f=f;a[tt].next=g[x];g[x]=tt;
    a[++tt].y=x;a[tt].f=0;a[tt].next=g[y];g[y]=tt;
}
void dfs1(int x)
{
    int p,y;
    size[x]=1,son[x]=0;
    for(p=g[x];p;p=e[p].next)
    if((y=e[p].y)^fa[x])
    {
        dep[y]=dep[x]+1;
        dfs1(y);
        size[x]+=size[y];
        if(size[y]>size[son[x]]) son[x]=y;
    }
}
void dfs2(int x,int rt)
{
    int p,y;
    top[x]=rt;
    tid[x]=++tot;
    pid[tot]=x;
    if(son[x]) dfs2(son[x],rt);
    for(p=g[x];p;p=e[p].next)
    if((y=e[p].y)^fa[x]&&y^son[x]) dfs2(y,y);
}
void build(int &x,int l,int r)
{
    x=++tot;
    if(l==r){id[pid[l]]=x;return;}
    int mid=(l+r)>>1;
    build(lc[x],l,mid);
    build(rc[x],mid+1,r);
    add(x,lc[x],INF);
    add(x,rc[x],INF);
}
void qlink(int x,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) {add(yy,x,INF);return;}
    int mid=(l+r)>>1;
    if(L<=mid) qlink(lc[x],l,mid,L,R);
    if(mid<R)qlink(rc[x],mid+1,r,L,R);
}
void link(int k,int x)
{
    if(k==0) return;
    x=fa[x];
    while(1)
    {
        int dist=dep[x]-dep[top[x]]+1;
        if(dist<k)
        {
            k-=dist;
            qlink(1,1,n,tid[top[x]],tid[x]);
            x=fa[top[x]];
        }
        else
        {
            qlink(1,1,n,tid[x]-k+1,tid[x]);
            break;
        }
    }
}
bool bfs()
{
    int h=0,t=1,p,y,k;
    memset(step,-1,sizeof(step));
    q[1]=S;
    step[S]=0;
    while(h^t)
    {
        k=q[++h];
        for(p=g[k];~p;p=a[p].next)
        if(a[p].f&&step[y=a[p].y]==-1)
        {
            step[y]=step[k]+1;
            q[++t]=y;
            if(y==T) return 1;
        }
    }
    return 0;
}
int dfs(int x,int flow)
{
    if(x==T) return flow;
    int ans=0,p,y,tmp;
    for(p=g[x];~p;p=a[p].next)
    if(a[p].f&&step[y=a[p].y]==step[x]+1)
    {
        tmp=dfs(y,min(a[p].f,flow));
        if(tmp)
        {
            a[p].f-=tmp;
            a[p^1].f+=tmp;
            ans+=tmp;
            flow-=tmp;
            if(flow==0) break;
        }
    }
    if(!ans) step[x]=-1;
    return ans;
}
int main()
{
     freopen("a.in","r",stdin);
    freopen("a1.out","w",stdout);
  
    int i;
    n=read();
    tt=0;
    for(i=1;i<=n;i++)
    {
        fa[i]=read(),v[i]=read(),k[i]=read(),p[i]=read();
        e[++tt].y=i,e[tt].next=g[fa[i]],g[fa[i]]=tt;
    }
    tot=0;
    dfs1(1);
    dfs2(1,1);
    tt=-1,tot=0;
    memset(g,-1,sizeof(g));
    build(i,1,n);
    S=0;T=tot+n+1;
    int ans=0;
    for(i=1;i<=n;i++)
    {
        yy=tot+i;
        if(v[i]<0) add(id[i],T,-v[i]);
        else add(S,id[i],v[i]),ans+=v[i];
        add(id[i],yy,p[i]);
        link(k[i],i);
    }
    int cnt=0;
     while(bfs())
        ans-=dfs(S,INF),++cnt;
    printf("%d\n",cnt);
    printf("%d\n",ans);
    return 0;
}
