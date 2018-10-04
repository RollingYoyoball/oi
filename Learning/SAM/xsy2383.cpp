#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=250010;
char s[MAXN];
int son[MAXN*2][26],suf[MAXN*2],len[MAXN*2],cnt[MAXN*2];
int loc[MAXN*2],ans[MAXN];
int n,m,tot,last,lens;
int insert(int ch);
int newnode(int x);
bool cmp(int x,int y) {return len[x]<len[y];}

int main()
{
	freopen("a.in","r",stdin);

	scanf("%s",s);
	lens=strlen(s);
	last=tot=1;
	for (int i=0;i<lens;++i)
		insert(s[i]-'a');
	for (int i=1;i<=tot;++i) loc[i]=i;
	sort(loc+1,loc+1+tot,cmp);
	for (int i=tot;i>=1;--i)
		cnt[suf[loc[i]]]+=cnt[loc[i]];
	memset(ans,0,sizeof(ans));
	for (int i=1;i<=tot;++i)
		ans[len[loc[i]]]=max(ans[len[loc[i]]],cnt[loc[i]]);
	for (int i=lens-1;i>=1;--i)
		ans[i]=max(ans[i],ans[i+1]);
	for (int i=1;i<=lens;++i)
		printf("%d\n",ans[i]);	
}

int insert(int ch)
{
	int p=last,np=newnode(len[p]+1),q,nq;
	for (;p&&!son[p][ch];p=suf[p]) 
		son[p][ch]=np;
	if (!p) suf[np]=1;
	else
	{
		q=son[p][ch];
		if (len[p]+1!=len[q])
		{
			nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof(son[q]));
			suf[nq]=suf[q],suf[np]=suf[q]=nq;
			for (;p&&son[p][ch]==q;p=suf[p]) son[p][ch]=nq;
		}
		else suf[np]=q;
	}
	last=np; ++cnt[np];
}

int newnode(int x)
{
	len[++tot]=x; return tot;
}
