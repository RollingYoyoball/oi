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
	int n=5;
	for (int i=1;i<=5;++i)
	{
		int m=rand()%10+1;
		printf("%d %0.2lf\n",m,(rand()%75+25)*0.01);
		for (int j=1;j<=m;++j)
			printf("%d ",rand()%100+1);
		printf("\n");
	}
}	
