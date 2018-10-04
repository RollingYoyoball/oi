#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=1e5+10;
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
	int len;
	void prework(int n,int m){
		int bit=0;
		for (int i=0;i<len;++i) A[i].init(),B[i].init();
		for (len=1;len<n+m;++bit,len<<=1);
		rev[0]=0;
		for (int i=1;i<len;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	}
	void fft(cmplx *a,int op){
		cmplx w_n,w,t,u;
		for (int i=0;i<len;++i)
			if (rev[i]>i) swap(a[i],a[rev[i]]);
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
		for (int i=0;i<len;++i) a[i].a/=len;
	}
	void FFt(cmplx *a,cmplx *b,int n,int m){
		for (int i=0;i<=n;++i) A[i]=a[i];
		for (int i=0;i<=m;++i) B[i]=b[i];
		fft(A,1);
		fft(B,1);
		for (int i=0;i<len;++i) A[i]=A[i]*B[i];
		fft(A,-1);
	}
};/*}}}*/
cmplx a[MAXN],b[MAXN];
int ans[MAXN*2];
char s[MAXN];
int n,m;

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%s",s);
	n=strlen(s);
	for (int i=0;i<n;++i) a[i]=cmplx(s[i]-'0',0);
	scanf("%s",s);
	m=strlen(s);
	for (int i=0;i<m;++i) b[i]=cmplx(s[i]-'0',0);
	FFT::prework(n,m);
	FFT::FFt(a,b,n,m);
	for (int i=0;i<n+m-1;++i) ans[i]=(int)(FFT::A[i].a+0.5);
	for (int i=n+m-2;i>=1;--i) 
		ans[i-1]+=ans[i]/10,ans[i]%=10;
	for (int i=0;i<n+m-1;++i) printf("%d",ans[i]);
	printf("\n");
}
