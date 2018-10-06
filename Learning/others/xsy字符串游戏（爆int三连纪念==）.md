**Portal --> broken qwq**

### Description

​	给你一个字符串$S$，总共有$M$个询问，询问有两种：

type 1：给定$k_1,k_2$，询问$S$的所以不同的子串中字典序第$k_1$小的子串中，起始位置第$k_2$小的是哪个（输出起始下标和结束下标）

type 2：给定$l,r$，询问$S$的子串$S[l,r]$在所有$S$的不同子串中从小到大的字典序排名，以及相同子串中从小到大的起始位置排名$k_1,k_2$

​	数据范围：$|S|<=5*10^5,M<=10^5$，询问保证合法

### Solution

​	其实这题好像没有太多的思维难度==

​	挂上来是因为。。我已经在字符串的子串计数上面爆int三连了== **字符串的子串的相关变量全部给我开long long啊！**

​	然后。。稍微说一下做法的话就是

​	对于第一问，用[【Portal-->相似子串】](https://www.cnblogs.com/yoyoball/p/9324662.html)中的那个前缀和可以定位到字典序第$k_1$小的子串，然后我们二分一下找到以这个子串为前缀的后缀的区间，然后找其中$sa$第$k_2$小的那个就好了，然后找第$k_2$小的直接套一个主席树就好了（注意因为是动态开点所以。。不用乘$4$==）

​	第二问更加好做，直接用前缀和找到这个子串对应的后缀然后二分找到以这个子串对应的后缀的区间，然后在主席树里面查一下排名就好了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int N=5*(1e5)+10,TOP=20,SEG=N*20;
char s[N];
int n,m;
namespace Seg{/*{{{*/
	int ch[SEG][2],rt[N];
	ll cnt[SEG];
	int n,tot;
	void init(int _n){
		n=_n; tot=0; rt[0]=0; cnt[0]=0; ch[0][0]=ch[0][1]=0;
	}
	int newnode(int pre){
		ch[++tot][0]=ch[pre][0]; ch[tot][1]=ch[pre][1];
		cnt[tot]=cnt[pre];
		return tot;
	}
	void pushup(int x){cnt[x]=cnt[ch[x][0]]+cnt[ch[x][1]];}
	void _insert(int pre,int &x,int d,int lx,int rx){
		x=newnode(pre);
		if (lx==rx){
			++cnt[x];
			return;
		}
		int mid=lx+rx>>1;
		if (d<=mid) _insert(ch[pre][0],ch[x][0],d,lx,mid);
		else _insert(ch[pre][1],ch[x][1],d,mid+1,rx);
		pushup(x);
	}
	void insert(int pre,int x,int d){_insert(rt[pre],rt[x],d,1,n);}
	ll _query1(int L,int R,int lx,int rx,ll k){
		if (lx==rx) return lx;
		int mid=lx+rx>>1;
		ll tmp=cnt[ch[R][0]]-cnt[ch[L][0]];
		if (k<=tmp) return _query1(ch[L][0],ch[R][0],lx,mid,k);
		else return _query1(ch[L][1],ch[R][1],mid+1,rx,k-tmp);
	}
	ll query1(int l,int r,int k){return _query1(rt[l-1],rt[r],1,n,k);}
	ll _query2(int L,int R,int l,int r,int lx,int rx){
		if (l<=lx&&rx<=r) return cnt[R]-cnt[L];
		int mid=lx+rx>>1;
		ll ret=0;
		if (l<=mid) ret+=_query2(ch[L][0],ch[R][0],l,r,lx,mid);
		if (r>mid) ret+=_query2(ch[L][1],ch[R][1],l,r,mid+1,rx);
		return ret;
	}
	ll query2(int L,int R,int l,int r){return _query2(rt[L-1],rt[R],l,r,1,n);}
}/*}}}*/
namespace Sa{/*{{{*/
	int a[N],b[N],c[N],rk[N],height[N],sa[N];
	ll num[N],mn[N][TOP+1];
	int mx;
	bool cmp(int x,int y,int len,int *r)
	{return r[x]==r[y]&&r[x+len]==r[y+len];}
	void sort(int n){
		for (int i=0;i<=mx;++i) c[i]=0;
		for (int i=1;i<=n;++i) c[a[b[i]]]++;
		for (int i=1;i<=mx;++i) c[i]+=c[i-1];
		for (int i=n;i>=1;--i) sa[c[a[b[i]]]--]=b[i];
	}
	void get_sa(int n){
		mx=0;
		for (int i=1;i<=n;++i) a[i]=s[i]-'a'+1,b[i]=i,mx=max(mx,a[i]);
		sort(n);
		int cnt=0;
		for (int len=1;cnt<n;len<<=1){
			cnt=0;
			for (int i=n-len+1;i<=n;++i) b[++cnt]=i;
			for (int i=1;i<=n;++i)
				if (sa[i]>len)
					b[++cnt]=sa[i]-len;
			sort(n);
			swap(a,b);
			cnt=1; a[sa[1]]=1;
			for (int i=2;i<=n;a[sa[i++]]=cnt)
				if (!cmp(sa[i],sa[i-1],len,b)) ++cnt;
			mx=cnt;
		}
		Seg::init(n);
		for (int i=1;i<=n;++i)
			Seg::insert(i-1,i,sa[i]);
	}
	void calc(){
		for (int i=1;i<=n;++i) mn[i][0]=height[i];
		for (int j=1;j<=TOP;++j)
			for (int i=n-(1<<j)+1;i>=1;--i)
				mn[i][j]=min(mn[i][j-1],mn[i+(1<<j-1)][j-1]);
	}
	void get_height(int n){
		for (int i=1;i<=n;++i) rk[sa[i]]=i;
		int k=0;
		for (int i=1;i<=n;++i){
			if (k) --k;
			while (s[i+k]==s[sa[rk[i]-1]+k]) ++k;
			height[rk[i]]=k;
		}
		calc();
		for (int i=1;i<=n;++i)
			num[i]=num[i-1]+(n-sa[i]+1)-height[i];
	}
	int get_lcp(int x,int y){
		if (x==y) return n-sa[x]+1;
		if (x>y) swap(x,y);
		++x;
		int len=y-x+1,lg=(int)(log(1.0*len)/log(2.0));
		return min(mn[x][lg],mn[y-(1<<lg)+1][lg]);
	}
	int get_ed(int l,int len){
		int r=n,mid,ans=l,st=l;
		while (l<=r){
			mid=l+r>>1;
			if (get_lcp(st,mid)>=len) ans=mid,l=mid+1;
			else r=mid-1;
		}
		return ans;
	}
	int get_st(int r,int len){
		int l=1,mid,ans=r,ed=r;
		while (l<=r){
			mid=l+r>>1;
			if (get_lcp(mid,ed)>=len) ans=mid,r=mid-1;
			else l=mid+1;
		}
		return ans;
	}
	void query1(ll k,ll k1){
		int loc=lower_bound(num+1,num+1+n,k)-num,len,st=loc,ed=loc;
		int ansl,ansr;
		len=n-sa[loc]+1-(num[loc]-k);

		ed=get_ed(st,len);
		ansl=Seg::query1(st,ed,k1);
		ansr=ansl+len-1;
		printf("%d %d\n",ansl,ansr);
	}
	void query2(int l,int r){
		int st,ed,len=r-l+1,tmp;
		st=get_st(rk[l],len);
		ed=get_ed(rk[l],len);
		tmp=Seg::query2(st,ed,1,l);
		printf("%lld %lld\n",num[st-1]+len-height[st],tmp);
	}
}/*}}}*/

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	ll op,x,y;
	scanf("%s",s+1);
	n=strlen(s+1);
	Sa::get_sa(n);
	Sa::get_height(n);
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%lld%lld%lld",&op,&x,&y);
		if (op==1){
			Sa::query1(x,y);
		}
		else{
			Sa::query2(x,y);
		}
	}
}
```



