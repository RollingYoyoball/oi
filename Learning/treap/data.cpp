#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<stdlib.h>
using namespace std;

int main()
{
	freopen("a.in","w",stdout);

	srand(time(NULL));
	int n=100000,m=500000;
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;++i)
	{
		int op=rand()%2;
		if (op)
		{
			printf("C %d %d %d\n",rand()%n+1,rand()%n+1,rand()%n+1);
		}
		else 
		{
			int st=rand()%n+1,add=rand()%(n-st+1);
			printf("Q %d %d\n",st,st+add);
		}
	}
}
