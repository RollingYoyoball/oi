#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 100000009
#define ll long long
using namespace std;
const int MAXN=1e7+10;
ll p[MAXN],g[MAXN],s[MAXN];
bool vis[MAXN];
int ans;
int n,m,T,pos,tmp;
int prework(int n);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d",&T);
	prework(10000000);
	for (int o=1;o<=T;++o){
		scanf("%d%d",&n,&m);
		if (n>m) swap(n,m);
		pos=ans=0;
		for (int i=1;i<=n;i=pos+1){
			pos=min(n/(n/i),m/(m/i));
			ll tmp=(s[n/i]*s[m/i]%MOD*(g[pos]-g[i-1])%MOD)%MOD;
			ans=((ll)ans+tmp+MOD)%MOD;
		}
		printf("%d\n",ans);
	}
}

int prework(int n){
	g[1]=1; s[1]=1;
	int cnt=0;
	memset(vis,false,sizeof(vis));
	for (int i=2;i<=n;++i){
		s[i]=(ll)i*(i+1)/2%MOD;
		if (!vis[i]){
			g[i]=(i-(ll)i*i%MOD+MOD)%MOD;
			p[++cnt]=i;
		}
		for (int j=1;j<=cnt&&i*p[j]<=n;++j){
			vis[i*p[j]]=true;
			if (i%p[j])
				g[i*p[j]]=g[i]*g[p[j]]%MOD;
			else{
				g[i*p[j]]=g[i]*p[j]%MOD;
				break;
			}
		}
	}
	for (int i=1;i<=n;++i)
		g[i]=(g[i]+g[i-1])%MOD;
}
