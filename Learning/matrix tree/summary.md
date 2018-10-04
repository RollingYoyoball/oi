### 问题描述

​	给你一个图（有向无向都ok），求这个图的生成树个数



### 一些概念

​	度数矩阵：$a[i][i]=degree[i]$，其他等于$0$

​	入度矩阵：$a[i][i]=in\_degree[i]$，其他等于$0$

​	出度矩阵：$a[i][i]=out\_ degree[i]$，其他等于$0$

​	邻接矩阵：$a[i][j]=[(i,j)\in 边集]$

​	基尔霍夫矩阵：度数矩阵-邻接矩阵



​	外向树：长成树的样子但是边有方向，方向为根-->叶子

​	外向树：长成树的样子但是边有方向，方向为叶子-->根



### 前置技能

**行列式**

​	因为接下来可能需要用到行列式中的某些概念所以还是简单讲一下吧（额只挑部分来讲毕竟我比较菜qwq）

​	上三角矩阵：就是。。只有主对角线及其上方的位置有值的行列式，主对角线以下的部分都是$0$

​	行列式的求值：我们可以先用高斯消元把这个行列式消成一个上三角矩阵的形式然后直接把对角线上的数乘起来得到这个行列式的值

​	余子式：一个行列式的余子式就是这个行列式去掉任意一行一列后剩下的那个少了一维的行列式



### 具体内容

**无向图的生成树计数**

​	无向图的话生成树个数就是这个图的基尔霍夫矩阵的任意一个余子式的行列式值

**有向图的生成树计数**

​	有向图的话分成两种情况：

​	1、求外向树：那么将无向图中的度数矩阵改成入度矩阵

​	2、求内向树：将无向图种的度数矩阵改成出度矩阵

​	不过需要特别注意的一点是：有向图的话余子式去掉的行、列必须是根节点对应的那个

~~（是不是特别特别简洁明了ovo）~~



### 证明

​	这是一个要慢慢填的坑。。。



### 例题

​	这里放一道模板题好了，另外还有几道相对来说貌似也是挺裸的，会在最后提供传送门这里就不贴详细啦

[Portal-->bzoj4031小z的房间](https://www.lydsy.com/JudgeOnline/problem.php?id=4031)

​	需要稍微注意一下的是，对于不能去的房间，要直接整个房间删掉（因为根本就不在连通的考虑范围内），还有就是注意这个模数不是质数所以要辗转相除一下（其实就是高消那里换成不为$0$就一直除除除除除就好了嗯）

​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int N=110,MOD=1e9;
const int dx[2]={-1,0},dy[2]={0,1};
ll a[N][N],rec[N][N],id[N][N];
char mp[N][N];
int n,m,ans,cnt;
void prework();
int solve(int n);
bool ok(int x,int y);
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d\n",&n,&m);
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j)
            scanf("%c",&mp[i][j]);
        scanf("\n");
    }
    prework();
    ans=solve(cnt-1);
    printf("%d\n",ans);
}
 
void prework(){
    int x,y,id1,id2;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            if (mp[i][j]=='.') id[i][j]=++cnt;
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            if (!ok(i,j)) continue;
            id1=id[i][j];
            for (int k=0;k<2;++k){
                x=i+dx[k]; y=j+dy[k];
                if (!ok(x,y)) continue;
                id2=id[x][y];
                ++a[id1][id1]; ++a[id2][id2];
                --a[id1][id2]; --a[id2][id1];
            }
        }
    }
}
 
bool ok(int x,int y){
    if (x<1||x>n||y<1||y>m) return false;
    if (mp[x][y]=='*') return false;
    return true;
}
 
int solve(int n){
    int id,mark=1;
    int tmp;
    for (int i=1;i<=n;++i){
        id=i;
        for (int j=i+1;j<=n;++j)
            if (a[j][i]){id=j;break;}
        if (id!=i){
            mark=-mark;
            for (int j=1;j<=n;++j) swap(a[id][j],a[i][j]);
        }
        for (int j=i+1;j<=n;++j){
            while (a[j][i]){
                tmp=a[j][i]/a[i][i];
                for (int k=1;k<=n;++k)
                    a[j][k]=(1LL*a[j][k]+MOD-1LL*tmp*a[i][k]%MOD)%MOD;
                if (a[j][i]==0) break;
                mark=-mark;
                for (int k=1;k<=n;++k)
                    swap(a[j][k],a[i][k]);
            }
        }
    }
    int ret=mark;
    for (int i=1;i<=n;++i) 
        ret=1LL*ret*a[i][i]%MOD;
    return (ret+MOD)%MOD;
}
```



​	其他的一些题目（是blog的传送门哦，题面传送门的话在blog里面也有）

[Portal-->bzoj4894天赋](https://www.cnblogs.com/yoyoball/p/9226287.html)

[Portal-->bzoj1002轮状病毒（这题很假对这题很假）](https://www.cnblogs.com/yoyoball/p/9226259.html)

[Portal-->bzoj4596黑暗前的幻想乡](https://www.cnblogs.com/yoyoball/p/9226226.html)

