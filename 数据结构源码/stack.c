//
// Created by kingpower on 2018/10/24.
//

#include<stdio.h>
#include <malloc.h>
typedef int ElementType;        //    定义数据类型,可根据需要进行其他类型定义
#define STACK_INIT_SIZE 100   //      储存空间初始分配
#define STACKINCREMENT 10      //储存空间分配增量
//顺序栈定义
typedef struct SqStack{
    ElementType  *base;
    ElementType  *top;
    int stacksize; //栈目前最大容量
}SqStack;

    //基本操作的算法描述
//构造一个空栈
SqStack InitStack(SqStack S){
    S.base = (ElementType *)malloc(STACK_INIT_SIZE * sizeof(ElementType));
    if(!S.base){                //储存分配失败
        printf("储存分配失败");
        return S;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return S;
}

//插入元素e为新的栈顶元素
SqStack Push(SqStack P,ElementType e){
    SqStack *S = &P;
    if(S->top - S->base >= S->stacksize){  //栈满，追加空间
        S->base = (ElementType *)realloc(S->base,(S->stacksize + STACKINCREMENT) * sizeof(ElementType));
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return P;
}

//删除栈顶元素
SqStack pop(SqStack S){
    if(S.base == S.top){
        printf("只有一个元素");
    }
    S.top--;
    return S;
}

//打印栈
void PrintStackData(SqStack s)
{
    ElementType *p;
    if(s.base==s.top&&s.base!=NULL)
    {
        printf("空栈无法打印");
    }
    else if(s.base==NULL)
    {
        printf("栈不存在!无法打印!");
    }
    else
    {
        p = s.top-1;
        while(p != s.base)
        {
            printf("%d\n",*p);
            p--;
        }
        printf("%d\n",*p);
    }
}

//算法3.1     对于输入的任意一个非负十进制整数，打印与其相等的八进制数
void conversion(){
    int N;  //十进制整数
    SqStack S;
    S = InitStack(S);   //构造空栈
    scanf("%d",&N);
    while(N){
        S = Push(S,N % 8);
        N = N / 8;
    }
    while(S.top != S.base){
        printf("%d",*--S.top);
    }
}
//清空栈
SqStack ClearStack(SqStack S){
    S.top = S.base;
    return S;
}

//算法3.2 行编辑程序 #退格符 @退行符
void LineEdit(){
    //利用字符栈S，从终端接收一行并传送并调用过程的数据区。
    SqStack S;
    char ch;
    InitStack(S);   //构造空栈S
    ch = getchar();
    while(ch != EOF){
        while (ch != EOF && ch != '\n') {
            switch (ch) {
                case '#':
                    S = pop(S);
                    break;
                case '@':
                    ClearStack(S);
                    break;
                default:
                    Push(S, ch);
                    break;
            }
            ch = getchar();
        }
        ClearStack(S);  //重置S为空栈
        if (ch != EOF) ch = getchar();
    }
}
int main(){
    SqStack S;
    S = InitStack(S);
    S = Push(S,1);
    S = Push(S,2);
    S = Push(S,3);
    S = Push(S,4);
    PrintStackData(S);
    conversion(10);
    LineEdit();
    return 0;
}