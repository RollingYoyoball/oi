#include <cstdio>
#include <cstring>
#include <iostream>
#define max(a,b) (a>b?a:b)
using namespace std;
const int Len=1010;
int n,m,s[Len],reala[Len],realb[Len],sa[Len],c[1010];
int *a=reala,*b=realb;
char str[Len];
void sort(int flag){
	if(!flag){
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[a[i]]++;
		for(int i=2;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[a[i]]--]=i;
	}
	else{
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[a[b[i]]]++;
		for(int i=2;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[a[b[i]]]--]=b[i];
	}
}
bool cmp(int u,int v,int len,int *r){
	return r[u]==r[v]&&r[u+len]==r[v+len];
}
int main(){
	freopen("input.in","r",stdin);
	scanf("%d%s",&n,str+1);
	for(int i=1;i<=n;i++) m=max(m,(a[i]=str[i]-'a'));
	sort(0);
	int all=-1;
	for(int l=1;all<n;l*=2){
		all=0;
		for(int i=n-l+1;i<=n;i++) b[++all]=i;
		for(int i=1;i<=n;i++) 
			if(sa[i]>l) 
				b[++all]=sa[i]-l;//b是按照第二关键字排序的第一关键字的位置，然后因为是两个上一步的合并的，所以这里赋值过去的是前面部分的开头 
		sort(1);
		swap(a,b);
		a[sa[1]]=1;
		all=1;
		for(int i=2;i<=n;i++){
			if(!cmp(sa[i-1],sa[i],l,b)) all++;
			a[sa[i]]=all;
		}
		m=all;
	}
}
