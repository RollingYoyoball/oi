[**Portal --> CF375C**](http://codeforces.com/problemset/problem/375/C)

### Solution

​	一个有趣的事情：题目中有很大的篇幅在介绍如何判断一个位置在不在所围的多边形中

​	那么。。~~给了方法当然就是要用啊~~

​	首先是不能包含$'B'$，处理方式很简单直接把他当成一个值为$-inf$的宝藏即可，这样所有的object就全部可以看成一类了，不需要再额外考虑

​	注意到object的总数很少，考虑状压，记$vis[x][y][st]$表示当前在$(x,y)$这个点，射线与路径的交点数量为奇数的object的状态为$st$，这种局面是否可行，然后对应的开一个$step[x][y][st]$表示达到这种局面所需要的最少步数，这个时候。。最短路既视感？

​	反正$n$和$m$也不大，所以我们可以考虑跑一个最短路，最后枚举一下$st$，然后用$(x,y)$为起点位置的状态去更新一下答案就好了

​	现在的问题是，如何计算一步移动对object的射线的影响

​	注意到这个射线其实随便选就好了。。所以方便起见，我们可以钦定每个点只看往其左上方延伸的、角度很小很小很小的一条射线就好了（也可以是别的方向啦随意随意，不过角度很小这个比较重要），角度小这个有一个好处就是，因为角度很小所以只有当纵坐标改变的时候才有可能产生交点，然后其他的情况判断就十分简单了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=25,dx[4]={-1,0,1,0},dy[4]={0,1,0,-1},ST=1<<8;
const int inf=1e4;
struct Rec{
	int x,y,val;
}a[20];
struct Data{
	int x,y,st;
	Data(){}
	Data(int x1,int y1,int st1){x=x1; y=y1; st=st1;}
};
queue<Data> q;
int vis[N][N][ST],step[N][N][ST],inq[N][N][ST];
char mp[N][N];
int n,m,t,stx,sty,cnt,ans;
int St(int x){return 1<<x-1;}
bool in(int st,int x){return st>>(x-1)&1;}
bool ok(int x,int y){
	if (x<1||y<1||x>n||y>m) return false;
	return mp[x][y]=='.'||mp[x][y]=='S';
}
bool check(int x,int y,int nwx,int nwy,int id){
	if (x==nwx) return false;
	if (x==a[id].x&&y<a[id].y) return nwx<x;
	if (nwx==a[id].x&&nwy<a[id].y) return x<nwx;
	return false;
}
void bfs(){
	Data v,u;
	int x,y,st,xx,yy,nw;
	while (!q.empty()) q.pop();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int k=0;k<(1<<cnt);++k)
				step[i][j][k]=inf,inq[i][j][k]=false;
	q.push(Data(stx,sty,0)); inq[stx][sty][0]=true;
	step[stx][sty][0]=0;
	while (!q.empty()){
		x=q.front().x; y=q.front().y; st=q.front().st; q.pop();
		vis[x][y][st]=true;
		for (int i=0;i<4;++i){
			xx=x+dx[i]; yy=y+dy[i];
			if (!ok(xx,yy)) continue;
			nw=st;
			for (int j=1;j<=cnt;++j)
				if (check(x,y,xx,yy,j))
					nw^=St(j);
			if (step[xx][yy][nw]>step[x][y][st]+1){
				step[xx][yy][nw]=step[x][y][st]+1;
				if (!inq[xx][yy][nw])
					q.push(Data(xx,yy,nw)),inq[xx][yy][nw]=true;
			}
		}
		inq[x][y][st]=false;
	}
}
void get_ans(){
	int tmp;
	for (int st=0;st<(1<<cnt);++st){
		if (!vis[stx][sty][st]) continue;
		tmp=0;
		for (int i=1;i<=cnt;++i)
			if (in(st,i))
				tmp+=a[i].val;
		ans=max(ans,tmp-step[stx][sty][st]);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d\n",&n,&m);
	t=0; cnt=0;
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			scanf("%c",&mp[i][j]);
			if ('0'<=mp[i][j]&&mp[i][j]<='9'){
				a[mp[i][j]-'0'].x=i,a[mp[i][j]-'0'].y=j;
				t=max(t,mp[i][j]-'0');
				++cnt;
			}
			else if (mp[i][j]=='S')
				stx=i,sty=j;
		}
		scanf("\n");
	}
	for (int i=1;i<=t;++i) scanf("%d",&a[i].val);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (mp[i][j]=='B')
				a[++cnt].x=i,a[cnt].y=j,a[cnt].val=-inf;
	bfs();
	get_ans();
	printf("%d\n",ans);
}
```



​	