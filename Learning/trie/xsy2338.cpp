#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1000010;
char s[MAXN];
int next1[MAXN];
int n,m;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	scanf("%s\n",&s);
	next1[0]=-1;
	int j=-1;
	for (int i=1;i<n;++i)
	{
		while (j!=-1&&s[j+1]!=s[i]) j=next1[j];
		if (s[j+1]==s[i]) ++j;
		next1[i]=j;
	}
	j=n-1;
	while (next1[j]) --j;
	printf("%d\n",j);
}
