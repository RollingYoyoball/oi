#### 多项式相关

**多项式求逆（元）**

- 定义

  对于一个多项式$A(x)$，如果存在一个多项式$B(x)$，满足$B(x)$的次数小于等于$A(x)$且$A(x)B(x)\equiv 1(mod\ x^n)$，那么我们称$B(x)$为$A(x)$在模$x^n$意义下的逆元，简单记作$A^{-1}(x)$


- 求解

  从最简单的情况开始考虑，当$n=1$的时候$A(x)\equiv\ c\ (mod\ x)$，$c$为$A(x)$的常数项，此时$A^{-1}(x)$为$c$的逆元

  在这个基础上我们继续考虑一般情况

  对于$n>1$的情况，不妨设$B(x)=A^{-1}(x)$，那么我们可以根据定义列出下面的式子：
  $$
  A(x)B(x)\equiv 1(mod\ x^n)
  $$
  这里的话考虑用倍增的方式求解（算倍增吧），这里假设我们已经知道了$A(x)$在$mod\ x^{\lceil \frac{n}{2} \rceil}$下的逆元$G(x)$，那么有：
  $$
  \begin{align}
  A(x)G(x)&\equiv 1(mod\ x^{\lceil \frac{n}{2} \rceil})\\
  \end{align}
  $$
  我们把$A(x)$和$B(x)$的式子写成$mod\ x^{\lceil \frac{n}{2} \rceil}$下的：

  （可以这么写是因为$mod\ x^n$相当于将乘积中$x$次数大于等于$n$的忽略掉了，而$mod\ x^{\lceil \frac{n}{2} \rceil}$则相当于忽略了更多的项，既然前者满足，那么后者肯定也满足）

$$
A(x)B(x)\equiv 1 (mod\ x^{\lceil \frac{n}{2} \rceil})
$$

​	把这两条式子相减，就可以搞事情了：
$$
\begin{align}
A(x)[B(x)-G(x)]\equiv 0\ (mod\ x^{\lceil \frac{n}{2} \rceil})\\
B(x)-G(x)\equiv 0\ (mod\ x^{\lceil \frac{n}{2} \rceil})\\
\end{align}
$$
​	然后我们两边平方一下：
$$
B^2(x)-2B(x)G(x)+G^2(x)\equiv 0\ (mod\ x^{\lceil \frac{n}{2} \rceil})
$$
​	然后这里有个很神奇的事情，$B(x)-G(x)$  在$mod\ x^{\lceil \frac{n}{2} \rceil}$下为0，说明这个式子最后的结果的$0$到$\lceil \frac{n}{2} \rceil -1$次项系数都为$0$，平方了之后，对于结果的$i$次项系数，（$0<=i<=2*\lceil \frac{n}{2} \rceil -1$ ），其系数$a_i = \sum\limits_{j=0}^{i}a_j a_{i-j}$，而$a_j$和$a_{i-j}$中必定有一项为$0$（因为$j$和$i-j$中必定有一个值小于$\lceil \frac{n}{2} \rceil$），所以我们可以得到一个结论，这个式子在平方了之后在$mod \ x^n$下也是$0$

​	那么我们就可以写成：
$$
\begin{equation}
B^2(x)-2B(x)G(x)+G^2(x)\equiv 0\ (mod\ x^n)\\
A(x)B(x)*B(x)-2*A(x)B(x)*G(x)+A(x)G^2(x)\equiv 0\ (mod\ x^n)\\
\end{equation}
$$
​	两边同时乘上$A(x)$，由逆元的定义我们可以将上面的式子化简成下面这样：
$$
B(x)-2G(x)+G^2(x)\equiv 0\ (mod\ x^n)
$$
​	最后得到：
$$
B(x)\equiv 2G(x)-A(x)G(x)\ (mod\ x^n)
$$
​	也就是说，如果我们知道$G(x)$，我们就可以推出$B(x)$了

​	具体的实现可以用递归的方式实现，中间的多项式乘法可以用fft加速一下，那么最终的时间复杂度就是
$$
T(n)=T(\frac{n}{2})+O(n \ log\ n)=O(n\ log \ n)
$$
​	然而为啥这样搞完了还是一个log呢？因为每次递归下去多项式的最高次数都会减半，稍微算一下就会发现最后总的时间复杂度合起来还是一个log而不是两个

​	注意，后面这一堆推式子的过程是建立在$n=1$的时候有解的前提下的，所以我们还可以得到一个结论：一个多项式在$mod\ x^n$下是否有逆元取决于其常数项在$mod \ x^n$下是否有逆元

