#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int MAXN=5000010;
char s[MAXN];
int ch[MAXN][2];
int suf[MAXN],len[MAXN];
int n,m,tot,last,now;
int insert(int x,int c);
int find(int x,int now);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%s\n",s);
	int lens=strlen(s),pre=0;
	len[0]=0,len[1]=-1,suf[0]=1,tot=1;
	for (int i=0;i<lens;++i)
		pre=tot,insert(i,s[i]-'a'),printf("%d",tot-pre);	
}

int insert(int x,int c)
{
	now=find(x,last);
	if (!ch[now][c])
	{
		suf[++tot]=ch[find(x,suf[now])][c];
		len[tot]=len[now]+2;
		ch[now][c]=tot;
	}
	last=ch[now][c];
}

int find(int x,int now)
{
	while (s[x]!=s[x-len[now]-1]) now=suf[now];
	return now;
}
