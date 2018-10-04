#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MOD 1000000007
#define ll long long
using namespace std;
const double pi=acos(-1);
const int MAXN=4*(1e5)+10;
struct cmplx
{
    double a,b;
    cmplx(){}
    cmplx(double x,double y){a=x,b=y;}
    friend cmplx operator + (cmplx x,cmplx y)
    {return cmplx(x.a+y.a,x.b+y.b);}
    friend cmplx operator - (cmplx x,cmplx y)
    {return cmplx(x.a-y.a,x.b-y.b);}
    friend cmplx operator * (cmplx x,cmplx y)
    {return cmplx(x.a*y.a-x.b*y.b,x.a*y.b+x.b*y.a);}
}a[MAXN],b[MAXN];
char s[MAXN],s1[MAXN];
int f[MAXN],mx[MAXN],two[MAXN];
int rev[MAXN];
int n,m,tot,k;//k=mx
ll ans;
int fft(cmplx *a,int op);
int manacher(char *s1,int lens);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%s",s);
	int len=strlen(s);
	for (int i=0;i<len;++i){
		if (s[i]=='a') a[i]=cmplx(1,0);
		else a[i]=cmplx(0,0);
	}
	k=1; two[0]=1;
	for (int i=1;i<=2*len;++i)
		two[i]=two[i-1]*2%MOD;
	while (k<2*len) k<<=1;
	fft(a,1);
	for (int i=0;i<k;++i) b[i]=a[i]*a[i];

	memset(a,0,sizeof(a));
	for (int i=0;i<len;++i){
		if (s[i]=='b') a[i]=cmplx(1,0);
		else a[i]=cmplx(0,0);
	}
	fft(a,1);
	for (int i=0;i<k;++i) b[i]=b[i]+a[i]*a[i];
	fft(b,-1);
	ans=0;
	for (int i=2;i<=2*len;++i) f[i]+=(ll)(b[i-2].a/k+0.5);
	for (int i=2;i<=2*len;++i) ans=(ans+two[(f[i]+1)>>1]-1)%MOD;
	printf("%lld\n",(ans+MOD-manacher(s,len))%MOD);
}

int fft(cmplx *a,int op)
{
    int step,bit=0;
    cmplx w_n,w,t,u;
    for (int i=1;i<k;i<<=1,++bit);
    rev[0]=0;
    for (int i=0;i<k;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    for (int i=0;i<k;++i) 
        if (i<rev[i]) swap(a[i],a[rev[i]]);
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

int manacher(char *s,int lens){
	int k,p=0,ret=0,len=1;
	s1[0]='$'; s1[1]='#';
	for (int i=0;i<lens;++i)
		s1[++len]=s[i],s1[++len]='#';
	memset(mx,0,sizeof(mx));
	for (int i=2;i<len;++i){
		if (p>i)
			mx[i]=min(mx[k*2-i],p-i);
		else
			mx[i]=1;
		while (s1[i+mx[i]]==s1[i-mx[i]]) ++mx[i];
		if (i+mx[i]>p) p=i+mx[i],k=i;
		ret=(ret+mx[i]/2)%MOD;
	}
	return ret;
}
