#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500010
using namespace std;
typedef long long ll;
ll n;
char s[N];
int sa[N],rnk[N],cnt[N],t0[N],t1[N];
ll height[N];
void getsa(int m)
{
    int *x=t0,*y=t1;
    for(int i=0;i<m;i++)cnt[i]=0;
    for(int i=0;i<n;i++)cnt[x[i]=s[i]]++;
    for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
    for(int i=n-1;i>=0;i--)sa[--cnt[x[i]]]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=n-k;i<n;i++)y[p++]=i;
        for(int i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
        for(int i=0;i<m;i++)cnt[i]=0;
        for(int i=0;i<n;i++)cnt[x[y[i]]]++;
        for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
        for(int i=n-1;i>=0;i--)sa[--cnt[x[y[i]]]]=y[i];
        swap(x,y);
        p=1,x[sa[0]]=0;
        for(int i=1;i<n;i++)
            x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&sa[i]+k<n&&sa[i-1]+k<n&&y[sa[i]+k]==y[sa[i-1]+k]?p-1:p++;
        if(p==n)break;
        m=p;
    }
}
void getheight()
{
    int k=0;
    for(int i=0;i<n;i++)rnk[sa[i]]=i;
    for(int i=0;i<n;i++)
    {
        if(k!=0)k--;
        if(!rnk[i])continue;
        int j=sa[rnk[i]-1];
        while(s[i+k]==s[j+k])k++;
        height[rnk[i]]=k;
    }
}
ll ans;
int sta[N];
int top;
ll l[N],r[N];
int main()
{
	freopen("a.in","r",stdin);
	
    scanf("%s",s);
    n=strlen(s);
    ans+=(n-1)*(1+n)*n/2;
    getsa(256);
    getheight();
    n--;
    for(int i=1;i<=n;i++)
    {
        while(top&&height[i]<height[sta[top]])r[sta[top--]]=i-1;
        sta[++top]=i;
    }
    while(top)r[sta[top--]]=n;
    for(int i=n;i>=1;i--)
    {
        while(top&&height[i]<=height[sta[top]])l[sta[top--]]=i+1;
        sta[++top]=i;
    }
    while(top)l[sta[top--]]=1;
    for(ll i=1;i<=n;i++)
    {
        ans-=2ll*height[i]*(i-l[i]+1)*(r[i]-i+1); 
    }
    printf("%lld\n",ans);
}
