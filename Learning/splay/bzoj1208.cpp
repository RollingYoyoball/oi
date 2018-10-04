#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000
using namespace std;
const int MAXN=80010;
int n,m;
struct Splay{
	int ch[MAXN][2],val[MAXN],fa[MAXN],type[MAXN];
	int tot,rt;
	int newnode(int delta,int op){
		ch[++tot][0]=ch[tot][1];val[tot]=delta;type[tot]=op;
		return tot;
	}
	int insert(int delta,int op){
		int now=type[rt],epty=rt;
		rt=_insert(rt,delta,op);
		splay(rt);
		if (epty&&now!=op)
			return choose(rt);
		return 0;
	}
	int _insert(int &x,int delta,int op){
		if (!x){
			x=newnode(delta,op);
			return x;
		}
		int dir=delta>val[x];
		int v=_insert(ch[x][dir],delta,op);
		fa[ch[x][dir]]=x;
		return v;
	}
	int which(int x) {return ch[fa[x]][1]==x;}
	bool isroot(int x) {return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int rotate(int x){
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
	}
	int splay(int x){
		for (int f=fa[x];!isroot(x);f=fa[x]){
			if (!isroot(f))
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
		rt=x;
	}
	int get_pre(int x){
		int ret=ch[x][0];
		while (ch[ret][1]) ret=ch[ret][1];
		return ret;
	}
	int get_nxt(int x){
		int ret=ch[x][1];
		while (ch[ret][0]) ret=ch[ret][0];
		return ret;
	}
	int choose(int loc){
		int pre=get_pre(loc),nxt=get_nxt(loc);
		int preval,nxtval;
		if (pre) preval=val[loc]-val[pre];
		if (nxt) nxtval=val[nxt]-val[loc];
		if (!pre||(pre&&nxt&&preval>nxtval)){
			del(loc); del(nxt);
			return nxtval;
		}
		if (!nxt||(pre&&nxt&&preval<=nxtval)){
			del(loc); del(pre);
			return preval;
		}
	}
	int del(int x){
		splay(x);
		if (!ch[x][0]&&!ch[x][1]) {rt=0; return 0;}
		if (!ch[x][0]||!ch[x][1]){
			rt=ch[x][0]+ch[x][1];
			fa[rt]=0;
			return 0;
		}
		int pre=get_pre(x);
		fa[ch[x][0]]=0;
		splay(pre);
		ch[pre][1]=ch[x][1]; fa[ch[x][1]]=pre;
	}
}splay;
int ans;

int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,op;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%d%d",&op,&x);
		ans=(ans+splay.insert(x,op))%MOD;
	}
	printf("%d\n",ans);
}
