#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define TOP 18
#define inf 20010
using namespace std;
const int MAXN=200010;
struct xxx
{
	int y,next,dis;
}a[MAXN*2];
struct bian1
{
	int x,y,dis;
}bian[MAXN];
vector<int> cross[MAXN];
int lch[MAXN*4],rch[MAXN*4],tag[MAXN*4],mn[MAXN*4],num[MAXN];
int son[MAXN],sz[MAXN],id[MAXN],f[MAXN][20],dep[MAXN],st[MAXN],ed[MAXN],top[MAXN],dfn[MAXN];
int fa[MAXN],out[MAXN],sum[MAXN],now[MAXN],h[MAXN];
bool used[MAXN];
int n,m,tot,tot1,sum1,T;
int dfs(int fa1,int x,int d);
int dfs1(int fa1,int x);
int build(int x,int l,int r);
int update(int x,int l,int r,int lx,int rx,int delta);
int downtag(int x);
int query(int x,int l,int r,int lx,int rx);
int add(int x,int y,int dis);
int get_f(int x);
int work(int x,int y,int delta);
int go(int x,int d);
int get_lca(int x,int y);
int solve(int x);
bool cmp(bian1 x,bian1 y);
bool cmp1(int x,int y);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,y,dd,c,cnt,fx,fy;
	scanf("%d",&T);
	for (int o=1;o<=T;++o)
	{
		scanf("%d%d",&n,&m);
	//	if (n==1) {printf("0\n");continue;}
		memset(h,-1,sizeof(h));
		for (int i=1;i<=n;++i) cross[i].clear();
		tot=0;
		for (int i=1;i<=m;++i)
		{
			scanf("%d%d%d%d",&bian[i].x,&bian[i].y,&dd,&c);
			bian[i].dis=dd*(1-c);
		}
		sort(bian+1,bian+1+m,cmp);
		for (int i=1;i<=n;++i) fa[i]=i,sum[i]=0;
		cnt=0; sum1=0;
		memset(used,false,sizeof(used));
		for (int i=1;i<=m&&cnt<n-1;++i)
		{
			fx=get_f(bian[i].x),fy=get_f(bian[i].y);
			if (fx!=fy)
			{
				fa[fx]=fy;
				add(bian[i].x,bian[i].y,bian[i].dis); add(bian[i].y,bian[i].x,bian[i].dis);
				++cnt;
				sum[bian[i].x]+=bian[i].dis; sum[bian[i].y]+=bian[i].dis;
				sum1+=bian[i].dis; used[i]=true;
			}
		}
		tot1=0;
		dfs(0,1,1);
		top[1]=1;
		dfs1(0,1);
		tot1=1;
		build(1,1,n);
		int lca,top1,top2;
		for (int i=1;i<=m;++i)
		{
			if (used[i]) continue;
			lca=get_lca(bian[i].x,bian[i].y);
			top1=go(bian[i].x,dep[lca]+2);//don't update the nodes whose deep=dep[lca]+1
			top2=go(bian[i].y,dep[lca]+2);
			if (top1!=-1) work(bian[i].x,top1,bian[i].dis);
			if (top2!=-1) work(bian[i].y,top2,bian[i].dis);	
			if (lca==bian[i].x||lca==bian[i].y) continue;
			cross[lca].push_back(i);
		}
		for (int i=1;i<=n;++i) 
			out[i]=query(1,dfn[i],dfn[i],1,n);
		int tmp;
		for (int i=1;i<=n;++i)
		{
			tmp=solve(i);
			if (tmp!=-1) printf("%d\n",sum1-sum[i]+tmp);
			else printf("inf\n");
		}
	}
}

int get_f(int x)
{
	if (fa[x]!=x) fa[x]=get_f(fa[x]);
	return fa[x];
}

int add(int x,int y,int dis)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].dis=dis;
}

int dfs(int fa1,int x,int d)
{
	sz[x]=1,son[x]=0,dep[x]=d;
	f[x][0]=fa1;
	for (int i=1;i<=TOP;++i) f[x][i]=f[f[x][i-1]][i-1];
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa1) continue;
		dfs(x,u,d+1);
		sz[x]+=sz[u];
		if (sz[son[x]]<sz[u]) son[x]=u;
	}
}

