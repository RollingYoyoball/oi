#include<iostream>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<ctime>
using namespace std;

int main()
{
	freopen("a.in","w",stdout);

	srand(time(NULL));
	int n,m;
	n=rand()%10+1; m=rand()%5+1;
	printf("1\n");
	printf("%d %d %d\n",n,m,rand()%2+1);
	for (int i=1;i<=m;++i)
	{
		int l=rand()%n+1,add=rand()%(n-l+1);
		printf("%d %d ",l,l+add);
		l=rand()%n+1,add=rand()%(n-l+1);
		printf("%d %d ",l,l+add);
		printf("%d\n",rand()%1000+1);	
	}
}
