#ifndef matrix_h
#define matrix_h
#include "rational.h"
#include <stdlib.h>
typedef struct MATRIX{
	Rational **matrix;			//存储矩阵的数据
	int row;					//矩阵的行
	int column;					//矩阵的列
}Matrix;
Status initMatrix(Matrix *mat,int row,int column);
//初始化矩阵，为其分配row*column的Rational变量
Status destroyMatrix(Matrix *mat);
//销毁矩阵，回收矩阵数组的空间并设置row与column为0
Status printm(Matrix mat);
//格式化打印矩阵
Status getmatrix(Matrix *matr);
//输入矩阵
Status getIdenMat(Matrix *matr,int n);
//将matr设置为n阶单位矩阵
Status copyMatrix(Matrix *des,Matrix sou);
//复制矩阵，des=sou。将des销毁重新初始化为行列与sou相同再赋值。
Status matrixAdd(Matrix *des,Matrix sou1,Matrix sou2);
//矩阵加法，若sou1与sou2行列数相同，则进行相加，否则返回ERROR
Status matrixSub(Matrix *des,Matrix sou1,Matrix sou2);
//矩阵减法，若sou1与sou2行列数相同，则进行相减，否则返回ERROR
Status matrixMul_scalar_f(Matrix *des,Matrix sou1,double num);
//矩阵数乘(与小数)
Status matrixMul_scalar_r(Matrix *des,Matrix sou1,Rational rat);
//矩阵数乘(与分数)
Status getResult(Rational *result,Matrix sou);
//计算行列式的值，并把结果储存在分数result中
Status matrixTra(Matrix *des,Matrix sou);
//求矩阵sou的转置并存在des中
Status matrixMul(Matrix *des,Matrix sou1,Matrix sou2);
//矩阵相乘，若sou1.row != sou2.column ，则返回ERROR，否则计算两个矩阵的乘
Status matrixCof(Rational *result,Matrix sou,int row,int column);
//求矩阵(row,column)元素的代数余子式，并把结果储存在resu中。要求矩阵行列数相等
Status matrixAdj(Matrix *des,Matrix sou);
//求矩阵的伴随阵，要求矩阵行列数相等
Status matrixInv(Matrix *des,Matrix sou);
//求矩阵的逆，要求矩阵行列数相等且行列式的值不为0
Status matrixPow(Matrix *des,Matrix sou,int n);
//求矩阵的n次幂，任何矩阵的0次幂是单位矩阵，1次幂是其本身，-n次幂是n次幂的逆
int matrixRank(Matrix sou);
//求矩阵的秩
Status matrixSimplest(Matrix *des,Matrix sou);
//求矩阵的最简形，储存在des中
Status matrixCanRepre(Matrix sou1,Matrix sou2);
//判断矩阵sou2能否由sou1线性表示，能返回true，否返回false。若sou1与sou2行数不同，返回ERROR
Status matrixIsEqual(Matrix sou1,Matrix sou2);
//判断两个矩阵是否等价，即sou1能被sou2线性表示且sou2能被sou1线性表示
Status matrixIsRelevant(Matrix sou);
//判断矩阵是否线性相关。是否线性相关的充要条件是向量组的秩小于列数
Status matrixMaxIrre(Matrix *des,Matrix sou);
//求sou的一个最大线性无关组
Status matrixHomogen(Matrix *des,Matrix sou);
//求齐次线性方程组的通解,返回-2表示只有唯一解
Status matrixNoHomogen(Matrix *des,Matrix sou);
//求非齐次线性方程组的通解,返回-2表示只有唯一解，若无解返回ERROR(还有其他情况可能返回ERROR)
Status matrixHomogenBasic(Matrix *des,Matrix sou);
//求齐次线性方程组的基础解系,返回-2表示只有唯一解
Status matrixNoHomogenBasic(Matrix *des,Matrix sou);
//求非齐次线性方程组的基础解系,返回-2表示只有唯一解，若无解返回ERROR(还有其他情况可能返回ERROR)
Status given(Matrix *des,Matrix sou);
//求矩阵的所有特征值，存放在1*n的矩阵中，n为矩阵sou不同特征值的个数
//虽然能求任意阶的矩阵，但由于Rational算法的原因，如果数太特殊容易出现问题
#endif
