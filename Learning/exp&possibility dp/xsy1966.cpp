#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
//const int MAXN=1e5;
double f[2][610];
int n,k,now;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d",&n,&k);
	now=0;
	memset(f,0,sizeof(f));
	for (int i=n;i>=1;--i,now^=1)
		for (int j=1;j<=min(i,600);++j)
			f[now][j]=(f[now^1][j]*j/(j+1.0)+j/2.0+(f[now^1][j+1]+j)/(j+1.0))*(1.0/k)+f[now^1][j]*(1-1.0/k);
	printf("%.10lf\n",f[now^1][1]*k);
}
//讲真这题好玄学啊qwq
//嗯因为题目中说k个不同部位的装备的概率是一样的，所以说，其实k种不同的部位情况是完全一样的
//所以，只要算出一种然后最后*K就好了
//方程很好推啦，但是有一个问题，如果顺着推的话会发现。。到最后状态很难统计
//然后感觉上好像可以反过来（这个真的就是感觉上了qwq到现在没想明白为啥）
//然后就反过来了qwq，然后就做完了。。
//完蛋。。做完了还是一脸懵qwq 
