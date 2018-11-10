//
// Created by kingpower on 2018/11/10.
//
//---------二叉树链表存储表示-------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


typedef int  ElemType; //数据类型

//定义二叉树结构，与单链表相似，多了一个右孩子结点
typedef struct BiTNode{
    ElemType  data; //数据域
    struct BiTNode *lChild, *rChlid; //左右子树域
}BiTNode, *BiTree;


//先序创建二叉树
int CreateBiTree(BiTree *T)
{
    ElemType ch;
    ElemType temp;
    scanf("%d", &ch);
    temp = getchar();
    if (ch == -1)
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!(*T))
            exit(-1);


        (*T)->data = ch;
        printf("输入%d的左子节点：", ch);
        CreateBiTree(&(*T)->lChild);
        printf("输入%d的右子节点：", ch);
        CreateBiTree(&(*T)->rChlid);
    }


    return 1;
}


//先序遍历二叉树
void TraverseBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    printf("%d ", T->data);
    TraverseBiTree(T->lChild);
    TraverseBiTree(T->rChlid);


}


//中序遍历二叉树
void InOrderBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    InOrderBiTree(T->lChild);
    printf("%d ", T->data);
    InOrderBiTree(T->rChlid);


}


//后序遍历二叉树
void PostOrderBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    PostOrderBiTree(T->lChild);
    PostOrderBiTree(T->rChlid);
    printf("%d ", T->data);


}




//二叉树的深度


int TreeDeep(BiTree T)
{
    int deep = 0;
    if(T)
    {
        int leftdeep = TreeDeep(T->lChild);
        int rightdeep = TreeDeep(T->rChlid);
        deep = leftdeep>=rightdeep?leftdeep+1:rightdeep+1;
    }
    return deep;
}


//求二叉树叶子结点个数


int Leafcount(BiTree T,int num)
{
if(T)
{
if(T->lChild ==NULL &&T->rChlid==NULL)
num++;
Leafcount(T->lChild,num);
Leafcount(T->rChlid,num);


}
return num;
}
//主函数
int main(void)
{
    BiTree T;
    BiTree *p = (BiTree*)malloc(sizeof(BiTree));
    int deepth,num=0 ;
    printf("请输入第一个结点的值,-1表示没有叶结点:\n");
    CreateBiTree(&T);
    printf("先序遍历二叉树:\n");
    TraverseBiTree(T);
    printf("\n");
    printf("中序遍历二叉树:\n");
    InOrderBiTree(T);
    printf("\n");
    printf("后序遍历二叉树:\n");
    PostOrderBiTree(T);
    printf("\n");
    deepth=TreeDeep(T);
    printf("树的深度为:%d",deepth);
    printf("\n");
    Leafcount(T,num);
    printf("树的叶子结点个数为:%d",num);
    printf("\n");
    return 0;
}