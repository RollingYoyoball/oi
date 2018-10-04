e.g1：[bzoj2654（tree）](https://www.lydsy.com/JudgeOnline/problem.php?id=2654)

​	一句话题意：给你若干条带权无向边，有黑有白，求白边数量恰好为$need$的最小生成树的边权和

e.g2：xsy2761（新访问计划）

​	几句话题意：给一棵树，每条边有花费，行走方式有两种，一种是直接按树上的边走，一种是花费C元直接跳到任意一个别的点，求从根节点经过每条边至少一次最后回到根节点的花费最小值，使用第二种行走方式的次数有限，且第二种行走方式不算“经过”



​	这两题的共同点是，都是选择某个东西的次数一定，求最优解，同时如果不看次数限制的话，问题的求解相对简单一点，且复杂度可以接受

​	那么这里提供一种思路。注意到**主要影响结果的因素是“费用”，那么我们可以通过给有次数限制的决策的费用加上或者减去一个值（也可以理解成。。一个偏移量），来达到限制次数的目的**

​	具体一点就是（拿第一题为例）：

​	k开头的最小生成树的求法是将所有的边按照权值排序，然后能加就加，如果我们直接求最小生成树，白边的数量不一定满足条件，但是如果说我们给所有的白边都加上一个偏移量$D$，再跑一次最小生成树，边的排序就可能会有一定的变化（比如说如果$D>0$那么部分白边的排序就会往后移，反之则会往前移），从而使得最终选出的方案中白边的数量有所改变（比如说$D>0$时白边的数量可能会减少，反之则可能增加）

​	记$f(D)$为偏移量为$D$时，跑出的最小生成树中白边的条数

​	那么通过调整$D$这个偏移量的值，我们可以得到一个$f(D)>=need$的解，最后显然就是找到$f(D)=need$时候的方案，然后将偏移量的影响去掉，就能得到答案了，根据偏移量$D$与$f(D)$的关系，不难想到$D$的调整可以通过二分来实现

​	然而，有一个问题就是，我们会发现$f(D)$这个函数并不一定是连续的（因为我们这里的$D$枚举的全部都是整数），也就是说可能不存在一个整数$D$满足$f(D)=need$，那么为了解决这个问题，我们就需要在求方案的时候进行一些处理了

​	在求方案的过程中，可能出现白边和黑边权值相同的情况，那么这个时候我们优先选择白边，那么就可以保证到$f(D)$表示的是，偏移量为$D$时，跑出的最小生成树中白边条数的最大值

​	接着我们考虑最后二分出来的结果$res$，应该是满足函数值大于等于$need$的偏移量的最小值，如果说$f(res)!=need$，那么说明$f(res+1)>need，f(res)<need$

​	我们考虑回我们是如何求出$f(res)$对应的方案的，有一个很重要的决策步骤是：**权值相同，白边优先**，也就是说在白边加上了偏移量$res$之后，这个图中**可能存在与某条白边权值相同并且可以替换这条白边的一条黑边**，又因为$f(res+1)$后，函数值就$<need$了，所以与某条白边$+res$后权值相同的黑边是一定存在的（不一定能替换这条白边）

​	然而，因为**题目保证一定有解**，所以一定存在$f(res)-need$条可以替换的权值相同的黑边，那么这个时候我们只要把这些黑边拿来替换掉白边就能满足条件了

​	我们用$val(res)$表示偏移量为$res$时跑出的最小生成树的权值，那么最终的答案是：
$$
\begin{aligned}
ans&=val(res)-res*f(res)+(f(res)-need)*res\\
&=val(res)-res*need\\
\end{aligned}
$$
​	（前面是减去白边的偏移值，后面是加上替换上来的黑边的贡献）

​	

​	总结一下就是，二分求得最大选择次数$>=need$的偏移量最小值，然后用同样代价的另一种方案来替换掉多余的部分，大概是这样嗯

​	（新访问计划其实是差不多的，只是把求“最大选择次数”的过程换成了树d而已，其他思路大体一致）



​	bzoj2654代码大概长这样

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5*(1e4)+10,M=1e5+10;
struct edge{
	int x,y,val,col;
}a[M];
int h[N],f[N];
int n,m,need,D,ans,sum;
void solve();
int check(int add);
bool cmp(edge x,edge y);
int get_f(int x){return f[x]=f[x]==x?f[x]:get_f(f[x]);}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int s,t,c,col;
	scanf("%d%d%d",&n,&m,&need);
	sum=0;
	for (int i=1;i<=m;++i)
		scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].val,&a[i].col);
	solve();
}

