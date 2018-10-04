#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 2147483647
#define ll long long
using namespace std;
const int MAXN=40000;
int n,m;
struct Splay
{
	int ch[MAXN][2],val[MAXN],fa[MAXN];
	int tot,rt;
	int newnode()
	{
		ch[++tot][0]=ch[tot][1]=0;
		return tot;
	}
	int insert(int delta) 
	{int ret=_insert(rt,delta);splay(ret);rt=ret;return ret;}
	int _insert(int &x,int delta)
	{
		if (!x)
		{
			x=newnode();
			val[x]=delta;
			return x;
		}
		int v;
		if (delta<val[x])
		{
			v=_insert(ch[x][0],delta);
			fa[ch[x][0]]=x;
		}
		else
		{
			v=_insert(ch[x][1],delta);
			fa[ch[x][1]]=x;
		}
		return v;
	}
	int which(int x) {return ch[fa[x]][1]==x;}
	bool isroot(int x) {return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int rotate(int x)
	{
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
		//update(f); update(x);
	}
	int splay(int x)
	{
		for (int f=fa[x];!isroot(x);f=fa[x])
		{
			if (!isroot(f))
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
	}
	int get_pre(int x)
	{
		int ret=ch[x][0];
		while (ch[ret][1]) ret=ch[ret][1];
		return ret;
	}
	int get_nxt(int x)
	{
		int ret=ch[x][1];
		while (ch[ret][0]) ret=ch[ret][0];
		return ret;
	}
	int query(int x)
	{
		int pre=get_pre(x),nxt=get_nxt(x);
		int ret=inf;
		if (pre) ret=val[x]-val[pre];
		if (nxt) ret=min(ret,val[nxt]-val[x]);
		return ret;
	}
}splay;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,loc;
	ll ans=0;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		loc=splay.insert(x);
		if (i>1) ans+=splay.query(loc);
		else ans+=x;
	}
	printf("%lld\n",ans);
}
