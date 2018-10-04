#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define LL long long
using namespace std;
const LL mod=1000000007;
const int maxn=2010;
int n,N,pos[maxn];
LL a[maxn],t[maxn],sum[maxn][maxn];
LL f[maxn][maxn],g[maxn],fac[maxn];

void init_hash(){
	for (int i=1;i<=n;++i) t[i]=a[i];
	sort(t+1,t+n+1);
	N=unique(t+1,t+n+1)-t-1;
}

int lowbit(int x){return x&-x;}

void update(int id,int x,LL v){
	for (int i=x;i<=n;i+=lowbit(i))
	    sum[id][i]=(sum[id][i]+v)%mod;
}

LL query(int id,int x){
	LL ret=0;
	for (int i=x;i;i-=lowbit(i))
		ret=(ret+sum[id][i])%mod;
	return ret;
}

int main(){
	freopen("a.in","r",stdin);
	
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%lld",&a[i]);
	init_hash(); fac[1]=1;
	for (int i=1;i<=n;++i)
	    pos[i]=lower_bound(t+1,t+N+1,a[i])-t;
	for (int i=2;i<=n;++i) fac[i]=1LL*fac[i-1]*i%mod;
	update(0,1,1);
	for (int i=1;i<=n;++i)
	    for (int j=i;j>=1;--j){
			f[i][j]=(f[i][j]+query(j-1,pos[i])%mod)%mod;
			update(j,pos[i],f[i][j]%mod);
	    }
	for (int i=1;i<=n;++i)
	    for (int j=i;j<=n;++j)
			g[i]=(g[i]+f[j][i])%mod;
	LL ans=0;
	for (int i=1;i<=n;++i)
	    ans=((ans%mod+(fac[n-i]%mod*g[i]%mod)%mod)%mod-fac[n-i-1]%mod*g[i+1]%mod*(i+1)%mod+mod)%mod;
	printf("%lld",ans);
}

