#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500000+10;
int a[MAXN];
int n,m,ans,tp;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",a+i);
	ans=n;
	sort(a+1,a+1+n);
	for (int i=n/2;i>=1;--i)
		if (a[ans]>=a[i]*2) --ans;
	printf("%d\n",ans);
}
//�������̰��������԰����֮��ǰ����һ���ǵ�ǰ���ϴ���Ӹ��ϴ�ģ���С���Ӹ���С�� 
