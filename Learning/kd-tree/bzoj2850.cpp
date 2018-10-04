#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=5*(1e4)+10;
int D;
struct dian{
	ll data[2];
	ll val;
	friend bool operator <(dian x,dian y)
	{return x.data[D]<y.data[D];}
}a[MAXN];
ll n,m,A,B,C,ans,cnt;
struct kdtree{
	int lch[MAXN],rch[MAXN],mnx[MAXN],mny[MAXN],mxx[MAXN],mxy[MAXN];
	ll sum[MAXN];
	int rt;
	int update(int x,int d){
		sum[x]+=sum[d]; 
		mnx[x]=min(mnx[x],mnx[d]); mny[x]=min(mny[x],mny[d]);
		mxx[x]=max(mxx[x],mxx[d]); mxy[x]=max(mxy[x],mxy[d]);
	}
	int pushup(int x){
		sum[x]=a[x].val;
		mnx[x]=mxx[x]=a[x].data[0];
		mny[x]=mxy[x]=a[x].data[1];
		if (lch[x]) update(x,lch[x]);
		if (rch[x]) update(x,rch[x]);
	}
	int build(){rt=_build(1,n,0);}
	int _build(int l,int r,int now){
		if (l>r) return 0;
		int mid=l+r>>1;
		D=now;
		nth_element(a+l,a+mid,a+r+1);
		lch[mid]=_build(l,mid-1,now^1);
		rch[mid]=_build(mid+1,r,now^1);
		pushup(mid);
		return mid;
	}
	bool ok(int x,int y){
		return (ll)A*x+(ll)B*y<C;
	}
	int check(int x){//注意是int不是bool Q^Q一个下午的调试啊啊啊啊！！哭瞎了qwq
		int ret=0;
		ret+=ok(mnx[x],mny[x]);
		ret+=ok(mnx[x],mxy[x]);
		ret+=ok(mxx[x],mny[x]);
		ret+=ok(mxx[x],mxy[x]);
		return ret;
  	}
	int query(){_query(rt);}
	int _query(int x){
		ans+=ok(a[x].data[0],a[x].data[1])*a[x].val;
		int tmp;
		if (lch[x]){
			tmp=check(lch[x]);
			if (tmp==4) ans+=sum[lch[x]];
			else if (tmp) _query(lch[x]);
		}
		if (rch[x]){
			tmp=check(rch[x]);
			if (tmp==4) ans+=sum[rch[x]];
			else if (tmp) _query(rch[x]);
		}
	}
}kd;
int read();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	//scanf("%lld%lld",&n,&m);
	n=read(); m=read();
	for (int i=1;i<=n;++i)
		//scanf("%lld%lld%lld\n",&a[i].data[0],&a[i].data[1],&a[i].val);
		a[i].data[0]=read(),a[i].data[1]=read(),a[i].val=read();
	kd.build();
	cnt=0;
	for (int i=1;i<=m;++i){
		//scanf("%lld%lld%lld",&A,&B,&C);
		A=read(); B=read(); C=read();
		ans=0;
		cnt=0;
		kd.query();
		printf("%lld\n",ans);
	}
}

int read(){
	int ret=0,t=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') t=-1; ch=getchar();}
	while ('0'<=ch&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*t;
}
