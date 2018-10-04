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
	ll expA[N],expB[N],visA[N],visB[N],mA[N],mB[N],slack[N];
	int T,n;
	bool dfs(int x){
		ll gap;
		visA[x]=T;
		for (int i=1;i<=n;++i){
			if (visB[i]==T) continue;
			gap=expA[x]+expB[i]-mp[x][i];
			if (gap==0){
				visB[i]=T;//imp
				if (mB[i]==-1||dfs(mB[i])){
					mB[i]=x;
					mA[x]=i;
					return true;
				}
			}
			else slack[i]=min(slack[i],gap);
		}
		return false;
	}
	void Solve(){
		for (int i=1;i<=n;++i) mB[i]=-1,expB[i]=0;
		for (int i=1;i<=n;++i){
			expA[i]=mp[i][1];//imp
			mA[i]=-1;
			for (int j=2;j<=n;++j)
				expA[i]=max(expA[i],mp[i][j]);
		}
		ll tmp;
		for (int i=1;i<=n;++i){
			for (int j=1;j<=n;++j) slack[j]=inf;
			while (1){
				++T;
				if (dfs(i)) break;
				tmp=inf;
				for (int j=1;j<=n;++j)
					if (visB[j]!=T) tmp=min(tmp,slack[j]);
				for (int j=1;j<=n;++j){
					if (visA[j]==T) expA[j]-=tmp;
					if (visB[j]==T) expB[j]+=tmp;
					else slack[j]-=tmp;
				}
			}
		}
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
