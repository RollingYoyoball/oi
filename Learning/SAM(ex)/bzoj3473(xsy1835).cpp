#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define ll long long
using namespace std;
const int MAXN=100010*2;
const int C=26;
struct xxx{
	int y,next;
}a[MAXN*2];
int h[MAXN];
string str[MAXN];
int n,m,tot1,k;
int add(int x,int y){a[++tot1].y=y; a[tot1].next=h[x]; h[x]=tot1;}
struct Sam{
	int ch[MAXN][C],suf[MAXN],len[MAXN],cnt[MAXN],sum[MAXN];
	int tot,last;
	set<int> rec[MAXN];
	set<int>::iterator it;
	int newnode(int Len){
		int ret=++tot;
		for (int i=0;i<C;++i) ch[ret][i]=0;
		len[ret]=Len;
		return ret;
	}
	int insert(int c,int id){
		int p=last,np=newnode(len[p]+1),q,nq;
		for (;p&&!ch[p][c];p=suf[p]) ch[p][c]=np;
		if (!p) suf[np]=1;
		else{
			q=ch[p][c];
			if (len[p]+1!=len[q]){
				nq=newnode(len[p]+1);
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				suf[nq]=suf[q],suf[np]=suf[q]=nq;
				for (;p&&ch[p][c]==q;p=suf[p]) ch[p][c]=nq;
			}
			else suf[np]=q;
		}
		last=np; ++cnt[np];
		rec[np].insert(id);
	}
	int init(){last=++tot;}
	int calc(){
		for (int i=1;i<=tot;++i)
			if (suf[i]) add(suf[i],i);
		dfs(1);
	}
	int dfs(int x){
		int u;
		for (int i=h[x];i!=-1;i=a[i].next){
			dfs(u=a[i].y);
			if (rec[x].size()<rec[u].size())
				swap(rec[x],rec[u]);
			for (it=rec[u].begin();it!=rec[u].end();++it)
				rec[x].insert(*it);
		}
		sum[x]=rec[x].size();
	}
}sam;

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int len,x;
	scanf("%d%d",&n,&k);
	sam.init();
	memset(h,-1,sizeof(h));
	for (int i=1;i<=n;++i){
		cin>>str[i];
		len=str[i].length();
		for (int j=0;j<len;++j)
			sam.insert(str[i][j]-'a',i);
		sam.last=1;
	}
	sam.calc();
	if (k>n){
		for (int i=1;i<=n;++i) printf("0\n");
		return 0;
	}
	ll ans;
	for (int now=1;now<=n;++now){
		ans=0;
		len=str[now].length();
		x=1;
		for (int i=0;i<len;++i){
			x=sam.ch[x][str[now][i]-'a'];
			while (sam.sum[x]<k)
				x=sam.suf[x];
			ans+=sam.len[x];
		}
		printf("%lld\n",ans);
	}
}
