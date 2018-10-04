#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
const int mod=51123987,N=4000010;
 
int f[N];
long long n,l[N],r[N];
char a[N];
 
void getans()
{
    int x,j;
    for (int i=1;i<=n;i++) {
        x=f[i]-1; j=i/2;
        if (i%2) {
            x=x/2;
            l[j-x+1]++; l[j+1]--;
            r[j+1]++; r[j+x+1]--;
        } else {
            x=(x+1)/2;
            l[j-x+1]++; l[j+1]--;
            r[j]++; r[j+x]--;
        }
    }
    n=(n-1)/2;
    for (int i=1;i<=n;i++) {
        l[i]=(l[i-1]+l[i])%mod;
        r[i]=(r[i-1]+r[i])%mod;
    }
    for (int i=1;i<=n;i++) {
        l[i]=(l[i-1]+l[i])%mod;
        r[i]=(r[i-1]+r[i])%mod;
    }
    //for (int i=1;i<=n;i++) printf("%d ",l[i]);
    //printf("\n");
    //for (int i=1;i<=n;i++) printf("%d ",r[i]);
    long long ans=r[n]*(r[n]-1)/2%mod;
    for (int i=1;i<n;i++) ans=(ans-r[i]*(l[i+1]-l[i])%mod+mod)%mod;
    printf("%I64d\n",ans);
}
 
void manacher()
{
    int pos=0,maxright=0;
    for (int i=1;i<=n;i++) {
        if (i<maxright) f[i]=min(f[pos*2-i],maxright-i+1);
        else f[i]=1;
        while (i-f[i]>0&&i+f[i]<=n&&a[i+f[i]]==a[i-f[i]]) f[i]++;
        if (i+f[i]-1>maxright) {
            maxright=i+f[i]-1;
            pos=i;
        }
    }
}
 
int main()
{
	freopen("a.in","r",stdin);
	
    scanf("%I64d",&n);
    scanf("%s",a+1);
    for (int i=n;i;i--) {
        a[i*2]=a[i];
        a[i*2-1]='*';
    }
    n=n*2+1; a[n]='*';
    manacher();
    getans();
    return 0;
}
