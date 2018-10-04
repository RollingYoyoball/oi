#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
struct xxx{
	int y,next;
}a[MAXN*2];
int h[MAXN],dfn[MAXN],ed[MAXN],lis[MAXN*2],w[MAXN],num[MAXN*2];
int n,m,tot,t;
struct Splay{
	int ch[MAXN*2][2],fa[MAXN*2],val[MAXN*2],sz[MAXN*2];
	ll sum[MAXN*2],tag[MAXN*2];
	int cnt[MAXN*2];//+1的数量
	int tot,rt;
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int which(int x){return ch[fa[x]][1]==x;}
	int pushup(int x){
		sz[x]=1; sum[x]=val[x]*num[x]; cnt[x]=num[x]==1?1:0;
		if (ch[x][0]) 
			sz[x]+=sz[ch[x][0]],sum[x]+=sum[ch[x][0]],cnt[x]+=cnt[ch[x][0]];
		if (ch[x][1]) 
			sz[x]+=sz[ch[x][1]],sum[x]+=sum[ch[x][1]],cnt[x]+=cnt[ch[x][1]];
	}
	int pushdown(int x){
		if (!tag[x]) return 0;
		if (ch[x][0]){
			val[ch[x][0]]+=tag[x],tag[ch[x][0]]+=tag[x];
			sum[ch[x][0]]+=tag[x]*(cnt[ch[x][0]]*2-sz[ch[x][0]]);
		}
		if (ch[x][1]){
			val[ch[x][1]]+=tag[x],tag[ch[x][1]]+=tag[x];
			sum[ch[x][1]]+=tag[x]*(cnt[ch[x][1]]*2-sz[ch[x][1]]);
		}
		tag[x]=0;
		pushup(x);
	}
	int Pushdown(int x){
		if (!isroot(x)) Pushdown(fa[x]);
		pushdown(x);
	}
	int newnode(int delta,int delta1){
		ch[++tot][0]=ch[tot][1]=0;sz[tot]=1;val[tot]=delta;
		cnt[tot]=delta1==1; sum[tot]=delta*delta1;
		return tot;
	}
	int insert(int delta){
		rt=_insert(rt,delta);
		splay(rt,0);
	}
	int _insert(int &x,int delta){
		if (!x){
			x=newnode(w[lis[delta]],num[delta]);
			return x;
		}
		pushdown(x);
		int dir=delta>x;
		int v=_insert(ch[x][dir],delta);
		fa[ch[x][dir]]=x;
		pushup(x);
		return v;
	}
	int rotate(int x){
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
		pushup(f); pushup(x);
	}
	int splay(int x,int top){
		Pushdown(x);
		for (int f=fa[x];fa[x]!=top;f=fa[x]){
			if (fa[f]!=top)
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
		if (!top) rt=x;
	}
	int get_rk(int x){
		splay(x,0);
		return sz[ch[x][0]]+1;
	}
	int get_kth(int k) {return _get_kth(rt,k);}
	int _get_kth(int x,int k){
		pushdown(x);
		if (sz[ch[x][0]]+1==k) return x;
		if (k<=sz[ch[x][0]]+1) return _get_kth(ch[x][0],k);
		return _get_kth(ch[x][1],k-sz[ch[x][0]]-1);
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
		int lch=ch[rt][1],tmp=ch[lch][0];
		return tmp;
	}
	int split(int l,int r){
		int tmprt=get_seg(l,r);
		ch[fa[tmprt]][which(tmprt)]=0; fa[tmprt]=0;
		return tmprt;
	}
	int change(int x,int y){
		int l=get_pre(dfn[x]),r=get_nxt(ed[x]);
		int tmprt=split(dfn[x],ed[x]),pre;
		pre=get_pre(ed[y]);
		splay(pre,0);
		splay(ed[y],pre);
		fa[tmprt]=ed[y];
		ch[ed[y]][0]=tmprt;
	}
	int update(int x,int delta){
		int tmprt=get_seg(dfn[x],ed[x]);
		val[tmprt]+=delta;
		tag[tmprt]+=delta;
		sum[tmprt]+=delta*(cnt[tmprt]*2-sz[tmprt]);
	}
	ll query(int x){
		x=dfn[x];
		splay(x,0);
		return (ll)val[x]+sum[ch[x][0]];
	}
	int debug(){
		for (int i=1;i<=t+2;++i)
			printf("%d ",lis[get_kth(i)]);
		printf("\n");
	}
}splay;
int dfs(int x);
int add(int x,int y);
int read();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int x,y;
	n=read();
	memset(h,-1,sizeof(h));
	for (int i=2;i<=n;++i){
		x=read();
		add(x,i);
	}
	t=1;
	for (int i=1;i<=n;++i)
		w[i]=read();
	dfs(1);
	for (int i=1;i<=t+1;++i)
		splay.insert(i);
	char op[5];
	m=read();
	for (int i=1;i<=m;++i){
		scanf("%s",op);
		if (op[0]=='Q'){
			x=read();
			printf("%lld\n",splay.query(x));
		}
		else if (op[0]=='C'){
			x=read(); y=read();//fa[x]=y;
			splay.change(x,y);
		}
		else{
			x=read(); y=read();
			splay.update(x,y);//add y to x
		}
	}
}

int add(int x,int y){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int x){
	dfn[x]=++t; lis[t]=x; num[t]=1;
	for (int i=h[x];i!=-1;i=a[i].next){
		dfs(a[i].y);
	}
	ed[x]=++t; lis[t]=x; num[t]=-1;
}

int read(){
	int ret=0,t=1; char ch=getchar(),pre;
	while (ch<'0'||ch>'9') pre=ch,ch=getchar();
	if (pre=='-') t=-1; 
	while ('0'<=ch&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*t;
}
