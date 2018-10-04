#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=2010;
map<int,int> id;
ll c[MAXN][MAXN],f[MAXN][MAXN],g[MAXN],peng[MAXN];
int a[MAXN],v[MAXN];
int n,m,tot;
ll ans; 
void update(int len,int x,ll d);
ll query(int len,int x);

int main()
{
	freopen("a.in","r",stdin);

	int x;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]),v[i]=a[i];
	sort(v+1,v+1+n);
	tot=0;
	for (int i=1;i<=n;id[a[i++]]=tot)
		if (v[i]!=v[i-1]) ++tot;
	for (int i=1;i<=n;++i) a[i]=id[a[i]];
	//sort(a+1,a+1+n,cmp1);
	update(0,1,1); 
	for (int i=1;i<=n;++i)
	{
	//	update(1,a[i].v,1);
	//	f[i][1]=1;
		for (int j=i;j>=1;--j)
		{
			f[i][j]=(f[i][j]+query(j-1,a[i]))%MOD;
			update(j,a[i],f[i][j]);
		}
	}
	//f[i][j]��ʾa[i]��β�ĳ���Ϊj�ķǽ����еĸ��� 
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;++j)
			g[i]=(g[i]+f[j][i])%MOD;
	peng[0]=1;
	for (int i=1;i<=n;++i) peng[i]=(peng[i-1]*i)%MOD;
	ans=0;
	for (int i=1;i<=n;++i)
	{
		ans=(ans+(g[i]*peng[n-i]%MOD)+MOD-(peng[n-(i+1)]*((g[i+1]*(i+1))%MOD))%MOD)%MOD;
		//����һ������Ϊi�ķǽ����У�һ������ԭ����ɾ����ĳЩ���õ��ģ���ôö������ɾ�����̿���֪��
		//һ���ǽ����ж��ڴ𰸵Ĺ�����g[i]*(n-i)!
		//���ǣ��������������������ģ����Կ��ܻ���ֵ�ǰ�Ѿ���һ���ǽ������˵����
		//���ʱ��������˵Ӧ��ֹͣ�����ǲ�û��ֹͣö�٣����Ի����
		//ͬʱ��Ҳ���ܶ����˳���Ϊi+1����������ö�ٵ������
		//��ˣ�ֻҪ�ǿ��Դ�i+1ת�ƹ����ģ������ǺϷ����ǷǷ�����Ӧ�ñ���ȥ 
		//ÿ������Ϊi+1�����У�����i+1�ַ�ʽɾ��һ�������i�����У�Ȼ���ܹ���peng[n-i-1]*g[i+1]��i+1������ 
	}
	printf("%lld\n",ans);
}

void update(int len,int x,ll d)
{
	for (;x<=tot;x+=x&-x)
		c[len][x]=(c[len][x]+d)%MOD;
}

ll query(int len,int x)
{
	ll ret=0;
	for (;x;x-=x&-x)
		ret=(ret+c[len][x])%MOD;
	return ret;
}
