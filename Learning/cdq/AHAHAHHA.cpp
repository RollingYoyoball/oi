#include <iostream>
#include <cstdio>
using namespace std;
const int go[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int ans=0,a[60][60],j,i,mx=0;
bool b[60][60];
inline int read(){
    int k=0;char c=getchar();
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar())k=(k<<3)+(k<<1)+c-'0';
    return k;
}
int dfs(int x,int y){
    int ret=1;b[x][y]|=1;
    for(int i=0;i<4;++i){
        int nx=x+i[go][0],ny=y+i[go][1];
        ((a[x][y]>>i)&1^1)&&(nx[b][ny]^1)?ret+=dfs(nx,ny):1;
    }
    return ret;
}
int main(){
  //  freopen("tmp.in","r",stdin);
    int n=read(),m=read();
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
            i[a][j]=read();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            ans+=(i[b][j]^1)?(bool)(mx=max(dfs(i,j),mx)):0;
    printf("%d\n%d\n",ans,mx);
}

