#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define behind 1
#define front -1
using namespace std;
const int N=12+3,HS=2333,TOT=1e6+10;
int n,m,edi,edj;
struct Hash{/*{{{*/
	int st[TOT],hd[HS],nxt[TOT];
	ll sum[TOT];
	int tot;
	void add(int x,int id,ll data){
		st[++tot]=id; nxt[tot]=hd[x]; hd[x]=tot; sum[tot]=data;
	}
	void insert(int id,ll data){
		int x=id%HS;
		for (int i=hd[x];i;i=nxt[i])
			if (st[i]==id){sum[i]+=data;return;}
		add(x,id,data);
	}
	void clear(){
		for (int i=0;i<HS;++i) hd[i]=0;
		tot=0;
	}
	void TakeOut(int *rec1,ll *rec2,int &len){
		len=0;
		for (int i=0;i<HS;++i){
			for (int j=hd[i];j;j=nxt[j]){
				rec1[++len]=st[j],rec2[len]=sum[j];
			}
		}
	}
}h[2];/*}}}*/
int mp[N][N],pw[N],rec_st[TOT];
ll rec_sum[TOT];
int now,pre,len;
ll ans;
void init();
void solve();
void dp(int i,int j);
int query(int st,int x){st>>=((x-1)<<1); return st-((st>>2)<<2);}//4 jinzhi
void add_st(int j,int st,ll val){h[now].insert(j==m?((st-query(st,m+1)*pw[m])<<2):st,val);}
void change(int &st,int x,int val){st+=(val-query(st,x))*pw[x-1];}
int find(int st,int x,int mark);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	char ch;
	scanf("%d%d\n",&n,&m);
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			scanf("%c",&ch);
			mp[i][j]=ch=='.';
			if (ch=='.') 
				edi=i,edj=j;
		}
		scanf("\n");
	}
	init();
	solve();
	printf("%lld\n",ans);
}

void init(){
	pw[0]=1;
	for (int i=1;i<=12;++i) pw[i]=pw[i-1]<<2;
	ans=0;
}

void solve(){
	now=1,pre=0;
	h[pre].insert(0,1);
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			h[now].clear();
			if (i==4&&j==1)
				int debug=1;
			dp(i,j);
			swap(now,pre);
		}
	}
}

void dp(int i,int j){
	h[pre].TakeOut(rec_st,rec_sum,len);
	int st,plugl,plugu,nw,pos;
	ll val;
	while (len){
		st=rec_st[len]; val=rec_sum[len]; --len;
		plugl=query(st,j);
		plugu=query(st,j+1);
		if (!mp[i][j]){//not ok
			if (plugl==0&&plugu==0)
				add_st(j,st,val);
			continue;
		}
		if (plugl==0&&plugu==0){
			if (i<n&&j<m){
				nw=st;
				change(nw,j,1);
				change(nw,j+1,2);
				add_st(j,nw,val);
			}
		}
		else if (plugl==0||plugu==0){
			if (i<n){
				nw=st;
				change(nw,j,plugu+plugl);
				change(nw,j+1,0);
				add_st(j,nw,val);
			}
			if (j<m){
				nw=st;
				change(nw,j,0);
				change(nw,j+1,plugu+plugl);
				add_st(j,nw,val);
			}
		}
		else if (plugl==2&&plugu==1){
			nw=st;
			change(nw,j,0);
			change(nw,j+1,0);
			add_st(j,nw,val);
		}
		else if (plugl==1&&plugu==2){
			if (i==edi&&j==edj){
				int check=true;
				for (int tmp=j+2;tmp<=m+1&&check;++tmp)
					if (query(st,tmp)) check=false;
				if (check) ans+=val;//!!!check!!!
			}
		}
		else if (plugl==1&&plugu==1){
			pos=find(st,j+1,behind);
			nw=st;
			change(nw,j,0);
			change(nw,j+1,0);
			change(nw,pos,1);
			add_st(j,nw,val);
		}
		else if (plugl==2&&plugu==2){
			pos=find(st,j,front);
			nw=st;
			change(nw,j,0);
			change(nw,j+1,0);
			change(nw,pos,2);
			add_st(j,nw,val);
		}
	}
}


int find(int st,int x,int step){
	int top=1,mark=query(st,x),tmp;
	x+=step;
	for (;top;x+=step){
		tmp=query(st,x);
		if (!tmp) continue;
		if (tmp==mark) ++top;
		else --top;
	}
	return x-step;
}

