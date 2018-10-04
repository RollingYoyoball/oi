#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=510;
const double eps=1e-6,inf=2147483647;
double h[N],r[N],O[N],k[N],b[N];
double lx[N],rx[N],ly[N],ry[N];
int have[N];
int n,m;
double alpha,L,R;
double val(double x);
double simpson(double l,double r);
void prework();
void calc(int x);
bool in(int x,int y){return fabs(O[x]-O[y])<=fabs(r[x]-r[y]);}
double sqr(double x){return x*x;}
double solve(double l,double r);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%lf\n",&n,&alpha);
	++n;
	for (int i=1;i<=n;++i){
		scanf("%lf",h+i);
		O[i]=h[i]/tan(alpha)+O[i-1];
	}
	L=inf,R=-inf;
	for (int i=1;i<n;++i) scanf("%lf",r+i);
	for (int i=1;i<=n;++i)
		L=min(O[i]-r[i],L),R=max(O[i]+r[i],R);

	prework();

	printf("%.2lf\n",solve(L,R)*2.0);
}

double solve(double l,double r){
	double mid=(l+r)*0.5,h=simpson(l,r),hmid=simpson(l,mid)+simpson(mid,r);
	if (fabs(r-l)<=eps||(fabs(h-hmid)<=eps)) return hmid;
	return solve(l,mid)+solve(mid,r);
}

double simpson(double l,double r){
	double hl=val(l),hr=val(r),hmid=val((l+r)*0.5);
	return (r-l)*(hl+hr+hmid*4.0)/6.0;
}

double val(double x){
	double ret=0;
	for (int i=1;i<=n;++i)
		if (fabs(x-O[i])<=r[i])
			ret=max(ret,sqrt(sqr(r[i])-sqr(x-O[i])));
	for (int i=1;i<n;++i){
		if (have[i]) continue;
		if (lx[i]<=x&&x<=rx[i]) 
			ret=max(ret,k[i]*x+b[i]);
	}
	return ret;
}

void prework(){
	for (int i=1;i<n;++i){
		have[i]=in(i,i+1);
		if (have[i]) continue;
		calc(i);
	}
	/*for (int i=1;i<=n;++i)
		if (!have[i]) 
			printf("%d     %.2lf     %.2lf\n",i,lx[i],rx[i]); */
}

void calc(int x){
	double l=(O[x+1]-O[x]);
	double theta=asin((r[x+1]-r[x])/l);
	double x1,y1,x2,y2;
	x1=O[x]-sin(theta)*r[x]; y1=cos(theta)*r[x];
	x2=O[x+1]-sin(theta)*r[x+1]; y2=cos(theta)*r[x+1];
	lx[x]=x1; ly[x]=y1;
	rx[x]=x2; ry[x]=y2;

	k[x]=(y2-y1)/(x2-x1);
	b[x]=y1-k[x]*x1;
}
