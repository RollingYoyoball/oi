#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
const int MOD=1000000000+7;
int next1[MAXN];
char s[MAXN],a[MAXN];
int pre[MAXN];
ll f[MAXN],sum[MAXN];
int n,m,tot;
 
int main()
{
	freopen("a.in","r",stdin);
	
    scanf("%s\n%s\n",s,a);
    n=strlen(s);
    m=strlen(a);
    next1[0]=-1;
    int j=-1;
    for (int i=1;i<m;++i)
    {
        while (j!=-1&&a[j+1]!=a[i]) j=next1[j];
        if (a[j+1]==a[i]) ++j;
        next1[i]=j;
    }   
    pre[0]=0;
    j=-1,tot=0;
    for (int i=0;i<n;++i)
    {
        while (j!=-1&&a[j+1]!=s[i]) j=next1[j];
        if (a[j+1]==s[i]) ++j;
        if (j==m-1)
        {
            pre[i+1]=i+1;
            j=next1[j];
        }
        else pre[i+1]=pre[i];   
    }
    sum[m-1]=0; f[m-1]=0;
    for (int i=m;i<=n;++i)
    {
        f[i]=f[i-1];
        if (pre[i]) f[i]=(f[i]+sum[pre[i]-m]+pre[i]-m+1)%MOD;
        sum[i]=(sum[i-1]+f[i])%MOD;
    }
    printf("%d\n",f[n]);
}