bool cmp(edge x,edge y){
	int valx=x.val,valy=y.val;
	if (!x.col) valx+=D;
	if (!y.col) valy+=D;
	return valx==valy?x.col<y.col:valx<valy;
}

int check(int add,int &ret){
	int fx,fy,x,y,cnt,cntw;
	D=add;
	sort(a+1,a+1+m,cmp);
	for (int i=0;i<n;++i) f[i]=i;
	cnt=0; ret=0; cntw=0;
	for (int i=1;i<=m&&cnt<n-1;++i){
		x=a[i].x; y=a[i].y;
		get_f(x); get_f(y);
		if (f[x]!=f[y]){
			++cnt;
			ret+=a[i].val+D*(a[i].col^1);
			f[f[x]]=f[y];
			cntw+=a[i].col^1;
		}
	}
	return cntw;
}

void solve(){
	int l=-101,r=101,mid,ok=-101,tmp,tmp1;
	while (l<=r){
		mid=l+r>>1;
		tmp=check(mid,tmp1);
		if (tmp>=need) ok=mid,l=mid+1;
		else r=mid-1;
	}
	check(ok,ans);
	ans=ans-ok*need;
	printf("%d\n",ans);
}
```



​	xsy新访问计划代码大概长这样

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 2147483647
#define ll long long
using namespace std;
const int MAXN=1e5+10;
struct xxx{
	int y,next,w;
}a[MAXN*2];
struct data{
	ll cost,car;
	data(){}
	data(int x,int y){cost=x; car=y;}
	friend bool operator <(data x,data y)
	{return x.cost==y.cost?x.car<y.car:x.cost<y.cost;}
}f[MAXN],g[MAXN];
int h[MAXN];
int n,m,tot,K,C;
ll ans,sum;
void add(int x,int y,int d);
void dp(int fa,int x,int val);
data Min(data x,data y){return x<y?x:y;}
bool ok(int val);
void solve();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	while (scanf("%d%d%d",&n,&K,&C)!=EOF){
		memset(h,-1,sizeof(h));
		tot=0; sum=0;
		int x,y,z;
		for (int i=1;i<n;++i){
			scanf("%d%d%d",&x,&y,&z);
			++x;++y;
			add(x,y,z); add(y,x,z);
			sum+=z;
		}
		solve();
	}
}

void add(int x,int y,int d){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].w=d;
}

void dp(int fa,int x,int val){
	int u,son=0;
	data tg,tf;
	f[x]=data(val,1); g[x]=data(0,0);
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==fa) continue;
		dp(x,u,val);
		tg=Min(data(f[x].cost+f[u].cost-val,f[x].car+f[u].car-1),
			   data(g[x].cost+g[u].cost+a[i].w,g[x].car+g[u].car));
		tf=Min(data(f[x].cost+g[u].cost+a[i].w,f[x].car+g[u].car),
			   data(g[x].cost+f[u].cost,g[x].car+f[u].car));
		g[x]=Min(tg,tf);
		f[x]=Min(tf,data(tg.cost+val,tg.car+1));
	}
}

bool ok(int val){
	dp(0,1,val);
	return g[1].car<=K;
}

void solve(){
	if (ok(C)){printf("%lld\n",sum+g[1].cost); return;}
	int l=C+1,r=1e9,mid,ans;
	while (l<=r){
		mid=l+r>>1;
		if (ok(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	dp(0,1,ans);
	printf("%lld\n",sum+g[1].cost+(C-ans)*g[1].car+(K-g[1].car)*(C-ans));
}
```



​	