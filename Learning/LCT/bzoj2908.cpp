//xsy1663
#include<iostream>
#include<cstdio>
#include<cstring>
#define MX 32
#define ll long long
using namespace std;
const int MAXN=1e5+10;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN];
int n,k,m,tot;
int nand(int x,int y) {return !(x&y);}
struct LCT
{
	int ch[MAXN][2],fa[MAXN],rev[MAXN];
	int l[MAXN][MX][2],r[MAXN][MX][2],val[MAXN][MX];
	bool isroot(int x) {return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int which(int x) {return ch[fa[x]][1]==x;}
	int update(int x)
	{
		int lch=ch[x][0],rch=ch[x][1];
		for (int i=0;i<k;++i)
		{
			l[x][i][0]=l[rch][i][nand(l[lch][i][0],val[x][i])];
			l[x][i][1]=l[rch][i][nand(l[lch][i][1],val[x][i])];
			r[x][i][0]=r[lch][i][nand(r[rch][i][0],val[x][i])];
			r[x][i][1]=r[lch][i][nand(r[rch][i][1],val[x][i])];
		}
	}
	int pushdown1(int x)
	{
		if (!rev[x]) return 0;
		if (ch[x][0]) reverse(ch[x][0]);
		if (ch[x][1]) reverse(ch[x][1]);
		rev[x]=0;
	}
	int pushdown(int x)
	{
		if (!isroot(x)) pushdown(fa[x]);
		pushdown1(x);
	}
	int reverse(int x)
	{
		rev[x]^=1;
		swap(ch[x][0],ch[x][1]);
		for (int i=0;i<k;++i)
		{
			swap(l[x][i][0],r[x][i][0]);
			swap(l[x][i][1],r[x][i][1]);
		}
	}
	int rotate(int x)
	{
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
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
		update(x);
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
	ll query(int x,int y)
	{
		ll ret=0;
		make_rt(x);
		access(y);
		splay(y);
		for (int i=0;i<k;++i)
			ret+=l[y][i][0]*((ll)1<<i);
		return ret;
	}
	int get_val(int x,ll num)
	{
		for (int i=0;i<k;++i)
			val[x][i]=(num>>i)&1LL;
	}
	int change(int x,ll num)
	{
		get_val(x,num);
		access(x);
		splay(x);
	}
	int init()
	{
		for (int i=0;i<k;++i)
		{
			l[0][i][0]=r[0][i][0]=0;
			l[0][i][1]=r[0][i][1]=1;
		}
		for (int i=1;i<=n;++i) update(i);
	}
}lct;
int build(int fa,int x);
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	ll val;
	int x,y;
	char op[10];
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;++i)
	{
		scanf("%lld",&val);
		lct.get_val(i,val);
	}
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	build(0,1);
	lct.init();
	for (int i=1;i<=m;++i)
	{
		scanf("%s%d",op,&x);
		if (op[0]=='R')
		{
			scanf("%lld\n",&val);
			lct.change(x,val);
		}
		else
		{
			scanf("%d\n",&y);
			printf("%lld\n",lct.query(x,y));
		}
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int build(int fa,int x)
{
	int u;
	for (int i=h[x];i;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		lct.fa[u]=x;
		build(x,u);
	}
}