- 实现

  首先先实现一个namespace NTT，然后除了基础的函数外主要供外部调用的过程是这个：

  ```C++
  void Ntt_getinv(vct &a,vct &b,int n,int m){
  	prework(a,b,n,2*m);//这里注意因为后面是A*B*B，所以m要*2
  	ntt(A,1);
  	ntt(B,1);
  	for (int i=0;i<len;++i) 
        	B[i]=(2LL-1LL*A[i]*B[i]%MOD+MOD)*1LL*B[i]%MOD;
  	ntt(B,-1);
  }
  ```

  然后求逆的过程大概是这样（这里用vector来写了）：

  ```C++
  vct Inv(vct a){
  	int N=a.size();
  	if (N==1){
  		a[0]=ksm(a[0],MOD-2);
  		return a;
  	}
  	vct b=a; b.resize((N+1)>>1);
  	b=Inv(b); b.resize(N);
  	NTT::Ntt_getinv(a,b,N,N);
  	b.resize(NTT::len);
  	for (int i=0;i<NTT::len;++i) b[i]=NTT::B[i];
  	b.resize(N);
  	return b;
  }
  ```

  求逆大概就是这样吧ovo

  ​



**多项式开根**

- 定义

  对于一个多项式$A(x)$，如果存在一个多项式$B(x)$，满足$B^2(x)\equiv\ A(x) (mod\ x^n)$，则称$B(x)$为$A(x)$在$mod\ x^n$下的平方根


- 求解

  同样是考虑最简单的情况，当$n=0$的时候，$B(x)$的常数项就是$1$

  然后考虑一般情况，同样的思路，考虑用倍增的方式来求

  假设我们已经知道了$A(x)$在$mod\ x^{\lceil \frac{n}{2} \rceil}$下的平方根$G(x)$，现在要求在$mod\ x^n$下的平方根$B(x)$，根据定义我们可以列出式子：
  $$
  \begin{equation}
  B^2(x)\equiv A(x)(mod\ x^n)\\
  G^2(x)\equiv A(x)(mod\ x^{\lceil \frac{n}{2} \rceil})
  \end{equation}
  $$
  用类似多项式求逆中的分析，我们可以知道第一条式子在$mod\ x^{\lceil \frac{n}{2} \rceil}$下也成立，得到：
  $$
  B^2(x)\equiv A(x)(mod\ x^{\lceil \frac{n}{2} \rceil})
  $$
  同样两式相减一下得到：
  $$
  [B^2(x)-G^2(x)]\equiv 0\ (mod\ x^{\lceil \frac{n}{2} \rceil})
  $$
  接下来就是跟上面多项式求逆中一样的套路了，平方一下得到：
  $$
  [B^2(x)-G^2(x)]^2\equiv 0\ (mod\ x^{\lceil \frac{n}{2} \rceil})
  $$
  同样的道理，这条式子在$mod\ x^n$下也成立，那么：
  $$
  \begin{align}
  [B^2(x)-G^2(x)]^2&\equiv 0\ (mod\ x^n)\\
  B^4(x)-2B^2(x)G^2(x)+G^4(x)&\equiv 0\ (mod\ x^n)\\
  [B^2(x)+G^2(x)]^2&\equiv [2B(x)G(x)]^2\ (mod\ x^n)\\
  B^2(x)+G^2(x)&\equiv2B(x)G(x)\ (mod\ x^n)\\
  \end{align}
  $$
  根据$B(x)$的定义我们可以写成：
  $$
  A(x)+G^2(x)\equiv 2B(x)G(x)\ (mod\ x^n)\\
  $$
  最后得到：
  $$
  B(x)\equiv\ \frac{A(x)+G^2(x)}{2G(x)}\ (mod\ x^n)
  $$
  所以如果说我们知道了$G(x)$，我们也就可以得出$B(x)$啦，分母可以用多项式求逆搞一下，其他的多项式乘法fft搞一下，问题不大

  总的复杂度是：
  $$
  T(n)=T(\frac{n}{2})+求逆复杂度+O(n\ log \ n)=O(n\ log\ n)
  $$




- 实现

  namespace NTT中主要需要调用的过程长这个样子

  ```C++
  void Ntt_getsqrt(vct &a,vct &invb,int n,int m){
  	prework(a,invb,n,m);
  	ntt(A,1);
  	ntt(B,1);
  	for (int i=0;i<len;++i) 
  		B[i]=1LL*B[i]*inv2%MOD*A[i]%MOD;
  	ntt(B,-1);
  }
  ```

  开根的话大概长这个样子

