#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1000010;
int lch[MAXN],rch[MAXN],val[MAXN],dis[MAXN],rt[MAXN];
bool godie[MAXN];
int n,m;
int merge(int x,int y);
int del(int x);
int get_rt(int x){if (rt[x]!=x) rt[x]=get_rt(rt[x]); return rt[x];}

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);

	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",val+i),rt[i]=i;
	char op;
	int x,y;
	memset(godie,false,sizeof(godie));
	scanf("%d\n",&m);
	for (int i=1;i<=m;++i)
	{
		scanf("%c",&op);
		if (op=='K')
		{
			scanf("%d\n",&x);
			if (godie[x]) {printf("0\n");continue;}
			x=get_rt(x);
			printf("%d\n",val[x]);
			godie[x]=true;
			rt[x]=del(x);
			rt[rt[x]]=rt[x];
		}
		else
		{
			scanf("%d%d\n",&x,&y);
			if (godie[x]||godie[y]) continue;
			x=get_rt(x);
			y=get_rt(y);
			if (x!=y)
				rt[x]=merge(x,y),rt[y]=rt[x];
		}
	}
}

int merge(int x,int y)
{
	if (x==0||y==0) return x+y;
	if (val[x]>val[y]) swap(x,y);
	rch[x]=merge(rch[x],y);
	if (dis[lch[x]]<dis[rch[x]]) swap(lch[x],rch[x]);
	dis[x]=dis[rch[x]]+1;
	return x;
}

int del(int x)
{
	return merge(lch[x],rch[x]);
}
