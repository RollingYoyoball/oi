#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 2333333333333
using namespace std;
const int MAXN=2010;
double f[MAXN][MAXN][2];
double k[MAXN],w[310][310];
int c[MAXN],d[MAXN];
int n,m,v,e;
int work();

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d%d%d",&n,&m,&v,&e);
	for (int i=1;i<=n;++i) scanf("%d",c+i);
	for (int i=1;i<=n;++i) scanf("%d",d+i);
	for (int i=1;i<=n;++i) scanf("%lf",k+i);
	int x,y;
	double z;
	for (int i=1;i<=v;++i)
		for (int j=1;j<=v;++j)
			if (i!=j) w[i][j]=inf;
	for (int i=1;i<=e;++i)
	{
		scanf("%d%d%lf",&x,&y,&z);
		w[x][y]=min(w[x][y],z);
		w[y][x]=min(w[y][x],z);
	}
	work();
	for (int i=0;i<=n;++i)
		for (int j=0;j<=m;++j)
			f[i][j][0]=f[i][j][1]=inf;
	f[1][0][0]=0; f[1][1][1]=0;
	for (int i=2;i<=n;++i)
	{
		f[i][0][0]=f[i-1][0][0]+w[c[i-1]][c[i]];
		for (int j=1;j<=min(m,i);++j)
		{
			f[i][j][0]=min(f[i-1][j][0]+w[c[i-1]][c[i]],f[i-1][j][1]+w[d[i-1]][c[i]]*k[i-1]+w[c[i-1]][c[i]]*(1-k[i-1]));
			f[i][j][1]=min(f[i-1][j-1][0]+w[c[i-1]][d[i]]*k[i]+w[c[i-1]][c[i]]*(1-k[i]),
						   f[i-1][j-1][1]+(w[d[i-1]][d[i]]*k[i-1]+w[c[i-1]][d[i]]*(1-k[i-1]))*k[i]+
						   (w[d[i-1]][c[i]]*k[i-1]+w[c[i-1]][c[i]]*(1-k[i-1]))*(1-k[i]));
		} 
	}
	double ans=inf;
	for (int i=0;i<=m;++i)
		ans=min(ans,min(f[n][i][0],f[n][i][1]));
	printf("%0.2lf\n",ans);
}

int work()
{
	//k一定要在最外层。。。 
	for (int k=1;k<=v;++k)
		for (int i=1;i<=v;++i)
			for (int j=1;j<=v;++j)
				w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
}
