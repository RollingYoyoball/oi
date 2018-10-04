#include <cstdio>
using namespace std;
int n,k,u=0;
double f[2][501];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=n;i>=1;i--,u^=1)
        for(int j=1;j<500;j++)
            f[u][j]=(1.0/k)*((f[u^1][j]*j+j*(j+1)/2)/(j+1.0)+(f[u^1][j+1]+j)/(j+1.0))+
                    f[u^1][j]*(1-1.0/k);
    printf("%.10lf\n",k*f[u^1][1]);
    return 0;
