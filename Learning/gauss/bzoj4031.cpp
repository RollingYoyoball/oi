#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000000
#define ll long long
using namespace std;
const int MAXN=9*9+10;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};
ll a[MAXN][MAXN];
int id[10][10];
char map[10][10];
int n,m,cnt,mark;
ll ans;
int add(int x,int y);
int gauss(int n);
ll Abs(ll x){return x<0?-x:x;}
bool ok(int x,int y);
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
#endif
    scanf("%d%d\n",&n,&m);
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            scanf("%c",&map[i][j]);
            if (map[i][j]=='.') id[i][j]=++cnt;
        }
        scanf("\n");
    }
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            if (map[i][j]=='.')
                add(i,j);
    mark=0;
    ans=1;
    gauss(cnt-1);
    if (mark) ans=MOD-ans;
    printf("%lld\n",ans);
}
 
int add(int x,int y){
    int xx=id[x][y],yy;
    for (int i=0;i<4;++i){
        if (!ok(x+dx[i],y+dy[i])) continue;
        yy=id[x+dx[i]][y+dy[i]];
        ++a[xx][xx]; a[xx][yy]=-1;
    }
}
 
int gauss(int n){
    int tmp;
    for (int i=1;i<=n;++i){
        tmp=i;
        for (int j=i+1;j<=n;++j)
            if (Abs(a[j][i])>Abs(a[tmp][i])) tmp=j;
        if (tmp!=i){
            mark^=1;
            for (int j=1;j<=n;++j) swap(a[tmp][j],a[i][j]);
        }
        for (int j=i+1;j<=n;++j){
            while (a[j][i]){
                ll t=a[j][i]/a[i][i];
                for (int k=1;k<=n;++k)
                    a[j][k]=(a[j][k]+MOD-t*a[i][k]%MOD)%MOD;
                if (a[j][i]==0) break;
                mark^=1;
                for (int k=1;k<=n;++k)
                    swap(a[j][k],a[i][k]);
            }
        }
    }
    for (int i=1;i<=n;++i) 
        ans=ans*a[i][i]%MOD;
}
 
bool ok(int x,int y){
    if (x<1||x>n||y<1||y>m) return false;
    if (map[x][y]!='.') return false;
    return true;
}
