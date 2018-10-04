#include <cstdio>
#include <windows.h>
#include <ctime>
using namespace std;
int n=5,m=10;//n=100000,m=200000,q=100000;
int main(){
	freopen("a.in","w",stdout);
	srand(time(NULL));
	printf("1\n");
	printf("%d %d\n",n,m);
	for(int i=2;i<=n;i++){
		if(i==2) 
		printf("%d %d ",i-1,i);
		else
		printf("%d %d ",rand()%(i-1)+1,i);
		printf("%d %d\n",rand()%100+1,rand()%2);
	}
	for(int i=1;i<=m-(n-1);i++){
		int x=rand()%(n-3)+4;
		printf("%d %d ",x,rand()%(x-1)+1);
		printf("%d %d\n",rand()%100+1,rand()%2);
	}
/*	printf("%d\n",q);
	for(int i=1;i<=q;i++) printf("%d %d\n",rand()%n+1,rand()%n+1);
	printf("0 0");*/
	return 0;
}
