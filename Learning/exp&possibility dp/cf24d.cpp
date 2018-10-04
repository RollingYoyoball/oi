#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1e3+10;
double f[MAXN][MAXN],a[MAXN],b[MAXN];//f[i][j]=a[i]*f[i][j+1]+b[i]
int n,m,x,y;

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	for (int i=1;i<=m;++i)
		f[n][i]=0;
	if (m==1){
		printf("%d",(n-x)*2);
		return 0;
	}
	for (int i=n-1;i>=x;--i){
		a[1]=0.5;
		b[1]=f[i+1][1]*0.5+1.5;
		for (int j=2;j<m;++j){
			a[j]=0.25;
			a[j]/=(1.0-(a[j-1]+1.0)*0.25);
			b[j]=b[j-1]*0.25+f[i+1][j]*0.25+1.0;
			b[j]/=(1.0-(a[j-1]+1.0)*0.25);
		}
		f[i][m]=(f[i+1][m]+b[m-1]+3.0)/(2-a[m-1]);
		for (int j=m-1;j>=1;--j)
			f[i][j]=a[j]*f[i][j+1]+b[j];
	}
	printf("%.6lf\n",f[x][y]);
}
