#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct xxx
{
	double a[4][4];
}origin,f;
int a[30];
double p;
int n,pre;
xxx ksm(int b);
xxx mul(xxx a,xxx b);

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);

	int x;
	xxx tmp;
	while (scanf("%d%lf\n",&n,&p)!=EOF)
	{
		memset(origin.a,0,sizeof(origin.a));
		origin.a[1][2]=1; origin.a[1][1]=p; origin.a[2][3]=1; origin.a[2][1]=1-p;
		memset(f.a,0,sizeof(f.a));
		f.a[1][1]=1; f.a[1][2]=0; 
		for (int i=1;i<=n;++i) scanf("%d",a+i);
		sort(a+1,a+1+n);
		a[0]=1;
		for (int i=1;i<=n;++i)
		{
			tmp=ksm(a[i]-a[i-1]);
			f=mul(f,tmp);
			f.a[1][1]=0;
		}
		if (a[n]!=100000000&&n!=0) f=mul(f,origin);
	//	tmp=ksm(100000000-a[n]);
	//	f=mul(f,tmp);
		printf("%0.7lf\n",f.a[1][1]);
			
	}
}

xxx ksm(int b)
{
	xxx r,aa=origin;
	memset(r.a,0,sizeof(r.a));
	for (int i=1;i<=3;++i) r.a[i][i]=1;
	while (b)
	{
		if (b&1) r=mul(r,aa);
		aa=mul(aa,aa);
		b>>=1;
	}
	return r;
}

xxx mul(xxx a,xxx b)
{
	xxx tmp;
	memset(tmp.a,0,sizeof(tmp.a));
	for (int i=1;i<=3;++i)
		for (int j=1;j<=3;++j)
			for (int k=1;k<=3;++k)
				tmp.a[i][j]+=a.a[i][k]*b.a[k][j];
	return tmp;
}
