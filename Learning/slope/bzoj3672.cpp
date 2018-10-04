#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=2*(1e5)+10;
const ll inf=1LL<<60;
struct xxx{
	int y,nxt;
}a[MAXN*2];
int h[MAXN],sz[MAXN],vis[MAXN],mx[MAXN],pre[MAXN];
int rec[MAXN],st[MAXN],rec_pre[MAXN];
ll p[MAXN],q[MAXN],l[MAXN],dep[MAXN];
ll f[MAXN];
int n,m,tot,rt,rt_mx,All,T;
void add(int x,int y);
void get_sz(int fa,int x);
void get_rt(int All,int fa,int x);
void dfs(int fa,int x);
void solve(int x,int All);
bool cmp(int x,int y){return dep[x]-l[x]>dep[y]-l[y];}
void update(int x,int top);
ll X(int i){return dep[i];}
ll Y(int i){return f[i];}
double get_k(int i,int j){if (X(i)==X(j)) return inf; return (1.0*(Y(i)-Y(j)))/(1.0*(X(i)-X(j)));}

int main(){
#ifndef ONLINE_JUDGE
	freopen("3.in","r",stdin);
#endif
	scanf("%d%d\n",&n,&T);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=2;i<=n;++i){
		scanf("%d%lld%lld%lld%lld\n",pre+i,dep+i,p+i,q+i,l+i);
		dep[i]+=dep[pre[i]];
		add(pre[i],i);
	}
	for (int i=1;i<=n;++i) f[i]=inf;
	f[1]=0;
	solve(1,n);
	for (int i=2;i<=n;++i) printf("%lld\n",f[i]);
}

void add(int x,int y){
	a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;
}

void get_sz(int fa,int x){
	int u;
	sz[x]=1; mx[x]=0;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_sz(x,u);
		sz[x]+=sz[u];
		mx[x]=max(mx[x],sz[u]);
	}
}

void get_rt(int All,int fa,int x){
	mx[x]=max(mx[x],All-sz[x]);
	if (mx[x]<=rt_mx) rt=x,rt_mx=mx[x];
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_rt(All,x,u);
	}
}

void solve(int x,int All){
	int u,Rt;
	rt=-1,rt_mx=n;
	get_sz(0,x);
	get_rt(All,0,x);
	vis[rt]=1;
	Rt=rt;
	if (Rt!=x)
		solve(x,All-sz[Rt]);
		
	rec[0]=0;
	for (int i=h[Rt];i!=-1;i=a[i].nxt)
		if (!vis[a[i].y]) dfs(x,a[i].y);
	sort(rec+1,rec+1+rec[0],cmp);

	rec_pre[0]=1; rec_pre[1]=Rt;
	for (int i=Rt;i!=x;i=pre[i]){
		if (dep[Rt]-dep[pre[i]]<=l[Rt])
			f[Rt]=min(f[Rt],f[pre[i]]+p[Rt]*(dep[Rt]-dep[pre[i]])+q[Rt]);
		rec_pre[++rec_pre[0]]=pre[i];
	}

	int top=0,tot=1;
	for (int i=1;i<=rec_pre[0];++i){
		while (tot<=rec[0]&&dep[rec[tot]]-dep[rec_pre[i]]>l[rec[tot]])
			update(rec[tot],top),++tot;
		while (top>1&&get_k(st[top-1],rec_pre[i])<=get_k(st[top],rec_pre[i])) //down
			--top;
		st[++top]=rec_pre[i];
	}
	while (tot<=rec[0]) update(rec[tot],top),++tot;

	for (int i=h[Rt];i!=-1;i=a[i].nxt){
		if (!vis[a[i].y])
			solve(a[i].y,sz[a[i].y]);
	}
}

void dfs(int fa,int x){
	int u;
	rec[++rec[0]]=x;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		dfs(x,u);
	}
}

void update(int i,int top){
	if (!top) return;
	int l=1,r=top-1,mid,ret=top,j,k;
	while (l<=r){
		mid=l+r>>1;
		j=st[mid];
		k=st[mid+1];
		if ((f[j]-f[k])<=p[i]*(dep[j]-dep[k])) ret=mid,r=mid-1;
		else l=mid+1;
	}
	ret=st[ret];
	f[i]=min(f[i],f[ret]+p[i]*(dep[i]-dep[ret])+q[i]);
}
