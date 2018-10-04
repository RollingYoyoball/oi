####莫比乌斯函数

莫比乌斯函数，符号为$\mu$，定义如下：

1. 若 $d=1$，那么$\mu(d) =1$

2. 若$d=\prod\limits_{i=1}^{k}p_i$，且$p_i$均为互异素数，那么$\mu(d) =(-1)^k$

3. 其他情况（$d$有平方因子）$\mu(d)=0$

   

####$\mu$的一些性质

1.对于任意正整数$n$满足：
$$
\sum\limits_{d\mid n}\mu(d) = [n=1]
$$
2.$\mu$与$\phi$的关系：
$$
\sum\limits_{d\mid n}\frac{\mu(d)}{d}=\frac{\phi(n)}{n}
$$

####莫比乌斯反演公式

$F(n)$和f(n)是定义在非负整数集合上面的两个函数，并且满足条件$F(n) = \sum\limits_{d\mid n}f(d)$，那么
$$
f(n) = \sum\limits_{d\mid n}\mu(d)F(\frac{n}{d})
$$
这条式子还有另一种描述:

$F(n)$和$f(n)$满足条件$F(n) = \sum\limits_{n\mid d}f(d)$，那么
$$
F(n)=\sum\limits_{n\mid d}\mu(\frac{d}{n})F(d)
$$

证明

$$
\sum\limits_{d\mid n}\mu(d)F(\frac{n}{d})=\sum\limits_{d\mid n}\mu(d)\sum\limits_{d'\mid \frac{n}{d}}f(d')=\sum\limits_{d'\mid n}f(d')\sum\limits_{d\mid \frac{n}{d'}}\mu(d)=f(n)
$$
#### 一些应用

参考自学长博客里的几条比较常用的形式（当然不是全部。。。）：
$$
\begin{aligned}
f(n)&=\sum\limits_{n|d}g(d)⇔g(n)=\sum\limits_{n|d}f(d)\cdot \mu(\frac{d}{n})\\
f(n)&=\prod\limits_{d|n}g(d)⇔g(n)=\prod\limits_{d|n}f(d)^{\mu (\frac{n}{d})}\\
f(n)&=\prod\limits_{n|d}g(d)⇔g(n)=\prod\limits_{n|d}f(d)^{\mu(\frac{d}{n})}\\
\end{aligned}
$$
能解决很多容斥原理或者$gcd$相关等问题。如果一个函数容易用来求出答案，一个容易直接求，并且满足上述关系，就可以使用莫比乌斯反演来求解了。

具体一点的话，比如对于一些函数$f(n)$，如果我们很难直接求出它的值，而容易求出倍数和或者约数和$F(n)$，那么我们可以直接利用莫比乌斯反演得到$f(n)$

$e.g.$  $f(n)$表示一定范围内$(x,y)=n$的数对的数量，$F(n)$表示一定范围内$n|(x,y)$的数对的数量，直接求$f(n)$并不是那么方便，而$F(n)$则相对来说比较好求，那么我们可以通过反演由$F(n)$得到$f(n)$

然后还有一点就是在化式子的时候要大力换元，从而得到有利用价值的等式