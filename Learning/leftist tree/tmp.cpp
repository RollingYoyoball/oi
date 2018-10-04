#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<stack>
#include<queue>
using namespace std;

const int M = 1e5 + 10;
struct node{
   int x,y;
   friend bool operator < (node a,node b){
        return a.y<b.y;
    }
}num[M];
priority_queue<node>a[2];

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	
    int n,tem=0;
    while (~scanf("%d",&n)&&n){
        printf("Case #%d:\n",++tem);
        while (!a[0].empty()) a[0].pop();
        while (!a[1].empty()) a[1].pop();
        int ans=0,flag=0;
        while (n--){
            char str[10],op;
            scanf("%s",str);scanf(" %c",&op);
            if (strcmp(str,"push")==0){
                scanf(" %d",&num[++ans].x);
                num[ans].y=ans;
                if (op=='A') a[flag].push(num[ans]);
                else a[flag^1].push(num[ans]);
            }
            else if (strcmp(str,"pop")==0){
                if (op=='A') printf("%d\n",a[flag].top().x),a[flag].pop();
                else printf("%d\n",a[flag^1].top().x),a[flag^1].pop();
            }
            else{
                char ch;
                scanf(" %c",&ch);
                while (!a[1].empty()){
                    a[0].push(a[1].top());
                    a[1].pop();
                }
                if (op=='A'&&flag==1) flag=0;
                if (op=='B'&&flag==0) flag=1;
            }
        }
    }
    return 0;
}
