**第一类斯特林数**

1.组合数下的定义：

​	用$S(p,k)$表示将$p$个元素（元素之间互不相同）分成$k$个非空循环排列（也就是$k$个圈）

​	递推式：$S(p,k)=(p-1)*S(p-1,k)+S(p-1,k-1)$

​	解释：

​		前一项是第$p$个数不单独成为一个循环排列的方案数，那么就是将$p-1$个元素分成$k$个非空循环排列，然后枚举第$p$个元素放在哪个元素的左边

​		后面一项是第$p$个数单独成为一个循环排列的方案数，那么就是$p-1$个元素分成$k-1$个非空循环排列

2.实际上的定义：

​	我们将排列数$P_n^p$展开，可以得到这样的式子：
$$
P_n^p=n(n-1)(n-2)(n-3)...(n-p+1)
$$
​	而第一类斯特林数的定义就是这个排列数完全展开后的每一项的系数，也就是：
$$
P_n^p=S(p,p)n^p+S(p,p-1)n^{p-1}+...+S(p,p-1)n^{p-k}+...+S(p,0)n^0
$$
​	然后会发现其实这个系数是正负交替的，所以最终得到定义为：
$$
P_n^p=\sum\limits_{k=0}^{p}(-1)^{p-k}S(p,k)n^k
$$
3.一些奇妙深刻的性质

​	这里把第一类斯特林数分成有符号（就是系数定义下的，下面写作$S_s$）和没符号的（就是组合数定义下的，下面写作$S_u$）两种好了，那么有这些小性质：

有符号的：
$$
\begin{aligned}
&S_s(n,m)=(-1)^{n+m}S_u(n,m)\\\\
&\sum\limits_{k=0}^nS_s(n,k)=0^n
\end{aligned}
$$
(这里强行定义$0^0$为1)



没符号的：
$$
\begin{aligned}
&\sum\limits_{k=0}^n S_u(n,k)=n!\\\\
&S_u(n,1)=(n-1)!\\\\
&S_u(n,n-1)=C(n,2)\\\\
&S_u(n,2)=(n-1)!\sum\limits_{i=1}^{n-1}\frac{1}{i}\\\\
\end{aligned}
$$
**第二类斯特林数**

1.组合数下的定义

​	用$S(p,k)$表示将$p$个元素（同样是两两之间互不相同）放进$k$个非空盒子（盒子之间相同）的方案数

​	递推式：$S(p,k)=k*S(p-1,k)+S(p-1,k-1)$

​	解释：后一项同样的就是单独一个盒子，前一项就是枚举放在哪个盒子就好了

2.通项公式

​	（然而并不知道怎么证）
$$
S(n,m)=\frac{1}{m!}*\sum\limits_{k=0}^{n}(-1)^k*C_m^k*(m-k)^n
$$
3.关于奇偶性的奇妙性质？

![img](http://my.csdn.net/uploads/201204/05/1333627157_5221.PNG)

​	也就是说，$S(n,k)$的奇偶性和$C(z,w)=\frac{z!}{(w!)*(z-w)!}$是一样的，那么所以如果要判断其奇偶性就直接判断分子分母所含的因子2的个数就好了

​	（啊？为啥会搞出这么一个奇怪的东西？额因为是一道题啊poj1430嗯qwq）



4.另一些奇妙深刻的性质

​	额有这样一条式子：
$$
x^n=\sum\limits_{k}S(n,k)\cdot x^{\underline k},整数n>=0
$$
​	其中$x^{\underline k} = x!/(x-k)!$，叫做下降阶乘幂

​	然后的证明的话用归纳法来证就好了

​	我们假定$x^{n-1}$是满足这个式子的，首先会发现有这样一条式子：
$$
x^{\underline {k+1}}=x^{\underline k}(x-k)
$$
​	拆个括号移下项从而得到：
$$
x\cdot x^{\underline k} = x^{\underline {k+1}}+kx^{\underline k}
$$
​	那么我们就可以发现
$$
\begin{aligned}
x^n&=x\cdot x^{n-1}\\&=x\sum\limits_{k}S(n-1,k)\cdot x^{\underline k}\\
&=\sum\limits_kS(n-1,k)x^{\underline {k+1}}+\sum\limits_kS(n-1,k)kx^{\underline k}\\
&=\sum\limits_kS(n-1,k-1)x^{\underline k}+\sum\limits_kS(n-1,k)kx^{\underline k}&（改变一下第一个sigma的枚举范围）\\
&=\sum\limits_k[k\cdot S(n-1,k)+S(n-1,k-1)]x^{\underline k}&(由S的递推公式可得到下一步)\\
&=\sum_kS(n,k)x^{\underline k}
\end{aligned}
$$
​	于是乎就证完啦

​	也有比较直观的证明

​	令$x^n$的含义为用$x$中颜色给$n$个物体染色的方案数，考虑把颜色相同的物体分到一类，那么有：
$$
x^n=\sum\limits_{i=1}^nS(n,i)\cdot x^{\underline i}
$$
​	解释的话就是：枚举方案中出现的颜色的个数，并将这$n$个物体划分成$i$个集合，满足每个集合内颜色相同且不同集合颜色不同的方案数，再乘上这些集合分别使用的是哪些颜色



**斯特林公式**

这个东西其实讲真跟斯特林数有什么关系吗qwq我也不是很清楚但是做题的时候看到了名字差不多写一起好了

斯特林公式是用来求$n!$的近似值的公式，一般来说当$n$十分大的时候，这个公式还是很好用的，但是如果$n$比较小的话会有些误差不过也不算特别大，还是比较精准的

公式就是这样的：
$$
n!\approx \sqrt{2\pi n}(\frac{n}{e})^n
$$
然后如果说要求这个阶乘在$k$进制下的位数的话就是$log_k(sqrt{\pi n}(\frac{n}{e})^n)+1$

当然啦因为误差的原因，如果说$n$小的话还是得老老实实算嗯qwq