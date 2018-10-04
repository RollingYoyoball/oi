#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define front -1
#define behind 1
using namespace std;
const int N=10,HS=2333,TOT=1e6+10;
const ll inf=1LL<<60;
struct Hash{/*{{{*/
	int nxt[TOT],id[TOT],st[TOT],hd[TOT];
	ll val[TOT];
	int tot;
	void add(int x,int id,ll data){
		st[++tot]=id; nxt[tot]=hd[x]; hd[x]=tot; val[tot]=data;
	}
	void insert(int id,ll data){
		if (id==1)
			int debug=1;
		int x=id%HS;
		for (int i=hd[x];i;i=nxt[i])
			if (st[i]==id){val[i]=max(val[i],data);return;}
		add(x,id,data);
	}
	void clear(){for (int i=0;i<HS;++i) hd[i]=0;tot=0;}
	void TakeOut(int *rec1,ll *rec2,int &len){
		len=0;
		for (int i=0;i<HS;++i)
			for (int j=hd[i];j;j=nxt[j])
				rec1[++len]=st[j],rec2[len]=val[j];
	}
}h[2];/*}}}*/
int rec_st[TOT],pw[N];
ll rec_val[TOT],v[110][N];
ll ans;
int n,m,now,pre,len;
void prework();
int query(int st,int x){st>>=((x-1)<<1);return st-((st>>2)<<2);}
void change(int &st,int x,int val){st+=(val-query(st,x))*pw[x-1];}
void add_st(int st,int j,ll val){h[now].insert(j==m?(st-query(st,m+1)*pw[m])<<2:st,val);}
int find(int st,int x,int step);
void solve();
void dp(int i,int j);
int calc(int st);

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
	for (int i=1;i<N;++i) pw[i]=pw[i-1]<<2;
	ans=-inf;
}

int find(int st,int x,int step){
	int cnt=1,mark=query(st,x),tmp;
	for (x+=step;cnt;x+=step){
		tmp=query(st,x);
		if (!tmp||tmp==3) continue;
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
			swap(now,pre);
		}
}

int calc(int st){
	int ret=0;
	for (;st;st>>=2)
		ret+=(st-((st>>2)<<2))==3;
	return ret;
}

void dp(int i,int j){
	int st,plugl,plugu,pos,which,dir,nw;
	ll val;
	h[pre].TakeOut(rec_st,rec_val,len);
	while (len){
		st=rec_st[len]; val=rec_val[len]; --len;
		plugl=query(st,j);
		plugu=query(st,j+1);

		nw=st;
		if (plugl==0&&plugu==0){//(0,0)
			add_st(st,j,val);
			if (i<n&&j<m)
				change(st,j,1),change(st,j+1,2),add_st(st,j,val+v[i][j]);

			if (calc(nw)<=1){
				if (i<n)
					change(nw,j,3),change(nw,j+1,0),add_st(nw,j,val+v[i][j]);
				if (j<m)
					change(nw,j,0),change(nw,j+1,3),add_st(nw,j,val+v[i][j]);
			}
		}
		else if (plugl==0||plugu==0){
			if (i<n)
				change(nw,j,plugu+plugl),change(nw,j+1,0),add_st(nw,j,val+v[i][j]);
			if (j<m)
				change(nw,j,0),change(nw,j+1,plugu+plugl),add_st(nw,j,val+v[i][j]);

			which=plugl?j:j+1,dir=plugl+plugu==1?behind:front;
			if (plugu+plugl==3){//(0,3)  (3,0)
				int flag=true;
				for (int tmp=1;tmp<=m+1&&flag;++tmp)
					if (tmp!=which&&query(st,tmp)) flag=false;
				if (flag)
					ans=max(ans,val+v[i][j]);
			}
			else{// (0,1/2)  (1/2,0)
				pos=find(st,which,dir);
				change(nw,pos,3); change(nw,j,0); change(nw,j+1,0);
				add_st(nw,j,val+v[i][j]);
			}
		}
		else if (plugl==plugu&&plugu<=2){//(1,1)   (2,2)
			which=plugl==1?j+1:j; dir=plugl==1?behind:front;
			pos=find(st,which,dir);
			change(nw,pos,plugl); change(nw,j,0); change(nw,j+1,0);
			add_st(nw,j,val+v[i][j]);
		}
		else if ((plugl==3&&plugu==3)||(plugl==1&&plugu==2)){//(3,3)  (1,2)
			int flag=true;
			for (int tmp=1;tmp<=m+1&&flag;++tmp)
				if (tmp!=j&&tmp!=j+1&&query(st,tmp)) flag=false;
			if (flag)
				ans=max(ans,val+v[i][j]);
		}
		else if (plugl==2&&plugu==1){//(2,1)
			change(nw,j,0); change(nw,j+1,0);
			add_st(nw,j,val+v[i][j]);
		}
		else if (plugl<=2&&plugu==3){//(1/2,3)
			dir=plugl==1?behind:front;
			pos=find(st,j,dir);
			change(nw,pos,3); change(nw,j,0); change(nw,j+1,0);
			add_st(nw,j,val+v[i][j]);
		}
		else if (plugl==3&&plugu<=2){//(3,1/2)
			dir=plugu==1?behind:front;
			pos=find(st,j+1,dir);
			change(nw,pos,3); change(nw,j,0); change(nw,j+1,0);
			add_st(nw,j,val+v[i][j]);
		}
	}
}
