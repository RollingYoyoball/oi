//xsy2844
#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000007
using namespace std;
const int MAXN=3*(1e6)+10,SAM=MAXN*2,C=4;
int pos[MAXN][2],rcnt[MAXN],lcnt[MAXN];
char S[MAXN],a[MAXN];
int change(char x);
struct Sam{/*{{{*/
	int ch[SAM][C],len[SAM],suf[SAM],cnt[SAM],loc[SAM];
	int str[SAM],trans[SAM][C],t[SAM],pos[SAM];
	int tot,last,sz;
	void init(){last=++sz;}
	int newnode(int Len){len[++sz]=Len; return sz;}
	int expand(int c){
		int p=last,np=newnode(len[p]+1),q,nq;
		loc[np]=len[p]+1,str[loc[np]]=c;
		for (;p&&!ch[p][c];p=suf[p]) ch[p][c]=np;
		if (!p) suf[np]=1;
		else{
			q=ch[p][c];
			if (len[q]!=len[p]+1){
				nq=newnode(len[p]+1);
				loc[nq]=loc[np];
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				suf[nq]=suf[q]; suf[q]=suf[np]=nq;
				for (;p&&ch[p][c]==q;p=suf[p]) ch[p][c]=nq;
			}
			else suf[np]=q;
		}
		last=np;
		return np;
	}
	void build(){
		for (int i=2;i<=sz;++i)
			trans[suf[i]][str[loc[i]-len[suf[i]]]]=i;
	}
	void addcnt(char *s,int lens){
		int now=1,c;
		for (int i=1;i<=lens;++i){
			c=change(s[i]);
			if (i>len[now]) now=trans[now][c];
			if (!now||str[loc[now]-i+1]!=c) return;
			++cnt[now];
		}
	}
	void sort(){
		for (int i=1;i<=sz;++i) t[i]=0;
		for (int i=1;i<=sz;++i) ++t[len[i]];
		for (int i=1;i<=sz;++i) t[i]+=t[i-1];
		for (int i=sz;i>=1;--i) loc[t[len[i]]--]=i;
	}
	void pushdown(){
		sort();
		for (int i=2;i<=sz;++i)
			cnt[loc[i]]=(cnt[suf[loc[i]]]+cnt[loc[i]])%MOD;
	}
}sam[2];/*}}}*/
int n,m,lens;
void get_ans();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%s",S);
	sam[0].init(); sam[1].init();
	lens=strlen(S);
	for (int i=0;i<lens;++i)
		pos[i][0]=sam[0].expand(change(S[i]));
	for (int i=lens-1;i>=0;--i)
		pos[i][1]=sam[1].expand(change(S[i]));
	sam[0].build();
	sam[1].build();
	scanf("%d",&m);
	int tmp;
	for (int i=1;i<=m;++i){
		scanf("%s",a+1);
		tmp=strlen(a+1);
		sam[0].addcnt(a,tmp);
		sam[1].addcnt(a,tmp);
	}
	get_ans();
}

int change(char x){
	if (x=='A') return 0;
	if (x=='C') return 1;
	if (x=='G') return 2;
	if (x=='T') return 3;
}

void get_ans(){
	int ans=0;
	sam[0].pushdown();
	sam[1].pushdown();
	for (int i=0;i<lens;++i){
		rcnt[i]=sam[1].cnt[pos[i][1]];
		lcnt[i]=sam[0].cnt[pos[i][0]];
	}
	for (int i=0;i<lens;++i)
		ans=(1LL*ans+1LL*lcnt[i]*rcnt[i+1]%MOD)%MOD;
	printf("%d\n",ans);
}