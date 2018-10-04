#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=30010*2;
int s[MAXN];
int sa[MAXN],rk[MAXN],a[MAXN],b[MAXN],ans[MAXN],c[MAXN];
//bool used[MAXN/2];
int n,m,mx,cnt;
int get_sa(int len);
int sort(int len);
int work(int len);
bool cmp(int x,int y,int len,int *r)
{return r[x]==r[y]&&r[len+x]==r[len+y];}

int main()
{
	freopen("a.in","r",stdin);

	char ch;
	scanf("%d\n",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%c\n",&ch);
		s[i]=ch-'A'; s[n*2-i+2]=s[i];
		mx=max(s[i],mx);
	}
	s[n+1]=mx+1;
	s[2*n+1]=mx+1;
	++mx;
	get_sa(n*2+2);
	work(n*2+2);
	for (int i=1;i<=n;++i) 
	{
		printf("%c",ans[i]+'A');
		if (i%80==0) printf("\n");
	}
}

int get_sa(int len)
{
	for (int i=1;i<=len;++i) b[i]=i,a[i]=s[i];
	sort(len);
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

int work(int len)
{
	for (int i=1;i<=len;++i) rk[sa[i]]=i;
	int p1=1,p2=n+2,cnt=0;
	while (cnt<=n)
	{
		if (rk[p1]<rk[p2]) 
			ans[++cnt]=s[p1],++p1;
		else
			ans[++cnt]=s[p2],++p2;
	//	if (used[p1]||used[p2]) break;
	}	
}
