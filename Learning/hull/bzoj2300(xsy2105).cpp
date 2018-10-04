#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<cmath>
#include<algorithm>
#define eps 0.0000001
using namespace std;
const int MAXN=1e5+10;
struct dian{
	double x,y;
	dian(){}
	dian(double x_,double y_){x=x_;y=y_;}
	friend double operator *(dian x,dian y)
	{return x.x*y.y-x.y*y.x;}
	friend dian operator +(dian x,dian y)
	{return dian(x.x+y.x,x.y+y.y);}
	friend dian operator -(dian x,dian y)
	{return dian(x.x-y.x,x.y-y.y);}
	friend bool operator <(dian x,dian y)
	{return x.x==y.x?x.y<y.y:x.x<y.x;}
}a[MAXN],rec[MAXN];
struct Q{
	int op,x;
}q[MAXN*2];
double sqr(double x){return x*x;}
double get_dis(dian x,dian y){return sqrt(sqr(x.x-y.x)+sqr(x.y-y.y));}
set<dian> s;
set<dian>::iterator l,r,it;
bool out[MAXN];
double ans[MAXN*2];
double ansnow;
int n,m,top,x,y,cnt;
int add(dian x);
double get_dis(dian x,dian y);
bool Cmp(dian x,dian y);
int add(dian x);
double cross(dian p,dian x,dian y){return (x-p)*(y-p);}//>0 xp逆时针得到yp
int debug();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&x,&y);
	s.insert(dian(n,0.0));
	s.insert(dian(x,y));
	s.insert(dian(0.0,0.0));
	ansnow=get_dis(dian(n,0.0),dian(x,y))+get_dis(dian(x,y),dian(0.0,0.0));
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%lf%lf\n",&a[i].x,&a[i].y);
	}
	n=m;
	int op,x;
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%d",&q[i].op);
		if (q[i].op==1){
			scanf("%d",&q[i].x);
			out[q[i].x]=true;
		}	
	}
	for (int i=1;i<=n;++i)
		if (!out[i])
			add(a[i]);
	for (int i=m;i>=1;--i){
		if (q[i].op==2)
			ans[i]=ansnow;
		else
			add(a[q[i].x]);
	}
	for (int i=1;i<=m;++i)
		if (q[i].op==2)
			printf("%.2lf\n",ans[i]);
}

int add(dian x){
//	debug();
	r=s.lower_bound(x); l=r;
	--l;
	if (cross(*l,x,*r)>=0) return 0;//contain
	ansnow-=get_dis(*l,*r);
	for (it=r++;r!=s.end();it=r++){
		if (cross(x,*it,*r)>=0){
			ansnow-=get_dis(*it,*r);
			s.erase(it);
		}
		else break;
	}
	for (it=l--;it!=s.begin();it=l--){
		if (cross(*l,*it,x)>=0){
			ansnow-=get_dis(*it,*l);
			s.erase(it);
		}
		else break;
	}
	s.insert(x);
	l=s.find(x); r=l;
	--l; ++r;
	ansnow+=get_dis(*l,x)+get_dis(x,*r);
	//printf("%.2lf\n",ansnow);
}

int debug(){
	for (it=s.begin();it!=s.end();++it){
		dian tmp=*it;
		printf("%.0lf %.0lf\n",tmp.x,tmp.y);
	}
	printf("\n");
}
