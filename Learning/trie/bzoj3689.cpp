#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=100010;
const int MAX=31;
struct xxx1
{
	int num,k,v;
	bool operator <(const xxx1 a) const
	{return num>a.num;}
};
priority_queue<xxx1> q;
int a1[MAXN],ch[MAXN][2],cnt[MAXN],fa[MAXN],mark[MAXN];
int n,m,tot;
int insert(int x);
int query(int x,int k);

int main()
{
	freopen("a.in","r",stdin);

	xxx1 x;
	scanf("%d%d\n",&n,&m);
	tot=1;
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a1[i]);
		insert(a1[i]);
	}
	for (int i=1;i<=n;++i)
	{
		x.num=query(a1[i],2);
		x.v=a1[i];
		x.k=2;
		q.push(x);
	}
	int num=0;
	for (int i=1;i<=m*2;++i)
	{
		x=q.top();
		if (i%2==1) printf("%d ",x.num);
		q.pop();
		x.k++;
		x.num=query(x.v,x.k);
		if (x.k<=n) q.push(x);	
	}
}

int insert(int x)
{
	int now=1;
	for (int i=MAX;i>=0;--i)
	{
		bool w=x&(1<<i);
		if (!ch[now][w]) ch[now][w]=++tot;
		now=ch[now][w];
		++cnt[now];
	}	
}

int query(int x,int k)
{
	int now=1,re=0;
	for (int i=MAX;i>=0;--i)
	{
		bool w=x&(1<<i);
		if (cnt[ch[now][w]]>=k) now=ch[now][w];
		else k-=cnt[ch[now][w]],now=ch[now][!w],re=re+(1<<i);
	}
	return re; 
}
