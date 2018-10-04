## 问题描述

​	已知$A(x)$和$B(x)$，$C[i]=\sum\limits_{j\otimes k=i}A[j]*B[k]$，求$C$

​	其中$\otimes$是三种位运算的其中一种

## 具体求解

​	说在前面：接下来的一些符号的话我们统一用$\otimes$代表某种位运算（选定的），如果这个符号出现在两个多项式之间（如：$A\otimes B$），那么是表示按照最上面那条式子卷积，如果出现在两个数之间（如$j\otimes k$），那么是表示这两个数进行这种位运算；然后我们用$\ \cdot\ $这个符号表示点积（也就是对应数位相乘）

​	这里我们用与运算（$\otimes=\&$）举例说明好了，另外两个差不多的

​	首先来个不太靠谱的联想，这个东西的名字长得跟FFT那么像那是不是可以借用FFT的形式啊（Portal -->FFT)

​	然后我们考虑构造一种变换$F(A)$（额其实就是FWT），其中$A$是一个多项式，这个变换满足：
$$
\begin{aligned}
&F(A)\cdot F(B)=F(A\otimes B)\\
&F(k* A)=k*F(A)\\
&F(A+B)=F(A)+F(B)\\
\end{aligned}
$$
​	这样我们就可以像FFT一样，先用某种方法求出$F(A)$和$F(B)$然后对应位相乘，再把得到的结果逆变换一下就可以得到$C(x)$了

​	

​	那么现在的问题是我们怎么构造$F$

​	参考FFT的求解我们还是尝试用分治的思想来解决这个问题

​	与FFT按照下标的奇偶性分类不同，因为位运算是跟二进制有关的，所以我们可以考虑按照下标的二进制最高位为$0$还是为$1$分成两类（因为算的时候长度是补成$2^k$这样的，所以其实也就是严格的前半部分和后半部分）

​	对于一个多项式$A$，下标二进制最高位为$0$的那部分记为$A_0$，为$1$的那部分记为$A_1$，$A=(A_0,A_1)$

​	

​	我们可以猜测一下这个$F(A)=(k_1A_0+k_2A_1,k_3A_0+k_4A_1)$

​	其中$k_1，k_2，k_3，k_4$都是常数

​	然后现在我们要做的就是求出这四个常数



​	我们将$A\otimes B$写成$(A_0,A_1)\otimes (B_0,B_1)$，然后看一下这个式子等于什么：

​	同样的我们还是将结果写成$(C_0,C_1)$的形式，那么根据与运算的特点我们可以的到：
$$
\begin{aligned}
(A_0,A_1)\otimes (B_0,B_1)=(A_0\otimes B_0+A_0\otimes B_1+A_1\otimes B_0，A_1\otimes B_1)\\
\end{aligned}
$$
​	（具体一点的话就是$0\&0=0，0\&1=0，1\&0=0$所以都是$C_0$的组成部分，只有$1\&1=1$是$C_1$的组成部分）



​	然后我们根据最上面的$F$这个变换满足的性质和我们猜测的$F(A)=(k_1A_0+k_2A_1,k_3A_0+k_4A_1)$来处理一下这个式子

​	（因为$k_1,k_2$和$k_3,k_4$满足的条件其实是一样的所以在下面化的时候我们可以只考虑前半部分的求解（也就是就解$k_1,k_2$，所有的变换什么的只写前半部分），然后求得多组解最后取其中两个可行解分别作为$k_1,k_2,k_3,k_4$即可）

​	（因为太长了。。所以一个等式我就换行来写了qwq）
$$
\begin{aligned}
&(k_1A_0+k_2A_1)\cdot (k_1B_0+k_2B_1)\\
&=k_1(A_0\otimes B_0+A_0\otimes B_1+A_1\otimes B_0)\cdot k_2(A_1\otimes B_1)\\
\\
&\Updownarrow\\
\\
&k_1^2(A_0\otimes B_0)+k_1k_2(A_0\otimes B_1)+k_1k_2(A_1\otimes B_0)+k_2^2(A_1\otimes B_1)\\
&=k_1(A_0\otimes B_0)+k_1(A_0\otimes B_1)+k_1(A_1\otimes B_0)+k_2(A_1\otimes B_1)
\end{aligned}
$$
​	然后我们就可以直接得到一个比较好看的方程组了：
$$
\begin{cases}
k_1^2=k_1\\
k_1k_2=k_1\\
k_2^2=k_2\\
\end{cases}
$$
​	然后我们解出来有三组解：$(0,0)，(1,1)，(0,1)$

​	接下来要做的就是从这三组解里面挑两组出来作为$(k_1,k_2)$和$(k_3,k_4)$

​	但这个并不是随便挑的，考虑到我们的这个变换必须要有一个逆变换，所以我们挑出来的两组不能是有一组是$(0,0)$或者有两组相等（不然就不可逆了嘛），实际上，我们可以将这四个系数写成一个矩阵，然后逆变换的系数的话就是对这个矩阵求个逆就好了

​	所以，这里我们只能选$(1,1)$和$(0,1)$，我们令$(k_1,k_2)=(1,1)$，$(k_3,k_4)=(0,1)$
$$
\begin{bmatrix}
    k_1&k_2\\
    k_3&k_4\\
\end{bmatrix}=
\begin{bmatrix}
1&1\\
0&1\\
\end{bmatrix}
$$
​	然后我们把这个东西看成一个行列式求一下逆，得到逆矩阵：
$$
\begin{bmatrix}
1&-1\\
0&1\\
\end{bmatrix}
$$
​	（具体求解的话。。当然可以直接用线代的那套但是qwq这里那么小那直接设数代一下就好了）

​	然后我们按照这个系数去算FWT（也就是变换$F$）和DFWT就好啦

​	然后如果是求异或或者是或运算的话，那直接改一下
$$
(A_0,A_1)\otimes (B_0,B_1)=(A_0\otimes B_0+A_0\otimes B_1+A_1\otimes B_0，A_1\otimes B_1)
$$
​	这个式子的左边然后再用同样的方法算一下就好了

​	xor的话就是：$(A_0\otimes B_0+A_1\otimes B_1，A_0\otimes B_1+A_1\otimes B_0)$

​	or的话就是：$(A_0\otimes B_0，A_0\otimes B_1+A_1\otimes B_0+A_1\otimes B_1)$

​	

​	代码什么的长得跟FFT其实差不多。。。哦不对。。会短很多ovo

​	大概是长这个样子：

```C++
#define OR 0
#define AND 1
#define XOR 2

void fwt(int *a,int op,int type,int len){//op=1为FWT，否则为DFWT
	int v,u;
	for (int step=2;step<=len;step<<=1)
		for (int st=0;st<len;st+=step)
			for (int i=0;i<step>>1;++i){
				u=a[st+i]; v=a[st+i+(step>>1)];//u=A0,v=A1
				if (op==1){
					if (type==XOR)
						a[st+i]=(u+v)%MOD,a[st+i+(step>>1)]=(u+MOD-v)%MOD;
					else if (type==AND)
						a[st+i]=(u+v)%MOD;
					else
						a[st+i+(step>>1)]=(u+v)%MOD;

				}
				else{
					if (type==XOR)
						a[st+i]=1LL*(u+v)*inv2%MOD,a[st+i+(step>>1)]=1LL*(1LL*u+MOD-v)*inv2%MOD;
					else if (type==AND)
						a[st+i]=(1LL*u-v+MOD)%MOD;
					else
						a[st+i+(step>>1)]=(1LL*v-u+MOD)%MOD;//v-u!!
				}
			}
}
```



​	