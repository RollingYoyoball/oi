//ÄæÊ±Õë 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define eps 0.00000001
using namespace std;
const int MAXN=5*(1e5)+10;
struct dian{
	double x,y;
	dian(){}
	dian(double _x,double _y){x=_x;y=_y;}
	friend dian operator -(dian x,dian y)
	{return dian(x.x-y.x,x.y-y.y);}
	friend double operator *(dian x,dian y)
	{return x.x*y.y-x.y*y.x;}
	friend dian operator *(dian x,double y)
	{return dian(x.x*y,x.y*y);}
	friend bool operator <(dian x,dian y)
	{return x.y==y.y?x.x<y.x:x.y<y.y;}
	friend dian operator +(dian x,dian y)
	{return dian(x.x+y.x,x.y+y.y);}
}a[MAXN],s[MAXN],rec[5];
int n,m,top;
int graham();
double sqr(double x){return x*x;}
double get_dis(dian x,dian y);
bool cmp(dian x,dian y);
int rc();
double cross(dian x,dian y,dian p);
double dot(dian x,dian y);
int Cmp(double x);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	double x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%lf%lf",&a[i].x,&a[i].y);
	}
	graham();
	rc();
}

double get_dis(dian x,dian y){
	return sqrt(sqr(x.x-y.x)+sqr(x.y-y.y));
}

int graham(){
	int tmp=1;
	for (int i=2;i<=n;++i)
		if (a[i]<a[tmp])
			tmp=i;
	swap(a[tmp],a[1]);
	sort(a+2,a+1+n,cmp);
	double ttmp=(a[n]-a[1])*(a[n-1]-a[1]);
	s[++top]=a[1]; s[++top]=a[2];
	for (int i=3;i<=n;++i){
		while (top>1&&(s[top]-s[top-1])*(a[i]-s[top-1])<eps) --top;
		s[++top]=a[i];
	}
}

bool cmp(dian x,dian y){
	double tmp=(x-a[1])*(y-a[1]);
	if (fabs(tmp)<=eps) return get_dis(x,a[1])-get_dis(y,a[1])<0;
	return tmp>0;
}

int rc(){
	s[top+1]=a[1];
	double ans=1e10;
	int h=2,l=2,r=2;
	double len1,len2,H,dist;
	for (int i=1;i<=top;++i){
		dist=get_dis(s[i],s[i+1]);
		while ((s[i+1]-s[i])*(s[h%top+1]-s[i])-(s[i+1]-s[i])*(s[h]-s[i])>-eps)
			h=h%top+1;
		while (dot(s[i+1]-s[i],s[r%top+1]-s[i])-dot(s[i+1]-s[i],s[r]-s[i])>-eps)
			r=r%top+1;
		if (i==1) l=r;
		while (dot(s[i+1]-s[i],s[l%top+1]-s[i])-dot(s[i+1]-s[i],s[l]-s[i])<eps)
			l=l%top+1;
		H=fabs((s[i+1]-s[i])*(s[h]-s[i])/dist);
		len1=dot(s[i+1]-s[i],s[r]-s[i])/dist;
		len2=dot(s[i+1]-s[i],s[l]-s[i])/dist;
		if (H*(len1-len2)<ans){
			ans=H*(len1-len2);
			rec[0]=s[i]+(s[i+1]-s[i])*(len1/dist);
			rec[1]=rec[0]+(s[r]-rec[0])*(H/get_dis(rec[0],s[r]));
			rec[2]=rec[1]-(rec[0]-s[i])*((len1-len2)/get_dis(s[i],rec[0]));
			rec[3]=rec[2]-(rec[1]-rec[0]);
		}
	}
	printf("%.5lf\n",ans);
	int st=0;
	for (int i=1;i<4;++i)
		if (rec[i]<rec[st]) st=i;
	for (int i=0;i<4;++i)
		printf("%.5lf %.5lf\n",rec[(st+i)%4].x,rec[(st+i)%4].y);
}

double dot(dian x,dian y){//x * y
	return x.x*y.x+x.y*y.y;
}

