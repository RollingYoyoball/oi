#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define behind 1
#define front -1
using namespace std;
const int M=10,HS=1001,TOT=1e6+10;
const ll inf=1LL<<60;
struct Hash{/*{{{*/
	int hd[TOT],st[TOT],nxt[TOT];
	ll val[TOT];
	int tot;
	void add(int x,int id,ll data){
		st[++tot]=id; nxt[tot]=hd[x]; hd[x]=tot; val[tot]=data;
	}
	void insert(int id,ll data){
		int x=id%HS;
		for (int i=hd[x];i;i=nxt[i])
			if (st[i]==id){val[i]=max(val[i],data);return;}
		add(x,id,data);
	}
	void TakeOut(int *rec1,ll *rec2,int &len){
		len=0;
		for (int i=0;i<HS;++i)
			for (int j=hd[i];j;j=nxt[j])
				rec1[++len]=st[j],rec2[len]=val[j];
	}
	void clear(){
		for (int i=0;i<HS;++i) hd[i]=0;
		tot=0;
	}
}h[2];/*}}}*/
int pw[M],rec_st[TOT];
ll rec_val[TOT],v[110][10];
int n,m,now,pre,len;
ll ans;
void solve();
void dp(int i,int j);
int find(int st,int x,int step);
int query(int st,int x){st>>=((x-1)<<1); return st-((st>>2)<<2);}
void add_st(int st,int j,ll val){h[now].insert(j==m?((st-query(st,m+1)*pw[m])<<2):st,val);}
void change(int &st,int x,int val){st+=(val-query(st,x))*pw[x-1];}
void prework();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			scanf("%lld",&v[i][j]);
	prework();
	solve();
	printf("%lld\n",ans);
}

void prework(){
	pw[0]=1;
	for (int i=1;i<M;++i) pw[i]=pw[i-1]<<2;
	ans=-inf;
}

int find(int st,int x,int step){
	int cnt=1,mark=query(st,x),tmp;
	x+=step;
	for (;cnt;x+=step){
		tmp=query(st,x);
		if (!tmp) continue;
		if (tmp==mark) ++cnt;
		else --cnt;
	}
	return x-step;
}

void solve(){
	now=1,pre=0;
	h[pre].insert(0,0);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			h[now].clear();
			dp(i,j);
			swap(pre,now);
		}
}

void dp(int i,int j){
	int st,plugl,plugu,pos;
	ll val;
	h[pre].TakeOut(rec_st,rec_val,len);
	while (len){
		st=rec_st[len]; val=rec_val[len]; --len;
		plugl=query(st,j);
		plugu=query(st,j+1);
		if (plugl==0&&plugu==0){
			add_st(st,j,val);
			if (i<n&&j<m){
				change(st,j,1);
				change(st,j+1,2);
				add_st(st,j,val+v[i][j]);
			}
		}
		else if (plugl==0||plugu==0){
			if (i<n){
				change(st,j,plugu+plugl);
				change(st,j+1,0);
				add_st(st,j,val+v[i][j]);
			}
			if (j<m){
				change(st,j,0);
				change(st,j+1,plugu+plugl);
				add_st(st,j,val+v[i][j]);
			}
		}
		else if (plugl==1&&plugu==1){
			pos=find(st,j+1,behind);
			change(st,j,0);
			change(st,j+1,0);
			change(st,pos,1);
			add_st(st,j,val+v[i][j]);
		}
		else if (plugl==2&&plugu==2){
			pos=find(st,j,front);
			change(st,j,0);
			change(st,j+1,0);
			change(st,pos,2);
			add_st(st,j,val+v[i][j]);
		}
		else if (plugl==1&&plugu==2){
			int check=true;
			for (int tmp=1;tmp<=m+1&&check;++tmp)//only one
				if (tmp!=j&&tmp!=j+1&&query(st,tmp)) check=false;
			if (val+v[i][j]==32)
				int debug=1;
			if (check) 
				ans=max(ans,val+v[i][j]);
		}
		else if (plugl==2&&plugu==1){
			change(st,j,0);
			change(st,j+1,0);
			add_st(st,j,val+v[i][j]);
		}
	}
}
