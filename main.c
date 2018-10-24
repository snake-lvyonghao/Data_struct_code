#include <malloc.h>
#include <stdio.h>
typedef struct Demo{
    int data;
    struct Demo1 *next;
}Demo1,*DNext;

void InitDemo(Demo1 *D){
    D->data = 5;
}
int main() {
    Demo1 D;
    DNext p = &D;
    D.data = 3;
    InitDemo(p);
    printf("%d",D.data);
    return 0;
}