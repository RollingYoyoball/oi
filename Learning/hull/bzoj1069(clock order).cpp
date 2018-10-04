#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2010;
struct dian{
	double x,y;
	dian(){}
	dian(int _x,int _y){x=_x;y=_y;}
	friend dian operator - (dian x,dian y)
	{return dian(x.x-y.x,x.y-y.y);}
	friend double operator *(dian x,dian y)//叉积>0 x左转之后得到y
	{return x.x*y.y-x.y*y.x;}
}a[MAXN],s[MAXN];
int n,m,top;
double get_dis(dian x,dian y);
double sqr(double x){return x*x;}
double rc();
int graham();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%lf%lf\n",&a[i].x,&a[i].y);
	graham();
	printf("%0.3lf\n",rc()/2);
}

double get_dis(dian x,dian y){
	return sqr(x.x-y.x)+sqr(x.y-y.y);
}

bool cmp(dian x,dian y){
	double tmp=(x-a[1])*(y-a[1]);
	if (tmp==0) return get_dis(x,a[1])<get_dis(y,a[1]);
	return tmp<0;
}

int graham(){
	int tmp=1;
	for (int i=2;i<=n;++i)
		if (a[tmp].y>a[i].y||(a[tmp].y==a[i].y&&a[tmp].x>a[i].x))
			tmp=i;
	swap(a[tmp],a[1]);
	sort(a+2,a+1+n,cmp);
	s[++top]=a[1]; s[++top]=a[2];
	for (int i=3;i<=n;++i){
		while (top>1&&(a[i]-s[top-1])*(s[top]-s[top-1])<=0)
			--top;
		s[++top]=a[i];
	}
}

double rc(){
	s[top+1]=a[1];
	double ans=0;
	int x,y;
	for (int i=1;i<=top;++i){
		x=i%top+1;
		y=(i+2)%top+1;
		for (int j=i+2;j<=top;++j){
			while (x%top+1!=j&&(s[j]-s[i])*(s[x+1]-s[i])>(s[j]-s[i])*(s[x]-s[i]))
				x=x%top+1;
			while (y%top+1!=i&&(s[y+1]-s[i])*(s[j]-s[i])>(s[y]-s[i])*(s[j]-s[i]))
				y=y%top+1;
			ans=max((s[j]-s[i])*(s[x]-s[i])+(s[y]-s[i])*(s[j]-s[i]),ans);
		}
	}
	return ans;
}

