#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long 
using namespace std;
const int MAXN=300010;
int ch[MAXN][26],suf[MAXN],len[MAXN],cnt[MAXN];
char s[MAXN];
int n,m,tot,last;
ll ans;
int init();
int insert(int x,int c); 
int find(int x,int now);
int work(int x);

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%s\n",s);
	int lens=strlen(s);
	init();
	for (int i=0;i<lens;++i) 
		insert(i,s[i]-'a');
	for (int i=tot;i>=1;--i)
		cnt[suf[i]]+=cnt[i];
	for (int i=2;i<=tot;++i)
		ans=max(ans,(ll)len[i]*cnt[i]);
	printf("%lld\n",ans);
}

int init()
{
	len[0]=0; len[1]=-1; suf[0]=1; tot=1;
}

int insert(int x,int c)
{
	int now=find(x,last);
	if (!ch[now][c])
	{
		len[++tot]=len[now]+2;
		cnt[tot]=0;
		suf[tot]=ch[find(x,suf[now])][c];
		ch[now][c]=tot;	//这句一定要放在找完suf之后再写，不然的话suf可能会找回自己然后就会出现奇妙死循环情况 
	}
	last=ch[now][c];
	++cnt[last];
}

int find(int x,int now)
{
	while (s[x]!=s[x-len[now]-1]) 
		now=suf[now];
	return now;
}
