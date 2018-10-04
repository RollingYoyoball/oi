#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
const int MAXN=100010;
const int MAXM=4010010;
struct xxx
{
	int y,next;
}a[MAXN];
struct xxx1
{
	int sz,y;
	bool operator < (const xxx1 b) const
	{ return sz>b.sz;}
};
priority_queue<xxx1> q[MAXN];
int h[MAXN];
int ch[MAXM][26],pre[MAXN],f[MAXN],size[MAXN];
int mark[MAXM];
int n,m,tot;
ll ans;
int insert(int xx,char *s,int len);
int dfs(int x,int pre1);
int get_sz(int x,int dep);
int newnode();
int add(int x,int y);
int work(int x);

int main()
{
	freopen("a.in","r",stdin);

	char s[MAXN];
	scanf("%d",&n);
	tot=1;
	for (int i=1;i<=n;++i)
	{
		scanf("%s\n",s);
		insert(i,s,strlen(s));	
	}
	tot=0;
	memset(h,-1,sizeof(h));
	dfs(1,0);
	get_sz(0,1);
	tot=0;
	work(0);
	for (int i=1;i<=n;++i)
		ans+=f[i]-f[pre[i]];
	printf("%lld\n",ans);
}

int insert(int xx,char *s,int len)
{
	int now=1;
	for (int i=len-1;i>=0;--i)
	{
		if (!ch[now][s[i]-'a']) ch[now][s[i]-'a']=newnode();
		now=ch[now][s[i]-'a'];
	}
	mark[now]=xx; 
}

int newnode()
{
	mark[++tot]=0;
	return tot;
}

int dfs(int x,int pre1)
{
	if (mark[x]&&x!=1) 
		add(pre1,mark[x]),pre[mark[x]]=pre1;
	for (int i=0;i<26;++i)
	{
		if (!ch[x][i]) continue;
		if (mark[x]) dfs(ch[x][i],mark[x]);
		else dfs(ch[x][i],pre1);
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int get_sz(int x,int dep)
{
	size[x]=1;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		get_sz(a[i].y,dep+1);
		xxx1 x1;
		x1.sz=size[a[i].y],x1.y=a[i].y;
		q[x].push(x1);
		size[x]+=size[a[i].y];
	}
}

int work(int x)
{
	xxx1 tmp;
	if (x!=0) f[x]=++tot;
	while (!q[x].empty())
	{
		tmp=q[x].top();
		work(tmp.y),q[x].pop();
	}
}
