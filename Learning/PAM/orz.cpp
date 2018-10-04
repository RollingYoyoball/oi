#include<iostream>
#include<stdio.h>
#include<string.h>
#define N 120000 
using namespace std;
int fail[N],len[N],s[N],ch[N][5],f[N];
char str[N]; 
int last,p,tot,n,q[N],T,sub[N],ans,op;
inline int hash1(char c){
    if(c=='A')return 1;
    if(c=='G')return 2;
    if(c=='C')return 3;
    if(c=='T')return 4;
}
inline int newnode(int x){
	ch[p][4]=0;ch[p][1]=0;ch[p][2]=0;ch[p][3]=0;
    len[p]=x;
    return p++;
}
int init(){
	memset(sub,0,sizeof(sub));
    tot=0;
    p=0;
    last=0;
    newnode(0);
    newnode(-1);
    fail[0]=1;
    s[0]=-1;
}
int get(int x){
    while(s[tot-len[x]-1]!=s[tot])x=fail[x];
    return x;
}
int insert(int c){
    tot++;
    s[tot]=c;
    int k=get(last);
    if(!ch[k][c]){
        int now=newnode(len[k]+2);
        fail[now]=ch[get(fail[k])][c];
        ch[k][c]=now;
        if(len[now]<=2)f[now]=len[now];
        else{
            int x=sub[k];
            while((s[tot-len[x]-1]!=s[tot])||(((len[x]+2)<<1)>len[now]))x=fail[x];
            sub[now]=ch[x][c];
        }
    }
    last=ch[k][c];
}
int bfs(){
    int head=0,tail=1;
    q[1]=0;
    f[0]=1;
    int y;
    while(head<tail){
        head++;
        int x=q[head];
        for(int i=1;i<=4;++i){
            if(ch[x][i]){
     		 	f[y=ch[x][i]]=f[x]+1;
    	 	 	f[y]=min(f[y],len[y]/2-len[sub[y]]+f[sub[y]]+1);
      			ans=min(ans,op-len[y]+f[y]);
     			q[++tail]=y;
    		}
        }
    }
}
int main(){
	freopen("a.in","r",stdin);
//	freopen("1.out","w",stdout);
    scanf("%d",&T);
    while(T){
        T--;
        scanf("%s",str+1);
        int n=strlen(str+1);
        init();
        s[n+1]=-1;
        for(int i=1;i<=n;++i)insert(hash1(str[i]));
        for(int i=1;i<=tot;i++)if(len[i]%2==1)f[i]=len[i];
        ans=n;
        op=n;
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
