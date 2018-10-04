#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define eps 0.0000001
#define inf 100000
using namespace std;
const int MAXN=5*(1e5)+10;
struct dian{
	double x,y;
	dian(){}
	dian(double x_,double y_){x=x_;y=y_;}
	friend double operator *(dian x,dian y)
	{return x.x*y.y-x.y*y.x;}
	friend dian operator -(dian x,dian y)
	{return dian(x.x-y.x,x.y-y.y);}
	friend bool operator < (dian x,dian y)
	{return fabs(x.x-y.x)<=eps?x.y<y.y:x.x<y.x;}
}q[MAXN],up[MAXN],dw[MAXN],a[MAXN];
int ans[MAXN],op[MAXN];
int n,m,top1,top2;
int graham(dian *d,int n);
int query(int x);
int solve(int l,int r);
double sqr(double x){return x*x;}
double dis(dian x,dian y){return sqrt(sqr(x.x-y.x)+sqr(x.y-y.y));}
double dot(dian x,dian y){return x.x*y.x+x.y*y.y;}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d",&n);
	int cnt=0;
	for (int i=1;i<=n;++i){
		scanf("%d%lf%lf\n",&op[i],&q[i].x,&q[i].y);
		if (op[i]) ans[i]=cnt;
		else cnt=1;
	}
	solve(1,n);
	for (int i=1;i<=n;++i)
		if (op[i])
			printf(ans[i]?"Yes\n":"No\n");
}

int graham(dian *d,int n){
	sort(d+1,d+1+n);
	top1=0; top2=0;
	for (int i=1;i<=n;++i){
		while (top1>1&&(up[top1]-up[top1-1])*(a[i]-up[top1-1])>=0) --top1;
		while (top2>1&&(a[i]-dw[top2-1])*(dw[top2]-dw[top2-1])>=0) --top2;
		up[++top1]=a[i]; dw[++top2]=a[i];
	}
}

int query(int x,dian *d,int n){
	int l=1,r=n,mid,ll,rr;
	/*printf("#%d\n",q[x].y>0?1:-1);
	for (int i=1;i<=n;++i)
		printf("%.0lf %.0lf\n",d[i].x,d[i].y);
	printf("\n");*/
	while (r-l>2){
		ll=(l*2+r)/3;
		rr=(l+r*2)/3;
		if (dot(q[x],d[ll])<dot(q[x],d[rr])) r=rr;
		else l=ll;
	}
	double tmp=123456789101112.0;
	for (int i=l;i<=r&&ans[x];++i)
		tmp=min(tmp,dot(q[x],d[i]));
	if (sqr(q[x].x)+sqr(q[x].y)>2.0*tmp) ans[x]=0;
}

int solve(int l,int r){
	if (l>=r) return 0;
	int mid=l+r>>1,tot;
	solve(l,mid);
	solve(mid+1,r);
	tot=0;
	for (int i=l;i<=mid;++i)
		if (!op[i]) a[++tot]=q[i];
	graham(a,tot);
	for (int i=mid+1;i<=r;++i)
		if (op[i]&&ans[i]){
			if (q[i].y<0)
				query(i,up,top1);
			else
				query(i,dw,top2);
		}
}
