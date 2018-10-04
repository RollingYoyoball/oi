#include<iostream>
#include<cstring>
#include<cstdio>
#define ll long long
#define MOD 1000000007
using namespace std;
const int MAXN=100010;
struct xxx
{
	int a[210][210];
}f,origin,tmp;
char s[210][MAXN];
int nxt[MAXN],len[MAXN];
ll c[MAXN];
int n,m,ans;
int work();
int get_nxt(int x);
int solve(int m);
xxx calc(xxx a,xxx b);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d\n",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%s\n",s[i]),len[i]=strlen(s[i]);
	c[0]=1;
	for (int i=1;i<=n;++i) c[i]=(c[i-1]*26)%MOD;
	work();	
	memset(f.a,0x7f,sizeof(f.a));
	solve(m);
	ans=2147483647;
	for (int i=0;i<=n;++i)
		for (int j=0;j<=n;++j)
			ans=min(ans,f.a[i][j]);
	printf("%d\n",ans);	
}

int work(int x,int y)
{
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
		{
			origin.a[i][j]=len[j];
			for (int k=1;k<=min(len[i],len[j]);++k)
				if (getpart(x,len[i]-k
		}
}

int solve(int x)
{
	if (x==1) {f=origin;return 0;}
	solve(x/2);
	
	f=calc(f,f);
	if (x%2) f=calc(f,origin);
}

xxx calc(xxx a,xxx b)
{
	memset(tmp.a,0x7f,sizeof(tmp.a));
	for (int i=0;i<=n;++i)
		for (int j=0;j<=n;++j)
			for (int k=0;k<=n;++k)
				tmp.a[i][j]=min(tmp.a[i][j],a.a[i][k]+b.a[k][j]);
}
