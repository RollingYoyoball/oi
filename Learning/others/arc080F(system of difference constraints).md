[**Portal --> arc080_f**](https://arc080.contest.atcoder.jp/tasks/arc080_d)

### Solution

​	这题的话。。差分套路题（算吗？反正就是想到差分就很好想了qwq）

​	（但是问题就是我不会这种套路啊qwq题解原话是：“这种翻面一段区间的题，就是差分套路题”==）

​	我们定义一个新的数组$A$，$A_i$表示的是第$i$个和第$i-1$个的状态是否相同，是的话为$0$否则为$1$，至于第$0$个的话。。我们强行定义第$0$个位置反面向上

​	这样我们就得到了一个$01$序列，然后原来的一段需要操作的区间就变成了两个$1$，那么我们现在要做的事情就变成了，每次找一个奇质数$p$，将第$i$位和第$i+p$位取反，最后让所有的$1$变成$0$即可

​	

​	接下来我们根据两个$1$的下标之差（记为相距）来分类讨论：

1.相距为奇质数：只需要$1$步，为了使得使用的步数尽量少，我们在后面的操作中显然应该尽量采取这种操作

2.相距为偶数：需要$2$步，这里用到哥德巴赫猜想，大于等于$6$的偶数可以分解成两个奇质数之和

3.相距为奇合数：需要$3$步，具体就是将这个奇合数变成一个奇质数与偶数之差就好了



​	然后我们要尽量让第一种操作尽量多，因为每次是挑两个$1$消掉，所以这里可以转化成一个最大匹配问题：我们将所有的$1$按照下标的奇偶性分成两类，偶数往奇数连，两个点连边当且仅当下标之差是一个奇质数，这样跑一遍最大匹配就可以得到尽量使用第一种操作的数量，记为$ans1$

​	然而这个时候可能还有剩的数，那么我们优先第二种操作，也就是同组匹配（差值为偶数），当这样匹配完了之后还有剩余，只可能是两组各剩一个的情况（因为$1​$总是成对出现的，总数量肯定是一个偶数），那么这两个再用第三种操作匹配掉，然后答案加$3​$就好了

​	额当然。。二分图匹配可以跑网络流qwq会快很多qwq



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=210,MX=1e7+10;
struct xxx{
	int y,nxt;
}a[N*N*2];
int h[N];
int inpt[N],p[MX],mark[MX],mnp[MX],col[MX],A[MX];
int used[N*2],match[N*2],llis[N*2],rlis[N*2];
int n,m,mx,tot,T,lcnt,rcnt;
ll ans;
void add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
void prework(int n){
	int cnt=0;
	mnp[1]=1;
	mark[1]=1;
	for (int i=2;i<=n;++i){
		if (!mark[i])
			p[++cnt]=i,mnp[i]=i;
		for (int j=1;j<=cnt&&i*p[j]<=n;++j){
			mark[i*p[j]]=true;
			if (i%p[j]==0){
				mnp[i*p[j]]=p[j];
				break;
			}
		}
	}
}
bool check(int x){
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (used[u]==T) continue;
		used[u]=T;
		if (!match[u]||check(match[u])){
			match[x]=u; match[u]=x;
			return true;
		}
	}
	return false;
}
void build(){
	int x,y;
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=llis[0];++i){
		x=llis[i];
		for (int j=1;j<=rlis[0];++j){
			y=rlis[j];
			if (mark[abs(x-y)]) continue;
			add(i,j+llis[0]);
			add(j+llis[0],i);
		}
	}
}
void solve(){
	llis[0]=0; rlis[0]=0;
	int tmpcnt=0;
	for (int i=1;i<=mx;++i)
		if (col[i]!=col[i-1]){
			if (i&1) 
				rlis[++rlis[0]]=i;
			else 
				llis[++llis[0]]=i;
			++tmpcnt;
		}
	build();
	T=0;
	for (int i=1;i<=llis[0];++i){
		if (!match[i]){
			++T;
			ans+=check(i);
		}
	}
	int tmp=0;
	if (ans<llis[0]) tmp+=(llis[0]-ans)/2*2;
	if (ans<rlis[0]) tmp+=(rlis[0]-ans)/2*2;
	if ((llis[0]-ans)%2==1) tmp+=3;
	printf("%d\n",ans+tmp);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	memset(col,0,sizeof(col));
	prework(MX-10);
	mx=0;
	for (int i=1;i<=n;++i){
		scanf("%d",inpt+i);
		col[inpt[i]]=1;
		mx=max(mx,inpt[i]);
	}
	++mx;
	solve();
}
```



​	