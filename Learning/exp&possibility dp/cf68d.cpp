#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
map<int,int> sum;
int h,q;
double ans;
double dfs(int x,int dep,int nowmx);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&h,&q);
	char op[10];
	int v,e;
	for (int i=1;i<=q;++i){
		scanf("%s",op);
		if (op[0]=='a'){
			scanf("%d%d",&v,&e);
			for(int now=v;now;now>>=1)
				sum[now]+=e;
		}
		else
			printf("%.5lf\n",dfs(1,0,0));
	}
}

double dfs(int x,int dep,int nowmx){
	if (sum[x]<nowmx||dep>h) return nowmx;
	int szl=sum[x]-sum[x*2+1],szr=sum[x]-sum[x*2];
	if (szl>=szr)
		return dfs(x*2,dep+1,max(nowmx,szr))*0.5+max(nowmx,szl)*0.5;
	return dfs(x*2+1,dep+1,max(nowmx,szl))*0.5+max(nowmx,szr)*0.5;
}

