#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100000*4+10;
struct xx1
{
	int cnt[26],total;
	bool turn,flag;
	friend inline xx1 operator + (const xx1 &a,const xx1 &b)
	{
		xx1 c; c.turn=false;
		for (int i=0;i<26;++i) c.cnt[i]=a.cnt[i]+b.cnt[i];
		c.total=a.total+b.total;
		return c;
	}
	void del(bool flag,int N)//1==小到大 0==大到小
	{
		total-=N;
		int add=flag?1:-1,st=flag?0:25;
		for (int i=st;i<26&&i>=0;i+=add)
			if (cnt[i]>=N) cnt[i]-=N,N=0;
			else N-=cnt[i],cnt[i]=0;
	}
	void take(bool flag,int N)
	{
		total=N;
		int add=flag?1:-1,st=flag?0:25;
		for (int i=st;i<26&&i>=0;i+=add)
			if (cnt[i]>=N) cnt[i]=N,N=0;
			else N-=cnt[i];
	}
}sorted;
struct xxx
{
	int lch,rch;
	xx1 num;
}a[MAXN];
char s[100010];
int n,m,tot;
int build(int x,int l,int r);
int pushup(int x);
int update(int x,int l,int r,int lx,int rx,int mark);
int downtag(int x);
int pushdown(int x,int lx,int rx);
xx1 query(int x,int l,int r,int lx,int rx);
int solve(int l,int r,int mark);

int main()
{
//	freopen("a.in","r",stdin);

	int x,y,op;
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	tot=1;
	build(1,1,n);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&y,&op);
		solve(x,y,op);
	//	pushdown(1,1,n);
	//	printf("%s\n",s+1);
	}
	pushdown(1,1,n);
	printf("%s",s+1);
}

int build(int x,int l,int r)
{
	if (l==r)
	{
		a[x].num.cnt[s[l]-'a']++; a[x].num.total=1;
		return 0;
	}	
	int mid=(l+r)/2;
	a[x].lch=++tot; build(a[x].lch,l,mid);
	a[x].rch=++tot; build(a[x].rch,mid+1,r);
	pushup(x);
}

int pushup(int x)
{
	a[x].num=a[a[x].lch].num+a[a[x].rch].num;
	a[x].num.total=a[a[x].lch].num.total+a[a[x].rch].num.total;
}

int update(int x,int l,int r,int lx,int rx)
{
	if (l<=lx&&rx<=r)
	{
		int tmp=a[x].num.total;
		a[x].num=sorted;
		a[x].num.take(sorted.flag,tmp);
		sorted.del(sorted.flag,tmp);
		return 0;
	}
	int mid=(lx+rx)/2;
	if (l<=mid) update(a[x].lch,l,r,lx,mid);
	if (r>mid) update(a[x].rch,l,r,mid+1,rx);
	pushup(x);
}

int downtag(int x)
{
	xx1 &lson=a[a[x].lch].num,&rson=a[a[x].rch].num;
	int tmp=lson.total;
	lson=a[x].num;
	lson.take(lson.flag,tmp);
	tmp=rson.total;
	rson=a[x].num;
	rson.take(!rson.flag,tmp);
	a[x].num.turn=false;
}

int pushdown(int x,int lx,int rx)
{
	if (lx==rx)
	{
		for (int i=0;i<26;++i)
			if (a[x].num.cnt[i])
				{s[lx]='a'+i; break;}
		return 0;
	}
	if (a[x].num.turn) 
		downtag(x);
	int mid=(lx+rx)/2;
	pushdown(a[x].lch,lx,mid);
	pushdown(a[x].rch,mid+1,rx);
}

xx1 query(int x,int l,int r,int lx,int rx)
{
	if (l<=lx&&rx<=r)
		return a[x].num;
	int mid=(lx+rx)/2;
	xx1 ret1,ret2;
	if (a[x].num.turn) downtag(x);
	int mark=0;
	if (l<=mid) ret1=query(a[x].lch,l,r,lx,mid),mark+=1;
	if (r>mid) ret2=query(a[x].rch,l,r,mid+1,rx),mark+=2;
	if (mark==1) return ret1;
	else return mark==2?ret2:ret1+ret2;
}

int solve(int l,int r,int mark)
{
	sorted=query(1,l,r,1,n);
//	printf("\n");
//	for (int i=0;i<26;++i) if (sorted.cnt[i]) printf("%c",'a'+i);
//	printf("\n");
	sorted.turn=true; sorted.flag=mark;
	update(1,l,r,1,n);
}
