#ifndef rational_h
#define rational_h
#include <stdio.h>
#define Status int
#define true 1
#define false 0
#define OK 0
#define ERROE -1
typedef struct RATIONAL{
	int numerator;				//分子
	int denominator;			//分母
	double friaction;			//小数形式
}Rational;
Status add_r(Rational *des,Rational sou1,Rational sou2);
//分数与分数加法，*des=sou1+sou2
Status sub_r(Rational *des,Rational sou1,Rational sou2);
//分数与分数减法，*des=sou1-sou2
Status mul_r(Rational *des,Rational sou1,Rational sou2);
//分数与分数乘法，*des=sou1*sou2
Status div_r(Rational *des,Rational sou1,Rational sou2);
//分数与分数除法，*des=sou1+sou2
Status add_f(Rational *des,Rational sou1,double num);
//分数与小数加法
Status sub_f(Rational *des,Rational sou1,double num);
//分数与小数减法
Status mul_f(Rational *des,Rational sou1,double num);
//分数与小数乘法
Status div_f(Rational *des,Rational sou1,double num);
//分数与小数除法
Status power(Rational *des,Rational sou,int n);
//分数n次幂
int ratcmp(Rational sou1,Rational sou2);
//比较两个分数的大小，返回sou1-sou2
int ratcmp_f(Rational sou1,double num);
//比较分数和小数的大小，返回sou1-num
Status inv(Rational *des,Rational sou);
//分数求倒数(逆)，*des=sou.denominator/sou.numerator
Status opp(Rational *des,Rational sou);
//分数求相反数，*des=-sou
Status simplify(Rational *sou);
//化简分数
double tof(Rational sou);
//求分数的小数形式，但不打印
Status printr(Rational sou);
//以分数形式打印sou,没有换行
Status putsr(Rational sou);
//以分数形式打印sou,包括换行
Status printr_f(Rational sou);
//以小数形式打印sou,没有换行
Status putsr_f(Rational sou);
//以小数形式打印sou，包括换行
int maxfactor(Rational sou);
//求分子分母的最大公因数
Status isfinite(Rational sou);
//判断分数是否是有限小数
Status assign(Rational *des,int numerator,int denominator);
//给分数赋值，相当于初始化
Status assign_f(Rational *des,double num);
//给分数赋值，将小数或者整数转化为分数
#endif

