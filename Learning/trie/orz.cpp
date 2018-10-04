#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#define F(i,j,n) for(int i=j;i<=n;i++)
#define D(i,j,n) for(int i=j;i>=n;i--)
#define ll long long
#define pa pair<int,int>
#define N 100005
#define M 520005
using namespace std;
int n,tot=1,cnt,a[M][26],id[M],fa[N],head[N],sz[N],f[N];
ll ans;
char s[M];
struct edge{int next,to;}e[N];
vector<pa> v[N];
void add_edge(int x,int y)
{
	e[++cnt]=(edge){head[x],y};
	head[x]=cnt;fa[y]=x;
}
void dfs(int x,int f)
{
	if (id[x]) add_edge(f,id[x]),f=id[x];
	F(i,0,25) if (a[x][i]) dfs(a[x][i],f);
}
void getsz(int x)
{
	sz[x]=1;
	for(int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		getsz(y);
		v[x].push_back(make_pair(sz[y],y));
		sz[x]+=sz[y];
	}
	sort(v[x].begin(),v[x].end());
}
void getf(int x)
{
	if (x) f[x]=++tot;
	for(int i=0;i<v[x].size();i++) getf(v[x][i].second);
}
int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%d",&n);
	F(i,1,n)
	{
		scanf("%s",s+1);
		int len=strlen(s+1),now=1,x;
		D(j,len,1)
		{
			x=s[j]-'a';
			if (!a[now][x]) a[now][x]=++tot;
			now=a[now][x];
		}
		id[now]=i;
	}
	dfs(1,0);
	getsz(0);
	tot=0;
	getf(0);
	F(i,1,n) ans+=f[i]-f[fa[i]];
	cout<<ans<<endl;
	return 0;
}

