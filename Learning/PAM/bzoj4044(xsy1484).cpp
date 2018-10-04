#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=1e5+10;
const int C=4;
char s[MAXN];
int lis[MAXN];
int n,m,cnt,T,ans;
struct Pam{
	int ch[MAXN][C],fail[MAXN],len[MAXN],val[MAXN],trans[MAXN];
	int f[MAXN];
	queue<int> q;
	int last,tot;
	int newnode(int Len){
		int ret=++tot;
		for (int i=0;i<C;++i) ch[ret][i]=0;
		len[ret]=Len;
		return ret;
	}
	int find(int x,int now){
		while (s[x]!=s[x-len[now]-1]) now=fail[now];
		return now;
	}
	int expand(int x,int c){
		int cur=find(x,last),tmp,now;
		if (!ch[cur][c]){
			now=newnode(len[cur]+2);
			fail[now]=ch[find(x,fail[cur])][c];
			val[now]=c;
			if (len[now]<=2) trans[now]=fail[now];
			else{
				tmp=trans[cur];
				while (s[x-len[tmp]-1]!=s[x]||(len[tmp]+2)*2>len[now])
					tmp=fail[tmp];
				trans[now]=ch[tmp][c];
			}
			ch[cur][c]=now;
		}
		last=ch[cur][c];
	}
	int init(){
		tot=-1; last=0;
		newnode(0); newnode(-1);
		fail[0]=1;
	}
	int dp(){
		for (int i=2;i<=tot;++i)
			if (len[i]&1) f[i]=len[i];
			else f[i]=len[i]/2+1;
		int u,v;
		q.push(0);
		f[q.front()]=1;
		while (!q.empty()){
			v=q.front(); q.pop();
			for (int i=0;i<4;++i)
				if (ch[v][i]){
					u=ch[v][i];
					f[u]=min(f[u],min(f[v]+1,len[u]/2-len[trans[u]]+f[trans[u]]+1));
					ans=min(ans,n-len[u]+f[u]);
					q.push(u);

				}
		}
	}
}pam;
int id(char ch);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif

	scanf("%d",&T);
	for (int o=1;o<=T;++o){
		scanf("%s",s+1);
		n=strlen(s+1);
		pam.init();
		for (int i=1;i<=n;++i){
			pam.expand(i,id(s[i]));
		}
		ans=n;
		pam.dp();
		printf("%d\n",ans);
	}
}

int id(char ch){
	if (ch=='A') return 0;
	if (ch=='T') return 1;
	if (ch=='C') return 2;
	return 3;
}

