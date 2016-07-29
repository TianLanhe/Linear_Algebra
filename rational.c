#include "rational.h"
Status assign(Rational *des,int numerator,int denominator){
	if(!denominator)return ERROE;				//分母不能为0
	if(numerator*denominator < 0){				//规定若分数为负数，则分子为负，分母为正
		denominator=denominator>0?denominator:-denominator;
		numerator=numerator<0?numerator:-numerator;
	}else{
		denominator=denominator>0?denominator:-denominator;
		numerator=numerator>0?numerator:-numerator;
	}
	des->numerator=numerator;					//规定若分数为0，则分子为0，分母为1
	if(des->numerator == 0)des->denominator=1;
	else des->denominator=denominator;
	des->friaction=numerator*1.0/denominator;
	if(simplify(des) == ERROE)return ERROE;
	return OK;
}
Status assign_f(Rational *des,double num){
	int numerator;
	if(num>0)numerator=(num+0.0005)*1000;		//由于浮点数转化为整数会有误差
	else numerator=(num-0.0005)*1000;			//因此采用四舍五入，消除误差
	return assign(des,numerator,1000);
}
double tof(Rational sou){
	sou.friaction=sou.numerator*1.0/sou.denominator;
	return sou.friaction;
}
Status printr(Rational sou){
	printf("%d/%d",sou.numerator,sou.denominator);
	return OK;
}
Status putsr(Rational sou){
	printf("%d/%d\n",sou.numerator,sou.denominator);
	return OK;
}
Status printr_f(Rational sou){
	printf("%f",sou.friaction);
	return OK;
}
Status putsr_f(Rational sou){
	printf("%f\n",sou.friaction);
	return OK;
}
int maxfactor(Rational sou){
	int small;
	int big;
	int temp;					//采用辗转相除法求最大公因数
	if(sou.numerator == 0)return 1;
	small=sou.numerator>0?sou.numerator:-sou.numerator;
	big=sou.denominator>0?sou.denominator:-sou.denominator;
	if(small > big){			//如果有负数要把它们转化为正数
		temp=small;
		small=big;
		big=temp;
	}
	temp=big%small;
	while(temp){
		big=small;
		small=temp;
		temp=big%small;
	}
	return small;
}
Status simplify(Rational *sou){
	int factor;					//化简操作会直接修改原分数
	factor=maxfactor(*sou);
	if(factor != 1){
		sou->denominator/=factor;
		sou->numerator/=factor;
	}
	return OK;
}
Status opp(Rational *des,Rational sou){
	des->numerator=-sou.numerator;
	des->denominator=sou.denominator;
	des->friaction=des->numerator*1.0/des->denominator;
	return OK;
}
Status inv(Rational *des,Rational sou){
	if(sou.denominator <= 0 || sou.numerator == 0)return ERROE;
	des->numerator=sou.denominator;			//如果分母小于等于0，表示出错了，因为分母不能为0
	des->denominator=sou.numerator;			//且前面规定了如果分数为负，规定分子为负，分母为正
	des->friaction=des->numerator*1.0/des->denominator;	//分子不能为0
	return OK;								//以上三种情况表示错误
}
Status add_r(Rational *des,Rational sou1,Rational sou2){
	int numerator,denominator;
	numerator=sou1.numerator*sou2.denominator+sou2.numerator*sou1.denominator;
	denominator=sou1.denominator*sou2.denominator;
	return assign(des,numerator,denominator);
}
Status sub_r(Rational *des,Rational sou1,Rational sou2){
	int numerator,denominator;
	numerator=sou1.numerator*sou2.denominator-sou2.numerator*sou1.denominator;
	denominator=sou1.denominator*sou2.denominator;
	return assign(des,numerator,denominator);
	//opp(des,sou2);
	//return assign(des,sou1,des);
}
Status mul_r(Rational *des,Rational sou1,Rational sou2){
	return assign(des,sou1.numerator*sou2.numerator,sou1.denominator*sou2.denominator);
}
Status div_r(Rational *des,Rational sou1,Rational sou2){
	Rational temp;
	if(inv(&temp,sou2) == ERROE)return ERROE;	//如果分子为0，无法求逆，自然无法相除
	return mul_r(des,sou1,temp);
}
int ratcmp_r(Rational sou1,Rational sou2){
	double result;
	double abs_result;
	result=sou1.friaction-sou2.friaction;
	if(result > 0)abs_result=result;
	else abs_result=-result;
	if(abs_result <= 1e-6)return 0;
	else if(result < 0)return -1;
	else return 1;
}
int ratcmp_f(Rational sou1,double num){
	double result;
	double abs_result;
	result=sou1.friaction-num;
	if(result > 0)abs_result=result;
	else abs_result=-result;
	if(abs_result <= 1e-6)return 0;
	else if(result < 0)return -1;
	else return 1;
}
Status add_f(Rational *des,Rational sou1,double num){
	Rational temp;
	if(assign_f(&temp,num) == ERROE)return ERROE;
	return add_r(des,sou1,temp);
}
Status sub_f(Rational *des,Rational sou1,double num){
	Rational temp;
	if(assign_f(&temp,num) == ERROE)return ERROE;
	return sub_r(des,sou1,temp);
}
Status mul_f(Rational *des,Rational sou1,double num){
	Rational temp;
	if(assign_f(&temp,num) == ERROE)return ERROE;
	return mul_r(des,sou1,temp);
}
Status div_f(Rational *des,Rational sou1,double num){
	Rational temp;
	if(assign_f(&temp,num) == ERROE)return ERROE;
	return div_r(des,sou1,temp);
}
Status power(Rational *des,Rational sou,int n){
	int i;
	if(n == 0){
		if(sou.numerator == 0)return ERROE;
		else return assign(des,1,1);
	}else if(n > 0){
		assign(des,sou.numerator,sou.denominator);
		for(i=1;i<n;i++)mul_r(des,*des,sou);
	}else{
		assign(des,sou.numerator,sou.denominator);
		for(i=1;i<-n;i++)mul_r(des,*des,sou);
		if(!inv(des,*des))return ERROE;
	}
	return OK;
}
Status isfinite(Rational sou){
	int denominator;
	int factor;
	if(sou.numerator == 0)return true;
	denominator=sou.denominator;
	while(denominator%2 == 0)denominator/=2;
	while(denominator%5 == 0)denominator/=5;
	return denominator == 1?true:false;
}
