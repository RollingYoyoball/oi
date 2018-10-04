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
	int n,m,q;
	n=5;
	for (int o=1;o<=5;++o)
	{
		n=rand()%10+1; m=rand()%12+1;
		printf("%d %d\n",n,m);
		for (int i=1;i<=m;++i)
			printf("%d %d\n",rand()%n+1,rand()%n+1);
		q=rand()%5+1;
		printf("%d\n",q);
		for (int i=1;i<=q;++i)
			printf("%d %d\n",rand()%n+1,rand()%n+1);
		printf("\n");
	}
	printf("0 0\n");
}
