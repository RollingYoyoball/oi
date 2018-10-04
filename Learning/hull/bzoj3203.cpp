#include<iostream>
#include<cstdio>
#include<cstring>
#define eps 0.000001
using namespace std;
const int MAXN=1e5+10;
struct dian{
	double x,y;
	dian(){}
	dian(double x_,double y_){x=x_;y=y_;}
	friend double operator *(dian x,dian y)
	{return x.x*y.y-x.y*y.x;}
	friend double operator /(dian x,dian y)
	{return (x.y-y.y)/(x.x-y.x);}
	friend dian operator -(dian x,dian y)
	{return dian(x.x-y.x,x.y-y.y);}
}s[MAXN];
double w[MAXN],loc[MAXN],sum[MAXN];
double ans,d;
int n,m,top;
double get_ans(dian x);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	double x;
	scanf("%d%lf",&n,&d);
	for (int i=1;i<=n;++i){
		scanf("%lf%lf",&x,loc+i);
		sum[i]=sum[i-1]+x;
	}
	top=0;
	dian tmp;
	ans=0.0;
	for (int i=1;i<=n;++i){
		tmp=dian(d*i,sum[i-1]);
		while (top>1&&(tmp-s[top-1])*(s[top]-s[top-1])>=0) --top;
		s[++top]=tmp;
		ans+=get_ans(dian(loc[i]+i*d,sum[i]));
	}
	printf("%.0lf\n",ans);
}

double get_ans(dian x){
	int l=1,r=top,mid,ll,rr;
	/*for (int i=1;i<=top;++i)
		printf("%.0lf %.0lf\n",s[i].x,s[i].y);
	printf("\n");*/
	while (r-l>2){
		ll=(l*2+r)/3;
		rr=(l+r*2)/3;
		if (x/s[ll]<x/s[rr]) l=ll;
		else r=rr;
	}
	double ret=0;
	for (int i=l;i<=r;++i){
		ret=max(ret,x/s[i]);
	}
	return ret;
}
