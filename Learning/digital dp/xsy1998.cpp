#include<iostream>
#include<cstring>
#include<cstdio>
#define ll long long
#define MOD 1000000007
using namespace std;
struct xxx
{
	ll a[2][2];
}origin;
ll f[62][2];
int a[62];
int T;
ll n;
ll dfs(int pos,int pre,bool limit);
ll solve(ll x);
xxx ksm(ll x,xxx a);
xxx mul(xxx a,xxx b);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf("%d",&T);
	for (int o=1;o<=T;++o)
	{
		scanf("%lld",&n);
		memset(f,-1,sizeof(f));
		printf("%lld\n",solve(n));
		origin.a[0][0]=1; origin.a[0][1]=1; origin.a[1][0]=1; origin.a[1][1]=0;
		origin=ksm(n+1,origin);
		printf("%lld\n",origin.a[0][0]);
	}
}

ll dfs(int pos,int num,bool limit)
{
	if (pos==0) return 1;
	if (!limit&&f[pos][num]!=-1) return f[pos][num];
	ll ret=0;
	int up=limit?a[pos]:1;
	for (int i=0;i<=up;++i)
		if (!(i&&num)) ret+=dfs(pos-1,i,limit&&i==a[pos]);
	if (!limit) f[pos][num]=ret;
	return ret;	
}

ll solve(ll x)
{
	if (x<=0) return 0;
	int cnt;
	for (cnt=0;x;x>>=1)
		a[++cnt]=x&1;
	return dfs(cnt,0,1)-1;
}

xxx ksm(ll x,xxx a)
{
	xxx r;
	r.a[0][0]=1; r.a[1][1]=1; r.a[0][1]=0; r.a[1][0]=0;
	while (x)
	{
		if (x&1) r=mul(a,r);
		a=mul(a,a);
		x>>=1;
	}
	return r;
}

xxx mul(xxx a,xxx b)
{
	xxx tmp;
	memset(tmp.a,0,sizeof(tmp.a));
	for (int i=0;i<=1;++i)
		for (int j=0;j<=1;++j)
			for (int k=0;k<=1;++k)
				tmp.a[i][j]=(tmp.a[i][j]+(a.a[i][k]*b.a[k][j])%MOD)%MOD;
	return tmp;
}
