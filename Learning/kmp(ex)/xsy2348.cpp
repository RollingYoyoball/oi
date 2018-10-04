#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=200010;
char s[MAXN],t[MAXN];
int nxt[MAXN],ex[MAXN];
int lens,lent,n;
int L,E,G,a;
int get_nxt();
int work();
int get_ex();

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf("%d",&n);
	for (int o=1;o<=n;++o)
	{
		scanf("%s\n",t);
		lent=strlen(t);
		for (int i=0;i<lent;++i) s[i]=t[i],s[i+lent]=t[i];
		lens=strlen(s);
		L=E=G=0;
		get_nxt();
		get_ex();
		a=work();
		printf("Case %d: %d %d %d\n",o,L/a,E/a,G/a);
	}	
}

int get_nxt()
{
	int j=-1,p=0,st=0;
	nxt[0]=lent; ++E;
	for (int i=1;i<lent;++i,--j)
	{
		if (j<0||i+nxt[i-st]>=p)
		{
			if (j<0)
				p=i,j=0;
			while (p<lent&&t[j]==t[p])
				++p,++j;
			nxt[i]=j;
			st=i;
		}
		else
			nxt[i]=nxt[i-st];
	}
}

int get_ex()
{
	int j=-1,p=0,st=0;
	++E;
	for (int i=0;i<lent;++i,--j)
	{
		if (j<0||i+nxt[i-st]>=p)
		{
			if (j<0)
				p=i,j=0;
			while (p<lens&&s[j]==s[p])
				++p,++j;
			ex[i]=j;
			st=i;
		}
		else
			ex[i]=nxt[i-st];
		if (s[ex[i]+i]>s[ex[i]]) 
			++G;
		else 
			if (s[ex[i]+i]<s[ex[i]]) ++L;
		else 
			++E;
	}
}

int work()
{
	int re=1,tmp=1,now=lent;
	while (nxt[tmp]==0&&tmp<lent) ++tmp;
	if (tmp==lent) return lent;
	for (int i=1;i<lent;++i)
		if ((i%tmp==0&&nxt[i]!=now)||(i%tmp!=0&&nxt[i]!=0))
			return 1;
		else
			if (i%tmp==0) now-=tmp;
	return lent/tmp;
}
