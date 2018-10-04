#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,cnt;
bool mark[1000];
int work(int x);

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);

/*	int x=1;
	memset(mark,false,sizeof(mark));
	for (;x<128;x*=2) mark[x]=true;
	cnt=0;
	for (int i=1;i<=10;++i)
	{
		int tmp=i^(3*i);
		if (tmp==2*i) 
			printf("%d\n",i),++cnt;
	//	if (mark[i]) printf("%d\n",cnt);
	}
	//printf("%d\n",cnt);
	cnt=0;
	long long tmp=50000000,ahaha=1;
	while (ahaha<tmp) ++cnt,ahaha*=2;
	printf("%d\n",cnt);*/
	
}

/*int work(int x)
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
}*/
