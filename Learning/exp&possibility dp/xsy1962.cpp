#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
double p[MAXN];
double exp,exp2,ans;
int n,m;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%lf",p+i);
	ans=exp=exp2=0;	
	for (int i=1;i<=n;++i)
	{
		ans+=(3*exp+3*exp2+1)*p[i];
		exp2=(exp2+2*exp+1)*p[i];
		exp=(exp+1)*p[i];
	}
	printf("%0.1lf\n",ans);
}
