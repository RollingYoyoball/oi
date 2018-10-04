#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	freopen("3.in","r",stdin);
	freopen("a1.out","w",stdout);
	
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	printf("%d %d 1\n",n,m);
	int x,y,z;
	for (int i=1;i<n;++i) scanf("%d%d",&x,&y),printf("%d %d\n",x,y);
	for (int i=1;i<=m;++i) scanf("%d",&x),printf("%d ",x);
	printf("\n");
	for (int i=1;i<=q;++i)
	{
		scanf("%d%d%d\n",&x,&y,&z);
		if (i==38799) {printf("%d %d %d\n",x,y,z);break;}
	}
}
