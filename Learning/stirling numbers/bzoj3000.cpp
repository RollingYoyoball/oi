#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
#define ld long double
#define eps 1e-10
using namespace std;
const ld pi=acos(-1.0);
const ld e=exp(1);
ll n,k,t;
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
#endif
    ld tmp,tmp1;
    while (scanf("%lld%lld",&n,&k)!=EOF){
        tmp=n;  tmp1=k;
        if (n<=1000){
            tmp=0;
            for (int i=1;i<=n;++i) tmp+=log(i);
            tmp/=log(k);
            tmp=ceil(tmp+eps);
            printf("%lld\n",(ll)tmp);
            continue;
        }
        printf("%lld\n",(ll)(0.5*log(2*pi*tmp)/log(tmp1)+tmp*log(tmp)/log(tmp1)-tmp*log(e)/log(tmp1)+1));
    }
}
