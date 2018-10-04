#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<stdlib.h>
using namespace std;
const int MAXN=(1e5+10)*20;
int a[MAXN];
struct Treap
{
	int ch[MAXN][2],fix[MAXN],sz[MAXN],val[MAXN];//0=lch,1=rch
	int id[MAXN],fa[MAXN],rt[MAXN];
	int tot;
	int rotate(int &x,int d)//turn_right=1,turn_left=0
	{
		int tmp=ch[x][d^1];
		ch[x][d^1]=ch[tmp][d];
		ch[tmp][d]=x;
		sz[tmp]=sz[x];
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
		x=tmp;
	}
	int newnode(int v,int num)
	{
		++tot; rt[tot]=tot; fa[tot]=tot;
		sz[tot]=1;
		val[tot]=v;
		id[tot]=num;
		fix[tot]=rand();//remember to change it back
		return tot;
	}
	int insert(int x,int v,int pos) {_insert(rt[x],v,pos);}
	int _insert(int &x,int v,int num)
	{
		if (!x) 
		{x=newnode(v,num);return 0;}
		if (v<val[x])
		{
			_insert(ch[x][0],v,num);
			if (fix[ch[x][0]]<fix[x]) rotate(x,1);
		}
		else
		{
			_insert(ch[x][1],v,num);
			if (fix[ch[x][1]]<fix[x]) rotate(x,0);
		}
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
	}
	int get_fa(int x)
	{
		if (fa[x]!=x) fa[x]=get_fa(fa[x]);
		return fa[x];
	}
	int merge(int x,int y)
	{
		x=get_fa(x); y=get_fa(y);
		if (x==y) return 0;
		if (sz[rt[x]]<sz[rt[y]]) swap(x,y);
		fa[y]=x;
		a[0]=0;
		dfs(rt[y]);
		for (int i=1;i<=a[0];++i)
			_insert(rt[x],val[a[i]],id[a[i]]);
	}
	int dfs(int x)
	{
		if (!x) return 0;
		dfs(ch[x][0]);
		a[++a[0]]=x;
		dfs(ch[x][1]);
	}
	int get_kth(int x,int k) 
	{
		x=rt[get_fa(x)];
		if (sz[x]<k) return -1;
		return _get_kth(x,k);
	}
	
	int _get_kth(int x,int k)
	{
		if (!x) return 0;
		int lch=ch[x][0],rch=ch[x][1];
		if (k==sz[lch]+1) return id[x];
		if (k>sz[lch]+1)
			return _get_kth(rch,k-sz[lch]-1);
		return _get_kth(lch,k);
	}

}tr;
int n,m;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,y;
	char op[2];
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%d",&x),tr.insert(i,x,i);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		tr.merge(x,y);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i)
	{
		scanf("%s %d %d",op,&x,&y);
		if (op[0]=='Q')
		{
			printf("%d\n",tr.get_kth(x,y));
		}
		else
		{
			tr.merge(x,y);
		}
	}
}
