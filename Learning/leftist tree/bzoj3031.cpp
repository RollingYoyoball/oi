#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=2000010;
int lch[MAXN],rch[MAXN],key[MAXN],dist[MAXN];
int card[110],tp[110];
int have[2],num[2],p[2];//0==sheep,1==wolf
int n,m,R,tot;
int merge(int x,int y);
int delt(int x);
int add(int x);

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	
	char ch;
	int x,tmp;
	while (~scanf("%d",&R))
	{
		p[0]=p[1]=0;
		for (int o=1;o<=R;++o)
		{
			scanf("%d%d\n",&m,&n);
			memset(tp,0,sizeof(tp));
			memset(card,0,sizeof(card));
			tot=0;
			for (int i=1;i<=n;++i)
				scanf("%d",&card[i]),tot+=card[i];
			for (int i=1;i<=n;++i)
			{
				scanf("%d",&x); //tp[i]=i;
				for (int j=1;j<=card[i];++j)
				{
					scanf("%d",&x);
					tp[i]=merge(tp[i],add(x));
				}
			}
			have[0]=have[1]=0;
			num[0]=num[1]=0;
			scanf("\n");
			for (int i=1;i<=m;++i)
			{
	
				scanf("%c",&ch);
				if (ch=='T')
				{
					scanf("%d",&x);
					num[i&1]+=card[x];
					card[x]=0;
					have[i&1]=merge(have[i&1],tp[x]);
				}
				else if (ch=='C')
				{
					if (key[have[1]]>key[have[0]]) tmp=1;
					else tmp=0;
					if (key[have[1]]==key[have[0]]) continue; 
					have[tmp]=merge(have[tmp],have[tmp^1]);
					have[tmp^1]=0;
					num[tmp]+=num[tmp^1];
					num[tmp^1]=0;
				}
				else if (ch=='L')
				{
					have[i&1]=delt(have[i&1]);
					--num[i&1];
				}
				else if (ch=='A')
				{
					scanf("%d",&x);
					key[have[i&1]]+=x;
				}
				else
				{
					scanf("%d",&x);
					tmp=have[i&1];
					have[i&1]=delt(have[i&1]);
					key[tmp]=x;
					have[i&1]=merge(have[i&1],tmp);
				}
				scanf("\n");
			}
			if (num[0]>num[1]) ++p[0];
			else ++p[1];
			printf("%d:%d\n",num[1],num[0]);
		}
		if (p[1]>p[0]) printf("Hahaha...I win!!\n");
		else printf("I will be back!!\n");
	}
}

int merge(int x,int y)
{
	if (x==0||y==0) return x+y;
	if (key[x]<key[y]) swap(x,y);
	rch[x]=merge(rch[x],y);
	if (dist[lch[x]]<dist[rch[x]]) swap(lch[x],rch[x]);
	dist[x]=rch[x]+1;
	return x;
}

int delt(int x)
{
	int l=lch[x],r=rch[x];
	dist[x]=-1;
	lch[x]=rch[x]=0;
	return merge(l,r);
}

int add(int x)
{
	lch[++tot]=0;
	rch[tot]=0;
	dist[tot]=-1;
	key[tot]=x;
	return tot;
}
