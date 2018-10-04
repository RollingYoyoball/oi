#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=2000010;
const int Q=10010;
struct xxx
{
	int type;
	int x,y,v,qnum;
	bool operator < (const xxx &b) const
	{return x<b.x;}
	xxx() {}
	xxx(int x1,int y1,int v1,int qnum1,int type1)
	{x=x1,y=y1,v=v1,qnum=qnum1,type=type1;}
}a[MAXN];
ll ans[MAXN];
ll c[MAXN];
int W,S,n,tot;
int add(int x,int d);
ll query(int x);
int cdq(int l,int r);

int main()
{
	scanf("%d%d",&S,&W);
	int op=1,x1,y1,x2,y2,x; 
	n=0; tot=0;
	while (scanf("%d",&op))
	{
		if (op==3) break;
		if (op==1)
		{
			scanf("%d%d%d",&x1,&y1,&x);
			a[++n]=xxx(x1,y1,x,0,1);
		}
		else
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			++tot;
			a[++n]=xxx(x2,y2,1,tot,2);
			a[++n]=xxx(x1-1,y2,-1,tot,2);
			a[++n]=xxx(x2,y1-1,-1,tot,2);
			a[++n]=xxx(x1-1,y1-1,1,tot,2);
			ans[tot]=(x2-x1+1)*(y2-y1+1)*S;
		}
	}
	cdq(1,n);
	for (int i=1;i<=tot;++i)
		printf("%lld\n",ans[i]);
}

int cdq(int l,int r)
{
	if (l==r) return 0;
	int mid=l+r>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	sort(a+l,a+1+mid);
	sort(a+mid+1,a+r+1);
	int now=l;
	for (int i=mid+1;i<=r;++i)
	{
		while (now<=mid&&a[now].x<=a[i].x)
		{
			if (a[now].type==1)
				add(a[now].y,a[now].v);
			++now;
		}
		if (a[i].type==2) ans[a[i].qnum]+=query(a[i].y)*a[i].v;
	}
	for (int i=l;i<now;++i)
		if (a[i].type==1) add(a[i].y,-a[i].v);
}

int add(int x,int d)
{
	for (;x<=n;x+=x&-x) c[x]+=d;
}

ll query(int x)
{
	ll ret=0;
	for (;x>0;x-=x&-x) ret+=c[x];
	return ret;
}
