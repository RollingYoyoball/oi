**Portal --> TC608 600pts**（懒得传送了==）

### Description

​	给你一个简单有向图，找一个最小的$K$，使得对于任意正整数$L$，图中长度为$L$的路径的个数都是$O(L^k)$的（也就是说对于任意的$L$满足路径个数$f(L)<=C\cdot L^k$，其中$C$是一个常数），不存在输出$-1$

​	数据范围：$N<=10^5,M<=10^6$

### Solution

​	这是一年前的题==然而一年前我还在划水

​	觉得这种思想挺好，场上虽然想到了但是想的不够透彻

​	首先考虑什么情况会无解：如果说图中存在一个非简单环的话，那么我们可以从一个类似dp的角度考虑$f(L)\rightarrow f(L+1)$，假设这个非简单环中的每一个节点都可以转移到$2$个该环中的节点，那么$f(L)\rightarrow f(L+1)$有一部分是乘上$2^x$，其中这个$x$是与$f(L)$中的一部分相关的（其实就是非简单环中长度为$L$的路径数量），那。。这个一旦跑到指数上面去。。就没有办法得到一个解了

​	然后接下来考虑图中没有非简单环的情况

​	因为是要**任意**的$L$都要满足条件，那么我们就直接考虑$L\rightarrow \infty$的情况（否则如果考虑$L$的具体数值的话你只要$C$巨大无比就一定可以满足条件了。。没有什么讨论的意义），我们将所有的环缩掉（接下来的环都指的是包含至少两个点的环不然根本没法绕qwq），得到一个拓扑图，那么一条长度为$L$的路径可以看成拓扑图上的一条简单路径，然后如果说这条简单路径上有的代表环的点为$h_1,h_2,h_3...h_m$，我们用$x_1,x_2,x_3...x_m$表示绕每个环多少圈，那么其实一条路径的贡献就变成了方程$h_1x_1+h_2x_2+h_3x_3+...+h_mx_m=L$有多少个解，然后这个解的数量是$O(L^{m-1})$的（具体就是你考虑最坏的情况。。这里我们环的长度都是$>=2$的，那考虑最坏情况就是每个环都是长度为$2$的，然后每个环都可以至多绕$\frac{L}{2}$圈，但是！这里我们考虑的是$L\rightarrow \infin$的情况，所以。。直接就是$L$圈了，然后又因为最后一个圈的话受到了前面的圈的限制，所以应该是$O(L^{m-1})$级别的，虽然说这么写不严谨但是大概就是做加法还是同一个数量级的，但是做乘法的话就翻了一个数量级了）

​	所以我们只要找到拓扑图中包含环最多的路径，那么答案就是包含环的数量$-1$了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=1e5+10,inf=2147483647;
struct xxx{
	int y,nxt;
}a[N*40];
queue<int> q;
int h[N],st[N],h1[N];
int dfn[N],low[N],inst[N],num[N],out[N],val[N],sz[N];
int in[N],f[N];
int n,m,tot,dfn_t,top,cnt,ans;
void add(int x,int y,int *h){a[++tot].y=y; a[tot].nxt=h[x];h[x]=tot;}
void tarjan(int x){
	int u;
	dfn[x]=low[x]=++dfn_t; st[++top]=x; inst[x]=true;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (!dfn[u]){
			tarjan(u);
			low[x]=min(low[x],low[u]);
		}
		else if (inst[u])
			low[x]=min(low[x],dfn[u]);
	}
	if (low[x]==dfn[x]){
		++cnt;
		u=st[top]; sz[cnt]=0;
		while (u!=x){
			num[u]=cnt; inst[u]=false;
			u=st[--top]; ++sz[cnt];
		}
		num[x]=cnt; inst[x]=false; ++sz[cnt];
		--top;
	}
}
void rebuild(){
	int u;
	memset(h1,-1,sizeof(h1));
	for (int i=1;i<=n;++i)
		for (int j=h[i];j!=-1;j=a[j].nxt){
			u=a[j].y;
			if (num[i]==num[u]) continue;
			add(num[i],num[u],h1); ++in[num[u]];
		}
}
int tp(){
	int u,v,ret;
	for (int i=1;i<=cnt;++i) val[i]=(sz[i]>=2);
	while (!q.empty()) q.pop();
	for (int i=1;i<=n;++i)
		if (in[i]==0) q.push(i);
	while (!q.empty()){
		v=q.front(); q.pop();
		f[v]+=val[v];
		for (int i=h1[v];i!=-1;i=a[i].nxt){
			u=a[i].y;
			f[u]=max(f[u],f[v]);
			--in[u];
			if (!in[u]) q.push(u);
		}
	}
	ret=0;
	for (int i=1;i<=n;++i) ret=max(ret,f[i]);
	return ret;
}
bool solve(){
	int id,u;
	memset(dfn,0,sizeof(dfn));
	memset(inst,false,sizeof(inst));
	dfn_t=0; cnt=0;
	for (int i=1;i<=n;++i)
		if (!dfn[i]) tarjan(i);
	for (int i=1;i<=n;++i){
		id=num[i]; out[i]=0;
		for (int j=h[i];j!=-1;j=a[j].nxt){
			u=a[j].y;
			out[i]+=(num[u]==num[i]);
		}
		if (out[i]>1) return false;
	}
	rebuild();
	ans=tp();
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y;
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		add(x,y,h);
	}
	if (!solve()) printf("-1\n");
	else printf("%d\n",max(0,ans-1));
}
```

