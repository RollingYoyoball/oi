#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100010;
struct xxx
{
	int y,next;
}a[MAXN],q[MAXN];
queue<int> q1;
char s[MAXN];
int h[MAXN],ch[MAXN][26],id[MAXN],cnt[MAXN],ans[MAXN];
int c[MAXN*4],fa[MAXN];
int lst[MAXN],f[MAXN];
int l[MAXN],r[MAXN];
int n,m,tot,tot1,len;
int insert(char *s);
int get_f();
int add(int x,int y);
int dfs(int x);
int update(int x,int d);
int query(int x);

int main()
{
	freopen("a.in","r",stdin);
	
	memset(h,-1,sizeof(h));
	memset(lst,-1,sizeof(lst));
	
	char s1[MAXN];
	scanf("%s\n",s);
	len=strlen(s);
	insert(s);
	
	tot1=0;
	get_f();
	tot=0;
	dfs(0);
	int x,y,now;
	scanf("%d",&m);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&y,&x);
		q[i].y=y; q[i].next=lst[x]; lst[x]=i;
	}
	x=0; now=0;
	
	for (int i=0;i<len;++i)
	{
		if (s[i]=='P')
		{
			++x;
			for (int j=lst[x];j!=-1;j=q[j].next)
			{
				int tmp=id[q[j].y],tmp1=query(r[tmp]),tmp2=query(l[tmp]-1);
				ans[j]=query(r[tmp])-query(l[tmp]-1);
			}
		}		
		else if (s[i]=='B')
			update(l[now],-1),now=fa[now];
		else 
			now=ch[now][s[i]-'a'],update(l[now],1);
	}
	for (int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
}

int insert(char *s)
{
	int now=0,pre=0;
	for (int i=0;i<len;++i)
	{
		if (s[i]=='P') id[++n]=now;
		else if (s[i]=='B') now=fa[now];
		else
		{
			if (!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++tot;
			fa[tot]=now;
			now=ch[now][s[i]-'a']; 
			//++cnt[now];	
		}
	}
}

int get_f()
{
	int v,u;
	for (int i=0;i<26;++i)
		if (ch[0][i]) 
			q1.push(ch[0][i]),f[ch[0][i]]=0,add(0,ch[0][i]);
	while (!q1.empty())
	{
		v=q1.front(); q1.pop();
		for (int i=0;i<26;++i)
		{
			if (!ch[v][i]) continue;
			u=f[v];
			while (u&&!ch[u][i]) u=f[u];
			f[ch[v][i]]=ch[u][i];
			add(ch[u][i],ch[v][i]);
			q1.push(ch[v][i]);				
		}
	}
}

int add(int x,int y)
{
	a[++tot1].y=y; a[tot1].next=h[x]; h[x]=tot1;
}

int dfs(int x)
{
	l[x]=++tot;
	for (int i=h[x];i!=-1;i=a[i].next)
		dfs(a[i].y);
	r[x]=tot;
}

int update(int x,int d)
{
	for (;x<=tot;x+=x&-x) c[x]+=d;
}

int query(int x)
{
	int re=0;
	for (;x>0;x-=x&-x) re+=c[x];
	return re;
}
