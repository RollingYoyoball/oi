#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
ll f[110][1<<19],mi[20]; 
int a[19];
int m,cnt;
ll n;
ll dfs(int pos,int now,int left,bool lead,bool limit);
ll solve(ll x);
bool check(int x,bool lead,int now);

int main()
{
//	freopen("a.in","r",stdin);

	scanf("%I64d%d\n",&n,&m);
	mi[0]=1;
	int tmp=5|(1<<2-1);
	for (int i=1;i<=18;++i) mi[i]=mi[i-1]*10;
	memset(f,-1,sizeof(f));
	printf("%I64d\n",solve(n));
}

ll dfs(int pos,int now,int left,bool lead,bool limit)
{
	if (pos==0) return left==0;
	if (!limit&&!lead&&f[left][now]!=-1) return f[left][now];
	int up=limit?a[pos]:9;
	ll ret=0;
	int used=0;
	for (int i=1;i<=cnt;++i)
	{
		if (used&(1<<a[i]-1)) continue;
		if (check(i,lead,now))
			ret+=dfs(pos-1,now|(1<<i-1),(left+a[i]*mi[pos-1])%m,0,limit&&a[i]==up),used|=(1<<a[i]-1);
	}	
	if (!limit&&!lead) f[left][now]=ret;
	return ret;
}

ll solve(ll x)
{
	for (cnt=0;x;x/=10) a[++cnt]=x%10;
	return dfs(cnt,0,0,1,1);
}

bool check(int x,bool lead,int now)
{
	if (now&(1<<x-1)) return false;
	if (a[x]==0&&lead) return false;
	return true;
}
