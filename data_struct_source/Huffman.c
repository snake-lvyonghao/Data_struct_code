#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef struct{
    unsigned int weight;    //  叶子节点权值
    unsigned int parent;    //  指向双亲的叶子节点
    unsigned int lchild;
    unsigned int rchild;
}Node,*HuffmanTree;

//动态分配数组，储存哈夫曼编码
typedef char *HuffmanCode;

//选择两个parent为0，且weight最小的结点s1和s2的方法实现
//n 为叶子节点总数，s1和s2两个指针参数指向要选取出来的两个权值最小的结点
void selecte(HuffmanTree *huffmanTree,int n,int *s1,int *s2){
    //标记i
    int i = 0;
    //记录最小权值
    int min;
    //遍历全部节点，找出单节点
    for(i = 1;i <= n;i++){
        //如果此结点的父亲没有，那麽把结点好赋值给min，跳出循环
        if((*huffmanTree)[i].parent == 0){
            min = i;
            break;
        }
    }
    //继续遍历全部节点，找出权值最小节点
    for(i = 1; i <= n;i++){
        if((*huffmanTree)[i].parent == 0){
            if((*huffmanTree)[i].weight < (*huffmanTree)[min].weight){
                min = i;
            }
        }
    }
    //找到了最小权值的结点，s1指向
    *s1 = min;
    //遍历全部结点
    for(i = 1;i <= n;i++){
        //找出下一个节点，且没有被s1指向，那麽赋值i给min，跳出循环
        if((*huffmanTree)[i].parent == 0 && i!= (*s1)){
            min = i;
            break;
        }
    }
    //继续遍历全部结点，找到权值最小的那一个
    for(i = 1; i <= n;i++){
        if((*huffmanTree)[i].parent == 0 && i!= (*s1)){
            if((*huffmanTree)[i].weight < (*huffmanTree)[min].weight){
                min = i;
            }
        }
    }
    //s2指针指向第二个权值最小的叶子结点
    *s2 = min;
}

//创建哈夫曼树并求哈夫曼树的编码，w数组存放已知的n个权值
void createHuffmanTree(HuffmanTree *huffmanTree,int w[],int n){
    //m为哈夫曼树总共的节点数，n为叶子结点数
    int m = 2 * n - 1;
    //s1和s2为当前结点里，要选取的最小权值结点
    int s1;
    int s2;
    //标记
    int i;
    //创建哈夫曼树的结点所需要的空间，m + 1,代表其中包含一个头结点
    *huffmanTree = (HuffmanTree)malloc((m + 1) * sizeof(Node));
    //1--n号放叶子节点，初始化叶子结点，初始的时候看做一个个单个结点的二叉树
    for(i = 1;i <= n;i++){
        //其中叶子结点的权值是w【n】数组来保存
        (*huffmanTree)[i].weight = w[i];
        //初始化叶子结点（单个二叉树）的孩子和双亲，单个节点，也就是没有孩子和双亲，==0
        (*huffmanTree)[i].lchild = 0;
        (*huffmanTree)[i].parent = 0;
        (*huffmanTree)[i].rchild = 0;
    }
    //非叶子结点的初始化
    for(int i = n + 1;i <= m;i++){
        (*huffmanTree)[i].weight = 0;
        (*huffmanTree)[i].lchild = 0;
        (*huffmanTree)[i].parent = 0;
        (*huffmanTree)[i].rchild = 0;
    }
    printf("\nHuffmanTree\n");
    //创建非叶子结点，建哈夫曼树
    for(i = n + 1;i <= m; i++){
        //在haffmantree【1】~huffmantree【i - 1】的范围内选择两个parent为0
        //且weight最小的结点，其序号分别为s1，s2
        selecte(huffmanTree,i - 1,&s1,&s2);
        //选出的两个权值最小的叶子结点，组成一个新的二叉树，根为i结点
        (*huffmanTree)[s1].parent = 1;
        (*huffmanTree)[s2].parent = 1;
        (*huffmanTree)[i].lchild = s1;
        (*huffmanTree)[i].rchild = s2;
        //新结点i的权值
        (*huffmanTree)[i].weight = (*huffmanTree)[s1].weight + (*huffmanTree)[s2].weight;
        printf("%d (%d,%d)\n",(*huffmanTree)[i].weight,(*huffmanTree)[s1].weight,(*huffmanTree)[s2].weight);
    }
    printf("\n");
}


//哈夫曼树建立完毕，从n个叶子节点到根，逆向求每个叶子节点对应的哈夫曼编码
void creatHuffmanCode(HuffmanTree *huffmanTree,HuffmanCode *huffmanCode,int n){
    //指示标记
    int i;
    //编码的起始指针
    int start;
    //编码的起始的父节点
    int p;
    //遍历n个叶子结点的指示标记c
    unsigned int c;
    //分配n个编码的头指针
    huffmanCode = (HuffmanCode *)malloc((n + 1) * sizeof(char *));
    //分配求当前编码的工作空间
    char *cd = (char *)malloc(n * sizeof(char));
    //从右向左逐位存放编码，首先存放编码结束符
    cd[n - 1] = '\0';
    //求n个叶子结点对应的哈夫曼编码
    for (i = 1;i <= n;i++){
        //初始化编码起始指针
        start = n - 1;
        //从叶子到根结点求编码
        for (c = i,p =  (*huffmanTree)[i].parent;p != 0; c = p, p = (*huffmanTree[p]).parent) {
            if ((*huffmanTree)[p].lchild == c) {
                //从右到左的顺序编码入数组内
                cd[--start] = '0';  //左分支标0
            } else {
                cd[--start] = '1';  //右分支标1
            }

        }//为第i个编码分配空间
            huffmanCode[i] = (char *)malloc((n - start) * sizeof(char));

            strcpy(huffmanCode[i],&cd[start]);
    }

        free(cd);
        //打印编码序列
        for(i = 1;i <= n;i++){
            printf("Huffmancode of %3d is %s\n",(*huffmanTree)[i].weight,huffmanCode[i]);
        }

    printf("\n");
}
int main(void){
    HuffmanTree HT;
    HuffmanCode HC;
    int *w,i,n,wei,m;

    printf("\nn =");

    scanf("%d",&n);

    w = (int *)malloc((n + 1) * sizeof(int));

    printf("\ninput the %d element's weight: \n",n);

    for (int i = 1; i <= n;i++) {
        printf("%d: ",i);
        fflush(stdin);
        scanf("%d",&wei);
        w[i] = wei;
    }
    createHuffmanTree(&HT,w,n);
    creatHuffmanCode(&HT,&HC,n);

    return 0;
}