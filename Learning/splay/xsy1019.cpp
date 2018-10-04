#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010*2;
struct xxx{
	int y,next;
}a[MAXN];
int w[MAXN],lis[MAXN],dfn[MAXN],ed[MAXN],num[MAXN],h[MAXN];
int n,m,tot1,t;
struct Splay{
	int ch[MAXN][2],fa[MAXN],cnt[MAXN],sz[MAXN];
	ll sum[MAXN],tag[MAXN],val[MAXN];
	int tot,rt;
	int pushup(int x){
		sz[x]=1; sum[x]=val[x];
		int lch=ch[x][0],rch=ch[x][1];
		if (lch){
			sz[x]+=sz[lch],sum[x]+=sum[lch];
		}
		if (rch){
			sz[x]+=sz[rch],sum[x]+=sum[rch];
		}
	}
	int pushdown1(int x){
		if (!tag[x]) return 0;
		int lch=ch[x][0],rch=ch[x][1];
		if (lch){
			tag[lch]+=tag[x]; sum[lch]+=(ll)tag[x]*sz[lch];
			val[lch]+=tag[x];
		}
		if (rch){
			tag[rch]+=tag[x]; sum[rch]+=(ll)tag[x]*sz[rch];
			val[rch]+=tag[x];
		}
		tag[x]=0;
		pushup(x);
	}
	int pushdown(int x){
		if (!isroot(x)) pushdown(fa[x]);
		pushdown1(x);
	}
	int build(int l,int r){rt=_build(l,r);tot=r;}
	int _build(int l,int r){
		if (l>r) return 0;
		int mid=l+r>>1;
		val[mid]=w[lis[mid]];
		sum[mid]=w[lis[mid]];
		ch[mid][0]=_build(l,mid-1);
		ch[mid][1]=_build(mid+1,r);
		if (ch[mid][0]) fa[ch[mid][0]]=mid;
		if (ch[mid][1]) fa[ch[mid][1]]=mid;
		pushup(mid);
		return mid;
	}
	int which(int x){return ch[fa[x]][1]==x;}
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int rotate(int x){
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; 
		if (ch[x][dir^1]) 
			fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
		pushup(f); pushup(x);
	}
	int splay(int x,int top){
		pushdown(x);
		for (int f=fa[x];fa[x]!=top;f=fa[x]){
			if (fa[f]!=top)
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
		if (!top) rt=x;
	}
	int get_pre(int x){
		splay(x,0);
		int ret=ch[x][0];
		while (ch[ret][1]) ret=ch[ret][1];
		return ret;
	}
	int get_nxt(int x){
		splay(x,0);
		int ret=ch[x][1];
		while (ch[ret][0]) ret=ch[ret][0];
		return ret;
	}
	int get_seg(int l,int r){
		l=get_pre(l); 
		r=get_nxt(r);
		splay(l,0);
		splay(r,l);
		int ret=ch[rt][1];
		return ch[ret][0];
	}
	ll query(int x){
		int segrt=get_seg(dfn[x],ed[x]);
		return sum[segrt]/2;
	}
	int update(int x,int delta){
		int segrt=get_seg(dfn[x],ed[x]);
		sum[segrt]+=delta*sz[segrt];
		val[segrt]+=delta;
		tag[segrt]+=delta;
		splay(segrt,0);
	}
	int change(int x,int y){
		int segrt=get_seg(dfn[x],ed[x]);
		if (!isroot(segrt)) ch[fa[segrt]][which(segrt)]=0;
		fa[segrt]=0;
		int pre=get_pre(ed[y]);
		splay(pre,0);
		splay(ed[y],pre);
		fa[segrt]=ed[y];
		ch[ed[y]][0]=segrt;
	}
}splay;
int add(int x,int y);
int dfs(int fa,int x);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%d",w+i);
	int x,y;
	memset(h,-1,sizeof(h));
	tot1=0;
	for (int i=1;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	t=1;
	dfs(0,1);
	splay.build(1,t+1);
	int op;
	for (int i=1;i<=m;++i){
		scanf("%d",&op);
		if (op==1){
			scanf("%d",&x);
			printf("%lld\n",splay.query(x));
		}
		else if (op==2){
			scanf("%d%d",&x,&y);
			splay.update(x,y);
		}
		else{
			scanf("%d%d",&x,&y);
			splay.change(x,y);
		}
	}
}

int add(int x,int y){
	a[++tot1].y=y; a[tot1].next=h[x]; h[x]=tot1;
}

int dfs(int fa,int x){
	int u;
	dfn[x]=++t; lis[t]=x; num[t]=1;
	for (int i=h[x];i!=-1;i=a[i].next){
		if (a[i].y==fa) continue;
		dfs(x,a[i].y);
	}
	ed[x]=t;
	ed[x]=++t; lis[t]=x; num[t]=1;
}