int dfs1(int fa1,int x)
{
	int u;
	dfn[x]=++tot1; num[tot]=x; st[x]=dfn[x];
	if (son[x]) 
	{
		top[son[x]]=top[x];
		dfs1(x,son[x]);
	}
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa1||u==son[x]) continue;
		top[u]=u;
		dfs1(x,u);
	}
	ed[x]=tot1;
}

int build(int x,int l,int r)
{
	mn[x]=inf; tag[x]=inf;//!!init!!
	if (l==r)
		return 0;
	int mid=l+r>>1;
	lch[x]=++tot1; build(lch[x],l,mid);
	rch[x]=++tot1; build(rch[x],mid+1,r);
}

int update(int x,int l,int r,int lx,int rx,int delta)
{
	if (l<=lx&&rx<=r)
	{
		mn[x]=min(mn[x],delta); tag[x]=min(tag[x],delta); //min or =
		return 0;
	}
	if (tag[x]!=inf) downtag(x);
	int mid=lx+rx>>1;
	if (l<=mid) update(lch[x],l,r,lx,mid,delta);
	if (r>mid) update(rch[x],l,r,mid+1,rx,delta);
	mn[x]=min(mn[lch[x]],mn[rch[x]]);
}

int query(int x,int l,int r,int lx,int rx)
{
	if (l<=lx&&rx<=r)
		return mn[x];
	int mid=lx+rx>>1,ret=inf;
	if (tag[x]!=inf) downtag(x);
	if (l<=mid) ret=min(ret,query(lch[x],l,r,lx,mid));
	if (r>mid) ret=min(ret,query(rch[x],l,r,mid+1,rx));
	mn[x]=min(mn[lch[x]],mn[rch[x]]);
	return ret;
}

int downtag(int x)
{
	mn[lch[x]]=min(mn[lch[x]],tag[x]); tag[lch[x]]=min(tag[lch[x]],tag[x]); //min or =
	mn[rch[x]]=min(mn[rch[x]],tag[x]); tag[rch[x]]=min(tag[rch[x]],tag[x]); //min or =
	tag[x]=inf;
}

int get_lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

int go(int x,int d)
{
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=d)
			x=f[x][i];
	return dep[x]==d?x:-1;
}

int work(int x,int y,int delta)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,dfn[top[x]],dfn[x],1,n,delta);
		x=f[top[x]][0];
	}
	if (dfn[x]>dfn[y]) swap(x,y);
	update(1,dfn[x],dfn[y],1,n,delta);
}

int solve(int x)
{
	now[0]=0;
	for (int i=0;i<cross[x].size();++i)
		now[++now[0]]=cross[x][i];
	int cnt=0,fx,fy,ret=0,soncnt=0;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		if (a[i].y==f[x][0]) continue;
		id[a[i].y]=++soncnt;
		if (out[a[i].y]!=inf) now[++now[0]]=-a[i].y;
	}//num_out<0  num_cross>0
	id[f[x][0]]=++soncnt;
	if (x==1) --soncnt;
	for (int i=1;i<=soncnt;++i) 
		fa[i]=i;
	sort(now+1,now+1+now[0],cmp1);

	cnt=0;
	for (int i=1;i<=now[0]&&cnt<soncnt-1;++i)
	{
		if (now[i]<0&&x!=1)
		{
			fx=get_f(id[-now[i]]),fy=get_f(id[f[x][0]]);
			if (fx!=fy)
			{
				++cnt; fa[fx]=fy; ret+=out[-now[i]];
			}
		}
		else
		{
			fx=get_f(id[go(bian[now[i]].x,dep[x]+1)]),fy=get_f(id[go(bian[now[i]].y,dep[x]+1)]);
			if (fx!=fy)
			{
				++cnt; fa[fx]=fy; ret+=bian[now[i]].dis;
			}
		}
	}
	return cnt==soncnt-1?ret:-1;
}

bool cmp1(int x,int y)
{
	int tmpx=x<0?out[-x]:bian[x].dis;
	int tmpy=y<0?out[-y]:bian[y].dis;
	return tmpx<tmpy;
}

bool cmp(bian1 x,bian1 y)
{
	return x.dis<y.dis;
}
