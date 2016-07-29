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
2. 化简
3. 求公因数

###算术运算：
1. 加法
2. 减法
3. 乘法
4. 除法
5. 求相反数
6. 求倒数
7. 求幂

###其他操作：
1. 打印
2. 比较
3. 判断是否是有限小数

Matrix:
--------
