#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
const int MAXN=100001;
map<int,int> ch[MAXN];
queue<int> q;
vector<int> miao[2][20001],to[MAXN];
int f[MAXN],id[50001],sum[20001],cnt[MAXN],vis[MAXN],len1[20001],len2[20001],mark[MAXN];
int n,m,mx,tot;
int insert(int len,int xx);
int get_f();
int work(int x,int i);

int main()
{
	int x;
	scanf("%d%d\n",&n,&m);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&len1[i]);
		for (int j=1;j<=len1[i];++j) 
			scanf("%d",&x),miao[0][i].push_back(x);
		scanf("%d",&len2[i]);
		for (int j=1;j<=len2[i];++j) 
			scanf("%d",&x),miao[1][i].push_back(x);
	}
	tot=0;
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&x);
		insert(x,i);
	}
	get_f();	
	int u;
	for (int i=1;i<=n;++i)
	{
		u=0;
		for (int j=0;j<len1[i];++j)
		{
			while (u&&!ch[u][miao[0][i][j]]) u=f[u];
			if (ch[u][miao[0][i][j]]) u=ch[u][miao[0][i][j]];
			work(u,i);
		}
		u=0;
		for (int j=0;j<len2[i];++j)
		{
			while (u&&!ch[u][miao[1][i][j]]) u=f[u];
			if (ch[u][miao[1][i][j]]) u=ch[u][miao[1][i][j]];
			work(u,i);
		}
	}
	for (int i=1;i<=m;++i) printf("%d\n",cnt[id[i]]);
	for (int i=1;i<=n;++i) printf("%d ",sum[i]);
}

int insert(int len,int xx)
{
	int now=0,x;
	for (int i=1;i<=len;++i)
	{
		scanf("%d",&x);
		if (!ch[now][x]) 
			ch[now][x]=++tot,to[now].push_back(x);
		now=ch[now][x];
	}
	id[xx]=now; ++mark[now];
}

int get_f()
{
	int v,u;
	for (int i=0;i<to[0].size();++i)
		if (ch[0][to[0][i]]) q.push(ch[0][to[0][i]]),f[ch[0][to[0][i]]]=0;
	while (!q.empty())
	{
		v=q.front(); q.pop();
		for (int i=0;i<to[v].size();++i)
		{
			u=f[v];
			while (u&&!ch[u][to[v][i]]) u=f[u];
			f[ch[v][to[v][i]]]=ch[u][to[v][i]];
			q.push(ch[v][to[v][i]]);
		}
	}
}

int work(int x,int i)
{
	while (x) 
	{
		if (mark[x]&&vis[x]!=i) 
			++cnt[x],sum[i]+=mark[x],vis[x]=i;
		x=f[x];
	}
}

//由于一个节点可能有的儿子会很多，所以要开一个数组（vector）来记录有什么儿子，不然的话。。会T。。。 
