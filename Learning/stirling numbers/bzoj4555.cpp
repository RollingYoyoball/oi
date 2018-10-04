#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 998244353
#define ll long long
using namespace std;
const int MAXN=1e5+10;
ll a[MAXN*4],b[MAXN*4],W[MAXN*4][2],c[MAXN*4],fac[MAXN*4],invfac[MAXN*4],two[MAXN];
int rev[MAXN*4];
int n,k;
ll invk,sum;
int Ntt();
int ntt(ll *a,int op);
ll ksm(ll x,int y);
ll inv(ll x){return ksm(x,MOD-2);}
int init();
int get_ans();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	init();
	Ntt();
	get_ans();
}

int Ntt(){
	ntt(a,1);
	ntt(b,1);
	for (int i=0;i<k;++i) c[i]=(a[i]*b[i])%MOD;
	ntt(c,-1);
}

int init(){
	fac[0]=1; invfac[0]=1; a[0]=invfac[0];
	for (int i=1;i<=n;++i){
		fac[i]=fac[i-1]*i%MOD;
		invfac[i]=inv(fac[i]);
		a[i]=i%2==0?invfac[i]:-invfac[i];
	}
	b[0]=1; b[1]=n+1;
	for (int i=2;i<=n;++i)
		b[i]=(ksm(i,n+1)-1)*inv(i-1)%MOD*invfac[i]%MOD;
	two[0]=1;
	for (int i=1;i<=n;++i) two[i]=two[i-1]*2%MOD;

	int bit=0;
	for (k=1;k<=n*2;k<<=1,++bit);//k的范围
	rev[0]=0;
	for (int i=1;i<k;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	ll Inv=ksm(3,MOD-2);
	for (int i=0;i<=bit;++i){
		W[1<<i][0]=ksm(3,(MOD-1)/(1<<i));
		W[1<<i][1]=ksm(Inv,(MOD-1)/(1<<i));
	}
	invk=inv(k);
}

int ntt(ll *a,int op){
	ll w_n,t,u,w;
	for (int i=0;i<k;++i)
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int len=2;len<=k;len<<=1){
		w_n=op==1?W[len][0]:W[len][1];
		for (int st=0;st<k;st+=len){
			w=1;
			for (int i=0;i<(len>>1);++i){
				t=(a[st+i+(len>>1)]*w)%MOD;
				u=a[st+i];
				a[st+i]=(u+t)%MOD;
				a[st+i+(len>>1)]=(u-t+MOD)%MOD;
				w=w*w_n%MOD;
			}
		}
	}
	if (op==1) return 0;
	for (int i=0;i<k;++i) a[i]=(a[i]*invk)%MOD;
}

ll ksm(ll x,int y){
	ll ret=1,base=x;
	while (y){
		if (y&1) ret=ret*base%MOD;
		base=base*base%MOD;
		y>>=1;
	}
	return ret;
}

int get_ans(){
	ll ans=0,tmp;
	for (int i=0;i<=n;++i){
		tmp=fac[i]*two[i]%MOD*c[i]%MOD;
		ans=(ans+tmp)%MOD;
	}
	printf("%lld\n",ans);
}
