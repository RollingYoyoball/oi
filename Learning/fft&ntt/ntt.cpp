#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define MOD 998244353
using namespace std;
const double pi=acos(-1);
const int MAXN=(1<<17)+10;
ll a[MAXN],b[MAXN],W[MAXN][2];
int rev[MAXN];
ll inv;
int n,m,k,lg;
int init();
int ntt(ll *a,int op);
ll ksm(ll x1,int x);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int type,x;
	scanf("%d%d%d",&n,&m,&type);
	++n,++m;
	for (int i=0;i<n;++i) scanf("%lld",&a[i]);
	for (int i=0;i<m;++i) scanf("%lld",&b[i]);
	init();
	ntt(a,1);
	ntt(b,1);
	for (int i=0;i<k;++i) a[i]=(a[i]*b[i])%MOD;
	ntt(a,-1);
	for (int i=0;i<n+m-1;++i)
		printf("%lld ",a[i]);
}

int init()
{
	int bit=0;
	for (k=1;k<n+m;k<<=1,++bit);
	rev[0]=0;
	for (int i=0;i<k;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	//预处理出递归最后一层的顺序
	ll base=ksm(3,MOD-2);
	for (int i=0;i<=bit;++i)
	{
		W[1<<i][0]=ksm(3,(MOD-1)/(1<<i));
		W[1<<i][1]=ksm(base,(MOD-1)/(1<<i));
	}
	//这个东西是一个类似复数单位根的东西但是是取模意义下的，相关证明要用到群论然而并不会qwq很尴尬qwq
	inv=ksm(k,MOD-2);	
}

int ntt(ll *a,int op)//跟fft其实是基本一样的这部分
{
	ll w_n,t,u,w;
	for (int i=0;i<k;++i) 
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int len=2;len<=k;len<<=1)
	{
		w_n=op==1?W[len][0]:W[len][1];
		for (int st=0;st<k;st+=len)
		{
			w=1;
			for (int i=0;i<(len>>1);++i)
			{
				t=(a[st+i+(len>>1)]*w)%MOD;
				u=a[st+i];
				a[st+i]=(u+t)%MOD;
				a[st+i+(len>>1)]=(u-t+MOD)%MOD;
				w=(w*w_n)%MOD;
			}
		}
	}
	if (op==1) return 0;
	for (int i=0;i<k;++i) a[i]=(a[i]*inv)%MOD;
}

ll ksm(ll x1,int x)
{
	ll ret=1,base=x1;
	while (x)
	{
		if (x&1) ret=(ret*base)%MOD;
		base=(base*base)%MOD;
		x>>=1;
	}
	return ret;
}
