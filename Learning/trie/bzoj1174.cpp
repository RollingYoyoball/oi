#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=12000010;
struct xxx
{
	int cnt,next;
	char ch;
}a[MAXN];
int h[MAXN];
int n,m,tot,now,len;
ll ans;

int main()
{
	freopen("a.in","r",stdin);
	
	memset(h,-1,sizeof(h));
	char ch;
	bool flag;
	scanf("%d\n",&n);
	tot=1; ans=0;
	for (int i=1;i<=n;++i)
	{
		ch=getchar();
		now=1; len=0;
		while (ch!='\n')
		{
			int tmp=h[now];
			flag=false;
			while (tmp!=-1) 
			{
				if (a[tmp].ch==ch) {flag=true; break;}
				tmp=a[tmp].next;
			}
			++len;
			if (flag) 
			{
				now=tmp; ++a[tmp].cnt; 
				ans=max(ans,(ll)a[tmp].cnt*len);
				ch=getchar(); continue;
			}
			a[++tot].ch=ch;
			a[tot].next=h[now];
			h[now]=tot;
			now=tot;
			++a[tot].cnt;
			ans=max(ans,(ll)a[tot].cnt*len);	
			ch=getchar();
		}	
	}	
	printf("%lld\n",ans);
}
