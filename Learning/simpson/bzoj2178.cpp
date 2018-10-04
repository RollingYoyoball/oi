#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define Pr pair<ld,ld>
#define mp make_pair
#define ld long double
using namespace std;
const int MAXN=1010;
const ld eps=1e-13,inf=2147483647;
struct Dot{/*{{{*/
	ld x,y;
	Dot(){}
	Dot(ld x1,ld y1){x=x1;y=y1;}
	friend ld dis(Dot x,Dot y){
		return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
	}
};/*}}}*/
struct Cir{/*{{{*/
	ld r;
	Dot O;
	Cir(){}
	Cir(Dot O1,ld r1){O=O1,r=r1;}
	friend bool operator < (Cir a,Cir b){
		if (a.O.x-a.r==b.O.x-b.r) return a.O.x+a.r<b.O.x+b.r;
		return a.O.x-a.r<b.O.x-b.r;
	}
	Pr getlen(ld x){
		if (r<=fabs(O.x-x)) return mp(0,0);
		ld ret=sqrt(r*r-(O.x-x)*(O.x-x));
		return mp(O.y-ret,O.y+ret);
	}
}a[MAXN];/*}}}*/
bool in[MAXN];
Pr rec[MAXN*4];
ld ans,mx,mn;
int n,m;
ld solve(ld l,ld r);
ld simpson(ld l,ld r);
ld get_val(ld x);
void prework();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	ld x,y,r;
	scanf("%d",&n);
	mx=-inf; mn=inf;
	for (int i=1;i<=n;++i){
		scanf("%Lf%Lf%Lf",&x,&y,&r);
		a[i]=Cir(Dot(x,y),r);
		if (x+r>mx) mx=x+r;
		if (x-r<mn) mn=x-r;
	}
	prework();
	ans=solve(mn,mx);
	printf("%.3Lf\n",ans);
}

ld solve(ld l,ld r){
	ld mid=(l+r)/2.0,h=simpson(l,r),hmid=simpson(l,mid)+simpson(mid,r);
	if ((fabs(r-l)<=eps)||(fabs(h-hmid)<=eps)) return hmid;
	return solve(l,mid)+solve(mid,r);	
}

ld simpson(ld l,ld r){
	ld hl=get_val(l),hr=get_val(r),hmid=get_val((l+r)/2.0);
	return (r-l)*(hl+hr+hmid*4.0)/6.0;
}

ld get_val(ld x){
	int cnt=0;
	ld ret=0,dw=-inf;
	for (int i=1;i<=n;++i){
		rec[++cnt]=a[i].getlen(x);
		if (rec[cnt]==Pr(0,0)) --cnt;
	}
	sort(rec+1,rec+1+cnt);
	for (int i=1;i<=cnt;++i){
		if (rec[i].first>dw)
			ret+=rec[i].second-rec[i].first,dw=rec[i].second;
		else if (rec[i].second>dw)
			ret+=rec[i].second-dw,dw=rec[i].second;
	}
	return ret;
}

void prework(){
	sort(a+1,a+1+n);
	for (int i=1;i<=n;++i){
		if (in[i]) continue;
		for (int j=i+1;j<=n;++j){
			if (in[j]) continue;
			if (dis(a[i].O,a[j].O)<=a[i].r-a[j].r)
				in[j]=1;
		}
	}
	for (int i=1;i<=n;++i)
		if (in[i]){
			swap(in[i],in[n]);
			swap(a[i],a[n]),--n,--i;
		}
}
