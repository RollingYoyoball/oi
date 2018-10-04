#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=2000010;
struct xxx
{
	int y,next;
}a[MAXN];
queue<int> q;
int ch[MAXN][26],f[MAXN],dep[MAXN],re[MAXN],h[MAXN];
int l[MAXN],r[MAXN],id[MAXN],fa[MAXN][22];
int c[MAXN*4];
int n,m,tot1,tot;
int insert(char *s,int xx);
int get_f();
int update(int x,int d);
int query(int x);
int get_lca(int x,int y);
int add(int x,int y);
int dfs(int fa,int x,int d);
bool cmp(int x,int y) {return dep[x]<dep[y];}

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	char s[MAXN];
	for (int i=1;i<=n;++i)
	{
		scanf("%s",s);
		insert(s,i);
	}	
	tot1=0; tot=0;
	memset(h,-1,sizeof(h));
	get_f();
	dfs(0,0,0);

	int op,x,len;
	scanf("%d\n",&m);
	int ttmp[110];//!!
	memset(ttmp,0,sizeof(ttmp));
	
	for (int i=1;i<=m;++i)
	{
		scanf("%d ",&op);
		if (op==2)
		{
			scanf("%d\n",&x); 
			printf("%d\n",query(r[id[x]])-query(l[id[x]]-1));
		}
		else
		{
			scanf("%s\n",s);
			len=strlen(s); x=0;
			re[0]=0;
			for (int j=0;j<len;++j)
			{
				while (x&&!ch[x][s[j]-'a']) x=f[x];
				if (ch[x][s[j]-'a']) x=ch[x][s[j]-'a'];
				++ttmp[l[x]];
				update(l[x],1); re[++re[0]]=x;
			}	
			sort(re+1,re+1+re[0],cmp);
			for (int j=2;j<=re[0];++j)
			{
				int tmp=get_lca(re[j],re[j-1]);
				--ttmp[l[tmp]];
				update(l[get_lca(re[j],re[j-1])],-1);	
			}
		}
	}
}

int insert(char *s,int xx)
{
	int now=0,len=strlen(s);
	for (int i=0;i<len;now=ch[now][s[i]-'a'],++i)
		if (!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++tot;
	id[xx]=now;
}

int get_f()
{
	int v,u;
	for (int i=0;i<26;++i)
		if (ch[0][i]) q.push(ch[0][i]),f[ch[0][i]]=0,add(0,ch[0][i]);
	while (!q.empty())
	{
		v=q.front(); q.pop();
		for (int i=0;i<26;++i)
		{
			if (!ch[v][i]) continue;
			u=f[v];
			while (u&&!ch[u][i]) u=f[u];
			f[ch[v][i]]=ch[u][i];
			add(ch[u][i],ch[v][i]);
			q.push(ch[v][i]);	
		}
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa1,int x,int d)
{
	l[x]=++tot1; dep[x]=d;
	fa[x][0]=fa1;
	for (int i=1;i<=21;++i) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=h[x];i!=-1;i=a[i].next)
		dfs(x,a[i].y,d+1);
	r[x]=tot1;
}

int update(int x,int d)
{
	for (;x<=tot1;x+=x&-x) c[x]+=d;
}

int query(int x)
{
	int ret=0;
	for (;x>0;x-=x&-x) ret+=c[x];
	return ret;
}

int get_lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=21;i>=0;--i)
		if (dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=21;i>=0;--i)
		if (fa[x][i]!=fa[y][i]) 
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
