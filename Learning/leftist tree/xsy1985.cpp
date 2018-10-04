#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=1e6+10;
int a[MAXN];
int abs(int x) {return x>0?x:-x;}
struct xxx
{
	int lch[MAXN],rch[MAXN],rt[MAXN],sz[MAXN],l[MAXN],r[MAXN],dis[MAXN],val[MAXN];
	int tot,now;
	int newnode(int x)
	{
		val[++tot]=x;
		lch[tot]=rch[tot]=dis[tot]=0;
		sz[tot]=1;
		return tot;
	}
	int newheap(int pos,int x)
	{
		rt[++now]=newnode(x);
		l[now]=r[now]=pos;
	}
	int _merge(int x,int y)
	{
		if (!x||!y) return x+y;
		if (val[x]<val[y]) swap(x,y);
		rch[x]=_merge(rch[x],y);
		sz[x]=sz[lch[x]]+sz[rch[x]]+1;
		if (dis[lch[x]]<dis[rch[x]]) swap(lch[x],rch[x]);
		dis[x]=dis[rch[x]]+1;
		return x;
	}
	int merge_last() 
	{
		--now;
		rt[now]=_merge(rt[now],rt[now+1]);
		r[now]=r[now+1];
		while (sz[rt[now]]*2>r[now]-l[now]+2)
			del(rt[now]);
	}
	int del(int &x)
	{
		--sz[x];
		x=_merge(lch[x],rch[x]);
	}
	int get_top(int x)
	{
		return val[rt[x]];
	}
	ll calc(int x)
	{
		ll ret=0;
		int top=get_top(x);
		for (int i=l[x];i<=r[x];++i)
			ret+=abs(top-val[i]);
		return ret;
	}
	int check()
	{
		return val[rt[now-1]]<val[rt[now]];
	}
}heap;
int n,m;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	for (int i=1;i<=n;++i) 
	{
		scanf("%d",a+i);
		heap.newheap(i,a[i]-i);
		while (!heap.check()&&heap.now>1)
			heap.merge_last();
	}
	ll ans=0;
	for (int i=1;i<=heap.now;++i)
		ans+=heap.calc(i);
	printf("%lld\n",ans);
}

//思路好像十分简单粗暴啊
//首先考虑如果是不下降的极端情况
//如果说序列a是不下降的，最优解就是取回自己
//如果a是不上升的，最优解就是中位数（嗯。。奇妙奥数好像证过。。）
//那么现在就是一个贪心的想法
//将原序列分成若干个小的不上升区间 
//那么最好的情况就是每个区间取中位数
//然而会出现后面的中位数比前面的小
//那么这个时候就将两个区间合并取中位数来使得该区间的解最优
//然后这题是严格上升的话。。奇妙小技巧，全部值-i就好 

//关于奇妙中位数的证明
//有一个很简单的想法
//如果取的不是中位数w，不妨设这个数为w+k
//那么，小于中位数的那些数的贡献会+k，大于中位数的每个数的贡献会-k
//这里的中位数是n/2，所以小于的个数是>=大于的个数的
//所以不会更优，所以中位数就是最优啦 
