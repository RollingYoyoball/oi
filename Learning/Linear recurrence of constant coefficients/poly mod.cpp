#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define ll long long
#define MOD 998244353
#define vct vector<long long>
#define G 3
using namespace std;
const int MAXN=50010*2;
ll a[MAXN],h[MAXN];
int n,k;
ll ksm(ll x,int y){
	ll ret=1,base=x;
	for (;y;base=base*base%MOD,y>>=1)
		if (y&1) ret=ret*base%MOD;
	return ret;
}
ll Inv(ll x){return ksm(x,MOD-2);}
namespace NTT{/*{{{*/
	ll rev[MAXN*4],W[MAXN*4][2],A[MAXN*4],B[MAXN*4];
	int len,invlen;
	void init(){
		int invg=Inv(G);
		for (int i=0;i<=18;++i){
			W[1<<i][0]=ksm(G,(MOD-1)/(1<<i));
			W[1<<i][1]=ksm(invg,(MOD-1)/(1<<i));
		}
	}
	void prework(vct &a,vct &b,int n,int m){
		int bit=0;
		for (int i=0;i<len;++i) A[i]=0,B[i]=0;
		for (len=1;len<n+m;len<<=1,++bit);
		invlen=Inv(len);
		rev[0]=0;
		for (int i=0;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		a.resize(n);
		b.resize(m);
		for (int i=0;i<n;++i) A[i]=a[i];
		for (int i=0;i<m;++i) B[i]=b[i];
	}
	void ntt(ll *a,int op){
		ll w_n,t,u,w;
		for (int i=0;i<len;++i) 
			if (i<rev[i]) swap(a[i],a[rev[i]]);
		for (int step=2;step<=len;step<<=1){
			w_n=op==1?W[step][0]:W[step][1];
			for (int st=0;st<len;st+=step){
				w=1;
				for (int i=0;i<(step>>1);++i){
					t=a[st+i+(step>>1)]*w%MOD;
					u=a[st+i];
					a[st+i]=(u+t)%MOD;
					a[st+i+(step>>1)]=(u+MOD-t)%MOD;
					w=w*w_n%MOD;
				}
			}
		}
		if (op==1) return;
		for (int i=0;i<len;++i) a[i]=a[i]*invlen%MOD;
	}
	void Ntt(vct &a,vct &b,int n,int m){
		prework(a,b,n,m);
		ntt(A,1);
		ntt(B,1);
		for (int i=0;i<len;++i) A[i]=A[i]*B[i]%MOD;
		ntt(A,-1);
	}
	void Ntt_getinv(vct &a,vct &b,int n,int m){
		prework(a,b,n,2*m);
		ntt(A,1);
		ntt(B,1);
		for (int i=0;i<len;++i) B[i]=(1LL*2-A[i]*B[i]%MOD+MOD)*B[i]%MOD;
		ntt(B,-1);
	}
};/*}}}*/
vct tmp,chu,t,invb,d,b,ans,base;
vct div(vct A,vct B);
void mul(ll *a,ll *b);
int mul(int x,int y){return 1LL*x*y%MOD;}
void ksm(int n);
vct Inv_p(vct a);
void mod(vct &a,vct b);
vct div(vct a,vct b);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	NTT::init();
	for (int i=1;i<=k;++i) scanf("%lld",h+i),h[i]-=h[i]<MOD?0:MOD;
	for (int i=1;i<=k;++i) scanf("%lld",a+i),a[i]-=a[i]<MOD?0:MOD;
	chu.resize(k+1);
	for (int i=1;i<=k;++i) chu[k-i]=(MOD-a[i])%MOD;
	chu[k]=1;
	/*ksm(n-k+1);如果说前k项不满足这个式子那么就用这段
	for (int i=1+k;i<=k-1+k;++i)
		for (int j=1;j<=k;++j)
			h[i]+=mul(h[i-j],a[j]),h[i]-=h[i]>=MOD?MOD:0;*/

	ksm(n);//如果说前k项也满足这个递推式就用这段
	ll Ans=0;
	for (int i=0;i<k;++i)
		Ans+=mul(h[i+1],ans[i]),Ans-=Ans>=MOD?MOD:0;
	if (n<k) printf("%lld\n",h[n+1]);
	else printf("%lld\n",Ans);
}

void mul(vct &a,vct b){
	//tmp=a*b;
	NTT::Ntt(a,b,k,k);
	tmp.resize(2*k-1);
	for (int i=0;i<2*k-1;++i) tmp[i]=NTT::A[i];
	mod(tmp,chu);
	for (int i=0;i<k;++i) a[i]=tmp[i];
}

vct operator * (vct x,vct y){
	vct ret;
	int n=x.size(),m=y.size();
	NTT::Ntt(x,y,n,m);
	ret.resize(n+m-1);
	for (int i=0;i<n+m-1;++i) ret[i]=NTT::A[i];
	return ret;
}
vct operator - (vct x,vct y){
	vct ret;
	int n=x.size(),m=y.size(),mx=max(n,m);
	ret.resize(mx);
	if (n!=mx) x.resize(mx);
	if (m!=mx) y.resize(mx);
	for (int i=0;i<mx;++i) ret[i]=x[i]-y[i],ret[i]+=ret[i]<0?MOD:0;
	return ret;
}

vct operator / (vct a,vct b){
	int N=a.size()-1,M=b.size()-1;
	if (N<M){
		d.resize(1);d[0]=0;
		return d;
	}
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	b.resize(N-M+1);
	d=Inv_p(b)*a;
	d.resize(N-M+1);
	reverse(d.begin(),d.end());
	return d;
}

void mod(vct &a,vct b){
	int N=a.size()-1,M=b.size()-1;
	if (N<M) return;
	t=a/b;
	a=a-(t*b);
	a.resize(M);
}

vct Inv_p(vct a){
	int N=a.size(),M;
	if (N==1){
		a[0]=ksm(a[0],MOD-2);
		return a;
	}
	vct b=a; b.resize((N+1)>>1);
	b=Inv_p(b); M=b.size();
	NTT::Ntt_getinv(a,b,N,M);
	b.resize(NTT::len);
	for (int i=0;i<NTT::len;++i) b[i]=NTT::B[i];
	b.resize(N);
	return b;
}

void ksm(int n){
	base.resize(2);base[1]=1;//base是一个多项式，表示的是M对于p(M)的余数
	ans.resize(1); ans[0]=1;
	while (n){
		if (n&1){ans=ans*base;mod(ans,chu);}
		base=base*base; mod(base,chu);
		n>>=1;
	}
}
