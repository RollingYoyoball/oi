#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=2*(1e5)+10;
const double pi=acos(-1);
struct cmplx{/*{{{*/
	double a,b;
	cmplx(){a=0,b=0;}
	cmplx(double _a,double _b){a=_a;b=_b;}
	void init(){a=0,b=0;}
	friend cmplx operator + (cmplx x,cmplx y)
	{return cmplx(x.a+y.a,x.b+y.b);}
	friend cmplx operator - (cmplx x,cmplx y)
	{return cmplx(x.a-y.a,x.b-y.b);}
	friend cmplx operator * (cmplx x,cmplx y)
	{return cmplx(x.a*y.a-x.b*y.b,x.a*y.b+x.b*y.a);}
};/*}}}*/
namespace FFT{/*{{{*/
	cmplx A[MAXN*4],B[MAXN*4];
	int rev[MAXN*4];
	int len,invlen;
	void prework(int n,int m){
		int bit=0;
		for (len=1;len<n+m;len<<=1,++bit);
		rev[0]=0;
		for (int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	}
	void fft(cmplx *a,int op){
		for (int i=0;i<len;++i) 
			if (i<rev[i]) swap(a[i],a[rev[i]]);
		cmplx w_n,w,t,u;
		for (int step=2;step<=len;step<<=1){
			w_n=cmplx(cos(2*pi/step),op*sin(2*pi/step));
			for (int st=0;st<len;st+=step){
				w=cmplx(1,0);
				for (int i=0;i<(step>>1);++i){
					t=a[st+i+(step>>1)]*w;
					u=a[st+i];
					a[st+i]=u+t;
					a[st+i+(step>>1)]=u-t;
					w=w*w_n;
				}
			}
		}
		if (op==1) return;
		for (int i=0;i<len;++i)
			a[i].a=a[i].a/len;
	}
	void FFt(cmplx *a,cmplx *b,int n,int m){
		for (int i=0;i<len;++i) A[i].init(),B[i].init();
		for (int i=0;i<=n;++i) A[i]=a[i];
		for (int i=0;i<=m;++i) B[i]=b[i];
		fft(A,1);
		fft(B,1);
		for (int i=0;i<len;++i) A[i]=A[i]*B[i];
		fft(A,-1);
	}
};/*}}}*/
char s[MAXN],t[MAXN];
int cnt[MAXN],ok[4][MAXN];
cmplx ms[MAXN],mt[MAXN];
int lens,lent,K,ans;
void solve(int ch);
int change(char ch);
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&lens,&lent,&K);
	scanf("%s",s);
	scanf("%s",t);
	FFT::prework(lens,lent);
	for (int i=0;i<4;++i)
		solve(i);
	ans=0;
	for (int i=0;i<lens;++i)
		if (ok[0][i]&&ok[1][i]&&ok[2][i]&&ok[3][i])
			++ans;
	printf("%d\n",ans);
}

int change(char ch){
	if (ch=='A') return 0;
	if (ch=='G') return 1;
	if (ch=='C') return 2;
	return 3;
}

void solve(int ch){
	for (int i=0;i<lens;++i) cnt[i]=0;
	for (int i=0;i<lens;++i)
		if (change(s[i])==ch){
			cnt[Max(0,i-K)]++;
			cnt[Min(i+K+1,lens)]--;
		}
	int all=0;
	for (int i=1;i<lens;++i) cnt[i]+=cnt[i-1];
	for (int i=0;i<lens;++i)
		ms[i]=cmplx(cnt[i]>0,0);
	for (int i=0;i<lent;++i)
		mt[lent-i-1]=cmplx(change(t[i])==ch,0),all+=change(t[i])==ch;
	FFT::FFt(ms,mt,lens,lent);
	for (int i=0;i<lens;++i){
		int tmp=(int)(FFT::A[i].a+0.5);
		ok[ch][i]=tmp==all;
	}
}
