#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
using namespace std;
const int MAXN=1e5;
const int N=1e7;

int main()
{
	freopen("a.in","w",stdout);

	srand(time(NULL));
	int n=1000,m=1000;
	printf("%d %d\n",n,m);
	printf("0 %d\n",rand()%N);
	for (int i=2;i<=n;++i)
	{
		printf("%d %d\n",rand()%(i-1)+1,rand()%N);
	}
	for (int i=1;i<=m;++i)
	{
		int op=rand()%3;
		if (op==0)
			printf("V %d %d\n",rand()%n+1,rand()%N);
		else if (op==1)
			printf("Q %d\n",rand()%n+1);
		else 
			printf("E %d\n",rand()%n+1);
	}
}
