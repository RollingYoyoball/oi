#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=2010;
ll c[MAXN],d[MAXN],b[MAXN],ans[MAXN];
ll X[MAXN],Y[MAXN];
int n,k,q;
ll ansl;
void solve(int n);
ll ksm(ll x,int y);
ll f(int x);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&k,&q);
	for (int i=1;i<=k+1;++i){
		scanf("%lld",Y+i);
		X[i]=i-1;
	}
	ll tmp;
	solve(k+1);
	ansl=0;
	ll bs=1;
	for (int i=0;i<=n;++i,bs=bs*q%MOD){
		tmp=f(i)*bs%MOD;
		ansl=(ansl+tmp)%MOD;
	}
	printf("%lld\n",ansl);
}

void solve(int n){
	memset(c,0,sizeof(c));
	c[0]=1;
	for (int i=1;i<=n;++i){
		for (int j=n;j>=0;--j){
			c[j+1]=(c[j+1]+c[j])%MOD;
			c[j]=(-c[j]*X[i])%MOD;
		}
	}//get xishu of \prod_{i=0}^k (x-x_i)
	ll s=0,tmp=1;
	for (int i=1;i<=n;++i){
		memcpy(d,c,sizeof(d));
		memset(b,0,sizeof(b));
		for (int j=n;j>=0;--j){
			b[j]=d[j+1];
			d[j]=(d[j]+d[j+1]*X[i])%MOD;
			d[j+1]=0;
		}//take (x-x_i) out of \prod_{j=0}^k (x-x_j)
		s=0,tmp=1;
		for (int j=0;j<=n;++j){
			s=(s+tmp*b[j])%MOD;
			tmp=tmp*X[i]%MOD;
		}//get \prod_{j=0,j!=i}^k (x_i-x_j)
		
		s=ksm(s,MOD-2)*Y[i]%MOD;
		for (int j=0;j<=n;++j) b[j]=b[j]*s%MOD;//get the final xishu
		for (int j=0;j<=n;++j)
			ans[j]=(ans[j]+b[j])%MOD;
	}
}

ll ksm(ll x,int y){
	ll ret=1,base=x;
	for (;y;y>>=1,base=base*base%MOD)
		if (y&1) ret=ret*base%MOD;
	return ret;
}

ll f(int x){
	if (x<=k) return Y[x+1];
	ll ret=0,bs=1;
	for (int i=0;i<=k;++i,bs=bs*x%MOD)
		ret=(ret+ans[i]*bs%MOD)%MOD;
	if (ret<0) ret+=MOD;
	return ret;
}

