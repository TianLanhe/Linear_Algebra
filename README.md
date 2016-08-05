线性代数
========

* __rational.h__：提供了分数的一组操作接口，使用Rational数据类型和函数轻松进行分数的各种操作。
* __matrix.h__:提供了线性代数的一组计算接口，包含了rational.h，使用分数代替整数和浮点数进行数值计算，可以方便简洁地显示结果。使用Matrix数据类型和其提供的函数可以进行线性代数的各种计算。

Rational:
--------

###分数结构体：
```c
typedef struct RATIONAL{
	int numerator;				//分子
	int denominator;			//分母
	double friaction;			//小数形式
}Rational;
```

###定义的宏：
```c
#define Status int      //返回类型(状态)
#define true 1          //真
#define false 0         //假
#define OK 0            //正确返回
#define ERROR -1        //错误返回
```

###基本操作：
1. 初始化(赋值)
2. 求公因数
3. 化简

```c
Status assign(Rational *des,int numerator,int denominator);	//赋值
Status assign_f(Rational *des,double num);
```
赋值分分数赋值和小数赋值，规定分母永远为正数，以分子的正负作为整个分数的正负。若分数为0，规定则分子为0，分母为1。小数赋值中通过四舍五入消除转换的误差，精确到`0.001`，结果转换为最简分数

```c
int maxfactor(Rational sou);		//最大公因数
```
用辗转相除法求最大公因数用于分数的化简

```c
Status simplify(Rational *sou);		//化简
```
化简操作直接在原分数上进行，会改变原分数的值


###算术运算：
1. 求相反数
1. 求倒数
1. 求幂
2. 开平方
1. 加法
2. 减法
3. 乘法
4. 除法

```c
Status opp(Rational *des,Rational sou);		//求相反数
```
只改变分子和小数符号，其他原样赋值给des。因为之前已经规定分母为正，以分子判断正负

```c
Status inv(Rational *des,Rational sou);		//求倒数
```
sou必须是非零数，即sou的分子不能为0，分母是大于0的整数。

```c
Status power(Rational *des,Rational sou,int n);		//求幂
```
指数n必须是整数，分n等于0，大于0，小于0三种情况。若n等于0时，原分数不能为0(0的0次方是非法的)，否则返回ERROR，其他返回1。若n不等于0时，用乘法操作累乘，若n小于0，还要求其倒数

```c
Status sqrt_r(Rational *des,Rational sou);
```
将sou开平方，精度取决于`assign_f`的精度，因此精确到0.001.

```c
Status add_r(Rational *des,Rational sou1,Rational sou2);
Status sub_r(Rational *des,Rational sou1,Rational sou2);
Status mul_r(Rational *des,Rational sou1,Rational sou2);
Status div_r(Rational *des,Rational sou1,Rational sou2);
Status add_f(Rational *des,Rational sou1,double num);
Status sub_f(Rational *des,Rational sou1,double num);
Status mul_f(Rational *des,Rational sou1,double num);
Status div_f(Rational *des,Rational sou1,double num);
```
每种运算分``分数与分数``和``分数与小数``两种计算形式(``小数和小数``先算完再转换)。

###其他操作：
1. 打印
2. 比较
3. 转化为小数
3. 判断是否是有限小数
4. 判断是否是整数

```c
Status printr(Rational sou);	//分数形式打印,不换行
Status putsr(Rational sou);		//分数形式打印,换行
Status printr_f(Rational sou);	//小数形式打印,不换行
Status putsr_f(Rational sou);	//小数形式打印，换行
```
本想格式化规范化地方便漂亮地打印出来，但分数内部的间距字长等不知道怎么控制，在还没有更好的主意之前先这样吧。

```c
int ratcmp(Rational sou1,Rational sou2);	//比较两个分数
int ratcmp_f(Rational sou1,double num);		//比较分数和小数
```
比较两个分数的fraction大小。注意__小数不能直接判断是否等于0__，规定若其绝对值小于10e-6才等于0。若前者大于后者，返回1，相等返回0，前者小于后者返回-1。但是函数定义返回类型是`int`，不太合理，有待改进。

```c
double tof(Rational sou);		//求小数
```
虽然可以直接查看结构体成员，不过还是封装起来用函数操作比较好。

```c
Status isfinite_r(Rational sou);	//有限小数
```
若分母的质因子中只含有2和5，则说明分数是有限小数

```c
Status isInt(Rational sou);	//是否整数
```
因为人为规定0的表示为分母是1，其他分数若是整数，必能化简到分母为1的情况。因此，只需判断分母是否为1即可判断是否是整数

Matrix:
--------
