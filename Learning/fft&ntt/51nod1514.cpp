#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 998244353
#define G 3
using namespace std;
const int MAXN=1e5+10;
int f[MAXN],b[MAXN],fac[MAXN],a[MAXN];
int T,n,m;
int ksm(int x,int y);
namespace NTT{/*{{{*/
	int A[MAXN*4],B[MAXN*4],rev[MAXN*4],W[MAXN*4][2];
	int len,invlen,invg;
	void init(){
		invg=ksm(G,MOD-2);
		for (int i=0;i<=18;++i){
			W[1<<i][0]=ksm(G,(MOD-1)/(1<<i));
			W[1<<i][1]=ksm(invg,(MOD-1)/(1<<i));
		}
	}
	void prework(int *a,int *b,int n,int m){
		int bit=0;
		for (int i=0;i<len;++i) A[i]=B[i]=0;
		for (len=1;len<=n+m;len<<=1,++bit);
		rev[0]=0;
		for (int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		invlen=ksm(len,MOD-2);
		for (int i=0;i<=n;++i) A[i]=a[i];
		for (int i=0;i<=m;++i) B[i]=b[i];
	}
	void ntt(int *a,int op){
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
	void Ntt(int *a,int *b,int n,int m){
		prework(a,b,n,m);
		ntt(A,1);
		ntt(B,1);
		for (int i=0;i<len;++i) A[i]=1LL*A[i]*B[i]%MOD;
		ntt(A,-1);
	}
};/*}}}*/
void prework();
void solve(int l,int r);
void calc(int l,int r);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&T);
	prework();
	solve(1,100000);
	for (int o=1;o<=T;++o){
		scanf("%d",&n);
		printf("%d\n",f[n]);
	}
}

int ksm(int x,int y){
	int ret=1,base=x;
	for (;y;y>>=1,base=1LL*base*base%MOD)
		if (y&1) ret=1LL*ret*base%MOD;
	return ret;
}

void prework(){
	NTT::init();
	fac[0]=1;
	for (int i=1;i<MAXN;++i) fac[i]=1LL*fac[i-1]*i%MOD;
}

void solve(int l,int r){
	if (l==r){
		if (l)
			f[l]=(1LL*fac[l]-f[l]+MOD)%MOD;
		return;
	}
	int mid=l+r>>1;
	solve(l,mid);
	calc(l,r);
	solve(mid+1,r);
}

void calc(int l,int r){
	int mid=l+r>>1,len=r-l+1;
	for (int i=l;i<=mid;++i) a[i-l]=f[i];
	for (int i=0;i<len;++i) b[i]=fac[i];
	NTT::Ntt(a,b,mid-l+1,len);
	for (int i=mid+1;i<=r;++i) f[i]=(1LL*f[i]+NTT::A[i-l])%MOD;
	for (int i=l;i<=mid;++i) a[i-l]=0;
	for (int i=0;i<len;++i) b[i]=0;
}
//f[n]=n!-sum(f[i]*(n-i)!)
