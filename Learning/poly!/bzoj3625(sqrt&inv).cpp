#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MOD 998244353
#define G 3
#define vct vector<long long>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
vct a,b,c;
int T,n,m,inv2;
ll ksm(int x,int y);
int Min(int x,int y){return x<y?x:y;}
namespace NTT{/*{{{*/
	ll A[MAXN*8],B[MAXN*8],rev[MAXN*8],W[MAXN*8][2];
	int len,invlen,invg;
	void init(){
		invg=ksm(G,MOD-2);
		for (int i=0;i<=19;++i){
			W[1<<i][0]=ksm(G,(MOD-1)/(1<<i));
			W[1<<i][1]=ksm(invg,(MOD-1)/(1<<i));
		}
	}
	void prework(vct &a,vct &b,int n,int m){
		int bit=0;
		for (int i=0;i<len;++i) A[i]=B[i]=0;
		for (len=1;len<n+m;len<<=1,++bit);
		rev[0]=0;
		for (int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		invlen=ksm(len,MOD-2);
		a.resize(n);
		b.resize(m);
		for (int i=0;i<n;++i) A[i]=a[i];
		for (int i=0;i<m;++i) B[i]=b[i];
	}
	void ntt(ll *a,int op){
		for (int i=0;i<len;++i) 
			if (rev[i]>i) swap(a[rev[i]],a[i]);
		int w,w_n,t,u;
		for (int step=2;step<=len;step<<=1){
			w_n=op==1?W[step][0]:W[step][1];
			for (int st=0;st<len;st+=step){
				w=1;
				for (int i=0;i<(step>>1);++i){
					t=1LL*a[st+i+(step>>1)]*w%MOD;
					u=a[st+i];
					a[st+i]=(1LL*u+t)%MOD;
					a[st+i+(step>>1)]=(1LL*u+MOD-t)%MOD;
					w=1LL*w*w_n%MOD;
				}
			}
		}
		if (op==1) return;
		for (int i=0;i<len;++i) a[i]=1LL*a[i]*invlen%MOD;
	}
	void Ntt(vct &a,vct &b,int n,int m){
		prework(a,b,n,m);
		ntt(A,1);
		ntt(B,1);
		for (int i=0;i<len;++i) A[i]=1LL*A[i]*B[i]%MOD;
		ntt(A,-1);
	}
	void Ntt_getinv(vct &a,vct &b,int n,int m){
		prework(a,b,n,2*m);
		ntt(A,1);
		ntt(B,1);
		for (int i=0;i<len;++i) B[i]=(2LL-1LL*A[i]*B[i]%MOD+MOD)*1LL*B[i]%MOD;
		ntt(B,-1);
	}
	void Ntt_getsqrt(vct &a,vct &invb,int n,int m){
		prework(a,invb,n,m);
		ntt(A,1);
		ntt(B,1);
		for (int i=0;i<len;++i) 
			B[i]=1LL*B[i]*inv2%MOD*A[i]%MOD;
		ntt(B,-1);
	}
};/*}}}*/
void prework();
void solve(int l,int r);
void calc(int l,int r);
vct Inv(vct a);
vct Sqrt(vct a);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x;
	NTT::init();
	inv2=ksm(2,MOD-2);
	scanf("%d%d",&n,&m);
	c.resize(m+1);
	for (int i=1;i<=n;++i){
		scanf("%d",&x);
		if (x<=m) c[x]++;
	}
	vct tmp;
	tmp.resize(3);
	tmp[0]=1; tmp[1]=2; tmp[2]=1;
	tmp=Sqrt(tmp);
	++m;
	c[0]=1;
	for (int i=1;i<m;++i) c[i]=4LL*(MOD-c[i])%MOD;
	c=Sqrt(c);
	c[0]=(c[0]+1)%MOD;
	c=Inv(c);
	for (int i=0;i<m;++i) c[i]=2LL*c[i]%MOD;
	for (int i=1;i<m;++i) printf("%d\n",c[i]);
}

ll ksm(int x,int y){
	ll ret=1,base=x;
	for (;y;y>>=1,base=1LL*base*base%MOD)
		if (y&1) ret=1LL*ret*base%MOD;
	return ret;
}

vct Inv(vct a){
	int N=a.size(),M;
	if (N==1){
		a[0]=ksm(a[0],MOD-2);
		return a;
	}
	vct b=a; b.resize((N+1)>>1);
	b=Inv(b); b.resize(N);
	NTT::Ntt_getinv(a,b,N,N);
	b.resize(NTT::len);
	for (int i=0;i<NTT::len;++i) b[i]=NTT::B[i];
	b.resize(N);
	return b;
}

vct Sqrt(vct a){
	int N=a.size(),M,M1;
	if (N==1){
		a[0]=1;
		return a;
	}
	vct b=a,invb;
	b.resize((N+1)>>1);
	b=Sqrt(b);
	invb=b; invb.resize(N);//resize!!!
	invb=Inv(invb);
	NTT::Ntt_getsqrt(a,invb,N,N);
	b.resize(NTT::len);
	for (int i=0;i<NTT::len;++i) b[i]=(1LL*b[i]*inv2%MOD+NTT::B[i])%MOD;
	b.resize(N);
	return b;
}
