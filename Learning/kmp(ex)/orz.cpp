#include <cstdio>
#include <cstring>
using namespace std;
const int N=150010;
int T,len,nex[N],x,y,z,sum;
char s[N*2];
void count(){
    int i=0,j=-1;
    nex[0]=-1;
    while(i<len){
        if(j==-1||s[i]==s[j]) i++,j++,nex[i]=j;
        else j=nex[j];
    }
    if(len%(len-nex[len])==0) sum=len/(len-nex[len]);
    else sum=1;
}
void getNext(){
    int a=0,p=0;
    nex[0]=len;
    for(int i=1,j=-1;i<len/2;i++,j--){
        if(j<0||i+nex[i-a]>=p){
            if(j<0) p=i,j=0;
            while(p<len&&s[p]==s[j]) p++,j++;
            nex[i]=j;
            a=i;
        }
        else nex[i]=nex[i-a];
    }
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
	
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        x=y=z=0;
        scanf("%s",s); len=strlen(s);
        count();
        for(int i=len;i<len*2;i++) s[i]=s[i-len];
        len*=2; getNext(); len/=2;
        for(int i=0;i<len;i++){
            if(nex[i]>=len) y++;
            else if(s[i+nex[i]]<s[nex[i]]) x++;
            else z++;
        }
        printf("Case %d: %d %d %d\n",t,x/sum,y/sum,z/sum); 
    }
    return 0;
}
