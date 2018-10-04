#### 一些坑&散件&传送门

**Lucas定理**

​	当$p$为素数的时候，我们有：
$$
\binom n m\equiv \binom {n\% p}{m\% p}\cdot\binom {n/p}{m/p}(mod\ p)
$$
​	可以用来解决$p$比较小且是质数但是$n$和$m$都比较大的时候的组合数求值

​	具体的话直接递归来写就好了

​	时间复杂度$O(log_p{n}*p)$

​	

​	证明的话可以看-->[这里](https://blog.csdn.net/arrowlll/article/details/53064748)（一个巨大的待填的坑qwq）



**容斥原理**

​	待填的坑。。。~~额。。有一种说法是。。从第一个（没有任何限制）开始数系数一正一负这样~~

​	有好多。。奇妙的操作的感觉qwq

​	可以看-->[这里](https://blog.csdn.net/arrowlll/article/details/52374330)



