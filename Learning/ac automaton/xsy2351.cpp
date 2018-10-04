#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=110;
struct xxx
{
	double a[MAXN][MAXN];
}aa,tmp;
queue<int> q;
double p[MAXN];
int ch[MAXN][10],f[MAXN],id[11];
bool mark[MAXN];
int n,m,l,tot;
int insert(char *s,int xx);
int work();
int mul();
int get_f();

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	char s[11];
	int x,y;
	scanf("%d%d%d\n",&n,&l,&m);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		p[i]=(double)x/y;
	}
	for (int i=1;i<=n;++i)
	{
		scanf("%s",s);
		insert(s,i);		
	}	
	get_f();
	work();
	for (int i=0;i<=tot;++i)
	{
		for (int j=0;j<=tot;++j)
			printf("%0.2lf ",aa.a[i][j]);
		printf("\n");
	}
	for (int i=1;i<=10;++i)
		mul();
	for (int i=1;i<=n;++i)
		printf("%0.2lf\n",aa.a[0][id[i]]);
}

int insert(char *s,int xx)
{
	int now=0;
	for (int i=0;i<l;++i)
	{
		if (!ch[now][s[i]-'A']) ch[now][s[i]-'A']=++tot;
		now=ch[now][s[i]-'A'];
	}	
	id[xx]=now;	mark[now]=1;
}

int get_f()
{
	int u,v;
	for (int i=0;i<m;++i)
		if (ch[0][i]) 
			q.push(ch[0][i]),f[ch[0][i]]=0;
	while (!q.empty())
	{
		v=q.front(); q.pop();
		for (int i=0;i<m;++i)
		{
			if (!ch[v][i]) continue;
			u=f[v];

			while (u&&!ch[u][i]) u=f[u];
			f[ch[v][i]]=ch[u][i];
			q.push(ch[v][i]);
		}
	}	
}

int work()
{
	int u;
	for (int i=0;i<=tot;++i)
	{
		if (mark[i]) {aa.a[i][i]=1;continue;}
		for (int j=0;j<m;++j)
		{
			u=i;
			while (u&&!ch[u][j]) u=f[u];
			aa.a[i][ch[u][j]]+=p[j+1];
		}
	}
}

int mul()
{
	for (int i=0;i<=tot;++i)
		for (int j=0;j<=tot;++j)
		{
			tmp.a[i][j]=0;
			for (int k=0;k<=tot;++k)
				tmp.a[i][j]+=aa.a[i][k]*aa.a[k][j];
		}
	aa=tmp;
}	
