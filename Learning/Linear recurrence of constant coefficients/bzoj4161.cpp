#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000007
using namespace std;
const int MAXN=2010*2;
int a[MAXN],h[MAXN],tmp[MAXN],chu[MAXN],base[MAXN],ans[MAXN];
int n,k;
void mul(int *a,int *b);
int add(int x,int y){return x+y-(x+y<MOD?0:MOD);}
int mul(int x,int y){return 1LL*x*y%MOD;}
void ksm(int n);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&k);
	for (int i=1;i<=k;++i) scanf("%d",a+i),a[i]=(a[i]+MOD)%MOD;
	for (int i=1;i<=k;++i) scanf("%d",h+i),h[i]=(h[i]+MOD)%MOD;
	for (int i=1;i<=k;++i) chu[k-i]=MOD-a[i];
	chu[k]=1; 
	ksm(n-k+1);
	for (int i=1+k;i<=k-1+k;++i)
		for (int j=1;j<=k;++j)
			//h[i]=add(h[i],mul(h[i-j],a[j]));
			h[i]+=mul(h[i-j],a[j]),h[i]-=h[i]>=MOD?MOD:0;
	int Ans=0;
	for (int i=0;i<k;++i)
		//Ans=add(Ans,mul(h[i+k],ans[i]));
		Ans+=mul(h[i+k],ans[i]),Ans-=Ans>=MOD?MOD:0;
	if (n<k) printf("%d\n",h[n]);
	else printf("%d\n",Ans);
}

void mul(int *a,int *b){
	for (int i=0;i<=k*2-2;++i) tmp[i]=0;
	for (int i=0;i<k;++i)
		for (int j=0;j<k;++j)
			//tmp[i+j]=add(tmp[i+j],mul(a[i],b[j]));
			tmp[i+j]+=mul(a[i],b[j]),tmp[i+j]-=tmp[i+j]>=MOD?MOD:0;

	for (int i=k*2-2;i>=k;--i)
		for (int j=k-1;j>=0;--j)
			//tmp[i-(k-j)]=add(tmp[i-(k-j)],-mul(tmp[i],chu[j]));
			tmp[i-(k-j)]+=MOD-mul(tmp[i],chu[j]),tmp[i-(k-j)]-=tmp[i-(k-j)]>=MOD?MOD:0;

	for (int i=0;i<k;++i) a[i]=tmp[i];
}

void ksm(int n){
	base[1]=1;//base是一个多项式，表示的是特征矩阵M对于p(M)的余数
	ans[0]=1;
	while (n){
		if (n&1) mul(ans,base);
		mul(base,base);
		n>>=1;
	}
}
