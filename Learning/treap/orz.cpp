#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=500010;
int node[MAXN],mx[MAXN],pos[MAXN];
double a[MAXN];
int tag,rt,check;
int tot,cnt,m,n;
struct data
{
	int l,r;
	friend bool operator>(data x,data y)//x>y
	{
		if (a[x.l]>a[y.l]) return true;
		if (a[x.l]==a[y.l]&&a[x.r]>a[y.r]) return true;
		return false;
	}
	friend bool operator==(data x,data y)
	{
		if (a[x.l]!=a[y.l]||a[x.r]!=a[y.r]) return false;
		return true;
	}
};
struct sctree
{
	int lch[MAXN],rch[MAXN],size[MAXN];
	data v[MAXN];
	int build(int &x,int l,int r,double vl,double vr)
	{
		if (l>r) {x=0; return 0;}
		double vmid=(vl+vr)/2.0;
		int mid=(l+r)/2;
		x=node[mid]; 
		a[x]=vmid;
		build(lch[x],l,mid-1,vl,vmid);
		build(rch[x],mid+1,r,vmid,vr);
		size[x]=size[lch[x]]+size[rch[x]]+1;
	}
	int dfs(int x)
	{
		if (x==0) return 0;
		dfs(lch[x]);
		node[++tot]=x;
		dfs(rch[x]);
	}
	int rebuild(int &x,double vl,double vr)
	{
		++check;
		tot=0;
		dfs(x);
		build(x,1,tot,vl,vr);
	}
	int insert(int &x,double vl,double vr,data val)
	{
		double vmid=(vl+vr)/2.0;
		if (x==0) 
		{
			x=++cnt;
			a[x]=vmid;
			size[x]=1;
			v[x]=val;
			return x;
		}
		int p;
		if (val==v[x]) return x;
		++size[x];
		if (val>v[x]) p=insert(rch[x],vmid,vr,val);
		else p=insert(lch[x],vl,vmid,val);
		if (size[x]*0.75>max(size[lch[x]],size[rch[x]]))
		{
			if (tag)
			{
				if (tag==lch[x]) rebuild(lch[x],vl,vmid);
				else rebuild(rch[x],vmid,vr);
				tag=0;
			}
		}
		else tag=x;
		return p;
	}
}sctree;
int modify(int x,int l,int r,int v);
int query(int x,int l,int r,int xl,int xr);

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a1.out","w",stdout);
	
	int l,r,now;
	char ch;
	rt=0;
	scanf("%d%d\n",&n,&m);
	sctree.insert(rt,0,1,(data){0,0});
	for (int i=1;i<=n;++i) pos[i]=1;
	for (int i=1;i<=n;++i) modify(1,1,n,i);
	tag=0;
	for (int i=1;i<=m;++i)
	{
		scanf("%c ",&ch);
		if (ch=='C') 
		{
			scanf("%d%d%d\n",&l,&r,&now);
			pos[now]=sctree.insert(rt,0,1,(data){pos[l],pos[r]});
			if (tag!=0) sctree.rebuild(rt,0,1);
			tag=0; 
			modify(1,1,n,now);
		}
		else
		{
			scanf("%d%d\n",&l,&r);
		//	printf("%d\n",query(1,l,r,1,n));
		}
	}
	printf("%d\n",check);
}

int modify(int x,int l,int r,int v)
{
	int mid=(l+r)/2;
	if (l==r) {mx[x]=l; return 0;}
	if (v<=mid) modify(x*2,l,mid,v);
	else modify(x*2+1,mid+1,r,v);
	int left=mx[x*2],right=mx[x*2+1];
	mx[x]=a[pos[left]]>=a[pos[right]]?left:right;
}

int query(int x,int l,int r,int xl,int xr)
{
	if (l<=xl&&xr<=r) return mx[x];
	int mid=(xl+xr)/2,tmp=0,re=0;
	if (l<=mid) 
	{
		tmp=query(x*2,l,r,xl,mid);
		if (a[pos[tmp]]>a[pos[re]]) re=tmp;
	}
	if (r>mid) 
	{
		tmp=query(x*2+1,l,r,mid+1,xr);
		if (a[pos[tmp]]>a[pos[re]]) re=tmp;
	}
	return re;
}
