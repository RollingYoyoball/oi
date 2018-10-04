#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=2010;
char A[MAXN],B[MAXN];
int son[MAXN*2][26],suf[MAXN*2],len[MAXN*2],f[MAXN*2];
int son1[MAXN][26];
int n,m,tot,last,lena,lenb;
int insert(int ch);
int newnode(int x);
int dfs(int x,int dep);
int work1();
int work2();
int work3();
int work4();

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%s%s\n",A+1,B+1);
	lena=strlen(A+1);
	lenb=strlen(B+1);
	last=tot=1;
	for (int i=1;i<=lenb;++i)
		insert(B[i]-'a');
	for (int i=lenb;i>=1;--i)
	{
		memcpy(son1[i],son1[i+1],sizeof(son1[i+1]));
		son1[i][B[i]-'a']=i+1;
	}	
	work1();
	work2();
	work3();
	work4();
}

int insert(int ch)
{
	int p=last,np=newnode(len[p]+1),nq,q;
	for (;p&&!son[p][ch];p=suf[p]) son[p][ch]=np;
	if (!p) suf[np]=1;
	else
	{
		q=son[p][ch];
		if (len[p]+1!=len[q])
		{
			nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof(son[q]));
			suf[nq]=suf[q],suf[q]=suf[np]=nq;
			for (;p&&son[p][ch]==q;p=suf[p]) son[p][ch]=nq;
		}
		else suf[np]=q;
	}
	last=np;
}

int newnode(int x)
{
	len[++tot]=x; return tot;
}

int work1()
{
	int ans=lena+1,l,now;
	for (int i=1;i<=lena;++i)
	{
		l=0; now=1;
		while (son[now][A[i+l]-'a']&&i+l<=lena) 
			now=son[now][A[i+l]-'a'],++l;
		if (i+l<=lena) ans=min(ans,l+1);	
	}
	if (ans!=lena+1) printf("%d\n",ans);
	else printf("-1\n");
}

int work2()
{
	int ans=lena+1,l,now;
	for (int i=1;i<=lena;++i)
	{
		l=0; now=1;
		while (son1[now][A[i+l]-'a']&&i+l<=lena)
			now=son1[now][A[i+l]-'a'],++l;
		if (i+l<=lena) ans=min(ans,l+1);
	}
	if (ans!=lena+1) printf("%d\n",ans);
	else printf("-1\n");
}

int work3()
{
	for (int i=0;i<=tot;++i) f[i]=lena+1;
	f[1]=0;
	for (int i=1;i<=lena;++i)
		for (int j=tot;j>=1;--j)
			f[son[j][A[i]-'a']]=min(f[son[j][A[i]-'a']],f[j]+1);
	if (f[0]!=lena+1) printf("%d\n",f[0]);
	else printf("-1\n");
}

int work4()
{
	for (int i=0;i<=lenb+1;++i) f[i]=lena+1;
	f[1]=0;
	for (int i=1;i<=lena;++i)
		for (int j=lenb+1;j>=1;--j)
			f[son1[j][A[i]-'a']]=min(f[son1[j][A[i]-'a']],f[j]+1);
	if (f[0]!=lena+1) printf("%d\n",f[0]);
	else printf("-1\n");
}
