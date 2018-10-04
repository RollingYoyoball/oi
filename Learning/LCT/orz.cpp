#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<iostream>
#include<algorithm>
#define mod 51061
#define ll unsigned int
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,top,cnt;
int c[100005][2],fa[100005];
int size[100005],q[100005];
bool rev[100005];
ll sum[100005],val[100005],at[100005],mt[100005];
void cal(int x,int m,int a)
{
	if(!x)return;
	val[x]=(val[x]*m+a)%mod;
	sum[x]=(sum[x]*m+a*size[x])%mod;
	at[x]=(at[x]*m+a)%mod;
	mt[x]=(mt[x]*m)%mod;
}
bool isroot(int x)
{
	return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
}
void update(int x)
{
	int l=c[x][0],r=c[x][1];
	sum[x]=(sum[l]+sum[r]+val[x])%mod;
	size[x]=(size[l]+size[r]+1)%mod;
}
void pushdown(int x)
{
	int l=c[x][0],r=c[x][1];
	if(rev[x])
	{
		rev[x]^=1;rev[l]^=1;rev[r]^=1;
		swap(c[x][0],c[x][1]);
	}
	int m=mt[x],a=at[x];
	mt[x]=1;at[x]=0;
	if(m!=1||a!=0)
	{
		cal(l,m,a);cal(r,m,a);
	}
}
void rotate(int x)
{
	int y=fa[x],z=fa[y],l,r;
	l=(c[y][1]==x);r=l^1;
	if(!isroot(y))c[z][c[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	update(y);update(x);
}
void splay(int x)
{
	q[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])
		q[++top]=fa[i];
	while(top)pushdown(q[top--]);
	while(!isroot(x))
	{
		int y=fa[x],z=fa[y];
		if(!isroot(y))
		{
			if(c[y][0]==x^c[z][0]==y)rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x)
{
	for(int t=0;x;t=x,x=fa[x])
	{
		splay(x);c[x][1]=t;update(x);
	}
}
void makeroot(int x)
{
	access(x);splay(x);rev[x]^=1;
}
void split(int x,int y)
{
	makeroot(y);access(x);splay(x);
}
void link(int x,int y)
{
	makeroot(x);fa[x]=y;
}
void cut(int x,int y)
{
	makeroot(x);access(y);splay(y);c[y][0]=fa[x]=0;
}
int main()
{
	freopen("a.in","r",stdin);

	n=read();m=read();
	int u,v,c;
	for(int i=1;i<=n;i++)
		val[i]=sum[i]=mt[i]=size[i]=1;
	for(int i=1;i<n;i++)
	{
		u=read(),v=read();
		link(u,v);
	}
	char ch[5];
	while(m--)
	{
		scanf("%s",ch);
		u=read();v=read();
		if(ch[0]=='+')
		{
			c=read();
			split(u,v);cal(u,1,c);
		}
		if(ch[0]=='-')
		{
			cut(u,v);
			u=read();v=read();link(u,v);
		}
		if(ch[0]=='*')
		{
			c=read();
			split(u,v);cal(u,c,0);
		}
		if(ch[0]=='/')
		{
			split(u,v);
			printf("%d\n",sum[u]);
		}
	}
	return 0;
}
