#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=510;
const int MAXM=500*500+10;
double a[MAXN][MAXN],f[MAXN],g[MAXM];
int d[MAXN],u[MAXM],v[MAXM];
int go[MAXN][MAXN];
double ans;
int n,m;
int gauss();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		u[i]=x; v[i]=y;
		go[x][y]=1; go[y][x]=1;
		++d[x]; ++d[y];
	}
	--n;
	a[1][n+1]=-1.0;
	for (int i=1;i<=n;++i){
		a[i][i]=-1.0;
		for (int j=1;j<=n;++j){
			if (!go[i][j]) continue;
			a[i][j]=1.0/d[j];
		}
	}
	gauss();
	for (int i=1;i<=m;++i)
		g[i]=f[u[i]]/d[u[i]]+f[v[i]]/d[v[i]];
	sort(g+1,g+1+m);
	for (int i=1;i<=m;++i)
		ans+=g[i]*(m-i+1);
	printf("%.3lf\n",ans);
}

int gauss(){
	int id;
	for (int i=1;i<=n;++i){
		id=i;
		for (int j=i+1;j<=n;++j)
			if (fabs(a[j][i])>fabs(a[id][i])) id=j;
		if (id!=i)
			for (int j=1;j<=n+1;++j) swap(a[i][j],a[id][j]);
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
