#include<iostream>
#include<cstdio>
#include<cstring>
#define alpha 0.75
using namespace std;
const int MAXN=(1e5+10)*5;
int flag,rt,check;
int pos[MAXN];
double num[MAXN];
struct Pr
{
	int l,r;
	friend bool operator <(Pr x,Pr y)
	{return num[x.l]==num[y.l]?num[x.r]<num[y.r]:num[x.l]<num[y.l];}
	friend bool operator ==(Pr x,Pr y)
	{return (num[x.l]==num[y.l])&&(num[x.r]==num[y.r]);}
};
struct sctree
{
	int lch[MAXN],rch[MAXN],a[MAXN];
	int sz[MAXN],sum[MAXN];
	Pr val[MAXN];
	int tot;
	int pushup(int x)
	{
		sz[x]=sz[lch[x]]+sz[rch[x]]+1;
	}
	int newnode(double v1,Pr v2)
	{
		lch[++tot]=rch[tot]=0;
		val[tot]=v2;
		num[tot]=v1;
		sz[tot]=1;
		return tot;
	}
	int dfs(int x)
	{
		if (!x) return 0;
		dfs(lch[x]);
		a[++a[0]]=x;
		dfs(rch[x]);
	}
	int rebuild(int &x,double lv,double rv)
	{
		++check;
		a[0]=0;
		dfs(x);
		build(x,1,a[0],lv,rv);
	}
	int build(int &x,int l,int r,double lv,double rv)
	{
		if (l>r) return x=0;
		int mid=l+r>>1;
		double midv=(lv+rv)/2.0;
		x=a[mid]; num[x]=midv;
		build(lch[x],l,mid-1,lv,midv);
		build(rch[x],mid+1,r,midv,rv);
		pushup(x);
		return x;
	}
	int insert(int x,int l,int r) {pos[x]=_insert(rt,0,1,(Pr){pos[l],pos[r]});}
	int _insert(int &x,double lv,double rv,Pr v2)
	{
		double midv=(lv+rv)/2.0;
		if (!x)
		{x=newnode(midv,v2);return x;}
		if (val[x]==v2) return x;
		int ret;
		if (v2<val[x])
			ret=_insert(lch[x],lv,midv,v2);
		else
			ret=_insert(rch[x],midv,rv,v2);
		pushup(x);
		int mx=max(sz[lch[x]],sz[rch[x]]);
		if (mx<sz[x]*alpha)
		{
			if (flag)
			{
				if (flag==lch[x]) rebuild(lch[x],lv,midv);
				else rebuild(rch[x],midv,rv);
				flag=0;
			}
		}
		else flag=x;
		pushup(x);
		return ret;
	}
}sct;
struct sgtree
{
	int mx[MAXN];
	int tot;
	int pushup(int x)
	{
		int left=mx[x*2],right=mx[x*2+1];
		mx[x]=num[pos[left]]>=num[pos[right]]?left:right;
	}
	int update(int x,int d,int lx,int rx)
	{
		if (lx==rx)
		{mx[x]=lx; return 0;}
		int mid=lx+rx>>1;
		if (d<=mid) update(x*2,d,lx,mid);
		else update(x*2+1,d,mid+1,rx);
		pushup(x);
	}
	int query(int x,int l,int r,int lx,int rx)
	{
		if (l<=lx&&rx<=r)
			return mx[x];
		int mid=lx+rx>>1;
		int ret=0,tmp;
		if (l<=mid) 
		{
			tmp=query(x*2,l,r,lx,mid);
			if (num[pos[tmp]]>num[pos[ret]]) ret=tmp;
		}
		if (r>mid)
		{
			tmp=query(x*2+1,l,r,mid+1,rx);
			if (num[pos[tmp]]>num[pos[ret]]) ret=tmp;
		}
		return ret;
	}
}seg;
int n,m;

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);

	int l,r,x;
	char op[2];
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) pos[i]=1,num[i]=0;
	sct._insert(rt,0,1,(Pr){0,0});
	for (int i=1;i<=n;++i) seg.update(1,i,1,n);
	flag=0;
	for (int i=1;i<=m;++i)
	{
		scanf("%s",op);
		if (op[0]=='C')
		{
			scanf("%d%d%d\n",&l,&r,&x);
			sct.insert(x,l,r);
			if (flag) 
				sct.rebuild(rt,0,1);
			flag=0;
			seg.update(1,x,1,n);
		}
		else
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",seg.query(1,l,r,1,n));
		}
	}
}
