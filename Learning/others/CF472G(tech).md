Portal --> broken qwq

### Description

​	给出两个$01$序列$A$和$B$

​	哈明距离定义为两个长度相同的序列中，有多少个对应位置上的数字不一样（如：$00111$和$10101$的距离为2）

​	现有$Q$次询问，每次给出$p1,p2,len$，求$A[p1...p1+len-1]$和$B[p2...p2+len-1]$两个子串的哈明距离，编号从$0$开始

数据范围：

$1<=|A|,|B|<=2*10^5,1<=Q<=4*10^5$，$0<=p1<=|A|-len,0<=p2<=|B|-len$



### ”Solution“

​	这是一篇假题解qwq只是记录一下这种优秀的压位做法（虽然说。。cf上面好像会被卡Q^Q）

​	因为没有修改操作之类的东西，串是给定的，所以说我们可以将原串中每一位开始的连续的64位（或者32位压也可以）压成一个unsigned long long（或者long long）

​	这样我们可以直接对应的一段取出来异或一下，然后再统计一下异或出来的结果中有多少个$1$就可以知道答案了

​	统计的话我们可以预处理一下$1\sim 2^{16}-1$的的每一个数写成二进制之后有多少个$1$（记录在$cnt$数组中）然后将异或出来的结果分成$4$段，每段$16$位这样来直接在$cnt$中查，最后将结果累加一下就能够得到答案了

​	如果说$64$位$64$位分有剩的话，最后一次查询的时候要强行把末尾多余的位去掉（左移一下就好了），时间复杂度是$O(\frac{nQ}{64})$，不过常数比较小



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ull unsigned long long
using namespace std;
const int N=2*(1e5)+10,Div=(1<<16)-1;
char A[N],B[N];
ull a[N],b[N],cnt[1<<16];
int n,m,tot,Q,lena,lenb,ans;
void prework(){
	for (int i=lena-1;i>=0;--i) a[i]=(a[i+1]>>1)|((ull)(A[i]-'0')<<63);
	for (int i=lenb-1;i>=0;--i) b[i]=(b[i+1]>>1)|((ull)(B[i]-'0')<<63);
	cnt[0]=0;
	for (int i=1;i<1<<16;++i) cnt[i]=cnt[i>>1]+(i&1);
}
ull sum(ull x){return cnt[x&Div]+cnt[x>>16&Div]+cnt[x>>32&Div]+cnt[x>>48&Div];}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int p1,p2,len;
	scanf("%s",A);lena=strlen(A);
	scanf("%s",B);lenb=strlen(B);
	scanf("%d",&Q);
	prework();
	for (int i=1;i<=Q;++i){
		scanf("%d%d%d",&p1,&p2,&len);
		ans=0;
		for (;len>=64;p1+=64,p2+=64,len-=64)
			ans+=sum(a[p1]^b[p2]);
		if (len)
			ans+=sum((a[p1]^b[p2])>>(64-len));
		printf("%d\n",ans);
	}
}
```

