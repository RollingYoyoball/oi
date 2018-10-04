#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=10000010;
queue<int> q;
int ch[MAXN][4],f[MAXN],id[MAXN],ans[MAXN],dep[MAXN];
char s[MAXN];
bool mark[MAXN];
int n,m,len,tot;
int change(char x);
int get_f();
int insert(char *s,int xx);
int get_ans(int x,int now);
int work(int x);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	char tmp1[110];
	scanf("%d%d\n",&n,&m);
	scanf("%s\n",s);
	tot=0;
	for (int i=1;i<=m;++i)
	{
		scanf("%s\n",tmp1);
		insert(tmp1,i);
	}
	int now=0,tmp;
	get_f();
	for (int i=0;i<n;++i)
	{
		tmp=change(s[i]);	
		mark[now]=true;
		while (now&&!ch[now][tmp]) now=f[now];
		if (ch[now][tmp]) now=ch[now][tmp];
		work(now);
	}
	get_ans(0,0);
	for (int i=1;i<=m;++i)
		printf("%d\n",ans[id[i]]);
		//get_ans(id[i]);
}

int change(char x)
{
	if (x=='E') return 0;
	if (x=='S') return 1;
	if (x=='W') return 2;
	return 3;
}

int insert(char *s,int xx)
{
	int now=0,len=strlen(s),d=0;
	for (int i=0;i<len;++i)
	{
		int tmp=change(s[i]);
		if (!ch[now][tmp]) ch[now][tmp]=++tot;
		//pre[ch[now][tmp]]=now;
		now=ch[now][tmp];
		dep[now]=++d;
	}
	id[xx]=now;
}

int get_f()
{
	int u,v;
	for (int i=0;i<4;++i)
		if (ch[0][i]) q.push(ch[0][i]),f[ch[0][i]]=0;
	while (!q.empty())
	{
		v=q.front(); q.pop();
		for (int i=0;i<4;++i)
		{
			if (!ch[v][i]) continue;
			u=f[v];
			while (u&&!ch[u][i]) u=f[u];
			f[ch[v][i]]=ch[u][i];
			q.push(ch[v][i]);
		}
	}
}

int get_ans(int x,int now)
{
    if(mark[x]) 
		now=dep[x];
    ans[x]=now;
    for(int i=0;i<4;i++)
    	if(ch[x][i]) 
			get_ans(ch[x][i],now);
}

int work(int x)
{
	while (x) 
		mark[x]=1,x=f[x];
}
