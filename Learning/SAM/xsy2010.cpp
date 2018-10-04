#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1200010;
char s[MAXN];
int son[MAXN][26],len[MAXN],suf[MAXN],cnt[MAXN],sum[MAXN];
int n,m,tot,last,mask,ans;
int insert(int ch);
int newnode(int x);
int work(int mask);
int get_ans(char *s,int lens);

int main()
{
	freopen("a.in","r",stdin);
	
	char op[10];
	scanf("%d\n",&m);
	scanf("%s",s);
	mask=0;
	int lens=strlen(s);
	tot=last=1;
	for (int i=0;i<lens;++i) 
		insert(s[i]-'A');
	for (int i=1;i<=m;++i)
	{
		scanf("%s",op);
		if (op[0]=='Q')
		{
			scanf("%s",s);
			lens=strlen(s);
			work(mask);
			ans=get_ans(s,lens);
			mask^=ans;
			printf("%d\n",ans);
		}
		else
		{
			scanf("%s",s);
			lens=strlen(s);
			work(mask);
			for (int i=0;i<lens;++i)
				insert(s[i]-'A');
		}
	}
}

int insert(int ch)
{
	int p=last,np=newnode(len[p]+1),q,nq;
	for (;p&&!son[p][ch]; p=suf[p]) 
		son[p][ch]=np;
	if (!p) suf[np]=1;
	else
	{
		q=son[p][ch];
		if (len[p]+1!=len[q])
		{
			nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof(son[q]));
			sum[nq]=sum[q];
			suf[nq]=suf[q],suf[q]=suf[np]=nq;
			for (;p&&son[p][ch]==q; p=suf[p]) son[p][ch]=nq;
		}
		else suf[np]=q;//!!!
	}
	last=np;
	for (;np;np=suf[np]) ++sum[np];
}

int newnode(int x)
{
	len[++tot]=x; /*sum[tot]=1; */return tot;
}

int work(int mask)
{
	int lenc=strlen(s);
	for (int j=0;j<lenc;++j)
	{
		mask=(mask*131+j)%lenc;
		char t=s[j];
		s[j]=s[mask];
		s[mask]=t;
	}
}

int get_ans(char *s,int lens)
{
	int now=1;
	for (int i=0;i<lens;++i)
		if (son[now][s[i]-'A']) now=son[now][s[i]-'A'];
		else return 0;
	return sum[now];
}
