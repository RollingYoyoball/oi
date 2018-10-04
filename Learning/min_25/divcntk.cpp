#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int SQRTN=100005;
bool vis[SQRTN];
ll p[SQRTN],pcnt;
ll n,k,sqrtn;
int m;
ll a[SQRTN*2],cnt;
int pos1[SQRTN],pos2[SQRTN];
ull g[SQRTN*2];
void prework(){/*{{{*/
	for(int i=2;i<SQRTN;i++){
		if(!vis[i])
			p[++pcnt]=i;
		for(int j=1;j<=pcnt&&i*p[j]<SQRTN;j++){
			int x=i*p[j];
			vis[x]=true;
			if(i%p[j]==0) break;
		}
	}
}/*}}}*/
int gp(ll x){//getpos{{{
	return x<=sqrtn?pos1[x]:pos2[n/x];
}
void Discretization(){
	for(ll i=1,j;i<=n;i=j+1){
		a[++cnt]=n/i;
		j=n/(n/i);
	}
	reverse(a+1,a+1+cnt);
	for(int i=1;i<=cnt;i++)
		if(a[i]<=sqrtn) pos1[a[i]]=i;
		else pos2[n/a[i]]=i;
}/*}}}*/
void calc_g(){
	for(int i=1;i<=cnt;i++) g[i]=a[i]-1;
	for(int j=1;j<=m;j++)
		for(int i=cnt;i>=1&&a[i]>=p[j]*p[j];i--)
			g[i]-=g[gp(a[i]/p[j])]-g[gp(p[j]-1)];
}
ull calc_h(ll i,ll j){
	if(i<=1) return 0;
	ull res=0;
	int a;
	for(a=j;a<=m&&p[a]*p[a]<=i;a++)
		for(ll pe=p[a],e=1;pe<=i;pe*=p[a],e++)
			res+=(ull)(e*k+1)*(calc_h(i/pe,a+1)+1);
	if(p[a-1]<=i) 
		res+=(ull)(k+1)*(g[gp(i)]-g[gp(p[a-1])]);
	return res;
}
int main(){
	freopen("input.in","r",stdin);
	prework();
	scanf("%lld%lld",&n,&k);
	sqrtn=(ll)sqrt(n);	
	m=upper_bound(p+1,p+1+pcnt,sqrtn)-p-1;
	Discretization();
	calc_g();
	ull ans=calc_h(n,1)+1;
	printf("%llu\n",ans);
	return 0;
}
