#### 式子？

​	欧拉定理的话是：当$gcd(a,m)=1$时有
$$
a^\varphi(m)\equiv1(mod\ m)
$$
​	然后由这个我们可以推出这样一个东西

​	当$gcd(p,q)=1$的时候，有：
$$
a^q\equiv a^{q\ mod\ \varphi(p)}(mod\ p)
$$
​	然后欧拉定理的推广是：
$$
a^q\equiv a^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)
$$

#### 证明

​	（这里的话只写最后那个推广的证明啦qwq）

​	首先我们转化一下问题

​	证明上面那个推广的式子其实只需要证明：对于$a$的任意一个质因子$p_i$，均有：
$$
p_i^q\equiv p_i^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)
$$
​	具体一点的话就是，我们先假设$a$分解质因数之后可以写成：
$$
a=p_1^{w_1}\cdot p_2^{w_2}\cdot p_3^{w_3}...p_n^{w_n}
$$
​	然后我们把上面那条式子转化一下：
$$
\begin{aligned}
p_i^q&\equiv p_i^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)\\
(p_i^q)^{w_i}&\equiv (p_i^{q\ mod\ \varphi(m)+\varphi(m)})^{w_i}(mod\ m)\\
(p_i^{w_i})^q&\equiv (p_i^{w_i})^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)\\
\end{aligned}
$$
​	再由同余式可乘，我们将每一个$p_i$的这样的式子乘起来：
$$
(p_1^{w_1}\cdot p_2^{w_2}\cdot p_3^{w_3}...p_n^{w_n})^q\equiv (p_1^{w_1}\cdot p_2^{w_2}\cdot p_3^{w_3}...p_n^{w_n})^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)
$$
​	也就是
$$
a^q\equiv a^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)
$$
​	所以我们只要证$p_i^q\equiv p_i^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)$这个东西就好了



​	我们将$p_i$分为两类

​	1、当$gcd(p_i,m)=1$的时候（由于$p_i\in prime$，所以也就是$p_i\nmid m$的时候），由欧拉定理得出的那个结论可得：
$$
(p_i^q)^{\varphi(m)}\equiv 1(mod\ m)
$$
​	那么
$$
\begin{aligned}
p_i^q&\equiv p_i^{q\ mod\ \varphi(m)+\varphi(m)}(mod\ m)\\
&\equiv (p_i^{q\ mod\ \varphi(m)}\cdot p_i^{\varphi(m)})(mod\ m)\\
&\equiv p_i^{q\ mod\ \varphi(m)}(mod\ m)\\
\end{aligned}
$$
​	2、当