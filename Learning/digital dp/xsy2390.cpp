#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define MOD 1000000007
using namespace std;
int f[2010][2010];
int a[2010],mi[2010];
char A[2010],B[2010];
int m,d;
ll dfs(int len,int pos,ll num,bool lead,bool limit,bool flag);
ll solve(char *s);
bool check(int pos,int x);
void work();

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%d %d\n",&m,&d);
	scanf("%s %s",&A,&B);
	mi[0]=1;
	memset(f,-1,sizeof(f));
	int len=strlen(B);
	for (int i=1;i<=len;++i) mi[i]=(mi[i-1]*10)%m;
	work();
	int tmp=solve(B),tmp1=solve(A);
	printf("%I64d\n",solve(B)-solve(A));
}

ll dfs(int len,int pos,int num,ll now,bool lead,bool limit,bool flag)
{
	if (pos==0) return now==0&&flag;
	if (!lead&&!limit&&f[pos][now]!=-1) return f[pos][now];
	ll ret=0;
	int up=limit?a[pos]:9;
	if ((!lead||pos==1)&&check(len+1,0)) 
		ret=(ret+dfs(len+1,pos-1,0,num,0,limit&&a[pos]==0,flag||0==d))%MOD;
	else if (lead)
		ret=(ret+dfs(len,pos-1,0,num,1,limit&&a[pos]==0,flag||0==d))%MOD;
	for (int i=1;i<=up;++i)
		if (check(len+1,i))
			ret=(ret+dfs(len+1,pos-1,i,(now+(i*mi[pos-1])%m)%m,0,limit&&i==up,flag||i==d))%MOD;
	if (!lead&&!limit) f[pos][num]=ret;
	return ret;
}

ll solve(char *s)
{
	int len=strlen(s),cnt=0,j=0;
	while (s[j]=='0') ++j;
	if (j==len) return d==0?1:0;
	for (int i=len-1;i>=j;--i)
		a[++cnt]=s[i]-'0';
	return dfs(0,cnt,0,0,1,1,0);
}

void work()
{
	int len=strlen(A),g=0;
	for (int i=len-1;i>=0;--i)
	{
		if (A[i]-'0'-g-(i==len-1?1:0)>=0)
			A[i]=A[i]-g-(i==len-1?1:0),g=0;
		else
			A[i]=A[i]+10-g-(i==len-1?1:0),g=1;
	}
}

bool check(int pos,int x)
{
	if (x==d) return pos%2==0;
	if (x!=d) return true;
}
//前导零到底是什么情况啊喂。。。反正题目搞得有点糊涂就是了。。 
