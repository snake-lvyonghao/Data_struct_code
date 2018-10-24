//
// Created by kingpower on 2018/10/24.
//
#include <stdio.h>
#include <malloc.h>
typedef int ElementType;        //    定义数据类型,可根据需要进行其他类型定义
typedef struct QNode{
    ElementType data;
    struct QNode *next;
}QNode,*QueuePtr;

//--------单链表队列————队列的链式存储结构-------
typedef struct {
    QueuePtr front;     //队头指针 不存放数据next指向第一个数据
    QueuePtr rear;      //队尾指针 存放最后一个数据next指向NULL
}LinkQueue;

//-------基本操作的函数原型说明------------
//构造一个空队列
LinkQueue InitQueue(LinkQueue Q){
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front){
        printf("储存分配失败");
    }
    Q.front->next = NULL;
    return Q;
}
//消除队列头元素
LinkQueue DeQueue(LinkQueue Q){
    if(Q.front == Q.rear){
        printf("队列为空");
    }
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));   //创建队列指针
    p = Q.front->next;//P指针指向队头指针所指向的   p指向头指针所指的下一个节点
    Q.front->next = p->next;    //队头指针指向P的next      头指针指向下一节点的下一个节点
    if(Q.rear == p)Q.rear = Q.front;    //若元素全部出队后 队尾指针丢失 重新赋值指向有节点
    free(p);
    printf("成功消除队列头元素\n");
    return Q;
}

//插入元素e为Q的新的队尾元素
LinkQueue EnQueue(LinkQueue Q,ElementType e){
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));   //创建新添加元素
    if(!p){
        printf("储存分配失败");
    }
    p->data = e; //把e赋值给新的元素
    p->next = NULL; //新元素的结尾指针为NULL
    Q.rear->next = p;      //把队尾指针的next指向p
    Q.rear = p;         //把P赋值给队尾指针
    printf("成功插入元素\n");
    return Q;
}

//销毁队列
LinkQueue DestroyQueue(LinkQueue Q){
    while(Q.front){ //只要头节点指向节点就进行删除
        Q.rear = Q.front->next; //尾指针指向头指针所指向的
        free(Q.front);  //释放头结点
        Q.front = Q.rear;       //头结点指向尾指针所指向的   就是指向被删除的节点之后的节点
    }
    printf("成功销毁队列\n");
    return Q;
}
int main(){
    LinkQueue Q;
    Q = InitQueue(Q);//创建队列
    Q = EnQueue(Q,6);// 队列插入654
    Q = EnQueue(Q,5);
    Q = EnQueue(Q,4);
    printf("%d\n",Q.rear->data);//打印队尾元素
    Q = DeQueue(Q);     //删除队头元素
    printf("%d\n",Q.front->next->data);     //输出队头元素
    Q = DestroyQueue(Q);        //销毁队列
    printf("%d %d\n",Q.rear->data,Q.front->next->data); //输出队头队尾元素（无法打印）
    return 0;
}
