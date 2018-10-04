#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=21;//!!!
struct xxx
{
	int a[MAXN][MAXN];
}f,A;
int n,m,K,len;
int next1[MAXN];
char s[MAXN]; 
xxx mul(xxx a,xxx b);
xxx ksm(xxx a,int b);

int main()
{
	freopen("a.in","r",stdin);
	
	int j=-1;
	scanf("%d%d%d\n",&n,&m,&K);
	scanf("%s\n",s);
	memset(next1,0,sizeof(next1));
	next1[0]=-1;
	for (int i=1;i<m;++i)
	{
		while (j!=-1&&s[j+1]!=s[i]) j=next1[j];
		if (s[j+1]==s[i]) ++j;
		next1[i]=j;
	}	
	f.a[0][0]=1;
	for (int i=-1;i<m-1;++i)
		for (int j=0;j<=9;++j)
		{
			int tmp=i;
			while (tmp!=-1&&s[tmp+1]-'0'!=j) tmp=next1[tmp];
			if (s[tmp+1]-'0'==j) A.a[i+1][tmp+2]=(A.a[i+1][tmp+2]+1)%K;
			else A.a[i+1][0]=(A.a[i+1][0]+1)%K;
		}	
	A=ksm(A,n);
	f=mul(f,A);
	int ans=0;
	for (int i=0;i<m;++i)
		ans=(ans+f.a[0][i])%K;
	printf("%d\n",ans);
}

xxx mul(xxx a,xxx b)
{
	xxx tmp;
	memset(tmp.a,0,sizeof(tmp.a));
	for (int i=0;i<m;++i)
		for (int j=0;j<m;++j)
			for (int k=0;k<m;++k)
			{
				tmp.a[i][j]=(tmp.a[i][j]+(a.a[i][k]*b.a[k][j])%K)%K;
			}
	return tmp;
}

xxx ksm(xxx a,int b)
{
	xxx r;
	memset(r.a,0,sizeof(r.a));
	for (int i=0;i<=m;++i) r.a[i][i]=1;
	while (b)
	{
		if (b&1) r=mul(r,a);
		a=mul(a,a);
		b>>=1;
	}
	return r;
}
