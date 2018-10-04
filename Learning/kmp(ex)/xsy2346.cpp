#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100010;
struct xxx
{
	int id,cnt;
}b[MAXN];
char s[MAXN],t[MAXN];
int nxt[MAXN],ex[MAXN];
int lens,lent,ans;
int get_nxt();
bool cmp(xxx x,xxx y) {return x.id<y.id;}

int main()
{
	freopen("a.in","r",stdin);

	scanf("%s\n",t);
	lent=strlen(t);
	lens=0;
	get_nxt();
	printf("%d\n",ans);
	for (int i=lent;i>=1;--i)
		b[i].cnt+=b[i+1].cnt;
	for (int i=1;i<=lent;++i)
		if (b[i].id) 
			printf("%d %d\n",b[i].id,b[i].cnt);
}

int get_nxt()
{
	int j=-1,p=0,a=0;
	nxt[0]=lent;
	++b[nxt[0]].cnt; b[nxt[0]].id=nxt[0];
	++ans;
	for (int i=1;i<lent;++i,--j)
	{
		if (j<0||i+nxt[i-a]>=p)
		{
			if (j<0)
				p=i,j=0;
			while (p<lent&&t[j]==t[p])
				++p,++j;
			nxt[i]=j;
			a=i;
		}
		else 
			nxt[i]=nxt[i-a];
		++b[nxt[i]].cnt;
		if (i+nxt[i]==lent) b[nxt[i]].id=nxt[i],++ans;
	}
}

