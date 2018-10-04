#include<iostream>
#include<cstdio>
#include<cstring>
#define lch(x) ch[0][x]
#define rch(x) ch[1][x]
#define ll long long
using namespace std;
const int MAXN=1e5+10;
ll val[MAXN];
int n,m,k;
int nand(int x,int y) {return !(x&y);}
struct data
{
	int v[2][32];
	ll get_val()
	{
		ll ret=0;
		for (int i=k-1;i>=0;--i)
			ret=(ret<<1)|v[0][i];
		return ret;
	}
};
struct LinkCutTree
{
	int ch[2][MAXN],fa[MAXN],rev[MAXN],num[MAXN][32];
	int l[MAXN][32][2],r[MAXN][32][2];
	bool isroot(int x)
	{
		return !x||(lch(fa[x])!=x&&rch(fa[x])!=x);
	}
	int update(int x)
	{
		for (int i=0;i<k;++i) 
		{
			l[x][i][0]=l[rch(x)][i][nand(l[lch(x)][i][0],num[x][i])];
			l[x][i][1]=l[rch(x)][i][nanx(l[lch(x)][i][1],num[x][i])];
			r[x][i][0]=r[lch(x)][i][nand(r[rch(x)][i][0],num[x][i])];
			r[x][i][1]=r[lch(x)][i][nand(r[rch(x)][i][1],num[x][i])];
		}
	}
	int rotate(int x)
	{
		int f=fa[x],dir=x==ch[1][fa[x]];
		if (!isroot(f)) ch[f==ch[1][fa[f]]][fa[f]]=x;
		fa[x]=fa[f]; fa[f]=x; fa[ch[dir^1][x]]=f;
		ch[dir][f]=ch[dir^1][x];
		ch[dir^1][x]=f;
		update(f); update(x);
	}
	int revese(int x)
	{
		rev[x]^=1;
		swap(lch(x),rch(x));
		for (int i=0;i<k;++i)
		{
			swap(l[x][i][0],r[x][i][0]);
			swap(l[x][i][1],r[x][i][1]);
		}
	}
	int pushdown(int x)
	{
		if (!isroot(x)) pushdown(fa[x]);
		if (rev[x])
		{
			if (lch(x)) rev[lch(x)]^=1;
			if (rch(x)) rev[rch(x)]^=1;
			rev[x]=0;
		}
	}
	int splay(int x)
	{
		pushdown(x);
		for (int f=fa[x];isroot(x);f=fa[x])
		{
			if (isroot(f)) rotate(x);
			else
			{
				if ((lch(f)==x)^(lch(fa[f])==f)) rotate(x);
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
			rch(x)=last;
			update(x);
		}
	}
	int make_rt(int x)
	{
		access(x);
		splay(x);
		rev[x]=1;
	}
	int change(int x,ll delta)
	{
		make_rt(x);
		access(x);
		for (int i=0;i<k;++i)
			num[x][i]=delta&(1<<i)?1:0;
		update(x);
	}
	ll query(int x,int y)
	{
		make_rt(x);
		access(y);
		return info_l[y].get_val();
	}
}lct;
struct xxx
{
	int y,next;
}a[MAXN];
int h[MAXN];
int tot;
int dfs(int fa,int x);
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;++i)
		scanf("%d",val+i);
	int x,y;
	ll z;
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	for (int i=1;i<=n;++i)
	{
		for (int j=0;j<k;++j)
			num[i][j]=val[i]&(1<<j)?1:0;
	}
	char op[10];
	dfs(0,1);
	for (int i=1;i<=n;++i)
	{
		for (int j=0;j<k;++j)
			printf("%d ",num[i][j]);
		printf("\n");
	}
	for (int i=1;i<=m;++i)
	{
		scanf("%s",op);
		if (op[0]=='Q')
		{
			scanf("%d%d\n",&x,&y);
			printf("%lld\n",lct.query(x,y));
		}
		else
		{
			scanf("%d%lld\n",&x,&z);
			lct.change(x,z);
		}
	}
}

int dfs(int fa,int x)
{
	lct.fa[x]=fa;
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
