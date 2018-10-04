//test???
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int v[210];
double f[2][210][410],p[210];
int n,K,l,now,pre;
int change(int x);

int main()
{
	freopen("a.in","r",stdin);
	
	int x;
	scanf("%d%d%d",&n,&l,&K);
	for (int i=1;i<=n;++i)
		scanf("%d",&x),p[i]=(double)x/100;
	for (int i=1;i<=n;++i)
		scanf("%d",v+i);
	memset(f,0,sizeof(f));
	K=min(K,n);
	pre=0,now=1;
	f[0][0][change(K)]=1; 
	for (int i=1;i<=n;++i)
	{
		for (int j=0;j<=i+1;++j)
			for (int k=-n;k<=n;++k)
			{
				if (j>0) f[now][j][change(k)]+=f[pre][j-1][change(k-v[i])]*p[i];
				f[now][j][change(k)]+=f[pre][j][change(k)]*(1-p[i]);
			}
		/*	{
				f[now][j][change(k)]+=f[pre][j][change(k)]*(1-p[i+1]);
				f[now][j+1][change(k+v[i+1])]+=f[pre][j][change(k)]*p[i+1];
			}*/
		swap(pre,now);
		memset(f[now],0,sizeof(f[now]));
	}
	double ans=0;
	for (int i=l;i<=n;++i)
		for (int j=0;j<=n;++j)
			ans+=f[pre][i][change(j)];
	printf("%0.6lf\n",ans);	
}

int change(int x)
{
	if (x>n) return n+n;
	if (x<-n) return 0;
	return x+n;
}
//所以说。。概d好像。。正着考虑会比较好？？？嗯因为如果用注释掉的写法只有30分。。真棒棒qwq
//肯定是漏掉了奇妙情况qwq
//好的，因为这里设定是n为上限，所以，j=n的情况其实统计到的是n~很多很多
//所以，这个时候顺推就很难枚举是从哪一步转移过来的了 
