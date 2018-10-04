#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
const int MOD=2147483647;
struct Q{
	int id,n,m,a;
	friend bool operator <(Q x,Q y)
	{return x.a<y.a;}
}q[MAXN];
int miu[MAXN],g[MAXN],p[MAXN],f[MAXN],loc[MAXN];
ll c[MAXN];
int ans[MAXN];
bool vis[MAXN];
int n,m,T,maxn,a,pos,nowans;
int prework(int n);
int ksm(int x,int y);
int add(int x,ll delta);
ll query(int x);
bool cmp(int x,int y){return f[x]<f[y];}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d",&T);
	maxn=0;
	for (int i=1;i<=T;++i){
		scanf("%d%d%d",&q[i].n,&q[i].m,&q[i].a);
		q[i].id=i;
		if (q[i].n>q[i].m) swap(q[i].n,q[i].m);
		maxn=max(maxn,q[i].n);
	}
	prework(maxn);
	sort(q+1,q+1+T);
	for (int i=1;i<=maxn;++i) loc[i]=i;
	sort(loc+1,loc+1+maxn,cmp);
	int now=1;
	for (int o=1;o<=T;++o){
		n=q[o].n;
		m=q[o].m;
		a=q[o].a;
		while (now<=maxn&&f[loc[now]]<=a){
			for (int t=1;t*loc[now]<=maxn;++t)
				add(t*loc[now],f[loc[now]]*miu[t]);
			++now;
		}
		nowans=pos=0;
		for (int i=1;i<=n;i=pos+1){
			pos=min(n/(n/i),m/(m/i));
			nowans+=(n/i)*(m/i)*(query(pos)-query(i-1));
		}
		ans[q[o].id]=nowans&MOD;
	}
	for (int i=1;i<=T;++i) printf("%lld\n",ans[i]);
}

int prework(int n){
	miu[1]=1; f[1]=1;
	memset(vis,false,sizeof(vis));
	int cnt=0,tmp,tot;
	for (int i=2;i<=n;++i){
		if (!vis[i]){
			p[++cnt]=i;
			miu[i]=-1;
			f[i]=i+1;
		}
		for (int j=1;j<=cnt&&p[j]*i<=n;++j){
			vis[i*p[j]]=true;
			if (i%p[j]){
				miu[i*p[j]]=-miu[i];
				f[i*p[j]]=f[i]*(1+p[j]);
			}
			else{
				miu[i*p[j]]=0;
				tmp=i;tot=1;
				while (tmp%p[j]==0) tmp/=p[j];
				f[i*p[j]]=f[tmp]+p[j]*f[i];
			}
		}
	}
}


int add(int x,ll delta){
	for (;x<=maxn;x+=x&-x)
		c[x]+=delta;
}

ll query(int x){
	ll ret=0;
	for (;x;x-=x&-x)
		ret+=c[x];
	return ret;
}
