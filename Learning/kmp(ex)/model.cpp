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
	int j=-1,p=0,a=0;//j��ʾp-i  a��¼���ǵõ���Զ��ƥ��λ��p��ƥ�俪ʼ��λ��
	nxt[0]=strlen(t);
	for (int i=1;i<nxt[0];++i,--j)//���������i+nxt[i-a]����Ϊ�Ǵ�0��ʼ�ģ�����i��С1����nxt��ex��¼�Ķ��ǳ��ȣ�����1�����Ծ͵����ˣ����ֱ����ôд�Ϳ����� 
	{
		if (j<0||i+nxt[i-a]>=p)//�����ܳ���>�����   ���>�Ļ�����Զ��ƥ���p��ֵ��Ӧ����i+nxt[i-a]������ֻ����= 
		{                       //���ǲ�����ֱ�Ӵ�== ��Ϊi+nxt[i-a] ���ܻᳬ�����ַ������ȷ�Χ��Ȼ�����ʱ���ǲ���ֱ�Ӹ�ֵ����Ҫ����ƥ��ģ����Ի���Ҫ��> 
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
	for (int i=0;i<strlen(s);++i,--j)//ע����Ϊiһֱ�ڼӶ���ʱp��������jҪ�� 
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
