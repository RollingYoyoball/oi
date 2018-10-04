#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<stdlib.h>
using namespace std;
const int MAXN=1e5+10;
const int MAXM=1000000000;

int main()
{
	freopen("a.in","w",stdout);
	
	srand(time(NULL));
	int task=rand()%5; 
	int cnt[2];
	for (int o=1;o<=task;++o)
	{
		int n=10;
		printf("%d\n",n);
		memset(cnt,0,sizeof(cnt));
		for (int i=1;i<=n;++i)
		{
			int op=rand()%3;
			if (!cnt[1]&&!cnt[0]) op=op==1?0:op;
			if (op==0)
			{
				int op1=rand()%2;
				printf("push %c ",'A'+op1);
				printf("%d\n",rand()%1000+1);
				++cnt[op1];
			}
			else if (op==1)
			{
				int op1=rand()%2;
				if (cnt[op1]==0) op1=op1^1;
				printf("pop %c\n",'A'+op1);
				--cnt[op1];
			}
			else
			{
				if (rand()%2)
					printf("merge A B\n"),cnt[0]+=cnt[1],cnt[1]=0;
				else printf("merge B A\n"),cnt[1]+=cnt[0],cnt[0]=0;
			}
		}
	}
	printf("0\n");
}
