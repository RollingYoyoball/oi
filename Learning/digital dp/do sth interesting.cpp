#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
int work(int x);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

//	for (int i=1;i<=10;++i) work(i);
	for (int i=1;i<=100;++i)
	{
		int tmp=i^(3*i);
		if (tmp==2*i) 
			printf("%d ",i),work(i);
	}
}

int work(int x)
{
	int tmp[1001],cnt=0;
	while (x!=0)
	{
		tmp[++cnt]=x&1;
		x>>=1;
	}
	for (int i=cnt;i>=1;--i)
		printf("%d",tmp[i]);
	printf("\n");
}
