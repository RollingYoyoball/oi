#include<iostream>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<ctime>
const int MAXN=100000;
using namespace std;
int fa[MAXN],f[MAXN],a[MAXN];
int n,m;
int get_fa(int x) { if (f[x]!=x) f[x]=get_fa(f[x]); return f[x]; }

int main()
{
	freopen("a.in","w",stdout);
	srand((unsigned)time(NULL));
	
	int order,x,y,xx,yy;
	int dep[MAXN];
	n=20000;
	m=rand()%1000+1;
	memset(fa,-1,sizeof(fa));
	for (int i=0;i<=n;++i) f[i]=i;
	printf("%d\n",n);
	f[1]=0; fa[1]=0; dep[1]=0;
	int tmp=rand()%10000-rand()%20000;
	if (rand()%2==1) tmp=-tmp;
	printf("0 %d %d %d\n",tmp,0,rand()%10000+1);
	for (int i=2;i<=n;++i)
	{
		x=rand()%(i-1)+1;
		y=i;
		xx=get_fa(x);
		yy=get_fa(y);
		while (xx==yy) x=rand()%(i-1)+1,xx=get_fa(x);
		fa[y]=x;
		f[y]=x;	 dep[y]=dep[x]+1;
		tmp=rand()%10000-rand()%20000;
		if (rand()%2==1) tmp=-tmp;
		printf("%d %d %d %d\n",x,tmp,rand()%dep[y],rand()%10000+1);
	}
}
