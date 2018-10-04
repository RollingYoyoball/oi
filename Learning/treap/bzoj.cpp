#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<stdlib.h>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN];
int n,m;
struct Treap
{
	int ch[MAXN][2],fix[MAXN],sz[MAXN],val[MAXN];//0=lch,1=rch
	int tot,rt;
	int rotate(int &x,int d)//turn_right=1,turn_left=0
	{
		int tmp=ch[x][d^1];
		ch[x][d^1]=ch[tmp][d];
		ch[tmp][d]=x;
		sz[tmp]=sz[x];
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
		x=tmp;
	}
	int newnode(int x)
	{
		++tot;
		sz[tot]=1;
		val[tot]=x;
		fix[tot]=rand();//remember to change it back
		return tot;
	}
	int insert(int pos,int v) {_insert(rt,pos,v);}
	int _insert(int &x,int pos,int v)
	{
		if (!x) 
			{x=newnode(v);return 0;}
		if (pos<=sz[ch[x][0]])
		{
			_insert(ch[x][0],pos,v);
			if (fix[ch[x][0]]<fix[x]) rotate(x,1);
		}
		else
		{
			_insert(ch[x][1],pos-sz[ch[x][0]]-1,v);
			if (fix[ch[x][1]]<fix[x]) rotate(x,0);
		}
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
	}
	int get_a() {dfs(rt);}
	int dfs(int x)
	{
		if (!x) return 0;
		dfs(ch[x][0]);
		a[++a[0]]=val[x];
		dfs(ch[x][1]);
	}

}treap;
struct cnting
{
	int c[MAXN];
	int update(int x,int delta)
	{
		for (;x<=n;x+=x&-x)
			c[x]=max(c[x],delta);
	}
	int query(int x)
	{
		int ret=0;
		for (;x;x-=x&-x)
			ret=max(c[x],ret);
		return ret;
	}
}c;
int ans[MAXN];

int main()
{
//	freopen("a.in","r",stdin);
	
	int x;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		treap.insert(x,i);
	}
	treap.get_a();
	for (int i=1;i<=a[0];++i)
	{
		int tmp=c.query(a[i])+1;
		c.update(a[i],tmp);
		ans[a[i]]=tmp;
	}
	for (int i=1;i<=n;++i)
		ans[i]=max(ans[i],ans[i-1]);
	for (int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
}
