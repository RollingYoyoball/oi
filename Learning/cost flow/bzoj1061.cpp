#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
#define inf 2147483647
using namespace std;
const int N=1010;
const int M=10010;
struct xxx{
	int y,next,r,op,c;
}a[M*10];
int q[N*2];
int h[N],X[N];
int pre[100010],mn[N],pred[100010];
ll d[N];
ll ans;
bool vis[N];
int n,m,vs,vt,tot,head,tail;
int add(int x,int y,int r,int c);
int spfa();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int l,r,c,tmp;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",X+i);
	vs=0,vt=n+2;
	memset(h,-1,sizeof(h));
	for (int i=2;i<=n+1;++i) add(i,i-1,inf,0);
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&l,&r,&c);
		add(l,r+1,inf,c);
	}
	for (int i=1;i<=n+1;++i){
		tmp=X[i]-X[i-1];
		if (tmp>0) add(vs,i,tmp,0);
		if (tmp<0) add(i,vt,-tmp,0);
	}
	ans=0;
	while (spfa());
	printf("%lld\n",ans);
}

int add(int x,int y,int r,int c){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].r=r; a[tot].op=tot+1; a[tot].c=c;
	a[++tot].y=x; a[tot].next=h[y]; h[y]=tot; a[tot].r=0; a[tot].op=tot-1; a[tot].c=-c;
}

int spfa(){
	head=0,tail=1;
	for (int i=vs;i<=vt;++i) d[i]=inf,vis[i]=false,mn[i]=inf;
	q[1]=vs; vis[vs]=1; d[vs]=0;
	mn[vs]=inf; pre[vs]=-1; pred[vs]=-1;
	int v,u;
	do{
		if (head==N) head=0;
		v=q[++head];
		for (int i=h[v];i!=-1;i=a[i].next){
			u=a[i].y;
			if (!a[i].r) continue;
			if (d[u]>d[v]+a[i].c){
				pre[u]=i; pred[u]=v;
				mn[u]=min(mn[v],a[i].r);
				d[u]=d[v]+a[i].c;
				if (!vis[u]){
					vis[u]=1;
					if (tail==N) tail=0;
					q[++tail]=u;
				}
			}
		}
		vis[v]=false;
	}while(head<tail);
	if (d[vt]==inf) return false;
	ll flow=mn[vt];
	ans+=flow*d[vt];
	u=vt;
	while (pre[u]!=-1){
		a[pre[u]].r-=flow;
		a[a[pre[u]].op].r+=flow;
		u=pred[u];
	}
	return true;
}
