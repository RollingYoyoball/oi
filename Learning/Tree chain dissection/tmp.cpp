#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int cnt,q;bool bridge[100002],bo[100002];
int hehehe=0;
int fa[100002],size[100002],son[100002],head[100002],dep[100002];
int n,m,vis[100002],a,b,tot,h[100002],low[100002],js;
int re[100002],xds[100002],tree[400003],tag[400003];
struct dd{int y,next1;}g[400003];
int dfs(int k,int fa1)
{
    js++;
    vis[k]=js;
    low[k]=js;
    int tmp=h[k];
    while (tmp!=-1)
    {
        int v=g[tmp].y;
        if (vis[v]==0)
        {
            int he=dfs(v,k);
            low[k]=min(low[k],he);
            if (he>vis[k])
            {
                bridge[v]=true;
                cnt++;
            }
        }
        else if (v!=fa1)
        {
            low[k]=min(low[k],vis[v]);
        }
        tmp=g[tmp].next1;
    }
    return low[k];
}
void dfs1(int k,int fa1)
{
    int maxn,id;
    maxn=0;id=-1;
    fa[k]=fa1;
    dep[k]=dep[fa1]+1;
    size[k]=1;
    bo[k]=true;
    int tmp=h[k];
    while (tmp!=-1)
    {
        int v=g[tmp].y;
        if (bo[v]==false)
        {
            dfs1(v,k);
            size[k]+=size[v];
            if (size[v]>maxn)
            {
                maxn=size[v];
                id=v;
            }
        }
        tmp=g[tmp].next1;
    }
    son[k]=id;
}
void downtag(int k,int l,int r)
{
    if (tag[k]==1)
    {
        tag[k*2]=tag[k*2+1]=1;
        tree[k*2]=tree[k*2+1]=0;
        tag[k]=0;
    }
}
void dfs2(int k)
{
    js++;
    re[k]=js;
    xds[js]=k;
    bo[k]=true;
    if (son[k]!=-1)
    {
        head[son[k]]=head[k];
        dfs2(son[k]);
    }
    int tmp=h[k];
    while (tmp!=-1)
    {
        int v=g[tmp].y;
        if (bo[v]==false)
        {
            head[v]=v;
            dfs2(v);
        }
        tmp=g[tmp].next1;
    }
}
void build(int k,int l,int r)
{
    if (l==r)
    {
        if (bridge[xds[l]]==true)
        tree[k]=1;
        else tree[k]=0;
        return;
    }
    int mid=(l+r)/2;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
    tree[k]=tree[k*2]+tree[k*2+1];
}
void change1(int k,int l,int r,int askx,int asky)
{
    if (askx<=l&&r<=asky)
    {
        tag[k]=1;
        cnt-=tree[k];
        tree[k]=0;
        return;
    }
    downtag(k,l,r);
    int mid=(l+r)/2;
    if (askx<=mid) change1(k*2,l,mid,askx,asky);
    if (asky>mid) change1(k*2+1,mid+1,r,askx,asky);
    tree[k]=tree[k*2]+tree[k*2+1];
}
void lca(int xx,int yy)
{
    while (head[xx]!=head[yy])
    {
        if (dep[head[xx]]>dep[head[yy]])
        {
            change1(1,1,n,re[head[xx]],re[xx]);
            xx=fa[head[xx]];
        }
        else
        {
            change1(1,1,n,re[head[yy]],re[yy]);
            yy=fa[head[yy]];
        }
    }int dd;
    if (min(re[xx],re[yy])<max(re[xx],re[yy]))
        change1(1,1,n,min(re[xx],re[yy])+1,max(re[xx],re[yy]));
     
    printf("%d\n",cnt);
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
	
    while (1==1)
    {
        hehehe++;
        tot=0;
        js=0;cnt=0;
        fa[1]=0;
        dep[0]=0;
        memset(bo,false,sizeof(bo));
        memset(tag,0,sizeof(tag));
        memset(bridge,0,sizeof(bridge));
        memset(h,-1,sizeof(h));
        memset(vis,0,sizeof(vis));
        memset(low,0x7f,sizeof(low));
        memset(fa,0,sizeof(fa));
        scanf("%d%d",&n,&m);
        if(n==0&&m==0) return 0;
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            tot++;
            g[tot].y=b;
            g[tot].next1=h[a];
            h[a]=tot;
            tot++;
            g[tot].y=a;
            g[tot].next1=h[b];
            h[b]=tot;
        }
        int cc=dfs(1,0);
        dfs1(1,0);
        js=0;
        head[1]=1;
        memset(bo,false,sizeof(bo));
        dfs2(1);
        build(1,1,n);
        scanf("%d",&q);
        printf("Case %d:\n",hehehe);
        for (int i=1;i<=q;i++)
        {
            scanf("%d%d",&a,&b);
            lca(a,b);
        }
        printf("\n");
    }
}
