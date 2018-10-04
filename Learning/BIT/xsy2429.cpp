#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=2010;
map<int,int> id;
ll c[MAXN][MAXN],f[MAXN][MAXN],g[MAXN],peng[MAXN];
int a[MAXN],v[MAXN];
int n,m,tot;
ll ans; 
void update(int len,int x,ll d);
ll query(int len,int x);

int main()
{
	freopen("a.in","r",stdin);

	int x;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]),v[i]=a[i];
	sort(v+1,v+1+n);
	tot=0;
	for (int i=1;i<=n;id[a[i++]]=tot)
		if (v[i]!=v[i-1]) ++tot;
	for (int i=1;i<=n;++i) a[i]=id[a[i]];
	//sort(a+1,a+1+n,cmp1);
	update(0,1,1); 
	for (int i=1;i<=n;++i)
	{
	//	update(1,a[i].v,1);
	//	f[i][1]=1;
		for (int j=i;j>=1;--j)
		{
			f[i][j]=(f[i][j]+query(j-1,a[i]))%MOD;
			update(j,a[i],f[i][j]);
		}
	}
	//f[i][j]表示a[i]结尾的长度为j的非降序列的个数 
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;++j)
			g[i]=(g[i]+f[j][i])%MOD;
	peng[0]=1;
	for (int i=1;i<=n;++i) peng[i]=(peng[i-1]*i)%MOD;
	ans=0;
	for (int i=1;i<=n;++i)
	{
		ans=(ans+(g[i]*peng[n-i]%MOD)+MOD-(peng[n-(i+1)]*((g[i+1]*(i+1))%MOD))%MOD)%MOD;
		//考虑一个长度为i的非降序列，一定是由原序列删掉了某些数得到的，那么枚举它的删除过程可以知道
		//一个非降序列对于答案的贡献是g[i]*(n-i)!
		//但是，由于是用组合数算出来的，所以可能会出现当前已经是一个非降序列了的情况
		//这个时候按题意来说应该停止，但是并没有停止枚举，所以会算多
		//同时，也可能多算了长度为i+1的序列所会枚举到的情况
		//因此，只要是可以从i+1转移过来的，不管是合法还是非法，都应该被减去 
		//每个长度为i+1的序列，都有i+1种方式删掉一个数变成i的序列，然后总共有peng[n-i-1]*g[i+1]个i+1的序列 
	}
	printf("%lld\n",ans);
}

void update(int len,int x,ll d)
{
	for (;x<=tot;x+=x&-x)
		c[len][x]=(c[len][x]+d)%MOD;
}

ll query(int len,int x)
{
	ll ret=0;
	for (;x;x-=x&-x)
		ret=(ret+c[len][x])%MOD;
	return ret;
}
