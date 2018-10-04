#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1000010;
const int MAXM=201;
struct xxx
{
	int a[MAXM][MAXM];
}origin,origin1;
char s[201][MAXN];
int next1[MAXN];
int n,m;
xxx work(int b);
xxx mul(xxx a,xxx b);

int main()
{
	freopen("a.in","r",stdin); 

	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%s\n",s[i]);
	for (int i=1;i<=n;++i)
	{
		int k1,k=-1; 
		next1[0]=-1;
		for (int j=1;j<strlen(s[i]);++j)
		{
			while (k!=-1&&s[i][k+1]!=s[i][j]) k=next1[k];
			if (s[i][k+1]==s[i][j]) ++k;
			next1[i]=k;
		}

		for (int j=0;j<n;++j)
		{
			k1=-1;
			for (k=j==i?1:0;k<strlen(s[j]);++k)
			{
				while (k1!=-1&&s[i][k1+1]!=s[j][k]) k1=next1[k1];
				if (s[i][k1+1]==s[j][k]) ++k1;
				
			}	
			origin.a[i][j]=k1;
			origin1.a[i][j]=strlen(s[i])+strlen(s[j]);
		}
	}
	origin=work(m);
	int ans=2147483647;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			if (origin1.a[i][j]-origin.a[i][j]<ans)
				ans=origin1.a[i][j]-origin.a[i][j];
	printf("%d\n",ans);
}

xxx work(int b)
{
	xxx r,r1,aa;
	for (int i=1;i<=n;++i) r.a[i][i]=1,r1.a[i][i]=1;
	while (b)
	{
		if (b&1) r=mul(r,origin),r1=mul(r1,aa);
		aa=mul(aa,aa);
		origin=mul(origin,origin);
		b>>=1;
	}
	memcpy(r1.a,origin1.a,sizeof(origin1.a));
	return r;
}

xxx mul(xxx a,xxx b)
{
	xxx tmp;
	memset(tmp.a,0,sizeof(tmp.a));
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			for (int k=1;k<=n;++k)
				tmp.a[i][j]=tmp.a[i][j]+a.a[i][k]*b.a[k][j];
	return tmp;
}
