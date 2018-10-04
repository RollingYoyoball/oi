#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 2147483647
using namespace std;
const int MAXN=1e5+10;
int id[MAXN];
int lens;
struct xxx
{
	int son[MAXN*2][26],len[MAXN*2],suf[MAXN*2],out[MAXN*2],cnt[MAXN*2];
	int c[MAXN*4];
	int tot,last;
	int newnode(int x)
	{
		len[++tot]=x; cnt[tot]=1; return tot;
	}
	int insert(int ch,int pos)
	{
		int p=last,np=newnode(len[p]+1),q,nq;
		for (;p&&!son[p][ch];p=suf[p]) son[p][ch]=np;
		if (!p) suf[np]=1;
		else
		{
			q=son[ch][ch];
			if (len[q]!=len[p]+1)
			{
				nq=newnode(len[p]+1);
				memcpy(son[nq],son[q],sizeof(son[q]));
				suf[nq]=suf[q],suf[q]=suf[np]=nq;
				out[suf[q]]+=2;
				for (;p&&son[p][ch]==q;p=suf[p]) son[p][ch]=nq;
			}
			else suf[np]=q;
		}
		last=np; id[pos]=last; ++out[suf[np]];
	}
	int calc()
	{
		for (int i=1;i<=tot;++i) if (out[i]==0) c[++c[0]]=i;
		for (int i=1;i<=c[0];++i)
		{
			cnt[suf[c[i]]]+=cnt[c[i]];
			if (--out[suf[c[i]]]==0) c[++c[0]]=suf[c[i]];
		}
	}
}sam;
struct segmentree
{
	int lch[MAXN*2*4],rch[MAXN*2*4],mn[MAXN*2*4],tag[MAXN*2*4];
	int tot;
	int init(int n)
	{
		tot=1;
		build(1,1,n);
	}
	int build(int x,int l,int r)
	{
		mn[x]=inf;
		if (l==r)
			return 0;
		int mid=l+r>>1;
		lch[x]=++tot; build(lch[x],l,mid);
		rch[x]=++tot; build(rch[x],mid+1,r);
		mn[x]=min(mn[lch[x]],mn[rch[x]]);
	}
	int downtag(int x)
	{
		mn[lch[x]]=min(mn[lch[x]],tag[x]); tag[lch[x]]=min(tag[lch[x]],tag[x]);
		mn[rch[x]]=min(mn[rch[x]],tag[x]); tag[rch[x]]=min(tag[rch[x]],tag[x]);
		tag[x]=0;
	}
	int update(int l,int r,int delta) {_update(1,l,r,1,lens,delta);}
	int _update(int x,int l,int r,int lx,int rx,int delta)
	{
		if (l<=lx&&rx<=r)
		{
			tag[x]=min(tag[x],delta);
			mn[x]=min(mn[x],delta);
			return 0;
		}
		int mid=lx+rx>>1;
		if (tag[x]) downtag(x);
		if (l<=mid) _update(lch[x],l,r,lx,mid,delta);
		if (r>mid) _update(rch[x],l,r,mid+1,rx,delta);
		mn[x]=min(mn[lch[x]],mn[rch[x]]);
	}
	int query(int l,int r) {return _query(1,l,r,1,lens);}
	int _query(int x,int l,int r,int lx,int rx)
	{
		if (l<=lx&&rx<=r)
			return mn[x];
		int mid=lx+rx>>1,ret=inf;
		if (tag[x]) downtag(x);
		if (l<=mid) ret=min(ret,_query(lch[x],l,r,lx,mid));
		if (r>mid) ret=min(ret,_query(rch[x],l,r,mid+1,rx));
		mn[x]=min(mn[lch[x]],mn[rch[x]]);
		return ret;
	}
}tree;
char s[MAXN];

int main()
{
	freopen("a.in","r",stdin);

	scanf("%s",s+1);
	lens=strlen(s+1);
	for (int i=1;i<=lens;++i)
		sam.insert(s[i]-'a',i);
	sam.calc();
	tree.init(lens);
	int x=0;
	for (int i=1;i<=lens;++i)
	{
		x=id[i];
		if (sam.cnt[x]!=1) continue;
		tree.update(sam.len[sam.suf[x]],sam.len[x],sam.len[x]-sam.len[sam.suf[x]]+1);
	}
	for (int i=1;i<=lens;++i)
	{
		printf("%d\n",tree.query(i,lens));
	}
}
