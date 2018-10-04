#include <cstdio>
#include <cstring>
#include <vector>
#define min(a,b) a<b?a:b
using namespace std;
const int N=205,S=233,Mod=1000000007;
int n,m,len[N];
long long mi[100010];
vector<long long>h[N];
long long dis[N][N],f[N][N],g[N][N],ans[N][N];
char str[N][100000];
long long count(int p,int s,int e){
    return (h[p][e]-(h[p][s-1]*mi[e-s+1])%Mod+Mod)%Mod;
}
void pub(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            dis[i][j]=len[j];
            for(int k=1;k<=(min(len[i],len[j]));k++)
            if(count(i,len[i]-k+1,len[i])==count(j,1,k)){
                if(len[j]-k) dis[i][j]=len[j]-k;
            }
        }
}
void floyd(int m){
    if(m==1){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                f[i][j]=dis[i][j];
        return;
    }
    floyd(m/2);
    memset(g,0x7f,sizeof g);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j]=min(g[i][j],f[i][k]+f[k][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) 
            f[i][j]=g[i][j];
    if(m%2==1){
        memset(g,0x7f,sizeof g);
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    g[i][j]=min(g[i][j],f[i][k]+dis[k][j]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) 
                f[i][j]=g[i][j];
    }
}
int main(){
	freopen("a.in","r",stdin);
	
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",str[i]+1);
        len[i]=strlen(str[i]+1);
        h[i].push_back(0);
        h[i][0]=0;
        for(int j=1;j<=len[i];j++)
            h[i].push_back((h[i][j-1]*S+str[i][j]-'a'+1)%Mod);
    }
    mi[0]=1;
    for(int i=1;i<=100000;i++) mi[i]=(mi[i-1]*S)%Mod;
    pub();
    if(m>1) floyd(m-1);
    long long ans=0x3f3f3f3f3f3f3f3fll;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            ans=min(ans,len[i]+f[i][j]);
    printf("%lld\n",ans);
    return 0;
}
