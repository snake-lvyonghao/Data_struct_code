//
// Created by kingLower on 2018/10/23.
//
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef int ElementType;        //    定义数据类型,可根据需要进行其他类型定义
//    链表节点的定义
typedef struct ListNode {
    ElementType  Element;        //    数据域，存放数据
    struct ListNode *Next;        //    指向下一个链表节点
}Node, *PNode;

//算法2.10    链表创建函数定义从表头到表尾逆向建立单链表
PNode CreateList(void) {
    int len ;    //    用于定义链表长度
    int val ;    //    用于存放节点数值
    PNode PHead = (PNode)malloc(sizeof(Node));    //    创建分配一个头节点内存空间
//头节点相当于链表的哨兵，不存放数据，指向首节点（第一个节点）
    if (PHead == NULL)    //    判断是否分配成功
    {
        printf("空间分配失败 \n");
        exit(-1);
    }

    PNode PTail = PHead;    //    链表的末尾节点，初始指向头节点
    PTail->Next = NULL;    //    最后一个节点指针置为空
    printf("请输入节点个数：");
    scanf("%d", &len);        //    输入节点个数
    for (int i = 0; i < len; i++) {

        PNode pNew = (PNode)malloc(sizeof(Node));    //    分配一个新节点
        if (pNew == NULL) {
            printf("分配新节点失败\n");
            exit(-1);
        }
        printf("请输入第 %d 个节点的数据：", i + 1);
        scanf("%d", &val);    //    输入链表节点的数据

        pNew->Element = val;    //    把数据赋值给节点数据域
        PTail->Next = pNew;    //    末尾节点指针指向下一个新节点
        pNew->Next = NULL;        //    新节点指针指向为空
        PTail = pNew;    //    将新节点复制给末尾节点
    }
    printf("创建链表成功\n");
    return PHead;    //    返回头节点
}

//打印链表
void TraverseList(PNode List) {
    PNode P = List->Next;    //    首节点赋值给临时节点P
    printf("遍历链表的值为：");
    if (P == NULL)
        printf("链表为空");
    while (P != NULL)        //当临时节点P不为尾节点时，输出当前节点值
    {
        printf("%d ", P->Element);
        P = P->Next;
    }
    printf("\n");
}

//算法2.8 单链表实现插入
void ListInsert(PNode L, int i,int e) {
    int j = 0;
    PNode p = L;    //    定义节点p指向头节点
    //    寻找i节点的前驱结点
    while (p &&j < i - 1)
    {
        p = p->Next;
        ++j;
    }
    PNode s = (PNode)malloc(sizeof(Node));    //    分配一个临时节点用来存储要插入的数据
    if (s == NULL)
    {
        printf("内存分配失败！");
        exit(-1);
    }
    //    插入节点
    s->Element = e;
    s->Next = p->Next;
    p->Next = s;
}

//算法2.9 删除结点
void ListDelet(PNode L,int i){
    int j = 0;
    PNode p = L;
    while(p != NULL&& j < i - 1){
        p = p->Next;
        ++j;
    }
    PNode q = p->Next; //定义q为要删除的结点
    p->Next = q->Next;
    free(q);        //回收内存
    q = NULL;       //回收野指针
}

//算法2.11 合并链表La，Lb 到La
void MergeList_L(PNode La,PNode Lb){
    while(La->Next != NULL){    //链表La，Lb合并到 La
        La = La->Next;
    }
    La->Next = Lb->Next;        //链表La末尾指针指向头结点指针所指向位置，就是Lb的第一个节点
    free(Lb);       //回收内存
    Lb = NULL;      //回收野指针
}
// 双向链表
typedef struct DuNode {
    ElementType  Element;        //    数据域，存放数据
    struct DuNode *Next;        //    指向下一个链表节点
    struct DuNode *prior;        //    指向下一个链表节点
}DNode, *DuNode;

