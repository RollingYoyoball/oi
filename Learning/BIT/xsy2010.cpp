#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int MAXN=100010;
struct xxx
{
	int l,r,x,y;
	int dir;
}a[MAXN*4];//并不是MAXN，因为一个点可能既连了横的也练了竖的，保险一点*4？ 
struct xx1
{
	int x,y;
}dot[MAXN];
map<int,int> id;
int c[MAXN*4];
int n,m,tot,ans,cnt;
void get_line();
bool cmp(xx1 x,xx1 y) {return x.x<y.x;}
bool cmp1(xx1 x,xx1 y) {return x.y==y.y?x.x<y.x:x.y<y.y;}
bool cmp2(xx1 x,xx1 y) {return x.x==y.x?x.y<y.y:x.x<y.x;}
bool cmp3(xxx x,xxx y) {return x.y==y.y?x.dir<y.dir:x.y<y.y;}
void update(int x,int delta);
int query(int x);
void add(int x,int l,int r,int mark);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d",&dot[i].x,&dot[i].y);
	}
	sort(dot+1,dot+1+n,cmp);
	for (int i=1;i<=n;id[dot[i++].x]=tot)
		if (dot[i].x!=dot[i-1].x) ++tot;
	ans=0;
	get_line();
	sort(a+1,a+1+cnt,cmp3);
	for (int i=1;i<=cnt;++i)
	{
		if (!a[i].dir) ans+=query(a[i].r)-query(a[i].l-1);
		else update(a[i].x,a[i].dir);
	}
	printf("%d\n",ans+n);
}

void get_line()
{
	sort(dot+1,dot+1+n,cmp2);
	for (int i=1;i<=n;++i)
		if (dot[i].x==dot[i-1].x)
			add(id[dot[i].x],dot[i-1].y,dot[i].y,1);
			
	sort(dot+1,dot+1+n,cmp1);
	for (int i=1;i<=n;++i)
		if (dot[i].y==dot[i-1].y)
			add(dot[i].y,id[dot[i-1].x],id[dot[i].x],0);
}

void update(int x,int delta)
{
	for (;x<=tot;x+=x&-x)
		c[x]+=delta;
}

int query(int x)
{
	int ret=0;
	for (;x;x-=x&-x)
		ret+=c[x];
	return ret;
}

void add(int x,int l,int r,int mark)//横的是0 竖的是1(query)
{
	if (!mark)
		a[++cnt].y=x,a[cnt].l=l,a[cnt].r=r,a[cnt].dir=mark;
	else
	{
		a[++cnt].x=x,a[cnt].y=l,a[cnt].dir=1;
		a[++cnt].x=x,a[cnt].y=r,a[cnt].dir=-1;
	}
}
