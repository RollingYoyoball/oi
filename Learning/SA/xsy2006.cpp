#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int MAXN=100010*2;
char s[MAXN];
int sa[MAXN],rk[MAXN],a[MAXN],b[MAXN],c[MAXN];
int n,m,cnt,mx;
int get_sa(int len);
int sort(int len);
int work(int len);
bool cmp(int x,int y,int len,int *r)
{return r[x]==r[y]&&r[x+len]==r[y+len];}
int change(int x)
{return x==0?n:x;}

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%s",s+1);
	n=strlen(s+1);
	int x;
	for (int i=1;i<=n;++i)
		s[n+i]=s[i],x=s[i],mx=max(mx,x);
	s[2*n+1]=mx+1;
	++mx; 
	get_sa(n*2+1);
	int ans=n,loc;
	for (int i=1;i<=n;++i) rk[sa[i]]=i;
	for (int i=1;i<=n*2;++i)
		if (sa[i]<=n) printf("%c",s[change((sa[i]+n-1)%n)]);
}

int get_sa(int len)
{
	for (int i=1;i<=len;++i) b[i]=i,a[i]=s[i];
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
	for (int i=1;i<=len;++i) ++c[a[b[i]]];
	for (int i=1;i<=mx;++i) c[i]+=c[i-1];
	for (int i=len;i>=1;--i) sa[c[a[b[i]]]--]=b[i];
}

