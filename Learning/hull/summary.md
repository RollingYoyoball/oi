**吐槽**

计算几何这种东西qwq一开始真的觉得恶心qwq（主要是总觉得为啥画图那么直观的东西非要写一大堆式子来求qwq真的难受qwq）

但其实静下心来学习的话感觉还是很妙的ovo题目思考起来也十分好玩ovo

**正题**

学习凸包需要一点前置技能：极角，向量点积，向量叉积

*1.极角*

​	在平面上取一定点$O$，从$O$引一条水平射线$Ox$，规定方向自左至右，再选定一个长度单位并规定角旋转的正方向（通常取逆时针方向），这样就构成了一个极坐标系，其中$O$叫做极点，射线$Ox$叫做极轴

​	在极坐标系中，平面上任意一点到极点的连线和极轴的夹角叫做极角

*2.向量点积*

​	一般写作：$\vec a \bullet \vec b$，几何定义为
$$
\vec a \bullet \vec b = |\vec a||\vec b|\cdot cos\theta
$$
​	其中$\theta$为两个向量的夹角，该定义只针对二维和三维（其他的。。暂时不需要用到所以就先不写了qwq），其实可以简单理解为第一个向量投影到第二个向量上的长度（就是作垂直啦其实），所以其实点积是个标量

​	特别的，如果是在二维平面中，两个向量$\vec a = (x_1,y_1)$和$\vec b = (x_2,y_2)$的点积可以表示为
$$
\vec a\bullet\vec b = x_1x_2 +y_1y_2
$$
​	点积满足交换律

*3.向量叉积*

​	一般写作：$\vec a × \vec b$，定义为
$$
\vec a × \vec b= ab \cdot sin \theta
$$
​	其中$\theta$为两个向量的夹角，简单理解的话就是两个向量围成的平行四边形的面积（但是是有正负的）

​	与点积不同的是，叉积是个矢量，带方向的

​	在二维平面中，两个向量$\vec a = (x_1,y_1)$和$\vec b = (x_2,y_2)$的叉积可以表示为
$$
\vec a × \vec b = x_1y_2-x_2y_1
$$
​	叉积不满足交换律，交换后的结果方向与原来相反（其实就是多个负号）



点积和叉积的几何意义十分好用，在题目中的应用很广泛，用起来也是很灵活的（具体还是要看题目说啦qwq不然都是空话）

好的然后我们正式开始讲凸包qwq



*graham算法*

​	这个算法的思路十分简单粗暴，就是首先找到最下面最左边的那个点（先按照$y$排序有相同的再看$x$），然后把这个点定为极点，把剩下的点按照极角排序，极角相同就按照到极点的距离排，然后用一个栈记录凸包上的点，O(n)扫一遍，如果说当前的点在目前围成的凸包外，那么就说明栈顶的点应该在凸包内，一直退栈直到满足当前点在凸包上为止，再将当前点进栈，然后再看下一个点

​	最后栈中的就是所有凸包上面的点啦ovo

​	现在的问题就是怎么求极角以及判断当前点的位置

​	这里有一个非常好的结论，$\vec a$如果满足$\vec a × \vec b > 0$，那么说明$\vec b$在$\vec a$的逆时针方向，反之就是在顺时针

​	那么极角其实我们可以直接用叉积来判断就好了，如果说两个向量的叉积$>0$，那么前者的极角一定小于后者，如果等于0说明在同一条直线上，就用距离判断

​	同样的我们就可以快速判断一个点是否在凸包外了

​	（这里是逆时针扫的）我们记当前栈顶的点为$s_0$，栈顶的下一个点为$s_1$，当前点为$x$

​	画一下图就能发现，$x$在当前的凸包上当且仅当$\overrightarrow{s_1x}$在$\overrightarrow{s_1s_0}$的逆时针方向，也就是两个向量的叉积要大于0，这样就能快速判断$x$的位置了

​	然后就这么一路扫一路操作就能得到凸包啦ovo



​	如果说要分别求得上凸包和下凸包，那就一开始按照$x$排序相同再按照$y$排序，然后扫的时候用两个栈分别记录上下凸包，判断条件相反（一个是叉积<=0就退栈，一个是>=0就退栈）就ok了

​	值得注意的是，这里的等号不能去掉，否则遇到多个坐标相同的点会出问题



*旋转卡壳*

​	提到凸包就不能不提到这个算法啦

​	以经典的求凸包直径做例子，首先讲一下大体思路

​	首先可以发现，一个点与凸包中其他点的连线长度是一个单峰函数，所以如果要枚举的话一旦发现答案开始递减了就可以停止了，普通的暴力在枚举下一个点的答案的时候，会又从最靠近的那个点开始扫，但其实我们画个图观察一下会发现其实不用，只要把上一个点（记作$x$）开始递减的那个点（记作$i$) 当做起点开始扫就可以了。原因的话是显然在$i$之前的那些点到$x$的距离会比到当前点的距离要长，所以根本就没有扫的必要了（只会直观证明qwq严格证明的话。。。不会qwq）

​	这样一来我们就可以线性处理出直径啦ovo

​	对于其他的问题，思路其实差不多，主要还是利用好单峰函数这个特点避免掉不必要的操作



*动态加点*

​	如果说是动态加点的话，维护起来差不多，一点小改动

​	将要加进来的点记作$x$，我们先在当前的凸包上找到$x$前面和后面的两个点，形象理解就是能将$x$夹在中间的两个点（额。。其实实现起来用lower_bound就好了），然后从这里开始重新模拟一遍graham中退栈进栈的过程就好了



*应用*

​	除了各种奇妙几何题之外，凸包还有一个很大的用处就是优化，最典型的例子就是斜率优化，其实就是维护一个下凸包

​	额不过这种东西的话。。好像还是要具体题目具体分析qwq反正总的应该就是转成点的形式然后乱搞就好了嗯qwq（好吧其实这种题目的重点应该都是推式子吧哈哈哈。。qwq）