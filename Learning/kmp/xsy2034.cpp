#include<iostream>
#include<cstring>
#include<cstdio>
#define ll int//long long
#define inf 2147483647//9223372036854775807
using namespace std;
const int MAXN=100010;
struct xxx
{
	ll a[210][210];
}f,origin,tmp;
char s[210][MAXN];
int nxt[MAXN],len[MAXN];
int n,m;
ll ans;
int work(int x,int y);
int get_nxt(int x);
void solve(int m);
xxx calc(xxx a,xxx b);

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%s",s[i]),len[i]=strlen(s[i]);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			origin.a[i][j]=len[j];
	for (int i=1;i<=n;++i)
	{
		get_nxt(i);
		for (int j=1;j<=n;++j)
			if (i!=j) work(i,j);
	}	
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			f.a[i][j]=inf;
	if (m>1) solve(m-1);
	else memset(f.a,0,sizeof(f.a));
	ans=inf;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			ans=min(ans,f.a[i][j]+len[i]);
	printf("%d\n",ans);	
}

int get_nxt(int x)
{
	nxt[0]=-1;
	int j=-1;
	for (int i=1;i<len[x];++i)
	{
		while (j!=-1&&s[x][j+1]!=s[x][i]) j=nxt[j];
		if (s[x][j+1]==s[x][i]) ++j;
		nxt[i]=j;
	}
}

int work(int x,int y)
{
	int j=-1;
	for (int i=0;i<len[y];++i)
	{
		while (j!=-1&&s[x][j+1]!=s[y][i]) j=nxt[j];
		if (s[x][j+1]==s[y][i]) ++j;
		if (i==len[y]-1)
			origin.a[y][x]=len[x]-j-1;
	}
}

void solve(int x)
{
	if (x==1) {f=origin;return;}
	solve(x/2);
	
	f=calc(f,f);
	if (x%2) f=calc(f,origin);
}

xxx calc(xxx a,xxx b)
{
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
		{
			tmp.a[i][j]=inf;
			for (int k=1;k<=n;++k)
				tmp.a[i][j]=min(tmp.a[i][j],a.a[i][k]+b.a[k][j]);
		}
	return tmp;
}
