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
struct cmplx
{
	double a,b;//a记录这个复数的实数部分，b记录这个复数的i的系数
	cmplx(){}
	cmplx(double x,double y){a=x,b=y;}
	friend cmplx operator + (cmplx x,cmplx y)
	{return cmplx(x.a+y.a,x.b+y.b);}
	friend cmplx operator - (cmplx x,cmplx y)
	{return cmplx(x.a-y.a,x.b-y.b);}
	friend cmplx operator * (cmplx x,cmplx y)
	{return cmplx(x.a*y.a-x.b*y.b,x.a*y.b+x.b*y.a);}
}a[MAXN],b[MAXN],ans[MAXN];
int rev[MAXN];
int n,m,k,lg;
//typedef vector<cmplx> vc
//vc fft(vc ans,int op);
int fft(cmplx *a,int op);
int get_rev(cmplx *a,int n);

int main()
{
	//	freopen("a.in","r",stdin);
	//	freopen("a.out","w",stdout);

	int type,x;
	scanf("%d%d%d",&n,&m,&type);
	++n,++m;
	for (int i=0;i<n;++i) scanf("%lf",&a[i].a);
	for (int i=0;i<m;++i) scanf("%lf",&b[i].a);
	k=1;
	while (k<n+m) k<<=1;
	fft(a,1);
	fft(b,1);
	for (int i=0;i<k;++i) a[i]=a[i]*b[i];
	fft(a,-1);
	for (int i=0;i<n+m-1;++i)
		printf("%lld ",(ll)(a[i].a/k+0.5));
}

/*vc fft(vc ans,int op) 递归版的ovo
{
	int n=ans.size();
	if (n==1) return ans;
	cmplx w_n=cmplx(cos(2*pi/n),op*sin(2*pi/n)),w=cmplx(1,0);
	vc a0,a1;
	for (int i=0;i<n;i+=2)
		a0.push_back(ans[i]),a1.push_back(ans[i+1]);
	a0=fft(a0,op);
	a1=fft(a1,op);
	for (int i=0;i<(n>>1);++i)
	{
		ans[i]=a0[i]+a1[i]*w;
		ans[i+(n>>1)]=a0[i]-a1[i]*w;
		w=w*w_n;
	}
	return ans;
}*/

int fft(cmplx *a,int op)//然而非递归的跑的比递归快多了qwq
{
	int step,bit=0;
	cmplx w_n,w,t,u;
	for (int i=1;i<k;i<<=1,++bit);
	rev[0]=0;
	for (int i=0;i<k;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	for (int i=0;i<k;++i) 
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	//通过奇妙方式将递归到最下面那层的顺序算出来ovo
	//然后接着就可以直接从最底层，所有的位置一起更新啦
	for (int step=2;step<=k;step<<=1)
	{
		w_n=cmplx(cos(2*pi/step),op*sin(2*pi/step));
		for (int st=0;st<k;st+=step)
		{
			w=cmplx(1,0);
			for (int i=0;i<(step>>1);++i)
			{
				t=a[st+i+(step>>1)]*w;
				u=a[st+i];
				a[st+i]=u+t;
				a[st+i+(step>>1)]=u-t;
				w=w*w_n;
			}
		}
	}
}
