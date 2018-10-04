#include<iostream>
#include<cstring>
#include<cstdio>
#define inf 1000000001//2147483647
using namespace std;
const int MAXN=1e5+10;
int w[MAXN*2];
int n,m;
int abs1(int x){return x<0?-x:x;}
struct Splay{
	int ch[MAXN*2][2],fa[MAXN*2],mx[MAXN*2],mn[MAXN*2],val[MAXN*2],sz[MAXN*2];
	int lnum[MAXN*2],rnum[MAXN*2],cha[MAXN*2];//lnum&rnum=num of node
	int tot,rt;
	int which(int x){return ch[fa[x]][1]==x;}
	int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int newnode(int delta){
		ch[++tot][0]=ch[tot][1]=0; sz[tot]=1;
		val[tot]=delta; mx[tot]=delta; mn[tot]=delta;
		lnum[tot]=tot; rnum[tot]=tot; cha[tot]=inf;
		return tot;
	}
	int pushup(int x){
		sz[x]=1; mx[x]=val[x]; mn[x]=val[x];
		lnum[x]=rnum[x]=val[x]; cha[x]=inf;
		int lch=ch[x][0],rch=ch[x][1];
		if (lch){
			lnum[x]=lnum[lch];
			sz[x]+=sz[lch],mx[x]=max(mx[x],mx[lch]);
			mn[x]=min(mn[x],mn[lch]);
			cha[x]=min(cha[x],min(cha[lch],abs1(val[x]-rnum[lch])));
		}
		if (rch){
			rnum[x]=rnum[rch];
			sz[x]+=sz[rch],mx[x]=max(mx[x],mx[rch]);
			mn[x]=min(mn[x],mn[rch]);
			cha[x]=min(cha[x],min(cha[rch],abs1(val[x]-lnum[rch])));
		}
	}
	int build(int l,int r){rt=_build(l,r);tot=r;}
	int _build(int l,int r){
		if (l>r) return 0;
		int mid=l+r>>1;
		val[mid]=w[mid];
		ch[mid][0]=_build(l,mid-1);
		ch[mid][1]=_build(mid+1,r);
		if (ch[mid][0]) fa[ch[mid][0]]=mid;
		if (ch[mid][1]) fa[ch[mid][1]]=mid;
		pushup(mid);
		return mid;
	}
	int insert(int pos,int delta){
		rt=_insert(rt,pos,delta);
		splay(rt,0);
	}
	int _insert(int &x,int pos,int delta){
		if (!x){
			x=newnode(delta);
			return x;
		}
		int dir=pos>x;
		int v=_insert(ch[x][dir],pos,delta);
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
	int get_kth(int k){return _get_kth(rt,k);}
	int _get_kth(int x,int k){
		if (sz[ch[x][0]]+1==k) return x;
		if (k<sz[ch[x][0]]+1) return _get_kth(ch[x][0],k);
		return _get_kth(ch[x][1],k-sz[ch[x][0]]-1);
	}
	int del(int x){
		splay(x,0);
		if (!ch[x][0]&&!ch[x][1]){rt=0; return 0;}
		if (!ch[x][0]||!ch[x][1]){
			rt=ch[x][0]+ch[x][1];
			fa[rt]=0;
			return 0;
		}
		int pre=get_pre(x);
		fa[ch[x][0]]=0;
		splay(pre,0);
		ch[pre][1]=ch[x][1]; fa[ch[x][1]]=pre;
	}
	int Query(int l,int r,int op){//mx==1 mn==0
		l=get_kth(l-1); r=get_kth(r+1);
		splay(l,0);
		splay(r,l);
		int tmp=ch[rt][1];
		tmp=ch[tmp][0];
		return op?mx[tmp]-mn[tmp]:cha[tmp];
	}
	int Merge(int x,int delta){
		x=get_kth(x);
		int y=get_nxt(x);
		del(x); 
		val[y]=delta;
		splay(y,0);
	}
	int Insert(int x,int delta){
		x=get_kth(x);
		int y=get_nxt(x);
		splay(x,0);
		splay(y,x);
		ch[y][0]=newnode(delta);
		fa[ch[y][0]]=y;
		splay(ch[y][0],0);
	}
}splay;

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int x,y;
	scanf("%d%d",&n,&m);
	for (int i=2;i<=n+1;++i){
		scanf("%d",w+i);
	}
	w[1]=0; w[n+2]=0;
	splay.build(1,n+2);
	char op[10];
	for (int i=1;i<=m;++i){
		scanf("%s",op);
		scanf("%d%d",&x,&y);
		if (op[0]=='m'&&op[1]=='e'){
			splay.Merge(x+1,y);
		}
		else if (op[0]=='m'&&op[1]=='a'){
			printf("%d\n",splay.Query(x+1,y+1,1));
		}
		else if (op[0]=='m'&&op[1]=='i'){
			printf("%d\n",splay.Query(x+1,y+1,0));
		}
		else{
			splay.Insert(x+1,y);
		}
	}
}
