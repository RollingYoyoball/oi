#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
vector<int> q[MAXN];
ll cnt[MAXN],a[MAXN],f[MAXN],loc[10010];//roll
int top[MAXN],pre[MAXN];
int n,m;
ll ans;
int query(int col,int i);
ll sqr(ll x){return x*x;}
ll chaji(ll x1,ll y1,ll x2,ll y2){return x1*y2-x2*y1;}
ll X(int i){return 2*(cnt[i]+1);}
ll Y(int i){return f[i-1]+a[i]*sqr(cnt[i]-1);}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",a+i);
	cnt[0]=0;
	for (int i=1;i<=n;++i){
		cnt[i]=cnt[loc[a[i]]]+1;
		pre[i]=loc[a[i]];
		loc[a[i]]=i;
	}
	f[0]=0;
	int x,sz,r,loc;
	for (int i=1;i<=n;++i){
		x=a[i];
		while (top[x]>1&&chaji(X(i)-X(q[x][top[x]-2]),Y(i)-Y(q[x][top[x]-2]),X(q[x][top[x]-1])-X(q[x][top[x]-2]),Y(q[x][top[x]-1])-Y(q[x][top[x]-2]))<0)
			--top[x],q[x].pop_back();
		q[x].push_back(i); ++top[x];
		loc=query(x,i);
		f[i]=f[loc-1]+x*sqr(cnt[i]-cnt[loc]+1);
		//printf("%lld\n",f[i]);
	}
	printf("%lld\n",f[n]);
}

int query(int col,int i){
	int l=1,r=q[col].size()-1,mid,ret=0,j,k;
	while (l<=r){
		mid=l+r>>1;
		j=q[col][mid-1];
		k=q[col][mid];
		if (f[j-1]+col*sqr(cnt[i]-cnt[j]+1)<f[k-1]+col*sqr(cnt[i]-cnt[k]+1)) ret=mid,l=mid+1;
		else 
			r=mid-1;
	}
	return q[col][ret];
}
