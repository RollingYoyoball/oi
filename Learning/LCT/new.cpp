#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=30010;
int w[MAXN];
struct LinkCutTree
{
	int ch[MAXN][2],fa[MAXN],mx[MAXN],rev[MAXN];
	int tot;
	bool isroot(int x)
	{
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	int which(int x)
	{
		return ch[fa[x]][1]==x;
	}
	int update(int x)
	{
		if (!x) return 0;
		mx[x]=max(w[x],max(mx[ch[x][0]],mx[ch[x][1]]));
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
	}
	int rotate(int x)
	{
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
		update(f); update(x);
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
	bool connected(int x,int y)
	{
		if (x==y) return true;
		make_rt(x);
		access(y);
		splay(y);
		return fa[x];
	}
};

int main()
{
	freopen("a.in","r",stdin);

}
