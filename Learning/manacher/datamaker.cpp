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
	int n=5;
	printf("%d\n",n);
	for (int i=1;i<=n;++i) 
		printf("%d",rand()%2);
	printf("\n");
}
