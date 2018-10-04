#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
int d;
ll n,k;
ll get2(ll x);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	ll z,w;
	scanf("%d",&d);
	for (int i=1;i<=d;++i){
		scanf("%lld%lld\n",&n,&k);
		z=(k+2)/2; z=n-z;
		w=(k-1)/2;
		if (get2(z)-get2(w)-get2(z-w)>0) printf("0\n");
		else printf("1\n");
	}
}

ll get2(ll x){
	ll ret=0,base=2;
	while (x/base){
		ret+=x/base;
		base<<=1;
	}
	return ret;
}
