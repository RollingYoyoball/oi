#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=200010*2;
int s[MAXN];
int sa[MAXN],a[MAXN],b[MAXN],c[MAXN],rk[MAXN];
int m,cnt,mx,N;
void get_sa(int n);
void sort(int n);
bool cmp(int x,int y,int len,int *r)
{return r[x]==r[y]&&r[x+len]==r[y+len];}
int work();

int main()
{
	//freopen("a.in","r",stdin);

	scanf("%d",&N);
	for (int i=1;i<=N;++i)
		scanf("%d",&s[i]),mx=max(mx,s[i]);
	scanf("%d",&m);
	for (int i=1;i<=m;++i)
		scanf("%d",&s[i+N+1]),mx=max(mx,s[i+N+1]);
	s[N+1]=mx+1;
	s[N+m+2]=mx+1;
	++mx;
	get_sa(N);
	work();
}

void get_sa(int n)
{
	for (int i=1;i<=n;++i) b[i]=i,a[i]=s[i];//b��ʵ����a����ʱ�����������±�λ�� 
	sort(n);//����Ԥ������һ�ε�sa 
	for (int l=1;cnt<n;l*=2)
	{
		cnt=0;
		for (int i=n-l+1;i<=n;++i) b[++cnt]=i;
		for (int i=1;i<=n;++i)
			if (sa[i]>l)
				b[++cnt]=sa[i]-l;//������for�ŵ��ǵڶ��ؼ��֣�b�������������Ϊl�Ĵ��ϲ�֮�󣬰��պ����Ǹ��Ĵ�С��Ҳ������һ����sa����������ŵ�i�Ĵ��Ŀ�ʼλ�������� 
		sort(n);//���ﰴ�յ�һ�ؼ������� 
		swap(a,b);
		cnt=1;
		a[sa[1]]=1;
		for (int i=2;i<=n;a[sa[i++]]=cnt)
			if (!cmp(sa[i],sa[i-1],l,b)) ++cnt;	//�������أ����±�ţ�a�������Ǳ�� 
		mx=cnt;
	}
}

void sort(int n)//����������� 
{
	for (int i=0;i<=mx;++i) c[i]=0;
	for (int i=1;i<=n;++i) c[a[b[i]]]++;
	for (int i=1;i<=mx;++i) c[i]+=c[i-1];
	for (int i=n;i>=1;--i) sa[c[a[b[i]]]--]=b[i];
}

int work()
{
	for (int i=1;i<=N+m+1;++i) rk[sa[i]]=i;
	int p1=1,p2=N+2,cnt=0;
	while (p1<=N&&p2<=N+m+1)
	{
		if (rk[p1]<rk[p2]) printf("%d ",s[p1]),++p1;
		else printf("%d ",s[p2]),++p2;
	}
	if (p1<=N) for (int i=p1;i<=N;++i) printf("%d ",s[i]);
	else for (int i=p2;i<=N+m+1;++i) printf("%d ",s[i]);
}

int get_height()
{
	int k=0,j;
	for (int i=1;i<=n;++i) rank[sa[i]]=i;
	for (int i=1;i<=n;height[rank[i++]]=k;)
	{
		if (k>0) --k; j=sa[rank[i]-1];
		while (s[j+k]==s[i+k]) ++k;
	}
}//height[i]=��i��i-1��suffix�������ǰ׺�ĳ���
