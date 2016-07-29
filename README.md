线性代数
========

* __[rational.h](#Rational:)__：提供了分数的一组操作接口，使用Rational数据类型和函数轻松进行分数的各种操作。
* __[matrix.h](#Matrix:)__:提供了线性代数的一组计算接口，包含了rational.h，使用分数代替整数和浮点数进行数值计算，可以方便简洁地显示结果。使用Matrix数据类型和其提供的函数可以进行线性代数的各种计算。

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
#define ERROE -1        //错误返回
```

###基本操作：
1. 初始化(赋值)
2. 求公因数
3. 化简

```c
Status assign(Rational *des,int numerator,int denominator);
Status assign_f(Rational *des,double num);
```
赋值分分数赋值和小数赋值，规定分母永远为正数，以分子的正负作为整个分数的正负。若分数为0，规定则分子为0，分母为1。小数赋值中通过四舍五入消除转换的误差，精确到0.0001，结果转换为最简分数

```c
int maxfactor(Rational sou)
```
用辗转相除法求最大公因式用于分数的化简

```c
Status simplify(Rational *sou);
```
化简操作直接在原分数上进行，会改变原分数的值


###算术运算：
1. 求相反数
1. 求倒数
1. 求幂
1. 加法
2. 减法
3. 乘法
4. 除法

```c
Status opp(Rational *des,Rational sou);
```
只改变分子和小数符号，其他原样赋值给des。因为之前已经规定分母为正，以分子判断正负

```c
Status inv(Rational *des,Rational sou);
```
sou必须是非零数，即sou的分子不能为0，分母是大于0的整数。

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
每种运算分``分数与分数``和``分数与小数``两种计算形式(``小数和小数``先算完再转换)，des=sou1+sou2，des可以是sou1,sou2或其他新分数

###其他操作：
1. 打印
2. 比较
3. 判断是否是有限小数

Matrix:
--------
