#include<iostream>
#include<cstdio>
#include<cstdio>
#define ll long long
using namespace std;
const int N=410;
const ll inf=8223372036854775808;
ll mp[N][N];
int m,n1,n2;
namespace KM{/*{{{*/
	ll expA[N],expB[N],mA[N],mB[N],slack[N];
	int pre[N],vis[N];
	int T,n;
	void bfs(int x){
		int na=0,nb=0,recb;
		ll tmp;
		for (int i=1;i<=n;++i)
			slack[i]=inf,pre[i]=0;
		mB[nb]=x;
		++T;
		do{
			na=mB[nb],tmp=inf,vis[nb]=T;
			recb=0;
			for (int i=1;i<=n;++i){
				if (vis[i]==T) continue;
				if (slack[i]>expA[na]+expB[i]-mp[na][i])
					slack[i]=expA[na]+expB[i]-mp[na][i],pre[i]=nb;
				if (slack[i]<tmp)
					tmp=slack[i],recb=i;
			}
			for (int i=0;i<=n;++i)
				if (vis[i]==T)
					expA[mB[i]]-=tmp,expB[i]+=tmp;
				else
					slack[i]-=tmp;
			nb=recb;
		}while (mB[nb]);
		for (;nb;nb=pre[nb]) mB[nb]=mB[pre[nb]];
	}
	void Solve(){
		for (int i=1;i<=n;++i) mB[i]=0,expB[i]=0;
		for (int i=1;i<=n;++i){
			expA[i]=mp[i][1];//imp
			mA[i]=0;
			for (int j=2;j<=n;++j)
				expA[i]=max(expA[i],mp[i][j]);
		}
		for (int i=1;i<=n;++i)
			bfs(i);
		for (int i=1;i<=n;++i)
			mA[mB[i]]=i;
		ll ans=0;
		for (int i=1;i<=n;++i) 
			ans+=mp[i][mA[i]];
		printf("%lld\n",ans);
		for (int i=1;i<=n1;++i)
			if (mp[i][mA[i]]!=0) printf("%d ",mA[i]);
			else printf("0 ");
	}
};/*}}}*/

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y;
	ll w;
	scanf("%d%d%d",&n1,&n2,&m);
	KM::n=max(n1,n2);
	for (int i=1;i<=m;++i){
		scanf("%d%d%lld",&x,&y,&w);
		mp[x][y]=w;
	}
	KM::Solve();
}
