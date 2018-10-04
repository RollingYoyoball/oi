#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=100010*2;
const int MX=20;
char s[MAXN];
int sa[MAXN],rk[MAXN],a[MAXN],b[MAXN],c[MAXN],height[MAXN];
int f[MAXN][21];
int n,m,ans,cnt,mx;
int get_sa(int len);
int sort(int len);
int get_height(int len);
int rmq(int len);
int get_mn(int x,int y);
bool cmp(int x,int y,int len,int *r)
{return r[x]==r[y]&&r[x+len]==r[y+len];}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	scanf("%s",s+1);
	n=strlen(s+1);
	get_sa(n);
	get_height(n);
	rmq(n);
	scanf("%d",&m);
	int x,y,l,r;
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d%d%d\n",&x,&y,&l,&r);
//		printf("%d %d %d %d\n",x,y,l,r);
		ans=get_mn(rk[x],rk[l]);
		ans=min(ans,min(y-x+1,r-l+1));
		printf("%d\n",ans);
	}
}

int get_sa(int len)
{
	for (int i=1;i<=len;++i) b[i]=i,a[i]=s[i]-'a'+1,mx=max(mx,a[i]);
	//a[i]的值如果为0的话会出问题？原因: sa[i-1]+l或者sa[i]+l会出现超过总长度的情况，这个时候如果是0的话，都会相等，那么编号的时候就会判成相等的情况
	//然后就会出问题了。。 
	cnt=0;
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
			if (!cmp(sa[i],sa[i-1],l,b)) 
				++cnt;
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

int rmq(int len)
{
	for (int i=1;i<=len;++i) f[i][0]=height[i];
	for (int j=1;j<=20;++j)
		for (int i=len-(1<<j)+1;i>=1;--i)
			f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
}

int get_mn(int x,int y)
{
	if (x==y) return n;
	if (x>y) swap(x,y); ++x;
	int tmp=(int)(log((double)y-x+1)/log(2.0));
	return min(f[x][tmp],f[y-(1<<tmp)+1][tmp]);
}
