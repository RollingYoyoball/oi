**Portal --> broken qwq**

### Solution

​	所以我不是很懂为什么我场上想到了凸包的解法但是。。老想着。。要整体处理==有毒

​	一开始。。自己进入了一个误区就是老想着要求交点

​	但是很显然求交点你就凉了，所以我们要转化问题![Mountainous_Landscape](E:\msys64\home\Administrator\program\learning\others\Mountainous_Landscape.png)

​	我们把橙黄色的那条线画出来，然后就发现。。其实我们是可以很方便地判断一段线段（$P_3P_4​$），在某一个区间里面有没有解，具体的话就是。。我们维护这个区间的上凸包，然后判断一下这条线跟是否与这个上凸包相交就好了

​	那然后就直接。。线段树维护每个区间的上凸包。。然后直接在线段树上查答案就ok了然后记得优秀左儿子。。时间复杂度$O(nlog^2n)$



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=1e5+10,SEG=N*4;
const double eps=1e-6;
struct Dot{
	double x,y;
	Dot(){}
	Dot(double _x,double _y){x=_x; y=_y;}
}a[N];
bool slope_dec(int x,int y,int i){return (a[x].y-a[y].y)*(a[y].x-a[i].x)>(a[y].y-a[i].y)*(a[x].x-a[y].x);}
void line(int x,int y,double &k,double &b){
	k=(a[x].y-a[y].y)/(a[x].x-a[y].x);
	b=a[x].y-k*a[x].x;
}
bool k_bigger(int x,int y,double k){
	if (a[y].x>a[x].x) swap(x,y);
	return (a[x].y-a[y].y)>k*(a[x].x-a[y].x);
}
int n,ans;
namespace Seg{/*{{{*/
	int ch[SEG][2],top[SEG];
	vector<int> rec[SEG];
	int n,tot;
	double k,b;
	void _build(int x,int l,int r){
		rec[x].resize(r-l+3); top[x]=0;
		for (int i=l;i<=r+1;++i){
			while (top[x]>1&&!slope_dec(rec[x][top[x]-1],rec[x][top[x]],i)) --top[x];
			rec[x][++top[x]]=i;
		}
		rec[x].resize(top[x]+1);
		if (l==r) return;
		int mid=l+r>>1;
		ch[x][0]=++tot; _build(ch[x][0],l,mid);
		ch[x][1]=++tot; _build(ch[x][1],mid+1,r);
	}
	void build(int _n){n=_n; tot=1; _build(1,1,n);}
	int check(int x){
		int l=1,r=top[x]-1,mid,tmp1,tmp2,ans=r;
		while (l<=r){
			mid=l+r>>1;
			tmp1=rec[x][mid];
			tmp2=rec[x][mid+1];
			if (k_bigger(tmp1,tmp2,k)) 
				ans=mid,l=mid+1;
			else r=mid-1;
		}
		tmp1=rec[x][ans+1];
		if (k*a[tmp1].x+b+eps<=a[tmp1].y) return tmp1-1;
		else return 0;
	}
	int _query(int x,int l,int r,int lx,int rx){
		int mid=lx+rx>>1,tmp;
		if (l<=lx&&rx<=r){
			if (lx==rx) return check(x);
			if (!check(x)) return 0;
			if (check(ch[x][0]))
				return _query(ch[x][0],l,r,lx,mid);
			return _query(ch[x][1],l,r,mid+1,rx);
		}
		if (r<=mid)
			return _query(ch[x][0],l,r,lx,mid);
		else if (l>mid)
			return _query(ch[x][1],l,r,mid+1,rx);
		else{
			tmp=_query(ch[x][0],l,mid,lx,mid);
			if (tmp) return tmp;
			return _query(ch[x][1],mid+1,r,mid+1,rx);
		}
	}
	int query(int l,int r,double k1,double b1){k=k1; b=b1;return _query(1,l,r,1,n);}
	void _debug(int x,int lx,int rx){
		printf("#%d %d: ",lx,rx);
		for (int i=1;i<=top[x];++i) printf("%d ",rec[x][i]);
		printf("\n");
		if (lx==rx)  return;
		int mid=lx+rx>>1;
		_debug(ch[x][0],lx,mid);
		_debug(ch[x][1],mid+1,rx);
	}
	void debug(){_debug(1,1,n);}
}/*}}}*/

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	double k,b;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%lf%lf\n",&a[i].x,&a[i].y);
	Seg::build(n-1);
	//Seg::debug();
	for (int i=1;i<n;++i){
		ans=0;
		if (i<=n-2){
			line(i,i+1,k,b);
			ans=Seg::query(i+1,n-1,k,b);
		}
		printf("%d ",ans);
		//Seg::debug();printf("\n");
	}
}
```

