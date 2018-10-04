#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=600010;
char s[MAXN];
int son[MAXN][26],len[MAXN],suf[MAXN],cnt[MAXN];
int n,m,tot,last;
int insert(int ch);

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%d\n",&m);
	scanf("%s",s);
	int lens=strlen(s);
	tot=last=1;
	for (int i=0;i<lens;++i) 
		insert(s[i]-'A');
	for (int i=1;i<=m;++i)
	{


}

int insert(int ch)
{
	int p=last,np=newnode(len[p]+1),q,nq;
	for (;p&&!son[p][ch]; p=suf[p]) son[p][ch]=np;
	if (p) suf[np]=1;
	else
	{
		q=son[p][ch];
		if (len[p]+1!=len[q])
		{
			nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof(son[q]));
			suf[nq]=suf[q],suf[q]=suf[np]=nq;
			for (;p&&son[p][ch]==q; p=suf[p]) son[p][ch]=nq;
		}
		else suf[np]=p;
	}
	last=np;
}
