#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define MOD 1000000007
using namespace std;
ll f[2010][2010];
ll a[2010],mi[2010];
int m,d;
char A[2010],B[2010];
ll dfs(int len,int pos,int left,bool limit);
ll solve(char *s);
bool check(int pos,int x);
bool add(char *s);
int work(int x);

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	
	scanf("%d%d\n",&m,&d);
	scanf("%s\n%s\n",A,B);
	mi[0]=1;
	for (int i=1;i<=18;++i) mi[i]=mi[i-1]*10;
	memset(f,-1,sizeof(f));
//	printf("\n");
//	int tmp1=solve(A);
//	int tmp=solve(B);
 	printf("%I64d\n",(solve(B)-solve(A)+add(A)+MOD)%MOD);//可否为0？ 
}

ll dfs(int len,int pos,int left,bool limit)
{
	if (pos==0) return left==0;
	if (!limit&&f[pos][left]!=-1) return f[pos][left];
	int up=limit?a[pos]:9;
	ll ret=0;
	
	if (len%2&&d<=up) 
		ret=(ret+dfs(len+1,pos-1,(left+d*mi[pos-1])%m,limit&&d==up))%MOD;

	for (int i=0;i<=up&&len%2!=1;++i)
		if (i!=d)
			ret=(ret+dfs(len+1,pos-1,(left+i*mi[pos-1])%m,limit&&i==up))%MOD;
	if (!limit) f[pos][left]=ret;
	return ret;
}

ll solve(char *s)
{
	int lens=strlen(s),cnt=0;
	for (int i=lens-1;i>=0;--i)
		a[++cnt]=s[i]-'0';
	return dfs(0,cnt,0,1);
}

bool check(int pos,int x)
{
	if (pos%2==0) return x==d;
	if (x==d) return pos%2==0;
	return true;
}

bool add(char *s)
{
	int lens=strlen(s),left=0;
	bool flag=true;
	for (int i=0;i<lens;left=(left*10+s[i++]-'0')%m)
		if (!check(i+1,s[i]-'0')) flag=false;
	return flag&&left==0;
}
//cf上好像并没有过。。。绝望qwq回去调吧qwq 
