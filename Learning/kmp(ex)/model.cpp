#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=10010;
char s[MAXN],t[MAXN];
int nxt[MAXN],ex[MAXN];
int n,m,len;
int get_nxt();
int get_ex();

int main()
{
	freopen("a.in","r",stdin);

	scanf("%s\n%s\n",s,t);
	get_nxt();
	get_ex();
	for (int i=0;i<strlen(t);++i) printf("%d ",nxt[i]);
	printf("\n");
	for (int i=0;i<strlen(s);++i) printf("%d ",ex[i]);
}

int get_nxt()
{
	int j=-1,p=0,a=0;//j表示p-i  a记录的是得到最远的匹配位置p的匹配开始的位置
	nxt[0]=strlen(t);
	for (int i=1;i<nxt[0];++i,--j)//关于下面的i+nxt[i-a]，因为是从0开始的，所以i会小1，而nxt和ex记录的都是长度，都大1，所以就抵消了，因此直接这么写就可以了 
	{
		if (j<0||i+nxt[i-a]>=p)//不可能出现>的情况   如果>的话，最远的匹配点p的值就应该是i+nxt[i-a]了所以只能是= 
		{                       //但是并不能直接打== 因为i+nxt[i-a] 可能会超出了字符串长度范围，然后这个时候是不能直接赋值而是要暴力匹配的，所以还是要打> 
			if (j<0)
				p=i,j=0;
			while (p<nxt[0]&&t[j]==t[p])
				++p,++j;
			nxt[i]=j;
			a=i;
		}
		else
			nxt[i]=nxt[i-a];
	}
}

int get_ex()
{
	int j=-1,p=0,a=0;
	int slen=strlen(s),tlen=strlen(t); 
	for (int i=0;i<strlen(s);++i,--j)//注意因为i一直在加而此时p不变所以j要减 
	{
		if (j<0||i+nxt[i-a]>=p)
		{
			if (j<0)
				p=i,j=0;
			while (p<slen&&j<tlen&&t[j]==s[p])
				++p,++j;
			ex[i]=j;
			a=i;
		}
		else
			ex[i]=nxt[i-a];	
	}
}
