#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=1000010;
queue<int> q;
int ch[MAXN][27],f[MAXN],cnt[MAXN];
int c[MAXN],num[MAXN];
int n,m,tot,root;
int insert(int xx,char *s);
int get_f();
int newnode();

int main()
{
	freopen("a.in","r",stdin);

	char s[MAXN];
	root=0;
	scanf("%d\n",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%s\n",s);
		insert(i,s);
	}
	get_f();
	for (int i=c[0];i>=1;--i)
		cnt[f[c[i]]]+=cnt[c[i]];
	for (int i=1;i<=n;++i)
		printf("%d\n",cnt[num[i]]);	
}

int insert(int xx,char *s)
{
	int len=strlen(s),x=0;
	for (int i=0;i<len;++i)
	{
		if (!ch[x][s[i]-'a']) 
			ch[x][s[i]-'a']=newnode();
		x=ch[x][s[i]-'a'];
		++cnt[x];
	}
	num[xx]=x;
}

int newnode()
{
	cnt[++tot]=0;
	return tot;
}

int get_f()
{
	int v,u;
	for (int i=0;i<=25;++i)
		if (ch[root][i]) q.push(ch[root][i]),f[ch[root][i]]=0;
	while (!q.empty())
	{
		v=q.front(); q.pop();
		c[++c[0]]=v;
		for (int i=0;i<=25;++i)
		{
			if (!ch[v][i]) continue;
			u=f[v];
			while (u&&!ch[u][i]) u=f[u];
			f[ch[v][i]]=ch[u][i];
			q.push(ch[v][i]);
		}	
	}	
}
