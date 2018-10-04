#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int f[32][32];
int a[32];
int l,r;
int dfs(int pos,int num,bool lead,bool limit);
int solve(int x);
int abs(int x) {return x>0?x:-x;}

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d",&l,&r);
	memset(f,-1,sizeof(f));
	printf("%d\n",solve(r)-solve(l-1));	
}

int solve(int x)
{
	if (x<0) return 0;
	if (x==0) return 0;
	int cnt;
	for (cnt=0;x;x/=10)
		a[++cnt]=x%10;
	return dfs(cnt,0,1,1);
}

int dfs(int pos,int num,bool lead,bool limit)
{
	if (pos==0) return 1;
	if (!limit&&!lead&&f[pos][num]!=-1) return f[pos][num];
	int up=limit?a[pos]:9,ret=0;
	if ((!lead||pos==1)&&num>=2) ret+=dfs(pos-1,0,0,limit&&a[pos]==0);
	else if (lead&&pos!=1) ret+=dfs(pos-1,0,1,limit&&a[pos]==0);
	for (int i=1;i<=up;++i)
		if (abs(i-num)>=2||lead)
			ret+=dfs(pos-1,i,0,limit&&i==up);
	if (!limit&&!lead) f[pos][num]=ret;
	return ret;
}
