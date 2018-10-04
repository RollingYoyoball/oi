#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define sec second
#define fir first
#define mp make_pair
#define ll long long
using namespace std;
const int MAXN=1e5+10;
const int TOP=20;
pair<pair<int,int>,int> pos[MAXN];
struct xxx{
	int y,next;
	char ch;
}a[MAXN*2];
char rec[MAXN];
int h[MAXN],imp[MAXN],st[MAXN];
int rk[MAXN][TOP+1],pre[MAXN][TOP+1],fa[MAXN],dep[MAXN],loc[MAXN];
int lcp[MAXN],pres[MAXN],nxts[MAXN];
int n,tot,d,lg,m,t,top;
ll ans;
int add(int x,int y,char ch);
int dfs(int fa,int x,int d);
int prework();
int get_lcp(int x,int y);
int solve(int t);
bool cmp(int x,int y){return rk[x][lg]==rk[y][lg]?dep[x]<dep[y]:rk[x][lg]<rk[y][lg];}
//注意因为是。。树上sa多串，然后这样搞出来可能会有两个串完全相同就排名相同了，所以如果说要求不相同的排名的话第二关键字是这个串的长度也就是dep

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	char s[10];
	int x,y;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		scanf("%d%d%s",&x,&y,s);
		add(x,y,s[0]); add(y,x,s[0]);
	}
	int t;
	dfs(0,1,1);
	lg=log(lg-1)/log(2.0);
	prework();
	scanf("%d",&m);
	for (int o=1;o<=m;++o){
		scanf("%d",&t);
		for (int i=1;i<=t;++i)
			scanf("%d",imp+i);
		solve(t);
	}
}

int dfs(int fa,int x,int d){
	int u;
	pre[x][0]=fa;lg=max(lg,d); dep[x]=d;
	for (int i=h[x];i!=-1;i=a[i].next){
		u=a[i].y;
		if (u==fa) continue;
		rec[d]=a[i].ch;
		rk[u][0]=a[i].ch-'a'+1;
		dfs(x,u,d+1);
	}
}

int add(int x,int y,char ch){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].ch=ch;
}

int prework(){
	for (int j=1;j<=lg;++j){
		for (int i=1;i<=n;++i){
			pos[i]=mp(mp(rk[i][j-1],rk[pre[i][j-1]][j-1]),i);
			pre[i][j]=pre[pre[i][j-1]][j-1];
		}
		sort(pos+1,pos+1+n);
		rk[pos[1].sec][j]=1;
		int p=1;
		for (int i=2;i<=n;++i)
			rk[pos[i].sec][j]=(pos[i].fir==pos[i-1].fir)?p:++p;
	}
}

int get_lcp(int x,int y){
	int ret=0,len=min(dep[x],dep[y])-1;
	for (int i=lg;i>=0;--i)
		if (rk[x][i]==rk[y][i]&&(1<<i)+ret<=len){
			ret+=1<<i;
			x=pre[x][i],y=pre[y][i];
		}
	return ret;
}

int solve(int t){
	sort(imp+1,imp+1+t,cmp);
	if (imp[1]==1){
		for (int i=2;i<=t;++i) imp[i-1]=imp[i];
		--t;
	}
	for (int i=1;i<t;++i){
		lcp[i]=get_lcp(imp[i],imp[i+1]);
	}
	top=0;
	st[++top]=0; lcp[0]=-1;
	for (int i=t;i>=1;--i){
		pres[i]=0;
		while (top&&lcp[i]<lcp[st[top]]){
			pres[st[top]]=i,--top;
		}
		st[++top]=i;
	}	
	top=0; st[++top]=t; lcp[t]=-1;
	for (int i=1;i<=t;++i){
		nxts[i]=t+1;
		while (top&&lcp[i]<=lcp[st[top]]){
			nxts[st[top]]=i,--top;
		}
		st[++top]=i;
	}
	ans=0;
	for (int i=1;i<=t;++i)
		ans+=(ll)lcp[i]*(i-pres[i])*(nxts[i]-i);
	printf("%lld\n",ans);
}