```C++
vct Sqrt(vct a){
	int N=a.size(),M,M1;
	if (N==1){
		a[0]=1;
		return a;
	}
	vct b=a,invb;
	b.resize((N+1)>>1);
	b=Sqrt(b);
	invb=b; invb.resize(N);//resize!!!
	invb=Inv(invb);
	NTT::Ntt_getsqrt(a,invb,N,N);
	b.resize(NTT::len);
	for (int i=0;i<NTT::len;++i) b[i]=(1LL*b[i]*inv2%MOD+NTT::B[i])%MOD;
	b.resize(N);
	return b;
}
```



**多项式除法**

- 问题

  给出一个$n$次多项式$A(x)$，以及一个$m（m<=n)$次多项式$B(x)$

  要求出$D(x)$满足$A(x)=D(x)B(x)+R(x)$，且$D(x)$的次数$<=n-m$，$R(x)$的次数$<m$

  简单来说就是类比整数的除法，$D(x)$就是商，$R(x)$就是余数，我们现在考虑求商


- 求解

  为了方便接下来的表述，先定义一些操作，我们记：
  $$
  rev(A(x))=x^nA(\frac{1}{n})
  $$
  也就是系数反转，举个简单的例子：
  $$
  \begin{equation}
  A(x)=4x^4+3x^3+2x^2+1\\
  rev(A(x))=x^4+2x^3+3x^2+4
  \end{equation}
  $$
  那么现在我们把上面那条式子搬下来：
  $$
  A(x)=D(x)B(x)+R(x)
  $$
  （接下来的步骤均将$D(x)$看成$n-m$次多项式，$R(x)$看成$m-1$次多项式，对于那些不存在的高次项我们就把系数看成$0$就好了）

  后面的余数看起来十分不友善，所以我们要想个办法把它去掉，于是我们可以进行以下的操作:

  我们将上面式子中的所有$x$换成$\frac{1}{x}$，然后等式两边同时乘上$x^n$，得到：
  $$
  \begin{align}
  x^nA(\frac{1}{x})&=x^{n-m}D(\frac{1}{x})x^mB(\frac{1}{x})+x^{n-m+1}x^{m-1}R(\frac{1}{x})\\
  rev(A(x))&=rev(D(x))rev(B(x))+x^{n-m+1}rev(R(x))\\
  \end{align}
  $$
  现在再来看一下各个项的最高次项，首先是我们要求的元素$D(x)$，由于这个多项式原来是$n-m$次，所以在系数反转之后肯定不会超过$n-m$次，而我们要“消掉”的$R(x)$原来是$m-1$次多项式，所以$x^{n-m+1}R(x)$的**最低次项**应该是**大于$n-m$** 的

  那么考虑将上面的式子放到$mod\ x^{n-m+1}$下，$x^{n-m+1}R(x)$的影响就可以十分愉快滴被消掉啦，同时我们也不会影响到$D(x)$的求解，因为$D(x)$是$n-m$次的（疯狂%miskcoo太强了qwq）

  于是我们就得到了这样一个式子：
  $$
  rev(A(x))\equiv\ rev(D(x))rev(B(x))\ (mod\ x^{n-m+1})
  $$
  那所以，我们只要求一个$rev(B(x))$在$mod x^{n-m+1}$意义下的逆元然后跟$rev(A(x))$乘一下，得到$rev(D(x))$，然后再把系数反转回来就得到$D(x)$啦

- 实现

  除法大概是长这个样子

  ```C++
  vct operator / (vct a,vct b){
  	int N=a.size()-1,M=b.size()-1;
  	if (N<M){
  		d.resize(1);d[0]=0;
  		return d;
  	}
  	reverse(a.begin(),a.end());
  	reverse(b.begin(),b.end());
  	b.resize(N-M+1);
  	d=Inv_p(b)*a;
  	d.resize(N-M+1);
  	reverse(d.begin(),d.end());
  	return d;
  }
  ```

  ​

  **多项式取模**

  - 问题

    这个。。其实就是求上面那个$R(x)$

  - 求解

    有了多项式除法（也就是求商）之后，求余数就变得比较简单了

    类比整数的取模，我们可以得到这样的一个式子：
    $$
    R(x)=A(x)-D(x)B(x)
    $$
    那就除法求出$D(x)$之后直接减一下就好了，$D(x)B(x)$这个多项式乘法也是直接用$ntt$求就好了

  - 实现

    ~~假装非常短的样子~~   (然而前面的东西都是要写的qwq醒醒)

    ```C++
    void mod(vct &a,vct b){
    	int N=a.size()-1,M=b.size()-1;
    	if (N<M) return;
    	t=a/b;
    	a=a-(t*b);
    	a.resize(M);
    }
    ```

  大概。。就先写这么多吧ovo

  ​

  ​

  ​



​	

