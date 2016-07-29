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
//矩阵减法，若sou1与sou2行列数相同，则进行想减，否则返回ERROR
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
//判断矩阵sou1能否被sou2线性表示，能返回true，否返回false。若sou1与sou2行数不同，返回ERROR
Status matrixIsEqual(Matrix sou1,Matrix sou2);
//判断两个矩阵是否等价，即sou1能被sou2线性表示且sou2能被sou1线性表示
Status matrixIsRelevant(Matrix sou);
//判断矩阵是否线性相关。是否线性相关的充要条件是向量组的秩小于列数

Status matrixMaxIrre(Matrix *des,Matrix sou);

Status initMatrix(Matrix *mat,int row,int column){
	int i,j;
	if(row == 0 && column == 0 ){
		mat->matrix=NULL;
	}else if(row <= 0 || column <= 0){
		return ERROR;
	}else{
		mat->matrix=(Rational**)malloc(sizeof(Rational*)*row);
		if(!mat->matrix)return ERROR;
		for(i=0;i<row;i++){
			mat->matrix[i]=(Rational*)malloc(sizeof(Rational)*column);
			if(!mat->matrix[i])return ERROR;
			for(j=0;j<column;j++){
				if(assign_f(&mat->matrix[i][j],0) == ERROR)
					return ERROR;
			}
		}
	}
	mat->row=row;
	mat->column=column;
	return OK;
}
Status destroyMatrix(Matrix *mat){
	int i,j;
	if(mat->matrix){
		for(i=0;i<mat->row;i++){
			free(mat->matrix[i]);
		}
		free(mat->matrix);
		mat->row=mat->column=0;
		mat->matrix=NULL;
		return OK;
	}else return ERROR;
}
Status copyMatrix(Matrix *des,Matrix sou){
	int i;
	int j;
	if(des->matrix == sou.matrix)return OK;
	destroyMatrix(des);
	if(initMatrix(des,sou.row,sou.column) == ERROR)return ERROR;
	for(i=0;i<sou.row;i++){
		for(j=0;j<sou.column;j++){
			if(assign(&des->matrix[i][j],sou.matrix[i][j].numerator,sou.matrix[i][j].denominator) == ERROR)
				return ERROR;
		}
	}
	return OK;
}
Status printm(Matrix mat){
	int i;
	int j;
	for(i=0;i<mat.row;i++){
		for(j=0;j<mat.column;j++){
			printr(mat.matrix[i][j]);
			printf("  ");
		}
		printf("\n");
	}
	printf("\n");
	return OK;
}
Status getmatrix(Matrix *matr){
	int i,j;
	double num;
	for(i=0;i<matr->row;i++){
		for(j=0;j<matr->column;j++){
			scanf("%lf",&num);
			if(assign_f(&matr->matrix[i][j],num) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status getIdenMat(Matrix *des,int n){
	int i;
	int j;
	Matrix tmp;
	tmp=*des;
	if(n <= 0)return ERROR;
	if(initMatrix(des,n,n) == ERROR)return ERROR;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i == j){
				if(assign(&des->matrix[j][i],1,1) == ERROR)
					return ERROR;
			}
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixTra(Matrix *des,Matrix sou){
	int i;
	int j;
	Matrix tmp;
	tmp=*des;
	if(initMatrix(des,sou.column,sou.row) == ERROR)return ERROR;
	for(i=0;i<sou.row;i++){
		for(j=0;j<sou.column;j++){
			if(assign(&des->matrix[j][i],sou.matrix[i][j].numerator,sou.matrix[i][j].denominator) == ERROR)
				return ERROR;
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixAdd(Matrix *des,Matrix sou1,Matrix sou2){
	int i,j;
	Rational temp;
	Matrix tmp;
	if(sou1.row != sou2.row || sou1.column != sou2.column)return ERROR;
	tmp=*des;
	if(initMatrix(des,sou1.row,sou1.column) == ERROR)return ERROR;
	for(i=0;i<sou1.row;i++){
		for(j=0;j<sou1.column;j++){
			if(add_r(&temp,sou1.matrix[i][j],sou2.matrix[i][j]) == ERROR)
				return ERROR;
			if(assign(&des->matrix[i][j],temp.numerator,temp.denominator) == ERROR)
				return ERROR;
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixSub(Matrix *des,Matrix sou1,Matrix sou2){
	int i,j;
	Rational temp;
	Matrix tmp;
	if(sou1.row != sou2.row || sou1.column != sou2.column)return ERROR;
	tmp=*des;
	if(initMatrix(des,sou1.row,sou1.column) == ERROR)return ERROR;
	for(i=0;i<sou1.row;i++){
		for(j=0;j<sou1.column;j++){
			if(sub_r(&temp,sou1.matrix[i][j],sou2.matrix[i][j]) == ERROR)
				return ERROR;
			if(assign(&des->matrix[i][j],temp.numerator,temp.denominator) == ERROR)
				return ERROR;
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixMul_scalar_f(Matrix *des,Matrix sou1,double num){
	int i,j;
	Rational temp;
	Matrix tmp;
	tmp=*des;
	if(initMatrix(des,sou1.row,sou1.column) == ERROR)return ERROR;
	for(i=0;i<sou1.row;i++){
		for(j=0;j<sou1.column;j++){
			if(mul_f(&temp,sou1.matrix[i][j],num) == ERROR)
				return ERROR;
			if(assign(&des->matrix[i][j],temp.numerator,temp.denominator) == ERROR)
				return ERROR;
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixMul_scalar_r(Matrix *des,Matrix sou1,Rational rat){
	int i,j;
	Rational temp;
	Matrix tmp;
	tmp=*des;
	if(initMatrix(des,sou1.row,sou1.column) == ERROR)return ERROR;
	for(i=0;i<sou1.row;i++){
		for(j=0;j<sou1.column;j++){
			if(mul_r(&temp,sou1.matrix[i][j],rat) == ERROR)
				return ERROR;
			if(assign(&des->matrix[i][j],temp.numerator,temp.denominator) == ERROR)
				return ERROR;
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status getResult(Rational *result,Matrix sou){
	int i,j;
	int row,column;
	Matrix temp;
	Rational tmp;
	Rational tmp2;
	if(sou.row != sou.column)return ERROR;
	initMatrix(&temp,0,0);
	copyMatrix(&temp,sou);
	for(i=0;i<temp.row;i++){
		row=i+1;
		while(ratcmp_f(temp.matrix[i][i],0) == 0){
			if(row == temp.row)break;
			for(column=0;column<temp.column;column++){
				if(add_r(&temp.matrix[i][column],temp.matrix[i][column],temp.matrix[row][column]) == ERROR)
					return ERROR;
			}
			row+=1;
		}
		if(ratcmp_f(temp.matrix[i][i],0) != 0){
			for(j=i+1;j<temp.row;j++){
				if(div_r(&tmp,temp.matrix[j][i],temp.matrix[i][i]) == ERROR)
	            	return ERROR;
	            for(column=i;column<temp.column;column++){
	            	if(mul_r(&tmp2,tmp,temp.matrix[i][column]) == ERROR)
						return ERROR;
					if(sub_r(&temp.matrix[j][column],temp.matrix[j][column],tmp2) == ERROR)
						return ERROR;
	            }
	        }
		}
	}
	assign_f(&tmp,1);
	for(i=0;i<temp.row;i++)
		if(mul_r(&tmp,tmp,temp.matrix[i][i]) == ERROR)
			return ERROR;
	destroyMatrix(&temp);
	if(assign(result,tmp.numerator,tmp.denominator) == ERROR)
		return ERROR;
	return OK;
}
Status matrixMul(Matrix *des,Matrix sou1,Matrix sou2){
	int i,j,k;
	Rational temp;
	Matrix tmp;
	tmp=*des;
	if(sou1.column != sou2.row)return ERROR;
	if(initMatrix(des,sou1.row,sou2.column) == ERROR)return ERROR;
	for(i=0;i<sou1.row;i++){
		for(j=0;j<sou2.column;j++){
			for(k=0;k<sou1.column;k++){
				if(mul_r(&temp,sou1.matrix[i][k],sou2.matrix[k][j]) == ERROR)
					return ERROR;
				if(add_r(&des->matrix[i][j],des->matrix[i][j],temp) == ERROR)
					return ERROR;
			}
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixCof(Rational *result,Matrix sou,int x,int y){
	int i,j;
	int row,column;
	int symbol;
	Matrix temp;
	Rational tmp;
	if(sou.row != sou.column)return ERROR;
	initMatrix(&temp,sou.row-1,sou.column-1);
	row=0;
	column=0;
	for(i=0;i<sou.row;i++){
		if(i == x)continue;
		for(j=0;j<sou.column;j++){
			if(y != j){
				if(assign(&temp.matrix[row][column++],sou.matrix[i][j].numerator,sou.matrix[i][j].denominator) == ERROR)
					return ERROR;
			}
		}
		row++;
		column=0;
	}
	if(getResult(&tmp,temp) == ERROR)return ERROR;
	symbol=(x+y)%2?-1:1;
	if(mul_f(result,tmp,symbol) == ERROR)return ERROR;
	return OK;
}
Status matrixAdj(Matrix *des,Matrix sou){
	int i,j;
	Rational temp;
	Matrix tmp;
	tmp=*des;
	if(sou.row != sou.column)return ERROR;
	if(initMatrix(des,sou.row,sou.column) == ERROR)return ERROR;
	for(i=0;i<sou.row;i++){
		for(j=0;j<sou.column;j++){
			if(matrixCof(&temp,sou,i,j) == ERROR)return ERROR;
			if(assign(&des->matrix[i][j],temp.numerator,temp.denominator) == ERROR)
				return ERROR;
		}
	}
	if(matrixTra(des,*des) == ERROR)return ERROR;
	destroyMatrix(&tmp);
	return OK;
}
Status matrixInv(Matrix *des,Matrix sou1){
	int i,j;
	Rational temp;
	Matrix tmp;
	Matrix adj;
	tmp=*des;
	if(initMatrix(&adj,0,0) == ERROR)return ERROR;
	if(initMatrix(des,sou1.row,sou1.column) == ERROR)return ERROR;
	if(getResult(&temp,sou1) == ERROR)return ERROR;
	if(inv(&temp,temp) == ERROR)return ERROR;
	if(matrixAdj(&adj,sou1) == ERROR)return ERROR;
	if(matrixMul_scalar_r(des,adj,temp) == ERROR)return ERROR;
	destroyMatrix(&tmp);
	destroyMatrix(&adj);
	return OK;
}
Status matrixPow(Matrix *des,Matrix sou,int n){
	int abs_n;
	int i;
	abs_n=n>0?n:-n;
	if(n == 0){
		if(getIdenMat(des,sou.row) == ERROR)return ERROR;
	}else{
		if(copyMatrix(des,sou) == ERROR)return ERROR;
		for(i=1;i<abs_n;i++)
			if(matrixMul(des,*des,sou) == ERROR)
				return ERROR;
		if(n < 0){
			if(matrixInv(des,*des) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status matrixSimplest(Matrix *des,Matrix sou){
	int i,j,k;
	int column,row;
	Rational temp,temp2;
	Matrix tmp;
	tmp=*des;
	if(copyMatrix(des,sou) == ERROR)return ERROR;
	for(i=0;i<sou.row;i++){
		column=i;
		row=i;
		if(column >= sou.column)break;
		while(ratcmp_f(des->matrix[i][column],0) == 0){
			if(ratcmp_f(des->matrix[row][column],0) != 0){
				for(k=column;k<sou.column;k++){
					if(add_r(&des->matrix[i][k],des->matrix[i][k],des->matrix[row][k]) == ERROR)
						return ERROR;
				}
			}else row++;
			if(row >= sou.row){
				column++;
				row=i;
			}
			if(column >= sou.column){
				column--;
				break;
			}
		}
		if(ratcmp_f(des->matrix[i][column],0) != 0){
			for(j=0;j<sou.row;j++){
				if(j == i)continue;
				if(div_r(&temp,des->matrix[j][column],des->matrix[i][column]) == ERROR)
					return ERROR;
				for(k=column;k<sou.column;k++){
					if(mul_r(&temp2,temp,des->matrix[i][k]) == ERROR)
						return ERROR;
					if(sub_r(&des->matrix[j][k],des->matrix[j][k],temp2) == ERROR)
						return ERROR;
				}
			}	
		}
	}
	for(i=0;i<sou.row;i++){
		for(j=0;j<sou.column;j++){
			if(ratcmp_f(des->matrix[i][j],0) != 0){
				for(k=sou.column-1;k>=j;k--){
					if(div_r(&des->matrix[i][k],des->matrix[i][k],des->matrix[i][j]) == ERROR)
						return ERROR;
				}
				break;
			}
		}
	}
	destroyMatrix(&tmp);
	return OK;
}
Status matrixIsEqual(Matrix sou1,Matrix sou2){
	return matrixCanRepre(sou1,sou2)&&matrixCanRepre(sou2,sou1)?true:false;
}
int matrixRank(Matrix sou){
	Matrix temp;
	int i,j;
	int rank;
	if(initMatrix(&temp,0,0) == ERROR)return ERROR;
	if(matrixSimplest(&temp,sou) == ERROR)return ERROR;
	rank=0;
	for(i=0;i<temp.row;i++){
		for(j=0;j<temp.column;j++){
			if(ratcmp_f(temp.matrix[i][j],0) != 0){
				rank++;
				break;
			}
		}
	}
	return rank;
}
Status matrixCanRepre(Matrix sou1,Matrix sou2){
	int rank1,rank2;
	int i,j;
	Matrix temp;
	if(sou1.row != sou2.row)return false;
	rank1=matrixRank(sou1);
	if(rank1 == ERROR)return ERROR;
	if(initMatrix(&temp,sou1.row,sou1.column+sou2.column) == ERROR)return ERROR;
	for(i=0;i<sou1.row;i++){
		for(j=0;j<sou1.column;j++){
			if(assign(&temp.matrix[i][j],sou1.matrix[i][j].numerator,sou1.matrix[i][j].denominator) == ERROR)
				return ERROR;
		}
	}
	for(i=0;i<sou2.row;i++){
		for(j=0;j<sou2.column;j++){
			if(assign(&temp.matrix[i][j+sou1.column],sou2.matrix[i][j].numerator,sou2.matrix[i][j].denominator) == ERROR)
				return ERROR;
		}
	}
	rank2=matrixRank(temp);
	if(rank2 == ERROR)return ERROR;
	destroyMatrix(&temp);
	return rank1==rank2?true:false;
}
Status matrixIsRelevant(Matrix sou){
	int rank;
	rank=matrixRank(sou);
	if(rank == ERROR)return ERROR;
	return rank<sou.column?true:false;
}
int main(){
	Matrix mat1;
	Matrix mat2;
	Matrix mat3;
	int i,j;
	initMatrix(&mat1,0,0);
	initMatrix(&mat2,0,0);
	initMatrix(&mat3,0,0);
	scanf("%d",&i);
	if(i ==1){
		scanf("%d%d",&i,&j);
		initMatrix(&mat1,i,j);
		getmatrix(&mat1);
		scanf("%d%d",&i,&j);
		initMatrix(&mat2,i,j);
		getmatrix(&mat2);
		printm(mat1);
		printm(mat2);
		if(matrixMul(&mat3,mat1,mat2) == ERROR)printf("error\n");
		else printm(mat3);
	}else if(i == 2){
		scanf("%d%d",&i,&j);
		initMatrix(&mat1,i,j);
		getmatrix(&mat1);
		printm(mat1);
		if(matrixInv(&mat3,mat1) == ERROR)printf("error\n");
		else printm(mat3);
	}else if(i ==3){
		scanf("%d%d",&i,&j);
		initMatrix(&mat1,i,j);
		getmatrix(&mat1);
		printm(mat1);
		if(matrixSimplest(&mat3,mat1) == ERROR)printf("error\n");
		else printm(mat3);
	}
	return 0;
}
