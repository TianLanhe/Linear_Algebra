#ifndef matrix_h
#define matrix_h
#include "rational.h"
#include <stdlib.h>
typedef struct MATRIX{
	Rational **matrix;			//�洢���������
	int row;					//�������
	int column;					//�������
}Matrix;
Status initMatrix(Matrix *mat,int row,int column);
//��ʼ������Ϊ�����row*column��Rational����
Status destroyMatrix(Matrix *mat);
//���پ��󣬻��վ�������Ŀռ䲢����row��columnΪ0
Status printm(Matrix mat);
//��ʽ����ӡ����
Status getmatrix(Matrix *matr);
//�������
Status getIdenMat(Matrix *matr,int n);
//��matr����Ϊn�׵�λ����
Status copyMatrix(Matrix *des,Matrix sou);
//���ƾ���des=sou����des�������³�ʼ��Ϊ������sou��ͬ�ٸ�ֵ��
Status matrixAdd(Matrix *des,Matrix sou1,Matrix sou2);
//����ӷ�����sou1��sou2��������ͬ���������ӣ����򷵻�ERROR
Status matrixSub(Matrix *des,Matrix sou1,Matrix sou2);
//�����������sou1��sou2��������ͬ���������������򷵻�ERROR
Status matrixMul_scalar_f(Matrix *des,Matrix sou1,double num);
//��������(��С��)
Status matrixMul_scalar_r(Matrix *des,Matrix sou1,Rational rat);
//��������(�����)
Status getResult(Rational *result,Matrix sou);
//��������ʽ��ֵ�����ѽ�������ڷ���result��
Status matrixTra(Matrix *des,Matrix sou);
//�����sou��ת�ò�����des��
Status matrixMul(Matrix *des,Matrix sou1,Matrix sou2);
//������ˣ���sou1.row != sou2.column ���򷵻�ERROR�����������������ĳ�
Status matrixCof(Rational *result,Matrix sou,int row,int column);
//�����(row,column)Ԫ�صĴ�������ʽ�����ѽ��������resu�С�Ҫ��������������
Status matrixAdj(Matrix *des,Matrix sou);
//�����İ�����Ҫ��������������
Status matrixInv(Matrix *des,Matrix sou);
//�������棬Ҫ��������������������ʽ��ֵ��Ϊ0
Status matrixPow(Matrix *des,Matrix sou,int n);
//������n���ݣ��κξ����0�����ǵ�λ����1�������䱾��-n������n���ݵ���
int matrixRank(Matrix sou);
//��������
Status matrixSimplest(Matrix *des,Matrix sou);
//����������Σ�������des��
Status matrixCanRepre(Matrix sou1,Matrix sou2);
//�жϾ���sou2�ܷ���sou1���Ա�ʾ���ܷ���true���񷵻�false����sou1��sou2������ͬ������ERROR
Status matrixIsEqual(Matrix sou1,Matrix sou2);
//�ж����������Ƿ�ȼۣ���sou1�ܱ�sou2���Ա�ʾ��sou2�ܱ�sou1���Ա�ʾ
Status matrixIsRelevant(Matrix sou);
//�жϾ����Ƿ�������ء��Ƿ�������صĳ�Ҫ���������������С������
Status matrixMaxIrre(Matrix *des,Matrix sou);
//��sou��һ����������޹���
Status matrixHomogen(Matrix *des,Matrix sou);
//��������Է������ͨ��,����-2��ʾֻ��Ψһ��
Status matrixNoHomogen(Matrix *des,Matrix sou);
//���������Է������ͨ��,����-2��ʾֻ��Ψһ�⣬���޽ⷵ��ERROR(��������������ܷ���ERROR)
Status matrixHomogenBasic(Matrix *des,Matrix sou);
//��������Է�����Ļ�����ϵ,����-2��ʾֻ��Ψһ��
Status matrixNoHomogenBasic(Matrix *des,Matrix sou);
//���������Է�����Ļ�����ϵ,����-2��ʾֻ��Ψһ�⣬���޽ⷵ��ERROR(��������������ܷ���ERROR)
Status given(Matrix *des,Matrix sou);
//��������������ֵ�������1*n�ľ����У�nΪ����sou��ͬ����ֵ�ĸ���
//��Ȼ��������׵ľ��󣬵�����Rational�㷨��ԭ�������̫�������׳�������
#endif
