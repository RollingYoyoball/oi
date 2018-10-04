#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
ll f[20][4];
int a[20];
ll l,r,T,k,mid;
ll solve(ll x);
ll dfs(int pos,int num,int limit);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&T);
	for (int o=1;o<=T;++o)
	{
		scanf("%lld",&k);
		memset(f,-1,sizeof(f));
		l=666,r=66666666666;
	//	ll tmp=solve(r);
		while (l<r)
		{
			mid=l+r>>1;
			if (solve(mid)<k)
				l=mid+1;
			else r=mid;
		}
		printf("%lld\n",l);
	}
}

ll dfs(int pos,int num,int limit)
{
	if (pos==0) return num==3;
	if (!limit&&f[pos][num]!=-1) return f[pos][num];
	int up=limit?a[pos]:9;
	ll ret=0;
	for (int i=0;i<=up;++i)
	{
		if (num!=3&&i==6)
			ret+=dfs(pos-1,num+1,limit&&i==up);
		else 
			ret+=dfs(pos-1,num==3?3:0,limit&&i==up);
	}
	if (!limit) f[pos][num]=ret;
	return ret;
}

ll solve(ll x)
{
	int cnt=0;
	for (;x;x/=10) a[++cnt]=x%10;
	return dfs(cnt,0,1);
}
