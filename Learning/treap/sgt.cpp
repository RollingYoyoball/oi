#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1e5+10;
const int alpha=0.75;
int flag;
struct xxx
{
	int lch[MAXN],rch[MAXN],sz[MAXN],sum[MAXN],cnt[MAXN];//sz=realnode sum=all
	int val[MAXN],a[MAXN];
	bool del[MAXN];
	int tot,rt;
	int rebuild(int x)
	{
		a[0]=0;
		dfs(x);
		rt=build(x,1,a[0]);
	}
	int build(int x,int l,int r)
	{
		if (l>r) return 0;
		int mid=l+r>>1;
		x=a[mid]; sz[x]=r-l+1;
		sum[x]=cnt[x];
		lch[x]=build(lch[x],l,mid-1);
		rch[x]=build(rch[x],mid+1,r);
		sum[x]+=sum[lch[x]]+sum[rch[x]];
		return x;
	}
	int dfs(int x)
	{
		if (!x) return 0;
		dfs(lch[x]);
		a[++a[0]]=x;
		dfs(rch[x]);
	}
	int newnode(int x)
	{
		lch[++tot]=rch[tot]=sum[tot]=del[tot]=cnt[tot]=0;
		sz[tot]=1;
		val[tot]=x;
		return tot;
	}
	int pushup(int x)
	{
		sz[x]=sz[lch[x]]+sz[rch[x]]+1;
	}
	int insert(int x) {rt=_insert(rt,x);}
	int _insert(int x,int v)
	{
		if (!x)
			x=newnode(v);
		++sum[x];
		if (val[x]==v)
		{
			++cnt[x];
			if (del[x]) del[x]=0,++sz[x];
			return x;
		}
		if (v<val[x]) 
			lch[x]=_insert(lch[x],v);
		else 
			rch[x]=_insert(rch[x],v);
		pushup(x);
		int node_mx=max(sz[lch[x]],sz[rch[x]]);
		if (node_mx>=sz[x]*alpha)
			flag=x;
		else
		{
			if (flag)
			{
				if (flag==lch[x]) lch[x]=rebuild(lch[x]);
				else rch[x]=rebuild(rch[x]);
				flag=0;
			}
		}
		pushup(x);
		return x;
	}
	int erase(int v) {_erase(rt,v);}
	int _erase(int x,int v)
	{
		--sum[x];
		if (v==val[x])
		{
			--cnt[x];
			if (!cnt[x]) del[x]=1,--sz[x];
			return 0;
		}
		if (v<val[x]) _erase(lch[x],v);
		else _erase(rch[x],v);
		pushup(x);
	}
	int get_rank(int x,bool pre) {int tmp=_get_rank(rt,x,pre);
		return _get_rank(rt,x,pre);}
	int _get_rank(int x,int v,bool pre)
	{
		if (!x) return 1;
		if (v==val[x]&&!del[x]) return sum[lch[x]]+1+pre*cnt[x];
		if (v<val[x]) return _get_rank(lch[x],v,pre);
		else return sum[lch[x]]+cnt[x]+_get_rank(rch[x],v,pre);
	}
	int get_kth(int k) {return _get_kth(rt,k);}
	int _get_kth(int x,int k)
	{
		if (!x) return 0;
		if (k>sum[lch[x]]+cnt[x])
			return _get_kth(rch[x],k-sum[lch[x]]-cnt[x]);
		if (k<=sum[lch[x]])
			return _get_kth(lch[x],k);
		return val[x];
	}
	int get_pre(int &ans,int x) {_get_pre(ans,rt,x);}
	int _get_pre(int &ans,int x,int v)
	{
		if (!x) return 0;
		if (v>val[x])
		{
			ans=val[x];
			_get_pre(ans,rch[x],v);
		}
		else
			_get_pre(ans,lch[x],v);
	}
	int get_sub(int &ans,int x) {_get_sub(ans,rt,x);}
	int _get_sub(int &ans,int x,int v)
	{
		if (!x) return 0;
		if (v<val[x])
		{
			ans=val[x];
			_get_sub(ans,lch[x],v);
		}
		else
			_get_sub(ans,rch[x],v);
	}
}sgt;
int n,m;
int ans;

int main()
{
	freopen("a.in","r",stdin);
	
	int op,x;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d %d\n",&op,&x);
		switch(op)
		{
			case 1:sgt.insert(x); break;
			case 2:sgt.erase(x); break; 
			case 3:ans=sgt.get_rank(x,0); break;
			case 4:ans=sgt.get_kth(x); break;
			//case 5:ans=sgt.get_kth(sgt.get_rank(x,0)-1); break;//sgt.get_pre(ans,x);
			//case 6:ans=sgt.get_kth(sgt.get_rank(x,1)); break;//sgt.get_sub(ans,x);
			case 5:sgt.get_pre(ans,x); break;
			case 6:sgt.get_sub(ans,x); break;
		}
		if (op!=1&&op!=2) printf("%d\n",ans);
	}
}
