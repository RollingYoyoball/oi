[**Portal --> arc079F**](https://arc079.contest.atcoder.jp/tasks/arc079_d)

### Solution

​	这题qwq真实乱搞题qwq这个时候应该疯狂膜拜ckw%%%

​	首先我们看一下那个奇奇怪怪的条件，会发现这个其实就是一个求$mex$的过程（这么明显我场上居然一点反应都没有！！！怎么回事啊==）

​	然后这个$mex$的话。。莫名就会想到树上$sg$。。。然后这个时候我们会发现，如果说在一棵树上的话，题目中的$a_i$其实可以看成$i$这个点的$sg$值，然后叶子节点显然是$0$，整棵树的形态固定，那么所有的$sg$都是固定的了，于是我们得到结论：树上的情况$a_i$是固定的

​	然后现在看这题，因为是$n$个点$n$条边的弱连通有向图，然后因为入度都是$1$，所以应该是一个。。基环外向树，然后因为树中的值是固定的，所以我们可以考虑将那个环拿出来看

​	这个环中的每个点其实都是那些树的树根，每个点的$a$都是确定的，注意这个时候环上点的$a$值并不一定是最终的$a$值，现在求出来的只是一个下界（为了满足子树内的连边），所以我们需要讨论在下界确定的情况下能否构造出一种方案使得这个环内本身合法，接下来分两种情况讨论：

​	在讨论之前要先指出一个。。可能容易忽略的事情：对于一个值为$x$的环上的点，如果它的一条出边指到了一个值不在$[0,x)$的点，问题不大

（以下提到的$a_i$都是第一阶段算出来的$a_i$，并非最终的结果，也就是说是下界，并且点和边的范围我们缩小到环上）

1、所有点的$a_i$值都相同

​	因为是求$mex$，所以相邻两个的$a_i$值肯定不相同，所以我们需要调整

​	一个简单粗暴的方式就是，把这个环断成一条链，然后编号，然后把所有偶数位（或者所有奇数位也行反正就其中一类）上的点的值$+1$即可（实际上也只有这一种方式。。因为这个环上所有值都相同。。。）

​	然后这里就出现问题了，我们发现如果说环的长度是偶数的话，不会有问题，但是如果是奇数的话，绕了一圈之后就出问题了（具体就是如果一开始是从奇数位开始跳的，绕了一圈之后就变成偶数位了，然后就必须一直加下去，无论怎样都不能满足条件），所以这个时候是无解的

2、并非所有点的$a_i$都相同

​	同样我们需要调整每个点的$a_i$，但是因为这里并非所有的下界都相同，所以调整的方式有很多种，所以我们考虑只看两个相邻的点$u$和$v$，连边关系假设为$u\rightarrow v$

​	接下来根据$a_u$和$a_v$的大小关系可以分成三种情况讨论

（1）$a_u<a_v$：注意到上面提到的那个容易忽略的事情，因为$a_v$不在$[0,a_u)$的范围内，所以相当于这条边根本不需要考虑，$a_u$和$a_v$的值都不需要变动

（2）$a_u=a_v$：将$a_u$调整成$a_v+1$即可

（3）$a_u>a_v$：$a_v$本来就在$[0,a_u)$的范围内了，不需要变动

​	也就是说，对于两个相邻的点我们总能通过调整使其满足条件，然后因为一旦不等便不需要调整，所以不会出现大情况$1$中奇环情况下的那种一直加根本停不下来的情况，所以这时是一定有解的

​	

​	综上，只有在存在一个$a$值下界相同的奇环的情况下才是无解的

​	

​	然后我们要做的就只是将环找出来，将树根的$a$的下界算出来，然后判断一下就好啦



​	代码大概长这个样子（话说回来我的找环好像写的很弱智的样子==不过不管了暴力便是艺术qwq）

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=200010;
struct xxx{
	int y,nxt;
}a[N];
int h[N],sg[N],pre[N],cir[N],lis[N],vis[N];
int n,m,tot,T;
void add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
void dfs(int x){
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt) 
		if (!cir[a[i].y])
			dfs(a[i].y);
	++T;
	for (int i=h[x];i!=-1;i=a[i].nxt) 
		if (!cir[a[i].y])
			vis[sg[a[i].y]]=T;
	sg[x]=0;
	while (vis[sg[x]]==T) ++sg[x];
}
void circle(){
	int x=1;
	memset(cir,false,sizeof(cir));
	while (!cir[x]) cir[x]=true,x=pre[x];
	lis[0]=0;
	memset(cir,false,sizeof(cir));
	while (!cir[x])
		lis[++lis[0]]=x,cir[x]=true,x=pre[x];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,mx,mn;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=n;++i)
		scanf("%d",&pre[i]),add(pre[i],i);
	circle();
	mx=0; mn=n+1;
	for (int i=1;i<=n;++i){
		if (!cir[i]) continue;
		dfs(i);
		mx=max(sg[i],mx);
		mn=min(sg[i],mn);
	}
	if (mx!=mn) printf("POSSIBLE\n");
	else if (mx==mn&&lis[0]%2==0) printf("POSSIBLE\n");
	else printf("IMPOSSIBLE\n");
}
```



​	