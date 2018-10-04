#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a2.out","w",stdout);
	
	int x,y,n,cnt=0;
	scanf("%d",&n);
	for (int i=1;i<n;++i) 
		scanf("%d%d",&x,&y);
	for (int i=1;i<=n;++i) scanf("%d",&x);
	scanf("%d",&n);
	char s[10];
	for (int i=1;i<=n;++i)
	{
		scanf("%s %d%d",s,&x,&y);
		if (s[0]!='C') ++cnt;
		if (cnt==347) {printf("%d ",i); break;}
	}
}
