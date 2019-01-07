#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define LH 1
#define EH 0
#define RH -1
#define false 0
#define true 1
typedef int  ElemType; //数据类型
typedef struct BiTNode{
    ElemType data; //数据域
    ElemType bf;
    struct BiTNode *lchild, *rchlid; //左右子树域
}BiTNode, *BiTree;

//左旋转
void L_Rotate(BiTree *T)
{
    BiTree R = (*T)->rchlid;
    (*T)->rchlid = R->lchild;
    R->lchild = *T;
    *T = R;
}

//右旋转
void R_Rotate(BiTree *T)
{
    BiTree L = (*T)->lchild;
    (*T)->lchild = L->rchlid;
    L->rchlid = *T;
    *T = L;
}

//T的左边高，不平衡，右旋转，旋转前检查L->bf
//如果为RH，L要先进行左旋转，使T->lchild->bf与T->bf一致
void LeftBalance(BiTree *T)
{
    BiTree L,Lr;
    L = (*T)->lchild;
    Lr = L->rchlid;
    switch (L->bf){
        case LH:
            L->bf = (*T)->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            switch (Lr->bf){
                case LH:
                    L->bf = EH;
                    (*T)->bf = RH;
                    break;
                case EH:
                    L->bf = (*T)->bf = EH;
                    break;
                case RH:
                    L->bf = LH;
                    (*T)->bf = EH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&L);
            R_Rotate(T);
            break;
    }
}

//T 的右边高，不平衡，使其平衡，左旋转，左旋转前先检查R->bf,
//如果为LH，R要先进行右旋转，使T->rchild->bf和T->bf一致
void RightBalance(BiTree* T)
{
    BiTree R,Rl;
    R = (*T)->rchlid;
    Rl = R->lchild;
    switch(R->bf)
    {
        case RH:
            R->bf = (*T)->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            switch(R->bf)
            {
                case LH:
                    R->bf = RH;
                    (*T)->bf = EH;
                    break;
                case EH:
                    R->bf = (*T)->bf = EH;
                    break;
                case RH:
                    R->bf = EH;
                    (*T)->bf = LH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(&R);
            L_Rotate(T);
            break;
    }
}
//往平衡二叉树上插入结点
int InsertAVL(BiTree *T,int data,int *taller)
{
    if(*T == NULL)  //找到插入位置
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->bf = EH;
        (*T)->rchlid = (*T)->lchild = NULL;
        (*T)->data = data;
        *taller = true;
    }
    else
    {
        if(data == (*T)->data)  //树中有相同的结点数据直接返回
        {
            *taller = false;
            return false;
        }
        if(data < (*T)->data)   //往左子树搜索进行插入
        {
            if(!InsertAVL(&(*T)->lchild,data,taller))   //树中有相同的结点
            {
                *taller = false;
                return false;
            }
            if (*taller)
            {
                switch ((*T)->bf)               //T插入结点后，检测平衡因子，根据情况，做相应的修改和旋转
                {
                    case LH:
                        LeftBalance(T);             //插入后左边不平衡了，让其左平衡
                        *taller = false;
                        break;
                    case EH:
                        (*T)->bf = LH;
                        *taller = true;
                        break;
                    case RH:
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                }
            }
        }
        else                    //往右子树搜索进行插入
        {
            if(!InsertAVL(&(*T)->rchlid,data,taller))      //树中有相同的结点
            {
                *taller = false;
                return false;
            }
            if (*taller)        //插入到右子树中且长高了
            {
                switch ((*T)->bf)                       //T插入结点后，检测平衡因子，根据情况，做相应的修改和旋转
                {
                    case LH:
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                    case EH:
                        (*T)->bf = RH;
                        *taller = true;
                        break;
                    case RH:
                        RightBalance(T);                       //插入后右边不平衡了，让其右平衡
                        *taller = false;
                        break;
                }
            }
        }
    }
    return true;
}

int SearchBBT(BiTree T,int key,BiTree m,BiTree *p){
    if(!T){             //查找失败
        *p = m;
        return 0;
    }
    else if (key == T->data){   //找到key
        *p = T;
        return 1;
    }
    else if(key < T->data){
        return SearchBBT(T->lchild,key,T,p);
    }
    else {
        return SearchBBT(T->rchlid,key,T,p);
    }
}

int Delete(BiTree *p){
    BiTree q,s;

    if((*p)->rchlid == NULL){     //右子树为空，重接他的左子树
        q = *p;
        *p = (*p)->lchild;
        free(q);
    } else if((*p)->lchild == NULL){  //左子树为空，重接他的右子树
        q = *p;
        *p = (*p)->rchlid;
        free(q);
    }else{                            //左右子树都部位空
        q = *p;
        s = (*p)->lchild;
        while(s->rchlid){             //找到左子树的最右子树
            q = s;
            s = s->rchlid;
        }

        (*p)->data = s->data;         //s指向被删除结点的直接前驱（将被删除结点的值改为直接前驱结点的值）

        q->lchild = s->lchild;    //重接q的左子树

        free(s);
    }
}

int DeleteBBT(BiTree *T,int key){
    if(!*T)      //不存在关键字等于key的元素
        return 0;
    else{
        if(key == (*T)->data)
            return Delete(T);
        else if (key < (*T)->data)
            return DeleteBBT(&(*T)->lchild,key);
        else
            return DeleteBBT(&(*T)->rchlid,key);
    }
}

//中序遍历查找二叉树
void InOrderBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    InOrderBiTree(T->lchild);
    printf("%d ", T->data);
    InOrderBiTree(T->rchlid);
}

int main(){
    int i,n;
    int a[10] ={62,88,58,47,35,73,51,99,37,93};

    BiTree T = NULL;
    for (i = 0; i < 10; i++) {  // 通过插入操作来构建二叉排序树
        InsertAVL(&T, a[i],&n);
    }

    printf("中序递归遍历二叉树：\n");
    InOrderBiTree(T);
    printf("\n\n");

    DeleteBBT(&T, 93);
    printf("删除结点 93 后的结果为：\n");
    InOrderBiTree(T);
    printf("\n\n");

    printf("插入 91 后的结果为：\n");
    InsertAVL(&T,91,&n);
    InOrderBiTree(T);
    printf("\n\n");
    return 0;
}
