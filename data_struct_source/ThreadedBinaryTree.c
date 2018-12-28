#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

//线索存储标志位
//link(0)： 指向左右孩子 | 表示当前结点的左指针(*lchild)或右指针(*rchild) 指向对应的左或右孩子
//Thread(1): 指向前驱后继线索 | 表示当前结点的左指针(*lchild)或右指针(*rchild) 指向对应的前驱或后继元素
typedef enum
{
    Link,                                   //link=0,
    Thread                                  //Thread=1
}PointerTag;

//BinaryThreadTree Node 线索二叉树结点结构
typedef struct BiThrNode
{
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}BiThrNode, *BiThrTree;                     //*BiThrTree: 指向结点的指针为树

//全局变量 始终指向刚刚访问过的结点
BiThrTree pre; //前一个结点/头结点指针

//创建一颗二叉树，约定用户遵照前序遍历方式输入数据
void CreateBiThrTree(BiThrTree *T)         //BiThrTree *T: T为指向树的指针 | 二级指针
{
    ElemType c;
    scanf("%c", &c);
    if (' ' == c)
    {
        *T = NULL;
    }
    else
    {
        *T = (BiThrNode*)malloc(sizeof(BiThrNode));
        (*T)->data = c;
        (*T)->ltag = Link;                    //标志位赋初值，默认所有结点有左右孩子
        (*T)->rtag = Link;
        CreateBiThrTree(&(*T)->lchild);       //递归法为左右子节点赋值
        CreateBiThrTree(&(*T)->rchild);
    }
}

//中序遍历线索化 | 改变无左或右孩子结点的tag标志位，使其指向前驱或后继(形成首尾相连的双向链表)
void InThreading(BiThrTree T)
{
    if (T)                                    //若不为空树
    {
        InThreading(T->lchild);               //递归左孩子线索化

        if (!T->lchild)                       //若该结点没有左孩子，设置Tag为Thread
        {
            T->ltag = Thread;
            T->lchild = pre;
        }
        if (!pre->rchild)                     //*****//
        {
            pre->rtag = Thread;
            pre->rchild = T;
        }

        pre = T;

        InThreading(T->rchild);               //递归右孩子线索化

    }
}

//初始化二叉树T 开始时的头指针pre + 中序遍历线索化 + 收尾:头尾相连
//参数 *p： 指向树的头指针
//参数  T : 要操作的二叉树
void InOrderThreading(BiThrTree *p, BiThrTree T)
{
    //*p = (BiThrTree)malloc(sizeof(BiThrTree));
    *p = (BiThrNode *)malloc(sizeof(BiThrTree));   //头指针分配内存

    (*p)->ltag = Link;                         //结点指针操作结点：赋值
    (*p)->rtag = Thread;
    (*p)->rchild = *p;                         //头指针右侧初始化指向自己
    if (!T)
    {
        (*p)->lchild = *p;                     //空二叉树，指向自己
    }
    else
    {
        (*p)->lchild = T;                      //头指针左侧 指向要操作的对象
        pre = *p;                              //初始化头指针pre

        InThreading(T);                        //中序遍历线索化 后pre 变成最后一个结点T

        pre->rchild = *p;                      //最后一个结点 指向 头指针
        pre->rtag = Thread;
        (*p)->rchild = pre;                    //头指针 指向 最后一个结点
    }
}

//打印输出
void myvisit(char c)
{
    printf("%c", c);
}
//中序遍历二叉树，迭代输出
//参数 T : 头指针
void InOrderTraverse(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;                             //从头指针位置迭代输出
    while (p != T)                             //若为结点非空
    {
        while (p->ltag == Link)                //输出最下层左结点数据
        {
            p = p->lchild;
        }
        myvisit(p->data);

        while (p->rtag == Thread && p->rchild != T)  //输出右结点下一个结点
        {
            p = p->rchild;
            myvisit(p->data);
        }
        p = p->rchild;                         //迭代
    }
}
int main()
{
    BiThrTree P, T = NULL;
    CreateBiThrTree(&T);                       //约定用户前序输入二叉树数据
    InOrderThreading(&P, T);                   //线索化二叉树
    printf("中序遍历输出结果为：");
    InOrderTraverse(P);                        //中序遍历二叉树，迭代输出
    printf("\n");
    return 0;
}
