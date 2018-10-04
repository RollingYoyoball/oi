#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define lson l,mid,o<<1
#define rson mid+1,r,o<<1|1

struct node { int t,next; }a[100010];

struct tree { int l,r,mn; }t[400010];

int head[100010],dep[100010],in[100010],out[100010],hh[100010];
int fa[100010][20],num[100010],bin[20],n,m,rt,tot,ind;
char ch[233];

inline int rd()
{
	int x=0;char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar());
	for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x;
}

inline void add(int x,int y) { a[++tot].t=y;a[tot].next=head[x];head[x]=tot; }

inline void dfs(int x)
{
	in[x]=++ind;hh[ind]=x;
	for (int i=1;i<17;i++) if (bin[i]<=dep[x]) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=head[x];i;i=a[i].next)
	{
		int t=a[i].t;
		dep[t]=dep[x]+1;
		fa[t][0]=x;dfs(t);
	}
	out[x]=ind;
}

inline void build(int l,int r,int o)
{
	t[o].l=l;t[o].r=r;
	if (l==r) { t[o].mn=num[hh[l]];return; }
	int mid=(l+r)>>1;
	build(lson);build(rson);
	t[o].mn=min(t[o<<1].mn,t[o<<1|1].mn);
}

inline void modify(int pos,int num,int o)
{
	int l=t[o].l,r=t[o].r,mid=(l+r)>>1;
	if (l==r) { t[o].mn=num;return; }
	if (pos<=mid) modify(pos,num,o<<1);
	else modify(pos,num,o<<1|1);
	t[o].mn=min(t[o<<1].mn,t[o<<1|1].mn);
}

inline int query(int x,int y,int o)
{
	if (x>y) return 1000000000;
	int l=t[o].l,r=t[o].r,mid=(l+r)>>1;
	if (l==x&&r==y) return t[o].mn;
	if (y<=mid) return query(x,y,o<<1);
	else if (x>mid) return query(x,y,o<<1|1);
	return min(query(x,mid,o<<1),query(mid+1,y,o<<1|1));
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
	n=rd();m=rd();bin[0]=1;tot=0;
	for (int i=1;i<20;i++) bin[i]=bin[i-1]<<1;
	for (int i=1;i<=n;i++)
	{
		int x=rd();num[i]=rd();
		if (x) add(x,i);
	}
	ind=0;dfs(rt=1);
	build(1,n,1);
	while (m--)
	{
		scanf("%s",ch);
		int x=rd();
		if (ch[0]=='V') { int hh=rd();modify(in[x],hh,1); }
		else if (ch[0]=='E') rt=x;
		else
		{
			if (rt==x) printf("%d\n",t[1].mn);
			else if (in[x]<=in[rt]&&out[x]>=out[rt])
			{
				int y=rt,d=dep[y]-dep[x]-1;
				for (int i=0;i<17;i++) if (bin[i]&d) y=fa[y][i];
				printf("%d\n",min(query(1,in[y]-1,1),query(out[y]+1,n,1)));
			}
			else printf("%d\n",query(in[x],out[x],1));
		}
	}
	return 0;
}
