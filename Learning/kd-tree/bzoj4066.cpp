#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=5*(1e5)+10;
const int N=2*(1e5)+10;
const int TOP=10000;
int D,all=233,cnt;
ll ans;
int n;
struct dian{
	int data[2],val;
	dian(){}
	dian(int x,int y,int val1){data[0]=x,data[1]=y,val=val1;}
	friend bool operator <(dian x,dian y)
	{return x.data[D]<y.data[D];}
	friend bool operator ==(dian x,dian y)
	{return x.data[0]==y.data[0]&&x.data[1]==y.data[1];}
	friend bool operator <=(dian x,dian y)
	{return x.data[0]<=y.data[0]&&x.data[1]<=y.data[1];}
}now;
struct kdtree{
	int lch[N],rch[N],mx[N][2],mn[N][2];
	ll sum[N];
	dian val[N];
	int rt,tot;
	int update(int x,int d){
		sum[x]+=sum[d];
		for (int i=0;i<2;++i)
			mx[x][i]=max(mx[d][i],mx[x][i]),mn[x][i]=min(mn[d][i],mn[x][i]);
	}
	int pushup(int x){
		sum[x]=val[x].val;
		for (int i=0;i<2;++i)
			mx[x][i]=mn[x][i]=val[x].data[i];
		if (lch[x]) update(x,lch[x]);
		if (rch[x]) update(x,rch[x]);
	}
	int newnode(int x,int y,int delta){
		val[++tot]=dian(x,y,delta);
		return tot;
	}
	int rebuild(){rt=_rebuild(1,tot,0);}
	int _rebuild(int l,int r,int now){
		if (l>r) return 0;
		D=now;
		int mid=l+r>>1;
		nth_element(val+l,val+mid,val+r+1);
		lch[mid]=_rebuild(l,mid-1,now^1);
		rch[mid]=_rebuild(mid+1,r,now^1);
		pushup(mid);
		return mid;
	}
	int insert(int x,int y,int delta){_insert(rt,dian(x,y,delta),0);}
	int _insert(int &x,dian delta,int now){
		if (!x){
			x=newnode(delta.data[0],delta.data[1],delta.val);
			pushup(x);
			return 0;
		}
		if (val[x]==delta){
			val[x].val+=delta.val;
			pushup(x);
			return 0;
		}
		D=now;
		if (delta<val[x])
			_insert(lch[x],delta,now^1);
		else
			_insert(rch[x],delta,now^1);
		pushup(x);
	}
	bool in(dian x,dian up,dian dw){return up<=x&&x<=dw;}
	int check(int x,dian up,dian dw){
		int ret=0;
		if (up<=dian(mn[x][0],mn[x][1],0)&&dian(mx[x][0],mx[x][1],0)<=dw) return all;
		if (mx[x][0]<up.data[0]||mx[x][1]<up.data[1]) return 0;
		if (dw.data[0]<mn[x][0]||dw.data[1]<mn[x][1]) return 0;
		return 1;
	}
	int query(int x1,int y1,int x2,int y2){_query(rt,dian(x1,y1,0),dian(x2,y2,0));}
	int _query(int x,dian up,dian dw){
		if (in(val[x],up,dw)) ans+=val[x].val;
		int tmp;
		if (lch[x]){
			tmp=check(x,up,dw);
			if (tmp==all) ans+=sum[lch[x]];
			else if (tmp) _query(lch[x],up,dw);
		}
		if (rch[x]){
			tmp=check(x,up,dw);
			if (tmp==all) ans+=sum[rch[x]];
			else if (tmp) _query(rch[x],up,dw);
		}
	}
}kd;

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int op,x,y,A,x1,x2,y1,y2;
	scanf("%d",&n);
	cnt=TOP;
	ans=0;
	while (1){
		scanf("%d",&op);
		if (op==3) break;
		if (op==1){
			scanf("%d%d%d",&x,&y,&A);
			x^=ans; y^=ans; A^=ans;
			kd.insert(x,y,A);
			if (kd.tot==cnt) 
				kd.rebuild(),cnt+=TOP;
		}
		else if (op==2){
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1^=ans; y1^=ans; x2^=ans; y2^=ans;
			ans=0;
			kd.query(x1,y1,x2,y2);
			printf("%lld\n",ans);
		}
	}
}
