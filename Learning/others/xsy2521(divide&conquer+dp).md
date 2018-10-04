**Portal --> broken qwq**

### Solution

​	怎么感觉自己在。。想这种子问题转化的时候总是容易出车祸Q^Q

​	假设当前我们有的串是$[---A---][-B-]$，其中$B$的长度就是$k$，然后一次操作之后我们可以得到的是$[---A---][-B-][-B-][---A---]$

​	对于一个查询$[l,r]$，我们可以转化成查询$[1,r]$和查询$[1,l-1]$，现在考虑查询$[1,x]$怎么做：我们考虑一次一次操作往前推，假设当前是第$tm$次操作之后得到的串，我们要查询这个串的第$x$位，我们记上面第一个$[-B-]$的结尾位置为$mid$（其实就是第$tm-1$次操作之后得到的串），第二个$[-B-]$的结尾位置为$p$，有一下几种情况：

1、如果说$x<=mid$，那么说明这个位置在第$tm-1$甚至更少次操作之后就可以确定下来了，递归处理查询$tm-1$次操作之后的第$x$个位置

2、如果说$mid<x<=p$，那么说明这个位置在第$tm$次操作中确定，并且注意到每次操作之后新增的都是一段原字符串，只是其中字符顺序不同罢了，所以我们可以直接将前$tm-1$次操作中新增的那些完整的原字符串的数量（也就是$tm-1$）*原字符串中该字符的出现次数作为$mid$以前的贡献，然后$mid\sim x$的贡献，因为$k$很小并且最大的操作次数其实最多到$60$多，所以可以直接用一个数组$f[tm][x][ch]$表示第$tm$次操作时，$[-B-]$中第$1\sim x$位中有多少个$ch$字符（这个东西可以预处理）

3、如果说$x>p$，那么我们可以将$[---A---][-B-][-B-]$的答案直接加进去，然后递归处理，因为可以转化成求$[---A---]$的第$1\sim (x-p)$位的贡献，所以直接递归查询$tm-1$次操作之后第$x-p$个位置即可

​	然后至于。。这个$f$怎么预处理。。其实我们只要实现一个能查询到一个位置是什么字符的函数就好了，然后这个的话。。其实就是跟上面一样的嘛qwq不同的是第2中情况我们可以看成查询第一个$[-B-]$中的位置（两个$[-B-]$一样的嘛），然后就快乐递归处理就好了（十分意外的是貌似这个是。。自己非常容易忽略的点。。至于为什么我也不是很清楚。。）



​	所以其实想清楚了超级清晰的==但是。。但是。。但是。。



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=1e5+10,C=26;
const ll TOP=2e18;//要乘一个2是因为。。查的时候会多查一次操作
char s[110];
ll f[70][110][C],cnt[110][C],K[N];
int n,m,lens;
ll get_len(int tm){return 1LL*lens*(1LL<<tm);}
int get_char(int tm,ll x){
	if (x<=lens) return s[x]-'a';
	ll mid=get_len(tm-1),p=mid+K[tm];
	if (x<=mid) return get_char(tm-1,x);
	if (x<=p) return get_char(tm-1,mid-(p-x));
	return get_char(tm-1,x-p);
}
int Get_char(ll x){
	int tm=0;
	while (get_len(tm)<x) ++tm;
	return get_char(tm,x);
}
void prework(int n){
	for (int i=1;i<=lens;++i)
		for (int j=0;j<C;++j)
			cnt[i][j]=cnt[i-1][j]+(s[i]-'a'==j);
	ll p;
	for (int tm=0;get_len(tm)<=TOP&&tm<=n;++tm){
		K[tm]%=get_len(tm);
		for (int ch=0;ch<C;++ch) f[tm][0][ch]=0;
		for (int i=1;i<=K[tm];++i){
			p=get_len(tm-1)+i;
			for (int ch=0;ch<C;++ch)
				f[tm][i][ch]=f[tm][i-1][ch]+(Get_char(p)==ch);
		}
	}
}
ll solve(int tm,ll x,int ch){
	if (tm==0) return cnt[x][ch];
	ll mid=get_len(tm-1),p=mid+K[tm];
	if (x<=mid) return solve(tm-1,x,ch);
	if (x<=p) return (1LL<<tm-1)*cnt[lens][ch]+f[tm][x-mid][ch];
	return (1LL<<tm-1)*cnt[lens][ch]+f[tm][K[tm]][ch]+solve(tm-1,x-p,ch);
}
ll calc(ll x,int ch){
	if (!x) return 0;
	int tm=0;
	while (get_len(tm)<x) ++tm;
	return solve(tm,x,ch);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	ll l,r,tmp1,tmp2;
	char ch;
	scanf("%s",s+1); lens=strlen(s+1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%lld",K+i);
	prework(n);
	for (int i=1;i<=m;++i){
		scanf("%lld%lld %c",&l,&r,&ch);
		tmp1=calc(r,ch-'a');
		tmp2=calc(l-1,ch-'a');
		printf("%lld\n",tmp1-tmp2);
	}
}
```

