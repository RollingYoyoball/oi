#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int m,d,len;
string a,b;
int num[2001];
long long dp[2001][2001];
long long dfs(int pos,int last,bool limit)
{
    if (pos==len) return last==0;
    if (!limit&&dp[pos][last]!=-1) return dp[pos][last];
    long long res=0;
    int up=limit?num[pos]:9;
    for(int i=0;i<=up;i++)
    {
        if (pos%2==0&&i==d) continue;
        if (pos%2==1&&i!=d) continue;
        res=(res+dfs(pos+1,(last*10+i)%m,limit&&i==up))%1000000007ll;
    }
    if(!limit) dp[pos][last] = res;
    return res;
}
long long solve(string str)
{
    int len=str.size(),cnt=0;
    for (int i=0;i<len;i++) num[i]=str[i]-'0';
    return dfs(0,0,true);
}
int find(string str)
{
    int len=str.size(),y=0;
    for  (int i=0;i<len;i++)
    {
        int c=str[i]-'0';
        y=(y*10+c)%m;
        if ((i+1)&1&&c==d) return 0;
        if (i&1&&c!=d) return 0;
    }
    return y==0;
}
int main()
{
//	freopen("a.in","r",stdin);
	
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&m,&d);
    cin>>a>>b; 
    len=a.size();
    int tmp=solve(a);
    int tmp1=solve(b);
    printf("%d",(solve(b)-solve(a)+find(a)+1000000007ll)%1000000007ll);
    return 0;
}
