#include<iostream>
#include<cstdio>
#include<cstring>
#define Hs 233
#define ull unsigned long long
using namespace std;
const int MAXN=2*(1e5)+10;
int p[MAXN],mnp[MAXN];
int h[MAXN],pre[MAXN],son[MAXN],sz[MAXN],mx[MAXN],dep[MAXN],top[MAXN];
bool vis[MAXN];
int chr[MAXN];
int st[MAXN],lis[MAXN];
ull pw[MAXN];
int n,m,dfn_t,tot;
struct xxx{
	int y,next;
	char ch;
}a[MAXN*2];
struct segtree{
	int lch[MAXN*4],rch[MAXN*4];
	ull tag[MAXN*4],val[MAXN*4][2];
	int tot;
	int build(){_build(++tot,1,n);}
	int _build(int x,int l,int r){
		tag[x]=0; lch[x]=0; rch[x]=0;
		if (l==r) return 0;
		int mid=l+r>>1;
		lch[x]=++tot; _build(lch[x],l,mid);
		rch[x]=++tot; _build(rch[x],mid+1,r);
	}
	int pushup(int x,int l,int r){
		int mid=l+r>>1;
		val[x][0]=val[lch[x]][0]+pw[mid-l+1]*val[rch[x]][0];
		val[x][1]=pw[r-mid]*val[lch[x]][1]+val[rch[x]][1];
	}
	int update(int d,ull delta){_update(1,d,1,n,delta);}
	int _update(int x,int d,int lx,int rx,ull delta){
		if (lx==rx){
			val[x][0]=val[x][1]=delta;
			return 0;
		}
		int mid=lx+rx>>1;
		if (d<=mid) _update(lch[x],d,lx,mid,delta);
		else _update(rch[x],d,mid+1,rx,delta);
		pushup(x,lx,rx);
	}
	ull query(int l,int r,int op){return _query(1,l,r,1,n,op);}
	ull _query(int x,int l,int r,int lx,int rx,int op){
		if (l<=lx&&rx<=r) return val[x][op];
		int mid=lx+rx>>1;
		if (r<=mid) return _query(lch[x],l,r,lx,mid,op);
		if (l>mid) return _query(rch[x],l,r,mid+1,rx,op);

		ull retl=_query(lch[x],l,mid,lx,mid,op);
		ull retr=_query(rch[x],mid+1,r,mid+1,rx,op);
		if (!op) return retl+pw[mid-l+1]*retr;
		return pw[r-mid]*retl+retr;
	}
}seg;
int add(int x,int y,char ch);
int dfs(int fa,int x,int d);
int dfs1(int fa,int x);
int prework();
ull get_hsl(int x,int lca,int y,int ed);
ull get_hsr(int x,int lca,int y,int st);
ull jump(int x,int y,int op);
int go(int x,int step);
int query(int x,int y);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int x,y;
	char s[10];
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		scanf("%d%d%s",&x,&y,s);
		add(x,y,s[0]); add(y,x,s[0]);
	}
	prework();
	dfs(0,1,1);
	top[1]=1;
	dfs1(0,1);
	scanf("%d",&m);
	int op;
	for (int i=1;i<=m;++i){
		scanf("%d",&op);
		if (op==1){
			scanf("%d%d",&x,&y);
			query(x,y);
		}
		else{
			scanf("%d%d%s",&x,&y,s);
			if (pre[x]==y) 
				seg.update(st[x],s[0]-'a');
			else 
				seg.update(st[y],s[0]-'a');
		}
	}
}

int add(int x,int y,char ch){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].ch=ch;
}

int dfs(int fa,int x,int d){
	int u;
	dep[x]=d; pre[x]=fa;
	sz[x]=1; mx[x]=0;
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==fa) continue;
		chr[u]=a[i].ch-'a';
		dfs(x,u,d+1);
		sz[x]+=sz[u];
		if (sz[son[x]]<sz[u]) son[x]=u;
	}
}

int prework(){
	pw[0]=1;
	for (int i=1;i<=n;++i) pw[i]=pw[i-1]*Hs,vis[i]=false;
	int cnt=0;
	for (int i=2;i<=n;++i){
		if (!vis[i])
			p[++cnt]=i,mnp[i]=i;
		for (int j=1;j<=cnt&&i*p[j]<=n;++j){
			vis[i*p[j]]=true;
			mnp[i*p[j]]=p[j];
			if (i%p[j]==0) break;
		}
	}
	seg.build();
}

int dfs1(int fa,int x){
	st[x]=++dfn_t; lis[dfn_t]=x;
	seg.update(dfn_t,chr[x]);
	int u;
	if (son[x]){
		top[son[x]]=top[x]; dfs1(x,son[x]);
	}
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==son[x]||u==fa) continue;
		top[u]=u;
		dfs1(x,u);
	}
}

int get_lca(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) y=pre[top[y]];
		else x=pre[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}

int query(int x,int y){
	int lca=get_lca(x,y),len=dep[x]+dep[y]-dep[lca]*2;
	int ret=1,tmp=len,mn,rec,mx;
	while (tmp!=1){
		mn=mnp[tmp];
		rec=1;mx=1;
		while (tmp>1&&mnp[tmp]==mn){
			rec*=mn;
			tmp/=mn;
			if (get_hsl(x,lca,y,len-len/rec)==get_hsr(x,lca,y,len/rec))
				mx=rec;
		}
		ret*=mx;
	}
	printf("%d\n",len/ret);
}

int go(int x,int step){
	while (step>=dep[x]-dep[top[x]]+1) step-=dep[x]-dep[top[x]]+1,x=pre[top[x]];
	return lis[st[x]-step];
}

ull get_hsl(int x,int lca,int y,int ed){
	int tmp,dis=dep[x]+dep[y]-dep[lca]*2;
	if (dep[x]-dep[lca]>=ed)
		tmp=go(x,ed);
	else 
		tmp=go(y,dis-ed);
	int tmplca=get_lca(tmp,x);
	ull ret=jump(x,tmplca,0);
	ret=ret*pw[dep[tmp]-dep[tmplca]]+jump(tmp,tmplca,1);
	return ret;
}

ull get_hsr(int x,int lca,int y,int st){
	int tmp,dis=dep[x]+dep[y]-dep[lca]*2;
	if (dep[x]-dep[lca]<=st)
		tmp=go(y,dis-st);
	else
		tmp=go(x,st);
	ull ret=0;
	int tmplca=get_lca(tmp,y);
	ret=jump(tmp,tmplca,0);
	ret=ret*pw[dep[y]-dep[tmplca]]+jump(y,tmplca,1);//!!
	return ret;
}

ull jump(int x,int y,int op){
	ull ret=0,cnt=0;
	while (top[x]!=top[y]){
		if (!op) ret=ret*pw[st[x]-st[top[x]]+1]+seg.query(st[top[x]],st[x],op);
		else ret=seg.query(st[top[x]],st[x],op)*pw[cnt]+ret,cnt+=st[x]-st[top[x]]+1;
		x=pre[top[x]];
	}
	if (dep[x]>dep[y]){
		if (!op)
			ret=ret*pw[st[x]-st[y]]+seg.query(st[y]+1,st[x],op);
		else ret=seg.query(st[y]+1,st[x],op)*pw[cnt]+ret;
	}
	return ret;
}
