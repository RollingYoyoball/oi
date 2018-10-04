#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000010;
char s[MAXN];
int son[MAXN*2][26],len[MAXN*2],suf[MAXN*2],cnt[MAXN*2];
int loc[MAXN*2],mark[MAXN]; 
int n,m,tot,last,lens,ans;
int insert(int ch);
int newnode(int x);
bool cmp(int x,int y) {return len[x]<len[y];}
int work(int n,int num);

int main()
{
//	freopen("a.in","r",stdin);
	
	scanf("%s",s);
	lens=strlen(s);
	last=tot=1;
	for (int i=0;i<lens;++i)
		insert(s[i]-'a');
	for (int i=1;i<=tot;++i) loc[i]=i;
	sort(loc+1,loc+1+tot,cmp);
	for (int i=tot;i>=1;--i)
		cnt[suf[loc[i]]]+=cnt[loc[i]];
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%s",s);
		lens=strlen(s);
		for (int j=0;j<lens;++j) s[j+lens]=s[j];
		ans=0;
		work(lens*2,i);
		printf("%d\n",ans);
	}	
}

int insert(int ch)
{
	int p=last,np=newnode(len[p]+1),q,nq;
	for (;p&&!son[p][ch];p=suf[p]) son[p][ch]=np;
	if (!p) suf[np]=1;
	else
	{
		q=son[p][ch];
		if (len[p]+1!=len[q])
		{
			nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof(son[q]));
			suf[nq]=suf[q],suf[q]=suf[np]=nq;
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

int work(int n,int num)
{
	int now=1,l=0;
	for (int i=0;i<n;++i)
	{
		if (son[now][s[i]-'a']) ++l,now=son[now][s[i]-'a'];
		else
		{
			while (now&&!son[now][s[i]-'a']) now=suf[now];
			if (!now) now=1,l=0;
			else l=len[now]+1,now=son[now][s[i]-'a'];
		}
		
		if (l>=n/2)
		{
			while (suf[now]&&len[suf[now]]>=n/2) now=suf[now];
		//	printf("#%d\n",len[now]);
			if (mark[now]!=num) 
				ans+=cnt[now],l=len[now],mark[now]=num;
		}
	}
}
