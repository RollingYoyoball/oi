#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500000+10;
struct xxx
{
	int x,y,z,id;
	int op;
	bool operator < (const xxx &b) const
	{
		if (x!=b.x) return x<b.x;
		if (y!=b.y) return y<b.y;
		if (z!=b.z) return z<b.z;
		return id<b.id;
	}
}a[MAXN],tmp[MAXN];
int c[MAXN],ans[MAXN],lv[MAXN];
int n,m,tot;
int insert(int x,int delta);
int query(int x);
int cdq(int l,int r);
bool cmp1(xxx x,xxx y) {return x.y<y.y;}

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
		a[i].id=i;
	}
	sort(a+1,a+1+n);
	cdq(1,n);
	sort(a+1,a+1+n);
	for (int i=n-1;i>=1;--i) 
		if (a[i].x==a[i+1].x&&a[i].y==a[i+1].y&&a[i].z==a[i+1].z)
			lv[a[i].id]=lv[a[i+1].id];
	for (int i=1;i<=n;++i) ++ans[lv[i]];
	for (int i=0;i<n;++i) printf("%d\n",ans[i]);
}

int insert(int x,int delta)
{
	for (;x<=m;x+=x&-x)
		c[x]+=delta;
}

int query(int x)
{
	int ret=0;
	for (;x;x-=x&-x)
		ret+=c[x];
	return ret;
}

int cdq(int l,int r)
{
	if (l==r) return 0;
	int mid=l+r>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	sort(a+l,a+1+mid,cmp1);
	sort(a+mid+1,a+r+1,cmp1);
	int now=l,tot=l-1;
	for (int i=mid+1;i<=r;++i)
	{
		while (now<=mid&&a[now].y<=a[i].y)
		{
//			tmp[++tot]=a[now];
			insert(a[now].z,1);
			++now;
		}
//		tmp[++tot]=a[i];
		lv[a[i].id]+=query(a[i].z);
	}
	for (int i=l;i<now;++i)
		insert(a[i].z,-1);
/*	for (int i=now;i<=mid;++i)
		tmp[++tot]=a[i];
	for (int i=l;i<=r;++i)
		a[i]=tmp[i];*/
}
