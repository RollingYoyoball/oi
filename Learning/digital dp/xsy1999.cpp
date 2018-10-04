#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
ll f[20][20][20],ans[10];
int a[20];
ll l,r;
ll dfs(int pos,int lead,int limit);
ll solve(ll x,int num);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%lld%lld",&l,&r);
	memset(f,-1,sizeof(f));
	for (int i=0;i<=9;++i)
		printf("%lld ",solve(r,i)-solve(l-1,i));
}

ll dfs(int pos,int num,int cnt,int lead,int limit)
{
	int up;
	ll ret=0;
	if (pos==0) return cnt;
	if (f[pos][num][cnt]!=-1&&!limit&&!lead) 
		return f[pos][num][cnt];
	up=limit?a[pos]:9;
	
	if (!lead||pos==1) 
		ret+=dfs(pos-1,num,cnt+(num==0),0,limit&&a[pos]==0);
	else 
		ret+=dfs(pos-1,num,cnt,1,limit&&a[pos]==0);
		
	for (int i=1;i<=up;++i)
		ret+=dfs(pos-1,num,cnt+(num==i),0,limit&&i==up);
	if (!limit&&!lead) f[pos][num][cnt]=ret;
	return ret;
}

ll solve(ll x,int num)
{
	if (x<0) return 0;
	if (x==0) return num==0?1:0;
	int cnt=0;
	for (cnt=0;x;x/=10)
		a[++cnt]=x%10;
	return dfs(cnt,num,0,1,1);
}
