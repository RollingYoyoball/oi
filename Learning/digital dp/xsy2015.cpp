#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define ll long long
#define MOD 20120427
const int aa[5]={0,2,3,5,7};
using namespace std;
map<int,int> id;
//int id[1010];
ll f[20][10];
int a[20];
ll mi[20];
ll n,k,A,B,tot;
//void get_num(ll x,ll last,ll s);
int get_num(int pre,ll x,ll s);
ll dfs(int pos,ll sum,ll mul,bool lead,bool limit);
ll solve(ll x);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%lld",&n);
	get_num(1,1,1);
	mi[0]=1;
	for (int i=1;i<=18;++i) mi[i]=mi[i-1]*10;
	for (int i=1;i<=n;++i)
	{
		memset(f,-1,sizeof(f));
		scanf("%lld%lld%lld",&A,&B,&k);
		ll tmp=solve(B),tmp1=solve(A-1);
		printf("%lld\n",(solve(B)-solve(A-1)+MOD)%MOD);
	}
}

ll dfs(int pos,ll sum,ll mul,bool lead,bool limit)
{
	if (pos==0&&mul==k) return sum;
	else if (pos==0) return 0;
	int tmp111=id[mul];
    if (!lead&&!limit&&f[pos][id[mul]]!=-1) return f[pos][id[mul]];
	int up=limit?a[pos]:9;
	ll ret=0;
	if (!lead||pos==1)
	{
		if (k==0) ret+=dfs(pos-1,sum,0,0,limit&&a[pos]==0);
	}
	else ret+=dfs(pos-1,sum,mul,1,limit&&a[pos]==0);
	
	for (int i=1;i<=up;++i)
		if (mul*i<=k)
			ret+=dfs(pos-1,(sum+i*mi[pos-1]%MOD)%MOD,mul*i,0,limit&&i==up);
	if (!lead&&!limit) f[pos][id[mul]]=ret;
	return ret;
}

ll solve(ll x)
{
	if (x<=0) return 0;
	int cnt=0;
	for (;x;x/=10) a[++cnt]=x%10;
	return dfs(cnt,0,1,1,1);	
}

int get_num(int pre,ll x,ll s)
{
	if (x>=1000000000000000000||s>=1000000000000000000)
    //if (x>=1000||s>=1000)//	
		return 0;
	id[x]=s;	++tot;	
	ll tmp;
	for (int i=pre;i<=4;++i)
	{
		tmp=x;
		if (tmp&&tmp%10*aa[i]<=9) tmp=tmp/10*10+tmp%10*aa[i];
		else tmp=tmp*10+aa[i];
		get_num(i,tmp,s*aa[i]);
	}
}


/*void get_num(ll x,ll last,ll s)
{
    //if(x>=1000000000000000000ll||s>=1000000000000000000ll)
//  if(s>=1000000000000000000ll)
	if (x>=1000||s>=1000)
        return;
    id[x]=s; ++tot;
    ll i;
    for(i=last;i<=4;i++)
    {
        ll v=x;
        if(v&&v%10*aa[i]<=9)
        {
            if(v>=90000000000000000ll)
                continue;
            v=v/10*10+v%10*aa[i];
        }
        else
            v=v*10+aa[i];
        get_num(v,i,s*aa[i]);
    }
}*/
