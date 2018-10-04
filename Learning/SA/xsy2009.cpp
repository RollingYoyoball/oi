#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=500010*2;
const int MX=20;
char s[MAXN];
int sa[MAXN],rk[MAXN],a[MAXN],b[MAXN],c[MAXN],height[MAXN];
int f[MAXN][21],st[MAXN],r[MAXN],l[MAXN];
int n,m,top,cnt,mx;
ll ans;
int get_sa(int len);
int sort(int len);
int get_height(int len);
int rmq(int len);
bool cmp(int x,int y,int len,int *r)
{return r[x]==r[y]&&r[x+len]==r[y+len];}

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%s",s+1);
	n=strlen(s+1);
	get_sa(n);
	get_height(n);
	top=0;
	for (int i=2;i<=n;++i)
	{
		while (top&&height[i]<height[st[top]]) 
			r[st[top--]]=i-1;
		st[++top]=i;
	}
	while (top) r[st[top--]]=n;
	for (int i=n;i>=2;--i)
	{
		while (top&&height[i]<=height[st[top]])
			l[st[top--]]=i+1;
		st[++top]=i;
	}
	while (top) l[st[top--]]=2;
	ans=(ll)(1+n)*n/2*(n-1);
	for (int i=2;i<=n;++i)
		ans-=(ll)(i-l[i]+1)*(r[i]-i+1)*height[i]*2;
	printf("%lld\n",ans);	
}

int get_sa(int len)
{
	for (int i=1;i<=len;++i) b[i]=i,a[i]=s[i]-'a'+1,mx=max(mx,a[i]);
	sort(len);
	cnt=0;
	for (int l=1;cnt<len;l*=2)
	{
		cnt=0;
		for (int i=len-l+1;i<=len;++i) b[++cnt]=i;
		for (int i=1;i<=len;++i) 
			if (sa[i]>l)
				b[++cnt]=sa[i]-l;
		sort(len);
		swap(a,b);
		cnt=1;
		a[sa[1]]=1;
		for (int i=2;i<=len;a[sa[i++]]=cnt)
			if (!cmp(sa[i],sa[i-1],l,b)) ++cnt;	
		mx=cnt;
	}
}

int sort(int len)
{
	for (int i=0;i<=mx;++i) c[i]=0;
	for (int i=1;i<=len;++i) c[a[b[i]]]++;
	for (int i=1;i<=mx;++i) c[i]+=c[i-1];
	for (int i=len;i>=1;--i) sa[c[a[b[i]]]--]=b[i];
}

int get_height(int len)
{
	for (int i=1;i<=len;++i) rk[sa[i]]=i;
	int k=0;
	for (int i=1;i<=len;++i)
	{
		if (k>0) --k;
		while (s[i+k]==s[sa[rk[i]-1]+k]) ++k;
		height[rk[i]]=k;
	}
}

