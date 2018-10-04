#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=10010;
char s[MAXN],t[MAXN];
int son[MAXN][26],suf[MAXN],len[MAXN];
int n,m,tot,last;
int insert(int ch);
int newnode(int x);
int dfs(int x,int dep);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%s",s);
	n=strlen(s);
	last=tot=1;
	for (int i=0;i<n;++i)
		insert(s[i]-'a');
	memset(t,0,sizeof(t));
	dfs(1,0);
}

int insert(int ch)
{
	int p=last,np=newnode(len[p]+1),nq,q;
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
			suf[nq]=suf[q]; suf[np]=nq; suf[q]=nq; 
			for (;p&&son[p][ch]==q;p=suf[p]) son[p][ch]=nq;
		}
		else suf[np]=q;//!!!
	}	
	last=np;
}

int newnode(int x)
{
	len[++tot]=x; return tot;
}

int dfs(int x,int dep)
{
	printf("%s\n",t+1);
	for (int i=0;i<26;++i)
	{
		if (!son[x][i]) continue;
		t[dep+1]=i+'a';
		dfs(son[x][i],dep+1);
		t[dep+1]=0;
	}
}
