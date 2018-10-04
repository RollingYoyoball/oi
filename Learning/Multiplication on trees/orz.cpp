#include<stdio.h>
#include<math.h>
#define mod 1000000007LL
int fa[100010][20];
int find(int i,int j){
    return fa[i][j]=(fa[i][j]==i)?i:find(fa[i][j],j);
}
void merge(int j,int x,int y){
    int f1,f2;
    f1=find(x,j);
    f2=find(y,j);
    if(f1==f2)return;
    fa[f2][j]=f1;
    if(!j)return;
    merge(j-1,x,y);
    merge(j-1,x+(1<<(j-1)),y+(1<<(j-1)));
}
int main(){
	freopen("a.in","r",stdin);
	
    int n,m,i,j,l1,r1,l2,r2;
    scanf("%d%d",&n,&m);
    if(n==1){
        puts("10");
        return 0;
    }
    for(i=1;i<=n;i++){
        for(j=0;j<18;j++)fa[i][j]=i;
    }
    while(m--){
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        if(l1>l2){
            j=l1;
            l1=l2;
            l2=j;
            j=r1;
            r1=r2;
            r2=j;
        }
        j=log2(r1-l1+1.);
        merge(j,l1,l2);
        merge(j,r1-(1<<j)+1,r2-(1<<j)+1);
    }
    j=0;
    for(i=1;i<=n;i++){
        if(find(i,0)==i)j++;
    }
    long long ans;
    ans=9;
    for(i=1;i<j;i++)ans=ans*10LL%mod;
    printf("%lld",ans);
}
