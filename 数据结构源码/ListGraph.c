
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a) ((((a) >= 'a') && ((a) <= 'z')) || (((a) >= 'A') && ((a) <= 'Z')))      //a - A,z - Z

//邻接表中表对应的链表顶点
typedef struct _ENode
{
    int ivex;                   //该边所指向的顶点的的位置
    struct _ENode *next_edge;   //指向下一条弧的指针
}ENode,*PENode;

//邻接表中表的顶点
typedef struct _VNode{
    char data;          //顶点信息
    ENode *first_edge;  //指向第一条依附该顶点的的弧
}VNode;

//邻接表
typedef struct _LGraph{
    int vexnum;             //图的顶点数目
    int edgnum;             //图的边的数目
    VNode vexs[MAX];        //
}LGraph;


//返回ch 在 matrix矩阵的位置
static int get_postition(LGraph g, char ch)
{
    int i;
    for(i = 0; i < g.vexnum; i++){
        if(g.vexs[i].data == ch)
            return i;
    }
    return -1;
}

//读入一个字符
static char read_char(){
    char ch;

    do{
        ch = getchar();
    }while(!isLetter(ch));

    return ch;
}

//将node链接到list末尾
static void link_last(ENode *list,ENode *node){
    ENode *p = list;

    while(p->next_edge)
        p = p->next_edge;
    p->next_edge = node;
}


//创建图
LGraph* create_lgraph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    ENode *node1, *node2;
    LGraph* pG;

    // 输入"顶点数"和"边数"
    printf("输入顶点数: ");
    scanf("%d", &v);
    printf("输入边数: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1))))
    {
        printf("input error: invalid parameters!\n");
        return NULL;
    }

    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgnum = e;
    // 初始化"邻接表"的顶点
    for(i=0; i<pG->vexnum; i++)
    {
        printf("vertex(%d): ", i + 1);
        pG->vexs[i].data = read_char();
        pG->vexs[i].first_edge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<pG->edgnum; i++)
    {
        // 读取边的起始顶点和结束顶点
        printf("edge(%d): ", i + 1);
        c1 = read_char();
        c2 = read_char();

        p1 = get_postition(*pG, c1);
        p2 = get_postition(*pG, c2);

        // 初始化node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(pG->vexs[p1].first_edge == NULL)
            pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
        // 初始化node2
        node2 = (ENode*)malloc(sizeof(ENode));
        node2->ivex = p1;
        // 将node2链接到"p2所在链表的末尾"
        if(pG->vexs[p2].first_edge == NULL)
            pG->vexs[p2].first_edge = node2;
        else
            link_last(pG->vexs[p2].first_edge, node2);
    }

    return pG;
}

//深度优先搜索遍历图的递归实现
static void DFS(LGraph G,int i,int *visited)
{
    ENode *node;
    visited[i] = 1;
    printf("%c ",G.vexs[i].data);
    node = G.vexs[i].first_edge;
    //遍历该顶点的所有邻接结点，没有访问过则继续往下走
    while (node != NULL){
        if(!visited[node->ivex])
            DFS(G,node->ivex,visited);
        node = node->next_edge;
    }
}

//深度优先搜索遍历图
void DFSTraverse(LGraph G){
    int i;
    int visited[MAX];       //顶点访问标记

    //初始化所有的顶点都没有被访问
    for(i = 0; i < G.vexnum; i++){
        visited[i] = 0;
    }

    printf("DFS: ");
    for (i = 0; i < G.vexnum; i++){
        if(!visited[i]){
            DFS(G,i,visited);
        }
    }
    printf("\n");
}

//打印矩形队列图
void print_lgraph(LGraph G)
{
    int i,j;
    ENode *node;

    printf("List Graph:\n");
    for(i = 0; i < G.vexnum; i++){
        printf("%d(%c):",i,G.vexs[i].data);
        node = G.vexs[i].first_edge;
        while (node != NULL){
            printf("%d(%c):",node->ivex,G.vexs[node->ivex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}
int main(){
    LGraph *pG;
    pG = create_lgraph();
    print_lgraph(*pG);
    DFSTraverse(*pG);
    return 0;
}