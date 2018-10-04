#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=4*(1e5)+10;
const long long inf=8223372036854775807;
struct dian{
	long long x,y;
	dian(){}
	dian(int x_,int y_){x=x_;y=y_;}
	friend long long operator *(dian x,dian y)
	{return 1LL*x.x*y.y-1LL*x.y*y.x;}
	friend dian operator -(dian x,dian y)
	{return dian(x.x-y.x,x.y-y.y);}
	friend bool operator <(dian x,dian y)
	{return x.x==y.x?x.y<y.y:x.x<y.x;}
}a[MAXN],s1[MAXN],s2[MAXN];
long long dot(dian x,dian y){return x.x*y.x+x.y*y.y;}
char s[10],op;
long long ans;
int n,m;
struct segtree{
	int lch[MAXN*4],rch[MAXN*4],cntup[MAXN*4],cntdw[MAXN*4];
	bool worked[MAXN*4];
	int tot;
	vector<dian> pt[MAXN*4],up[MAXN*4],dw[MAXN*4];
	int build(){_build(++tot,1,n);}
	int _build(int x,int l,int r){
		cntup[x]=cntdw[x]=0; worked[x]=false;
		if (l==r) return 0;
		int mid=l+r>>1;
		lch[x]=++tot; _build(lch[x],l,mid);
		rch[x]=++tot; _build(rch[x],mid+1,r);
	}
	int insert(int pos,dian delta){_insert(1,pos,1,n,delta);}
	int _insert(int x,int d,int lx,int rx,dian delta){
		pt[x].push_back(delta);
		worked[x]=false;
		if (lx==rx) return 0;
		int mid=lx+rx>>1;
		if (d<=mid) _insert(lch[x],d,lx,mid,delta);
		else _insert(rch[x],d,mid+1,rx,delta);
	}
	int calc(int x){
		int cnt=0,top1=0,top2=0;
		for (int i=0;i<pt[x].size();++i) a[++cnt]=pt[x][i];
		sort(a+1,a+1+cnt);
		for (int i=1;i<=cnt;++i){
			while (top1>1&&(s1[top1]-s1[top1-1])*(a[i]-s1[top1-1])>=0) --top1;
			s1[++top1]=a[i];
			while (top2>1&&(a[i]-s2[top2-1])*(s2[top2]-s2[top2-1])>=0) --top2;
			s2[++top2]=a[i];
		}
		up[x].push_back(dian(0,0));
		for (int i=1;i<=top1;++i) up[x].push_back(s1[i]);
		dw[x].push_back(dian(0,0));
		for (int i=1;i<=top2;++i) dw[x].push_back(s2[i]);
		worked[x]=true; cntup[x]=top1; cntdw[x]=top2;
	}
	long long query(int l,int r,dian q){return _query(1,l,r,1,n,q);}
	long long _query(int x,int l,int r,int lx,int rx,dian q){
		if (l<=lx&&rx<=r){
			if (!worked[x]) calc(x);	
			return get_ans(x,q);
		}
		int mid=lx+rx>>1;
		long long ret=-inf;
		if (l<=mid) ret=max(ret,_query(lch[x],l,r,lx,mid,q));
		if (r>mid) ret=max(ret,_query(rch[x],l,r,mid+1,rx,q));
		return ret;
	}
	long long get_ans(int x,dian q){
		long long ret=-inf;
		int l,r,ll,rr;
		if (q.y>=0){
			l=1,r=cntup[x];
			while (r-l>2){
				ll=(l*2+r)/3;
				rr=(l+r*2)/3;
				if (dot(up[x][ll],q)<dot(up[x][rr],q)) l=ll;
				else r=rr;
			}
			for (int i=l;i<=r;++i)
				ret=max(ret,dot(up[x][i],q));
		}
		else{
			l=1,r=cntdw[x];
			while (r-l>2){
				ll=(l*2+r)/3;
				rr=(l+r*2)/3;
				if (dot(dw[x][ll],q)<dot(dw[x][rr],q)) l=ll;
				else r=rr;
			}
			for (int i=l;i<=r;++i)
				ret=max(ret,dot(dw[x][i],q));
		}
		return ret;
	}
}seg;
inline int decode (int x,long long lastans) {
	return x ^ (lastans & 0x7fffffff);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d ",&n);
	scanf("%c\n",&op);
	int x,y,l,r,now=0;
	seg.build();
	ans=0;
	for (int i=1;i<=n;++i){
		scanf("%s",s);
		if (s[0]=='A'){
			scanf("%d%d",&x,&y);
			if (op!='E'){
				x=decode(x,ans); y=decode(y,ans);
			}
			seg.insert(++now,dian(x,y));
		}
		else{
			scanf("%d%d%d%d",&x,&y,&l,&r);
			if (op!='E'){
				x=decode(x,ans); y=decode(y,ans);
				l=decode(l,ans); r=decode(r,ans);
			}
			ans=seg.query(l,r,dian(x,y));
			printf("%lld\n",ans);
		}
	}
}
