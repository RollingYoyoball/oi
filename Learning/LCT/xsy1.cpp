#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 51061
#define ll unsigned int
using namespace std;
const int MAXN=1e5+10;
int w[MAXN],h[MAXN];
struct xxx
{
	int y,next;
}a[MAXN*2];
struct LinkCutTree
{
	int ch[MAXN][2],rev[MAXN];
	ll taga[MAXN],tagt[MAXN],fa[MAXN],sz[MAXN],sum[MAXN];
	bool isroot(int x) {return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int which(int x) {return ch[fa[x]][1]==x;}
	int downtag(int x,int deltaa,int deltat)
	{
		taga[x]=(taga[x]*deltat+deltaa)%MOD; 
		tagt[x]=(tagt[x]*deltat)%MOD;
		sum[x]=((ll)sum[x]*deltat+(ll)sz[x]*deltaa)%MOD;
		w[x]=((ll)w[x]*deltat+deltaa)%MOD;
	}
	int update(int x)
	{
		sum[x]=(sum[ch[x][0]]+sum[ch[x][1]]+w[x])%MOD;
		sz[x]=(sz[ch[x][0]]+sz[ch[x][1]]+1)%MOD;
	}
	int pushdown1(int x)
	{
		if (tagt[x]!=1||taga[x])
		{
			if (ch[x][0]) downtag(ch[x][0],taga[x],tagt[x]);
			if (ch[x][1]) downtag(ch[x][1],taga[x],tagt[x]);
			taga[x]=0;
			tagt[x]=1;
		}
		if (rev[x])
		{
			if (ch[x][0]) reverse(ch[x][0]);
			if (ch[x][1]) reverse(ch[x][1]);
			rev[x]=0;
		}
	}
	int pushdown(int x)
	{
		if (!isroot(x)) pushdown(fa[x]);
		pushdown1(x);
	}
	int rotate(int x)
	{
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f];
		ch[f][dir]=ch[x][dir^1]; fa[ch[x][dir^1]]=f;
		ch[x][dir^1]=f; fa[f]=x;
		update(f);
		update(x);
	}
	int reverse(int x)
	{
		rev[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
	int splay(int x)
	{
		pushdown(x);
		for (int f=fa[x];!isroot(x);f=fa[x])
		{
			if (!isroot(f))
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
	}
	int access(int x)
	{
		for (int last=0;x;last=x,x=fa[x])
		{
			splay(x);
			ch[x][1]=last;
			update(x);
		}
	}
	int make_rt(int x)
	{
		access(x);
		splay(x);
		reverse(x);
	}
	int link(int x,int y)
	{
		make_rt(x);
		fa[x]=y;
	}
	int cut(int x,int y)
	{
		make_rt(x);
		access(y);
		splay(y);
		fa[x]=0;
		ch[y][0]=0;
		update(y);
	}
	int add(int x,int y,int delta)
	{
		make_rt(x);
		access(y);
		splay(y);
		downtag(y,delta,1);
	}
	int times(int x,int y,int delta)
	{
		make_rt(x);
		access(y);
		splay(y);
		downtag(y,0,delta);
	}
	int get_ans(int x,int y)
	{
		make_rt(x);
		access(y);
		splay(y);
		return (sum[ch[y][0]]+w[y])%MOD;
	}
	int dfs(int fa1,int x)
	{
		int u;
		fa[x]=fa1; sz[x]=1; sum[x]=1; w[x]=1;
		for (int i=h[x];i;i=a[i].next)
		{
			u=a[i].y;
			if (u==fa1) continue;
			dfs(x,u);
		}
	}
	int init(int n)
	{
		for (int i=1;i<=n;++i)
		{
			ch[i][0]=ch[i][1]=fa[i]=0;
			sz[i]=sum[i]=1;
			tagt[i]=1;
			taga[i]=0;
			w[i]=1;
		}
	}
}lct;
int n,m,tot;
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	int x,y,delta,x1,y1;
	scanf("%d%d",&n,&m);
	lct.init(n);
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		lct.link(x,y);
	}
	char op[5];
	for (int i=1;i<=m;++i)
	{
		scanf("%s",op);
		if (op[0]=='+')
		{
			scanf("%d%d%d",&x,&y,&delta);
			lct.add(x,y,delta);
		}
		else if (op[0]=='-')
		{
			scanf("%d%d%d%d",&x,&y,&x1,&y1);
			lct.cut(x,y);
			lct.link(x1,y1);
		}
		else if (op[0]=='*')
		{
			scanf("%d%d%d",&x,&y,&delta);
			lct.times(x,y,delta);
		}
		else
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",lct.get_ans(x,y));
		}
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
