#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=300010;
int id[MAXN];
int n,m;
int debug();
struct Splay{
	int ch[MAXN][2],val[MAXN],fa[MAXN],sz[MAXN],loc[MAXN];
	int tot,rt;
	int newnode(int pos,int delta){
		ch[++tot][0]=ch[tot][1]=0; val[tot]=delta; 
		loc[tot]=pos; sz[tot]=1;
		return tot;
	}
	int pushup(int x){
		sz[x]=1;
		if (ch[x][0]) sz[x]+=sz[ch[x][0]];
		if (ch[x][1]) sz[x]+=sz[ch[x][1]];
	}
	int insert(int pos,int delta){
		rt=_insert(rt,pos,delta);
		splay(rt);
		return rt;
	}
	int _insert(int &x,int pos,int delta){
		if (!x){
			x=newnode(pos,delta);
			return x;
		}
		int dir=pos>loc[x];
		int v=_insert(ch[x][dir],pos,delta);
		fa[ch[x][dir]]=x;
		pushup(x);
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
		pushup(f); pushup(x);
	}
	int splay(int x){
		for (int f=fa[x];!isroot(x);f=fa[x]){
			if (!isroot(f))
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
		rt=x;
	}
	int find_pos(int x){
		x=id[x];
		splay(x);
		return sz[ch[x][0]];
	}
	int find_kth(int x) {return val[_find_kth(rt,x)];}
	int _find_kth(int x,int k){
		if (sz[ch[x][0]]+1==k) return x;
		if (k<sz[ch[x][0]]+1) return _find_kth(ch[x][0],k);
		return _find_kth(ch[x][1],k-(sz[ch[x][0]]+1));
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
		pushup(pre);
	}
	int Insert(int x,int pos){
		int num=id[x];
		del(num);
		id[x]=insert(pos,x);
		splay(id[x]);
	}
	int Change(int x,int t){
		int num=id[x],another,pos=loc[num];
		splay(num);
		if (t==1) another=get_nxt(num);
		else another=get_pre(num);
		del(num);
		del(another);
		id[x]=insert(pos+t,x);
		id[val[another]]=insert(pos,val[another]);
	}
}splay;
int fir,lst;
bool check(int x,int t);

int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	char op[10];
	int x,t;
	scanf("%d%d",&n,&m);
	fir=1;lst=n;
	for (int i=1;i<=n;++i){
		scanf("%d",&x);
		id[x]=splay.insert(i,x);
	}
	for (int i=1;i<=m;++i){
		scanf("%s",op);
		if (op[0]=='Q'){
			scanf("%d",&x);
			printf("%d\n",splay.find_kth(x));
		}
		else if (op[0]=='A'){
			scanf("%d",&x);
			printf("%d\n",splay.find_pos(x));
		}
		else if (op[0]=='I'){
			scanf("%d%d",&x,&t);
			if (!t) continue;
			//if (!check(x,t)) continue;
			splay.Change(x,t);
		}
		else if (op[0]=='T'){
			scanf("%d",&x);
			splay.Insert(x,--fir);
		}
		else{
			scanf("%d",&x);
			splay.Insert(x,++lst);
		}
//		debug();
	}
}

int debug(){
	int tmp;
	for (int i=1;i<=n;++i){
		tmp=splay.find_kth(i);
		printf("%d ",tmp);
	}
	printf("\n");
}

bool check(int x,int t){
	x=id[x];
	splay.splay(x);
	if (t==1&&!splay.ch[x][1]) return false;
	if (t==-1&&!splay.ch[x][0]) return false;
	return true;
}
