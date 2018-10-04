#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1e5+10;
struct xxx
{
	int lch[MAXN],rch[MAXN],dis[MAXN],val[MAXN],v[MAXN];
	int tot,rt[2];

	int init()
	{
		tot=0;
		rt[0]=rt[1]=0;
		memset(lch,0,sizeof(lch));
		memset(rch,0,sizeof(rch));
	}
	int newnode(int x,int t)
	{
		val[++tot]=t; v[tot]=x;
		lch[tot]=rch[tot]=0;
		return tot;
	}
	int merge(int x,int y)
	{
		rt[x]=_merge(rt[x],rt[y]);
		rt[y]=0;
	}
	int _merge(int x,int y)
	{
		if (!x||!y) return x+y;
		if (val[x]<val[y]) swap(x,y);
		rch[x]=_merge(rch[x],y);
		if (dis[lch[x]]<dis[rch[x]]) swap(lch[x],rch[x]);
		dis[x]=dis[rch[x]]+1;
		return x;
	}
	int insert(int who,int t,int delta)
	{
		int x=newnode(delta,t);
		rt[who]=_merge(rt[who],tot);
	}
	int pop(int who)
	{
		printf("%d\n",v[rt[who]]);
		rt[who]=_merge(lch[rt[who]],rch[rt[who]]);
	}
}heap;
int n,m,cnt;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	char s[10],s1[10];
	int lens,x;
	cnt=0;
	while (1)
	{
		scanf("%d",&n);
		if (!n) break;
		++cnt;
		printf("Case #%d\n",cnt);
		heap.init();
		for (int i=1;i<=n;++i)
		{
			scanf("%s",s);
			lens=strlen(s);
			if (s[0]=='p')
			{
				if (s[1]=='o') 
				{
					scanf("%s",s);
					heap.pop(s[0]-'A');
				}
				else 
				{
					scanf("%s %d",s,&x);
					heap.insert(s[0]-'A',i,x);
				}
			}
			else
			{
				scanf("%s",s); 
				scanf("%s",s1);
				heap.merge(s[0]-'A',s1[0]-'A');
			}
		}
	}
}
