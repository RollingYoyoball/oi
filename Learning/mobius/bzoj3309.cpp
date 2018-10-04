#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=1e7+10;
int p[MAXN];
ll g[MAXN],cnt[MAXN],mnp[MAXN];//才不是mmp
bool vis[MAXN];
int n,m,T,pos;
ll ans;
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
		ans=pos=0;
		for (int i=1;i<=n;i=pos+1){
			pos=min(n/(n/i),m/(m/i));
			ans+=(g[pos]-g[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",ans);
	}
}

int prework(int n){
	memset(vis,false,sizeof(vis));
	int tot=0,d;
	for (int i=2;i<=n;++i){
		if (!vis[i]){
			g[i]=1;
			mnp[i]=i; cnt[i]=1;
			p[++tot]=i;
		}
		for (int j=1;j<=tot&&i*p[j]<=n;++j){
			vis[i*p[j]]=true;
			if (i%p[j]){
				mnp[i*p[j]]=p[j]; cnt[i*p[j]]=1;
				g[i*p[j]]=cnt[i]==1?-g[i]:0;
			}
			else{
				cnt[i*p[j]]=cnt[i]+1;
				mnp[i*p[j]]=mnp[i]*p[j];
				d=i/mnp[i];
				if (d==1) g[i*p[j]]=1;
				else
					g[i*p[j]]=(cnt[i*p[j]]==cnt[d])?-g[d]:0;
				break;
			}
		}
	}
	for (int i=1;i<=n;++i) g[i]+=g[i-1];
}
