#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=12*50+10;
const int MAXM=3000010;
int ch[MAXN][26],f[MAXN];
int a[MAXN];
int q[MAXM],pre[MAXM],f1[MAXM];
char c[MAXN];
bool vis[MAXN][1<<12];
int n,m,tot;
int insert(char *s,int xx);
int get_f();
int bfs();
int print(int x);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	char s[60];
	scanf("%d",&n);
	tot=0;
	memset(a,0,sizeof(a));
	for (int i=1;i<=n;++i)
	{
		scanf("%s",s);
		insert(s,i);
	}
	get_f();
	bfs();
//	for (int i=0;i<=tot;++i) printf("%d ",a[i]);
}

int insert(char *s,int xx)
{
	int now=0,len=strlen(s);
	for (int i=0;i<len;++i)
	{
		if (!ch[now][s[i]-'A']) ch[now][s[i]-'A']=++tot;
		now=ch[now][s[i]-'A'];
		c[now]=s[i];
	}	
	a[now]=1<<(xx-1);
}

int get_f()
{
	int v,head=0,tail=1;
	q[1]=0;
	do
	{
		v=q[++head];
		for (int i=0;i<26;++i)
		{
			if (!ch[v][i]) {ch[v][i]=ch[f[v]][i];continue;}
			if (v)
				f[ch[v][i]]=ch[f[v]][i];
			else 
				f[ch[v][i]]=0;
			a[ch[v][i]]|=a[f[ch[v][i]]];
			q[++tail]=ch[v][i];
		}
	}while (head<tail);
}

int bfs()
{
	int v,u,head=0,tail=1;
	q[1]=0; f1[1]=0; pre[1]=0;
	do
	{
		v=q[++head];
	//	if (f1[head]) printf("%d\n",f1[head]);
		if (f1[head]==(1<<n)-1)
		{
			print(head);
			return 0;
		}
		for (int i=0;i<26;++i)
		{
			//if (!ch[v][i]) continue;
			if (vis[ch[v][i]][f1[head]|a[ch[v][i]]]) continue;
			f1[++tail]=f1[head]|a[ch[v][i]];
			vis[ch[v][i]][f1[head]|a[ch[v][i]]]=true;
			pre[tail]=head;
			q[tail]=ch[v][i];
		}
	}while (head<tail);
}

int print(int x)
{
	if (q[pre[x]]) print(pre[x]);
	if (q[x]) printf("%c\n",c[q[x]]);
}
