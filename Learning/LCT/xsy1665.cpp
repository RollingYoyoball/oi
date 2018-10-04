#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define lch(x) ch[0][x]
#define rch(x) ch[1][x]
#define inf 10000000
using namespace std;
const int MAXN=1e5+10;
int v[MAXN];
multiset<int> s[MAXN];
struct LineCutTree
{
	int ch[2][MAXN],fa[MAXN],mn[MAXN],rev[MAXN];
	bool isroot(int x)
	{
		if (!x) return true;
		return lch(fa[x])!=x&&rch(fa[x])!=x;
	}
	int update(int x)
	{
		mn[x]=min(*s[x].begin(),min(lch(x)?mn[lch(x)]:inf,rch(x)?mn[rch(x)]:inf));
	}
	int rotate(int x)
	{
		int dir=ch[1][fa[x]]==x,f=fa[x];
		if (!isroot(f)) ch[f==ch[1][fa[f]]][fa[f]]=x;
		fa[x]=fa[f],fa[f]=x,fa[ch[dir^1][x]]=f;
		ch[dir][f]=ch[dir^1][x];
		ch[dir^1][x]=f;
		update(f);
		update(x);
	}
	int pushdown(int x)
	{
		if (!isroot(x)) pushdown(fa[x]);
		if (!rev[x]) return 0;
		if (lch(x)) rev[lch(x)]^=1;
		if (rch(x)) rev[rch(x)]^=1;
		swap(lch(x),rch(x));
		rev[x]=0;
	}
	int splay(int x)
	{
		pushdown(x);
		for (int f=fa[x];!isroot(x);f=fa[x])
		{
			if (isroot(f)) rotate(x);
			else
			{
				if ((lch(fa[f])==f)^(lch(f)==x)) rotate(x);
				else rotate(f);
				rotate(x);
			}
		}
	}
	int access(int x)
	{
		for (int last=0;x;last=x,x=fa[x])
		{
			splay(x);
			if (rch(x)) s[x].insert(mn[rch(x)]);
			rch(x)=last;
			if (rch(x)) s[x].erase(s[x].lower_bound(mn[rch(x)]));
			update(x);
		}
	}
	int make_rt(int x)
	{
		access(x);
		splay(x);
		rev[x]=1;
	}
	int link(int x,int y)
	{
		make_rt(x);
		fa[x]=y;		
	}
	int change(int x,int delta)
	{
		access(x);
		splay(x);
		//print(x);
		s[x].erase(s[x].lower_bound(v[x]));
		v[x]=delta;
		s[x].insert(v[x]);
		//print(x);
		update(x);
	}
	int print(int x)
	{
		for (multiset<int>::iterator it=s[x].begin();it!=s[x].end();++it)
			printf("%d ",*it);
		printf("\n");
	}
}lct;
struct xxx
{
	int y,next;
}a[MAXN];
int h[MAXN];
int n,m,root,tot;
int dfs(int x);
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d",&lct.fa[i],&v[i]);
		if (lct.fa[i]) add(lct.fa[i],i);
	}
	root=1;
	dfs(root);
	char op[2];
	int x,y;
	for (int i=1;i<=m;++i)
	{
		scanf("%s",op);
		if (op[0]=='V')
		{
			scanf("%d%d",&x,&y);
			lct.change(x,y);
		}
		else if (op[0]=='E')
		{
			scanf("%d",&x);
			lct.make_rt(x);
		}
		else
		{
			scanf("%d",&x);
			lct.access(x);
			printf("%d\n",*s[x].begin());
		}
	}
}

int dfs(int x)
{
	s[x].insert(v[x]);
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==lct.fa[x]) continue;
		dfs(u);
		s[x].insert(lct.mn[u]);
	}
	lct.update(x);
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
