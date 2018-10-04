#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=3010;
ll a[MAXN],f[MAXN][MAXN];
int q[MAXN],sum[MAXN];
int n,m,l,r;
int sqr(int x){return x*x;}
double xie(int x,int y,int duan);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int tmp;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%lld",a+i),sum[i]=sum[i-1]+a[i];
	memset(f,0x7f,sizeof(f));
	f[0][0]=0;
	for (int j=0;j<m;++j){
		l=1;
		r=0;
		q[++r]=0;
		for (int i=1;i<=n;++i){
			while (l+1<=r&&xie(q[l+1],q[l],j)<sum[i]) ++l;
			f[i][j+1]=f[q[l]][j]+sqr(sum[i]-sum[q[l]]);
			while (r-1>=l&&xie(i,q[r],j)<xie(q[r],q[r-1],j)) --r;
			q[++r]=i;
		}
	}
	printf("%lld\n",m*f[n][m]-sqr(sum[n]));
}

double xie(int x,int y,int duan){   
	return (1.0*f[x][duan]+sqr(sum[x])-1.0*f[y][duan]-sqr(sum[y]))/(2.0*(sum[x]-sum[y]));
}

