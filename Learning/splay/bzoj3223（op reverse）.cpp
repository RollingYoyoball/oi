#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
int n,m;
struct Splay{
	int ch[MAXN][2],val[MAXN],rev[MAXN],fa[MAXN],sz[MAXN];
	int tot,rt;
	int which(int x){return ch[fa[x]][1]==x;}
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int newnode(int x){
		ch[++tot][0]=0; ch[tot][1]=0; val[tot]=x; sz[tot]=1;
		return tot;
	}
	int pushup(int x){
		sz[x]=1;
		if (ch[x][0]) sz[x]+=sz[ch[x][0]];
		if (ch[x][1]) sz[x]+=sz[ch[x][1]];
	}
	int insert(int delta){
		int v=_insert(rt,delta);
		splay(v,0);
		rt=v;
	}
	int _insert(int &x,int delta){
		if (!x){
			x=newnode(delta);
			return x;
		}
		int dir=delta>val[x];
		int v=_insert(ch[x][dir],delta);
		fa[ch[x][dir]]=x;
		pushup(x);
		return v;
	}
	int reverse(int x){
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	int pushdown(int x){
		if (!rev[x]) return 0;
		if (ch[x][0]) reverse(ch[x][0]);
		if (ch[x][1]) reverse(ch[x][1]);
		rev[x]=0;
		pushup(x);
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
		pushdown(x);
		for (int f=fa[x];fa[x]!=top;f=fa[x]){
			if (fa[f]!=top)
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
	}
	int get_kth(int k){return val[_get_kth(rt,k)];}
	int _get_kth(int x,int k){
		pushdown(x);
		if (sz[ch[x][0]]+1==k) return x;
		if (k<sz[ch[x][0]]+1) return _get_kth(ch[x][0],k);
		return _get_kth(ch[x][1],k-sz[ch[x][0]]-1);
	}
	int flip(int l,int r){
		l=_get_kth(rt,l-1);
		r=_get_kth(rt,r+1);
		splay(l,0);
		rt=l;
		splay(r,l);
		int lch=ch[rt][1],tmp=ch[lch][0];
		swap(ch[tmp][0],ch[tmp][1]);
		rev[tmp]^=1;
	}
}splay;

int main(){
	freopen("a.in","r",stdin);

	int l,r;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n+2;++i) 
		splay.insert(i);
	for (int i=1;i<=m;++i){
		scanf("%d%d",&l,&r);
		++l,++r;
		splay.flip(l,r);
	}
	for (int i=2;i<=n+1;++i)
		printf("%d ",splay.get_kth(i)-1);
}
