#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define TOP 20
using namespace std;
const int MAXN=8*(1e4)+10;
struct xxx{
	int y,next;
}a[MAXN*2];
int val[MAXN],fa[MAXN],f[MAXN][TOP+1],dep[MAXN],h[MAXN],num[MAXN];
int bsz[MAXN],loc[MAXN];
map<int,int>id;
int n,m,t,tc,ans,tot1,mx;
struct segtree{/*{{{*/
	int lch[MAXN*20*20],rch[MAXN*20*20],sz[MAXN*20*20],rt[MAXN];
	int tot;
	int newnode(int x){
		lch[++tot]=lch[x];rch[tot]=rch[x];sz[tot]=sz[x];
		return tot;
	}
	int insert(int x,int y,int delta){_insert(rt[y],rt[x],delta,0,mx);}
	int _insert(int pre,int &x,int d,int lx,int rx){
		x=newnode(pre);
		++sz[x];
		if (lx==rx) return 0;
		int mid=lx+rx>>1;
		if (d<=mid) _insert(lch[pre],lch[x],d,lx,mid);
		else _insert(rch[pre],rch[x],d,mid+1,rx);
	}
	int query(int x,int y,int lca,int lcaf,int k)
	{return _query(rt[x],rt[y],rt[lca],rt[lcaf],0,mx,k);}
	int _query(int x,int y,int lca,int lcaf,int lx,int rx,int k){
		if (lx==rx) return lx;
		int mid=lx+rx>>1;
		int size=sz[lch[x]]+sz[lch[y]]-sz[lch[lca]]-sz[lch[lcaf]];
		if (k<=size) return _query(lch[x],lch[y],lch[lca],lch[lcaf],lx,mid,k);
		return _query(rch[x],rch[y],rch[lca],rch[lcaf],mid+1,rx,k-size);
	}
	int init(){
		tot=0;
		for (int i=1;i<=n;++i) rt[i]=0;
	}
}seg;/*}}}*/
int dfs(int fa,int x,int d);
int merge(int x,int y);
int get_f(int x);
int get_lca(int x,int y);
int prework();
bool cmp(int x,int y) {return val[x]<val[y];}
int read();

int main(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);

	char op[5];
	int x,y,k,lca;
	tc=read();
	n=read();m=read();t=read();
	memset(h,-1,sizeof(h));
	seg.init();
	ans=0; mx=0;
	for (int i=1;i<=n;++i){
		val[i]=read();
		fa[i]=i; bsz[i]=1; dep[i]=1; loc[i]=i;
	}
	prework();
	for (int i=1;i<=n;++i)
		seg.insert(i,i,val[i]);
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		merge(x,y);
	}
	for (int i=1;i<=t;++i){
		scanf("%s",op);
		if (op[0]=='L'){
			x=read(); y=read();
			x^=ans;y^=ans;
			merge(x,y);
		}
		else{
			x=read(); y=read(); k=read();
			x^=ans; y^=ans; k^=ans;
			lca=get_lca(x,y);
			ans=seg.query(x,y,lca,f[lca][0],k);
			ans=num[ans];
			printf("%d\n",ans);
		}
	}
}

int add(int x,int y){
	a[++tot1].y=y; a[tot1].next=h[x]; h[x]=tot1;
}

int get_f(int x){
	if (fa[x]!=x) fa[x]=get_f(fa[x]);
	return fa[x];
}

int dfs(int fa,int x,int d){
	int u;
	dep[x]=d;f[x][0]=fa;
	for (int i=1;i<=TOP;++i) f[x][i]=f[f[x][i-1]][i-1];
	seg.insert(x,fa,val[x]);
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1);
	}
}

int get_lca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

int merge(int x,int y){
	int fx=get_f(x),fy=get_f(y);
	add(x,y); add(y,x);
	if (bsz[fx]>bsz[fy]) 
		swap(fx,fy),swap(x,y);
	fa[x]=y;
	bsz[fy]+=bsz[fx];
	dfs(y,x,dep[y]+1);
}

int prework(){
	sort(loc+1,loc+1+n,cmp);
	id[val[loc[1]]]=1;
	int cnt=1;
	for (int i=2;i<=n;id[val[loc[i]]]=cnt,++i)
		if (val[loc[i]]!=val[loc[i-1]]) ++cnt;
	for (int i=1;i<=n;++i) num[id[val[i]]]=val[i],val[i]=id[val[i]];
	mx=cnt;
}

int read(){
	int ret=0,t=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	if (ch=='-') t=-1;
	while ('0'<=ch&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*t;
}
