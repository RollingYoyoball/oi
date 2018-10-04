#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 2147483647
using namespace std;
const int MAXN=1e5+10;
double w[MAXN],mx[MAXN],f[5010][5010];
int n,m,q,tot;
struct segtree{
	int lch[MAXN*4],rch[MAXN*4];
	double mx[MAXN*4];
	int tot;
	int pushup(int x){
		mx[x]=max(mx[lch[x]],mx[rch[x]]);
	}
	int build(){_build(++tot,1,n);}
	int _build(int x,int l,int r){
		if (l==r){
			mx[x]=w[l]; return 0;
		}
		int mid=l+r>>1;
		lch[x]=++tot; _build(lch[x],l,mid);
		rch[x]=++tot; _build(rch[x],mid+1,r);
		pushup(x);
	}
	int query(int l,int r){return _query(1,l,r,1,n);}
	int _query(int x,int l,int r,int lx,int rx){
		if (l<=lx&&rx<=r) return mx[x];
		int mid=lx+rx>>1,ret=-inf;
		if (l<=mid) ret=max(ret,_query(lch[x],l,r,lx,mid));
		if (r>mid) ret=max(ret,_query(rch[x],l,r,mid+1,rx));
		return ret;
	}
}seg;
struct OP{
	int l,r;
	double p;
	OP(){}
	OP(int _l,int _r,double _p){l=_l,r=_r,p=_p;}
	friend bool operator <(OP x,OP y)
	{return x.l==y.l?x.r>y.r:x.l<y.l;}
}op[MAXN];
struct xxx{
	int y,next;
}a[MAXN*2];
int h[MAXN],fa[MAXN];
double ans,mx0;
int build(int n);
int add(int x,int y);
int dfs(int x);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&q);
	mx0=0;
	for (int i=1;i<=n;++i){
		scanf("%lf",w+i);
		if (w[i]-mx0>0) mx0=w[i];
	}
	op[++tot]=OP(1,n,0);
	seg.build();
	for (int i=1;i<=q;++i){
		++tot;
		scanf("%d%d%lf",&op[tot].l,&op[tot].r,&op[tot].p);
	}
	sort(op+2,op+1+tot);
	build(tot);
	dfs(1);
	ans=mx0*f[1][0];
	for (int i=1;i<=q;++i)
		ans+=(f[1][i]-f[1][i-1])*(mx0+i);
	printf("%.10lf\n",ans);
}

int build(int n){
	int father=1;
	memset(h,-1,sizeof(h));
	mx[1]=seg.query(op[1].l,op[1].r);
	for (int i=2;i<=n;++i){
		while (!(op[father].l<=op[i].l&&op[i].r<=op[father].r)) father=fa[father];
		fa[i]=father;
		add(father,i);
		mx[i]=seg.query(op[i].l,op[i].r);
		father=i;
	}
}

int add(int x,int y){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int x){
	int u,son=0,tmp;
	double pick,npick;
	for (int i=h[x];i!=-1;i=a[i].next){
		dfs(a[i].y);
		++son;
	}
	if (!son){
		f[x][0]=1-op[x].p;
		for (int i=1;i<=q;++i) f[x][i]=1;
		return 0;
	}
	for (int j=0;j<=q;++j){
		pick=op[x].p; npick=1.0-op[x].p;
		for (int i=h[x];i!=-1;i=a[i].next){
			u=a[i].y;
			tmp=mx[x]-mx[u]+j;
			if (0<=tmp&&tmp<=q) npick*=f[u][tmp];
			if (0<=tmp-1&&tmp-1<=q) pick*=f[u][tmp-1];
		}
		if (!j) f[x][j]=npick;
		else f[x][j]=pick+npick;
	}
}
