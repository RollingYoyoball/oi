#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	freopen("a.in","w",stdout);
	
	int n=10;
	srand(time(NULL));
	for (int i=1;i<=10;++i) printf("%c",'a'+rand()%2);
	printf("\n5\n");
	for (int i=1;i<=5;++i)
	{
		int l=rand()%9+1,l1=rand()%9+1;
		printf("%d %d %d %d\n",l,l+rand()%(10-l),l1,l1+rand()%(10-l1));
	}
}
