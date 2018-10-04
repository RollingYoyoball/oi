#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=2010;
const int N=2000;
ll s[MAXN][MAXN],c[MAXN][MAXN];
int n,m,t,f,b;
int prework();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&t);
	prework();
	for (int o=1;o<=t;++o){
		scanf("%d%d%d",&n,&f,&b);
		--n; --f; --b;
		printf("%lld\n",c[f+b][f]*s[n][f+b]%MOD);
	}
}

int prework(){
	c[0][0]=1;
	for (int i=1;i<=N;++i){
		s[i][0]=0; c[i][0]=1;
		for (int j=1;j<i;++j)
			s[i][j]=((i-1)*s[i-1][j]%MOD+s[i-1][j-1])%MOD,
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
		s[i][i]=1; c[i][i]=1;
	}
}
