#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=20*20+10;
double a[MAXN][MAXN],p[30],f[MAXN];
int du[MAXN];
vector<int> go[MAXN];
int n,m,st1,st2,cnt;
int id(int x,int y){return (x-1)*n+y;}
int gauss(int n);
int prework();
double fabs(double x){return x<0?-x:x;}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d%d",&n,&m,&st1,&st2);
	int x,y;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		go[x].push_back(y); go[y].push_back(x);
		++du[x]; ++du[y];
	}
	for (int i=1;i<=n;++i)
		scanf("%lf",p+i);
	prework();
	gauss(n*n);
	for (int i=1;i<=n;++i)
		printf("%.6lf ",f[id(i,i)]);
}

int prework(){
	int now,x,y;
	for (int i=1;i<=n;++i){
		for (int j=1;j<=n;++j){
			a[id(i,j)][id(i,j)]-=1.0;
			if (i==j) continue;
			for (int k=0;k<go[i].size();++k){
				x=go[i][k];
				a[id(x,j)][id(i,j)]+=(1.0-p[i])/du[i]*p[j];
			}
			for (int k=0;k<go[j].size();++k){
				y=go[j][k];
				a[id(i,y)][id(i,j)]+=(1.0-p[j])/du[j]*p[i];
			}
			for (int k=0;k<go[i].size();++k)
				for (int k1=0;k1<go[j].size();++k1){
					x=go[i][k]; y=go[j][k1];
					a[id(x,y)][id(i,j)]+=(1.0-p[i])/du[i]*(1.0-p[j])/du[j];
				}
			a[id(i,j)][id(i,j)]+=p[i]*p[j];
		}
	}
	a[id(st1,st2)][n*n+1]-=1.0;
}

int gauss(int n){
	int tmp;
	for (int i=1;i<=n;++i){
		tmp=i;
		for (int j=i+1;j<=n;++j)
			if (fabs(a[j][i])>fabs(a[tmp][i])) tmp=j;
		if (tmp!=i)
			for (int j=1;j<=n+1;++j) swap(a[i][j],a[tmp][j]);
		for (int j=i+1;j<=n;++j){
			double t=a[j][i]/a[i][i];
			for (int k=i;k<=n+1;++k)
				a[j][k]-=t*a[i][k];
		}
	}
	for (int i=n;i>=1;--i){
		for (int j=n;j>i;--j)
			a[i][n+1]-=a[i][j]*a[j][n+1];
		a[i][n+1]/=a[i][i];
	}
	for (int i=1;i<=n;++i)
		f[i]=a[i][n+1];
}
