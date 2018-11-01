//
// Created by kingpower on 2018/11/1.
//
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int Element;
#define MAXSIZE 12500   //假设非零元素的最大值为12500
typedef struct Triple{
    int i,j;    //该非零元素的行下标和列下标
    Element e;
}Triple;
typedef struct TSMatrix{
    Triple data[MAXSIZE + 1];   //非零元三元组表，data【0】未用
    int mu,nu,tu;   //矩阵的行数，列数和非零元素g个数
}TSMatrix;

//创建稀疏矩阵
TSMatrix CreateSMatrix(){
    TSMatrix S;
    int i,j,e,k;
    printf("情输入矩阵的矩阵行数列数和非零元素个数 eg: 5 5 5 表示创建一个5x5的非零元素为5的矩阵");
    scanf("%d %d %d",&S.mu,&S.nu,&S.tu);
    printf("%d %d %d",S.mu,S.nu,S.tu);
    printf("请输入所创建矩阵数据所在位置 eg：3 2 4两行三列数值为4。按照先行后列输入");
    for(k = 1;k <= S.tu; k++){
        scanf("%d %d %d", &i, &j, &e);
        S.data[k].i = i;
        S.data[k].j = j;
        S.data[k].e = e;
    }
    return S;
}

//打印稀疏矩阵
void PrintSMatrix(TSMatrix T){
    int i,j,k = 1;
    for(i = 1;i <= T.mu; i++) {
        for (j = 1; j <= T.nu; j++) {
            if (T.data[k].i == i && T.data[k].j == j) {
                printf("%d   ", T.data[k].e);
                k++;
            } else {
                printf("0   ");
            }
        }
        printf("   \n");
    }
    printf("\n");
}
//算法5.1
TSMatrix TRansposeSMatrix(TSMatrix M,TSMatrix T){
    //采用三元组表存储表示，求稀疏矩阵M的转置矩阵T。
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if(T.tu){
        int q = 1;
        int col = 0;
        for (col = 1; col <= M.nu ; ++col){
            for(int p = 1;p <= M.tu; ++p){  //
                if(M.data[p].j == col){    //从第一列开始转置
                    T.data[p].i = M.data[q].j;
                    T.data[p].j = M.data[q].i;
                    T.data[p].e = M.data[q].e;
                    ++q;
                }
            }
        }
    }
    return T;
}   //TransposeSMatrix

//快速转置
TSMatrix FastTransposeSMatrix(TSMatrix M,TSMatrix T){
    //采用三元组顺序表存储表示，求稀疏矩阵M的的转置矩阵T。
    int col,t,cpot[MAXSIZE],p,q,num[MAXSIZE];
    T.mu = M.mu;
    T.nu = M.mu;
    T.tu = M.tu;
    if(T.tu){
        for(col = 1;col <= M.nu;++col){ //初始化num，每列的非零元素为零
            num[col] = 0;
        }
        for(t = 1;t <= M.nu; ++t){
            ++num[M.data[t].j]; //求M中每一列含非零元素个数 对应的j对应列对应num[序列号]自增
        }
        cpot[1] = 1;
        //求第col列中第一个非零元素在b.data中的序号
        for(col = 2 ; col <= M.nu; ++col){
            cpot[col] = cpot[col - 1] + num[col - 1];   //序号为之前的加上非零元素
        }
        for(p = 1;p <= M.tu; ++p){
            col = M.data[p].j;  //把每一个非零元素的列赋值给col
            q = cpot[col];  //把col列的非零元素位置赋值给q
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];    //第col列后一个非零元素在b.data的序号
        }   //  for
    }   // if
    return T;
}
int main(){
    TSMatrix M = CreateSMatrix();
    TSMatrix T;
    PrintSMatrix(M);
    T = TRansposeSMatrix(M,T);
    PrintSMatrix(M);
    T = FastTransposeSMatrix(M,T);
    PrintSMatrix(T);
    return 0;
}
