//bzoj3456
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define MOD 1004535809
#define G 3
using namespace std;
const int MAXN=4*130010;
ll a[MAXN],b[MAXN],g[MAXN],fac[MAXN],invfac[MAXN],f[MAXN];
ll W[MAXN][2];
int rev[MAXN];
int n,m,tot,k,invk;
int init();
int Ntt(int l,int r);
int prework(int n);
int ntt(ll *a,int op);
ll ksm(ll x,ll y);
ll inv(ll x){return ksm(x,MOD-2);}
int solve(int l,int r);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	ll ttmp=ksm(2,5);
	scanf("%d",&n);
	init();
	solve(1,n);
	printf("%lld\n",g[n]);
}

ll ksm(ll x,ll y){
	ll ret=1,base=x;
	while (y){
		if (y&1) ret=ret*base%MOD;
		base=base*base%MOD;
		y>>=1;
	}
	return ret;
}

int init(){
	fac[0]=1;
	for (int i=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD;
	for (int i=0;i<=n;++i) invfac[i]=inv(fac[i]);
	for (int i=1;i<=n;++i) f[i]=ksm(2,(1LL*i*(i-1)/2));
	g[0]=1;
}

int prework(int n){
	int bit=0;
	for (k=1;k<=n*2;++bit,k<<=1);
	for (int i=0;i<k;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	ll Inv=inv(G);
	for (int i=0;i<=bit;++i){
		W[1<<i][0]=ksm(G,(MOD-1)/(1<<i));
		W[1<<i][1]=ksm(Inv,(MOD-1)/(1<<i));
	}
	invk=inv(k);
}

int ntt(ll *a,int op){
	ll w_n,w,t,u;
	for (int i=0;i<k;++i)
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int len=2;len<=k;len<<=1){
		w_n=op==1?W[len][0]:W[len][1];
		for (int st=0;st<k;st+=len){
			w=1;
			for (int i=0;i<(len>>1);++i){
				t=a[st+i+(len>>1)]*w%MOD;
				u=a[st+i];
				a[st+i]=(u+t)%MOD;
				a[st+i+(len>>1)]=(u-t+MOD)%MOD;
				w=w*w_n%MOD;
			}
		}
	}
	if (op==1) return 0;
	for (int i=0;i<k;++i) a[i]=a[i]*invk%MOD;
}

int solve(int l,int r){
	if (l==r){
		if (l)
			g[l]=(f[l]+MOD-fac[l-1]*g[l]%MOD)%MOD;
		return 0;
	}
	int mid=l+r>>1;
	solve(l,mid);
	Ntt(l,r);
	solve(mid+1,r);
}

int Ntt(int l,int r){
	int mid=l+r>>1;
	k=r-l+1;
	prework(k);
	for (int i=l;i<=mid;++i) a[i-l]=g[i]*invfac[i-1]%MOD;
	for (int i=l;i<=r;++i) b[i-l]=f[i-l]*invfac[i-l]%MOD;
	ntt(a,1);
	ntt(b,1);
	for (int i=0;i<k;++i) a[i]=a[i]*b[i]%MOD;
	ntt(a,-1);
	for (int i=mid+1;i<=r;++i) g[i]=(g[i]+a[i-l])%MOD;
	for (int i=0;i<k;++i) a[i]=b[i]=0;
}
