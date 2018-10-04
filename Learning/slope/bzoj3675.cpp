#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
ll a[MAXN],sum[MAXN],q[MAXN];
ll f[MAXN][2];
int n,m,l,r,now,pre;
bool check(int i,int j,int k,int duan,ll K);
bool check1(int r1,int r,int i,int duan);
ll F(int i,int duan){return f[i][duan]-sum[i]*sum[i];}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%lld",a+i),sum[i]=sum[i-1]+a[i];
	f[0][0]=0;
	pre=0,now=1;
	for (int j=0;j<m;++j){
		l=1;r=0; q[++r]=0;
		for (int i=1;i<=n;++i){
			while (l+1<=r&&check(i,q[l+1],q[l],pre,-sum[i])) ++l;//compare by using the formular
			f[i][now]=F(q[l],pre)+sum[i]*sum[q[l]];
			while (r-1>=l&&check1(q[r-1],q[r],i,pre)) --r;//compare K_{r-1} and K_{r}
			q[++r]=i;
		}
		swap(now,pre);
	}
	printf("%lld\n",f[n][pre]);
}

bool check(int i,int j,int k,int duan,ll K){//j better than k?
	return F(k,duan)-F(j,duan)<=K*(sum[k]-sum[j]);
}

bool check1(int r1,int r,int i,int duan){//r1 better than r?
	return (F(r,duan)-F(r1,duan))*(sum[i]-sum[r])<=(F(i,duan)-F(r,duan))*(sum[r]-sum[r1]);
}
