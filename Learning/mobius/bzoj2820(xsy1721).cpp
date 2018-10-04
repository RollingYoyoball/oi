#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=1e7+10;
int miu[MAXN],p[MAXN],g[MAXN],sum[MAXN];
bool vis[MAXN];
ll ans;
int n,m,T,cnt,pos;
int prework(int n);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&T);
	prework(10000000);
	for (int o=1;o<=T;++o){
		scanf("%d%d",&n,&m);
		if (n>m) swap(n,m);
		ans=0;
		for (int i=1;i<=n;i=pos+1){
			pos=min(n/(n/i),m/(m/i));
			ans+=(ll)(sum[pos]-sum[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",ans);
	}
}

int prework(int n){
	memset(vis,0,sizeof(vis));
	miu[1]=1;
	cnt=0;
	for (int i=2;i<=n;++i){
		if (!vis[i]){
			p[++cnt]=i;
			miu[i]=-1; g[i]=1;
		}
		for (int j=1;j<=cnt&&i*p[j]<=n;++j){
			vis[i*p[j]]=1;
			if (i%p[j]){
				miu[i*p[j]]=-miu[i];
				g[i*p[j]]=miu[i]-g[i];
			}
			else{
				miu[i*p[j]]=0,g[i*p[j]]=miu[i];
				break;
			}
		}
	}
	for (int i=1;i<=n;++i)
		sum[i]=sum[i-1]+g[i];
}
