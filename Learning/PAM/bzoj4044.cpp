//unfinished  T
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=120000;
char s[MAXN];
int ch[MAXN][4],suf[MAXN],len[MAXN],sub[MAXN],q[MAXN]; 
int f[MAXN];
int n,m,tot,last,ans,lens,head,tail;
int change(char x);
int insert(int x,int c);
int find(int x,int now);
int bfs();

int main()
{
	freopen("a.in","r",stdin);
		
	scanf("%d\n",&n);
	for (int o=1;o<=n;++o)
	{
		scanf("%s\n",s);
		lens=strlen(s);
		s[lens]=-1;
		memset(suf,0,sizeof(suf));
		memset(len,0,sizeof(len));
		memset(ch,0,sizeof(ch));
		len[0]=0,len[1]=-1,tot=1,suf[0]=1,last=0;
		for (int i=0;i<lens;++i)
			insert(i,change(s[i]));
		for (int i=2;i<=tot;++i)
			if (len[i]%2) f[i]=len[i];
		ans=lens;
		bfs();		
		printf("%d\n",ans);
	}
}

int change(char x)
{
	if (x=='A') return 0;
	if (x=='C') return 1;
	if (x=='G') return 2;
	return 3;
}

int insert(int x,int c)
{
	int now=find(x,last),tmp;
	if (!ch[now][c])
	{
		len[++tot]=len[now]+2;
		suf[tot]=ch[find(x,suf[now])][c];
		ch[now][c]=tot;
		
		if (len[tot]<=2) sub[tot]=suf[tot];
		else
		{
			tmp=sub[now];
			while (s[x]!=s[x-len[tmp]-1]||(len[tmp]+2)*2>len[tot]) tmp=suf[tmp];
			sub[tot]=ch[tmp][c];
		}
	}
	last=ch[now][c];
}

int find(int x,int now)
{
	while (s[x]!=s[x-len[now]-1]) now=suf[now];
	return now;
}

int bfs()
{
	int v,u;
	head=0,tail=1;
	q[1]=0;
	f[0]=1; //q.push(1);
	do
	{
		v=q[++head];
		for (int i=0;i<4;++i)
		{
			if (!ch[v][i]) continue;
			u=ch[v][i];
			f[u]=min(f[v]+1,len[u]/2-len[sub[u]]+f[sub[u]]+1);
			ans=min(ans,lens-len[u]+f[u]);	
			q[++tail]=u;
		}
	}while (head<tail);
}	
//因为反转的操作是整个串都要反转的，也就是说只能这样省一个回文串，所以只要求出得到每个回文串最少的步数就好了 
