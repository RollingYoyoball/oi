#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=(1e5)*3+10;
int w[MAXN];
struct xxx
{
	int x,y,next;
}a[MAXN*2];
int h[MAXN];
struct LinkCutTree
{
	int ch[MAXN][2],rev[MAXN],tag[MAXN],mx[MAXN],fa[MAXN];
	int tot;

	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	int which(int x)
	{
		return ch[fa[x]][1]==x;
	}
	int downtag(int x,int delta)
	{
		mx[x]+=delta; tag[x]+=delta; w[x]+=delta;
	}
	int reverse(int x)
	{
		rev[x]^=1;
		swap(ch[x][1],ch[x][0]);
	}
	int update(int x)
	{
		mx[x]=max(w[x],max(mx[ch[x][0]],mx[ch[x][1]]));
	}
	int pushdown1(int x)
	{
		if (tag[x])
		{
			if (ch[x][0]) downtag(ch[x][0],tag[x]);
			if (ch[x][1]) downtag(ch[x][1],tag[x]);
			tag[x]=0;
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
		if (connected(x,y)) {printf("-1\n"); return 0;}
		make_rt(x);
		fa[x]=y;
	}
	int cut(int x,int y)
	{
		if (!connected(x,y)) {printf("-1\n");return 0;}
		make_rt(x);
		access(y);
		splay(y);
		fa[x]=0;
		ch[y][0]=0;
		update(y);
	}
	bool connected(int x,int y)
	{
		if (x==y) return true;
		make_rt(x);
		access(y);
		splay(y);
		return fa[x];
	}
	int add(int x,int y,int delta)
	{
		if (!connected(x,y)) {printf("-1\n"); return 0;}
		make_rt(x);
		access(y);
		splay(y);
/*		update(y);
		downtag(y,delta);*/
	}
	int getmx(int x,int y)
	{
		if (!connected(x,y)) {printf("-1\n"); return 0;}
		make_rt(x);
		access(y);
		splay(y);
		printf("%d\n",max(mx[ch[y][0]],w[y]));
	}
	int dfs(int fa1,int x)
	{
		int u;
		fa[x]=fa1;
		mx[x]=w[x];
		for (int i=h[x];i;i=a[i].next)
		{
			u=a[i].y;
			if (u==fa1) continue;
			dfs(x,u);
		}
	}
}lct;
int n,m,tot;
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	int op,x,y,delta;
	scanf("%d",&n);
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	for (int i=1;i<=n;++i)
		scanf("%d",w+i);
	lct.dfs(0,1);
	scanf("%d",&m);
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d%d",&x,&y);
			lct.link(x,y);
		}
		else if (op==2)
		{
			scanf("%d%d",&x,&y);
			if (!lct.connected(x,y)) {printf("-1\n"); continue;}
			lct.cut(x,y);
		}
		else if (op==3)
		{
			scanf("%d%d%d",&delta,&x,&y);
			lct.add(x,y,delta);
		}
		else if (op==4)
		{
			scanf("%d%d",&x,&y);
			lct.getmx(x,y);
		}
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].x=x;
}
