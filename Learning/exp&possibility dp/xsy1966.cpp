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
//�����������ѧ��qwq
//����Ϊ��Ŀ��˵k����ͬ��λ��װ���ĸ�����һ���ģ�����˵����ʵk�ֲ�ͬ�Ĳ�λ�������ȫһ����
//���ԣ�ֻҪ���һ��Ȼ�����*K�ͺ���
//���̺ܺ�������������һ�����⣬���˳���ƵĻ��ᷢ�֡��������״̬����ͳ��
//Ȼ��о��Ϻ�����Է������������ľ��Ǹо�����qwq������û������Ϊɶ��
//Ȼ��ͷ�������qwq��Ȼ��������ˡ���
//�군���������˻���һ����qwq 
