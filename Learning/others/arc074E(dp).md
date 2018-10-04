[**Portal --> arc074_e**](https://arc074.contest.atcoder.jp/tasks/arc074_c)

### Solution

​	这题的话。。一眼看过去应该是dp但是。。一开始没有注意到只有三种颜色。。qwq

​	因为颜色的种类数很少，所以我们可以尽量往这边靠，注意到其实真正重要的应该是当前每种颜色最后在的位置，只要通过判断这个位置和$l,r$的关系就可以快速判断区间$[l,r]$内有多少种颜色了

​	于是我们可以想到这样的一个状态：记$f[i][j][k]​$表示当前枚举到第$i​$位，与$i​$不同的两种颜色的最后位置分别为$j​$和$k​$（将较后的那个排在前面，之所以这么奇怪是因为。。枚举的时候范围的方便。。），如果不考虑题目的限制的话，转移应该是：
$$
f[i][j][k]\rightarrow
\begin{cases}
f[i+1][j][k]&(i取与j和k不同的颜色)\\
f[i+1][i][k]&(i取j的颜色)\\
f[i+1][i][j]&(i取k的颜色)\\
\end{cases}
$$
​	然后加上限制的话，就是我们每一条限制$(l,r,x)$存到$r$这个位置上，这样考虑$f[i][j][k]$的转移的时候，就考虑$f[i][j][k]$这个状态是否满足以$i$为右端点的所有限制区间的限制，如果不满足的话就直接将$f[i][j][k]$赋成$0$，达到不转移的效果就好了

​	最后统计完之后，$ans$记得要$*3$，因为有三种不同的颜色选择，而我们的dp只是考虑了相同与不同并没有将具体是什么颜色算进去



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define Pr pair<int,int>
#define mp make_pair
using namespace std;
const int N=310,MOD=1e9+7;
vector<Pr> rec[N];
int f[N][N][N];
int n,m,ans;
void update(int &x,int y){x=(1LL*x+y+MOD+MOD)%MOD;}
void solve(){
	int sz,l,x;
	f[1][0][0]=1;
	for (int i=1;i<=n;++i){
		sz=rec[i].size();
		for (int p=0;p<sz;++p){
			l=rec[i][p].first; x=rec[i][p].second;
			for (int j=0;j<i;++j)
				for (int k=0;k<=max(0,j-1);++k){
					if (x==1){
						if (l<=j) f[i][j][k]=0;
					}
					else if (x==2){
						if (l<=k||j<l) f[i][j][k]=0;
					}
					else{
						if (k<l) f[i][j][k]=0;
					}
				}
		}
		if (i==n) break;
		for (int j=0;j<i;++j)
			for (int k=0;k<=max(j-1,0);++k){
				if (!f[i][j][k]) continue;
				update(f[i+1][j][k],f[i][j][k]);
				update(f[i+1][i][k],f[i][j][k]);
				update(f[i+1][i][j],f[i][j][k]);
			}
	}
	ans=0;
	for (int j=0;j<n;++j)
		for (int k=0;k<=max(0,j-1);++k)
			update(ans,f[n][j][k]);
	ans=1LL*ans*3%MOD;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int l,r,x;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&l,&r,&x);
		rec[r].push_back(mp(l,x));
	}
	solve();
	printf("%d\n",ans);
}
```





​	