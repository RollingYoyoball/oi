（所以说过了这么久才更博肯定不是因为懒嗯）

**吐槽**

额其实这个东西的话。。好像缠着机房里面的dalao们给我讲过好多遍了然后。。

拖到现在才搞懂也是服了qwq（可能有个猪脑子）

感觉就是主要几条式子然后疯狂换元换着换着就化简运算了？

草稿纸杀手qwq

------

**莫比乌斯反演公式**

$F(n)$和f(n)是定义在非负整数集合上面的两个函数，并且满足条件$F(n) = \sum\limits_{d\mid n}f(d)$，那么
$$
f(n) = \sum\limits_{d\mid n}\mu(d)F(\frac{n}{d})
$$
这条式子还有另一种描述

$F(n)$和f(n)$足条件F(n) = \sum\limits_{n\mid d}f(d)$，那么
$$
F(n)=\sum\limits_{n\mid d}\mu(\frac{d}{n})F(d)
$$


上面的公式有个$\mu$函数，定义如下：

1. 若 $d=1$，那么$\mu(d) =1$
2. 若$d=\prod\limits_{i=1}^{k}p_i$，且$p_i$均为互异素数，那么$\mu(d) =(-1)^k$
3. 其他情况（$d$有平方因子）$\mu(d)=0$

**$\mu$的常见性质**

对于任意正整数$n$满足
$$
\sum\limits_{d\mid n}\mu(d) = [n=1]
$$
和
$$
\sum\limits_{d\mid n}\frac{\mu(d)}{d}=\frac{\phi(n)}{n}
$$
**证明**

啊。。是证明莫比乌斯反演公式啦。。不是上面两条qwq
$$
\sum\limits_{d\mid n}\mu(d)F(\frac{n}{d})=\sum\limits_{d\mid n}\mu(d)\sum\limits_{d'\mid \frac{n}{d}}f(d')=\sum\limits_{d'\mid n}f(d')\sum\limits_{d\mid \frac{n}{d'}}\mu(d)=f(n)
$$
**应用**

目前做到的几题都是。。各种换元然后优化式子？

总之大概就是上面四条式子（性质两条+反演两条）+各种玄学换来换去，最后好像。。目前做的几题都是化成了一个带有$g(T) = \sum\limits_{d\mid T}f(d)\mu(\frac{T}{d})$的式子，然后就想办法把$g(x)$筛出来

最后的求解基本上是要用到一个（类似）分块的方法用前缀和在根号的时间内把式子里面的其他一些奇奇怪怪的部分求出来

主要题做的也不多qwq大概就先这样吧qwq