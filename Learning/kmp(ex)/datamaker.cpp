#include<iostream>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<ctime>
using namespace std;

int main()
{
	freopen("a.in","w",stdout);
	
	int n=10;
	srand(time(NULL));
	printf("%d\n",n);
	for (int i=1;i<=n;++i)
	{
		int x=rand()%100000+1;
		for (int j=1;j<=x;++j)
			printf("%d",rand()%10);
		printf("\n");
	}
}
