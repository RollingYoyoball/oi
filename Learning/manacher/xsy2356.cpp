#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
char s1[MAXN],s[MAXN*2];
int mx[MAXN*2],len1,len,ans;
int work();

int main()
{
	freopen("a.in","r",stdin);
	
	while (scanf("%s",s1)!=EOF)
	{
		len1=strlen(s1);
		len=1; s[0]='$'; s[1]='#';
		for (int i=0;i<len1;++i)
			s[++len]=s1[i],s[++len]='#';
		memset(mx,0,sizeof(mx));
		ans=0;
		work();		
		printf("%d\n",ans-1);
	}
}

int work()
{
	int p=0,k=0;
	for (int i=2;i<len;++i)
	{
		if (p>=i)
			mx[i]=min(mx[k*2-i],p-i+1); 
		else
			mx[i]=1;
		while (s[i+mx[i]]==s[i-mx[i]]) ++mx[i];//��Ϊs[0]��λ�ü���һ�������ַ������Բ��õ��ı߽�����⣬�϶����ܼ���ƥ����ȥ�� 
		if (i+mx[i]-1>p) p=i+mx[i]-1,k=i;
		ans=max(ans,mx[i]);
	}		
}