//创建双向链表
DuNode CreativeDuList(){
    int len ;    //    用于定义链表长度
    int val ;    //    用于存放节点数值
    DuNode DHead = (DuNode)malloc(sizeof(DNode));    //    创建分配一个头节点内存空间
//头节点相当于链表的哨兵，不存放数据，指向首节点（第一个节点）
    DHead->prior = NULL;    //头节点前驱为Null
    if (DHead == NULL)    //    判断是否分配成功
    {
        printf("空间分配失败 \n");
        exit(-1);
    }
    DuNode DTail = DHead;    //    链表的末尾节点，初始指向头节点
    DTail->Next = NULL;    //    最后一个节点next指针置为空
    DTail->prior = NULL;    //      最后一个节点prior指针为空
    printf("请输入节点个数：");
    scanf("%d", &len);        //    输入节点个数
    for (int i = 0; i < len; i++) {

        DuNode dNew = (DuNode)malloc(sizeof(DNode));    //    分配一个新节点
        if (dNew == NULL) {
            printf("分配新节点失败\n");
            exit(-1);
        }
        printf("请输入第 %d 个节点的数据：", i + 1);
        scanf("%d", &val);    //    输入链表节点的数据

        dNew->Element = val;    //    把数据赋值给节点数据域
        DTail->Next = dNew;    //    末尾节点指针指向下一个新节点
        dNew->Next = NULL;        //    新节点next指针指向为空
        dNew->prior = DTail;        //新节点prior指针指向尾结点
        DTail = dNew;    //    将新节点复制给末尾节点
    }
    printf("创建链表成功\n");
    return DHead;    //    返回头节点
}
//  遍历双向链表
void TraverseDlist(DuNode List) {
    DuNode P = List->Next;    //    首节点赋值给临时节点P
    printf("遍历链表的值为：");
    if (P == NULL)
        printf("链表为空");
    while (P != NULL)        //当临时节点P不为尾节点时，输出当前节点值
    {
        printf("%d ", P->Element);
        P = P->Next;
    }
    printf("\n");
}

//算法 2.18 双向链表插入元素
void ListDinsert(DuNode L, int i,int e){
    int j = 0;
    DuNode p = L;   //定义结点p指向头节点
    while(j < i && p != NULL){        //找到插入节点的后继
        p = p->Next;
        j++;
    }
    DuNode s = (DuNode)malloc(sizeof(DNode));       //分配一块内存给新节点
    s->Element = e;     //赋值给新节点
    s->prior = p->prior;    //新节点的prior指向第i位置的prior
    p->prior->Next = s; //第i位置prior的next指针指向新节点
    s->Next = p;    //新节点next指向第i节点
    p->prior = s;   //第i节prior指向新节点
}
//算法2.19 双向链表删除元素
void ListDdelet(DuNode L,int i){
    int j = 0;
    DuNode p = L;
    while(p != NULL&& j < i - 1){
        p = p->Next;
        ++j;
    }
    p->Next->prior = p->prior;  //后一节点的prior为被删除节点的prior
    p->prior->Next = p->Next;   //前一节点的next为被删除节点的next
    free(p);        //回收内存
    p = NULL;       //回收野指针
}
//    主函数
int main() {
//    PNode List = CreateList();    //创建一个指针，使其指向新创建的链表的头指针
//    ListInsert(List,3,5);   //在第1个位置前加入结点值为5
//    TraverseList(List);     //打印链表
//    PNode List2 = CreateList();    //创建一个指针，使其指向新创建的链表的头指针
//    MergeList_L(List,List2);
//    TraverseList(List);     //打印链表
//    ListDelet(List,3); //删除结点
//    TraverseList(List);     //打印链表
    DuNode DList = CreativeDuList(); //创建双向链表
    ListDinsert(DList,2,5);
    TraverseDlist(DList);   //打印双向链表
    ListDdelet(DList,3);
    TraverseDlist(DList);   //打印双向链表
    return 0;
}