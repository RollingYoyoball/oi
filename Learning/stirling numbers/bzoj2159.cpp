#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 10007
#define ll long long
using namespace std;
const int MAXN=50010;
const int K=160;
struct xxx{
	int y,next;
}a[MAXN*2];
ll f[MAXN][K],g[MAXN][K],h[MAXN],fac[MAXN],s[MAXN][K];
int n,m,tot,k,l,A,B,Q,now;
ll ans;
int add(int x,int y);
int dfs(int fa,int x);
int dfs1(int fa,int x);
int prework();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y,tmp;
	scanf("%d%d%d",&n,&k,&l);
	scanf("%d%d%d%d",&now,&A,&B,&Q);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		now=(now*A+B)%Q;
		tmp=(i<l)?i:l;
		x=i-now%tmp; y=i+1;
		add(x,y); add(y,x);
		printf("%d %d\n",x,y);
	}
	prework();
	for (int i=1;i<=n;++i){
		ans=0;
		for (int j=1;j<=k;++j)
			ans=(ans+s[k][j]*fac[j]%MOD*(f[i][j]+g[i][j])%MOD)%MOD;
		printf("%lld\n",ans);
	}
}

int add(int x,int y){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa,int x){
	int u;
	f[x][0]=1;
	for (int i=1;i<=k;++i) f[x][i]=0;
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
		f[x][0]=(f[x][0]+f[u][0])%MOD;
		for (int j=1;j<=k;++j)
			f[x][j]=(f[u][j]+f[u][j-1]+f[x][j])%MOD;
	}
}

int dfs1(int fa,int x){
	int u;
	ll tmp;
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==fa) continue;
		for (int j=1;j<=k;++j){
			tmp=(f[x][j]-f[u][j]-f[u][j-1]+2*MOD)%MOD;
			tmp=(tmp+f[x][j-1]-f[u][j-1]+2*MOD)%MOD;
			if (j>=2) tmp=(tmp-f[u][j-2]+MOD)%MOD;
			g[u][j]=(g[u][j]+g[x][j]+g[x][j-1]+tmp)%MOD;
		}
		g[u][0]=(g[u][0]+g[x][0]+(f[x][0]-f[u][0]+MOD)%MOD)%MOD;
		dfs1(x,u);
	}
}

int prework(){
	dfs(0,1);
	dfs1(0,1);
	fac[0]=1;
	for (int i=1;i<=k;++i) fac[i]=fac[i-1]*i%MOD;
	for (int i=1;i<=k;++i){
		s[i][0]=0;
		for (int j=1;j<i;++j)
			s[i][j]=(j*s[i-1][j]%MOD+s[i-1][j-1])%MOD;
		s[i][i]=1;
	}
}
