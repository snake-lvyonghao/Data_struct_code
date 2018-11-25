#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a) ((((a) >= 'a') && ((a) <= 'z')) || (((a) >= 'A') && ((a) <= 'Z')))      //a - A,z - Z
//邻接矩阵
typedef struct _graph
{
    char vexs[MAX];             //顶点集合
    int vexnum;                 //顶点数
    int edgnum;                 //边数
    int matrix[MAX][MAX];       //邻接矩阵
}Graph,*PGraph;


//返回ch 在 matrix矩阵的位置
static int get_postition(Graph g, char ch)
{
    int i;
    for(i = 0; i < g.vexnum; i++){
        if(g.vexs[i] == ch)
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

//创建图
Graph* create_graph(){
    char c1,c2;
    int v,e;    //顶点与边
    int i,p1,p2;
    Graph* pG;

    //输入定点数和边数
    printf("输入顶点数");
    scanf("%d",&v);
    printf("输入边数");
    scanf("%d",&e);
    if(v < 1 || e < 1 || (e > (v * (v - 1)))){      //符合要求的变数和顶点数
        printf("input error\n");
        return NULL;
    }

    if((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
        return NULL;

    memset(pG,0, sizeof(Graph));

    //初始化顶点数和边数
    pG->vexnum = v;
    pG->edgnum = e;
    //初始化顶点
    for(i = 0;i < pG->vexnum; i++){
        printf("vertex(%d): ",i + 1);
        pG->vexs[i] = read_char();
    }

    //初始化边
    for(i = 0; i < pG->edgnum; i++){
        //读取边的起始位置和结束顶点
        printf("edge(%d):",i + 1);
        c1 = read_char();
        c2 = read_char();

        p1 = get_postition(*pG,c1);
        p2 = get_postition(*pG,c2);
        if(p1 == -1 || p2 == -1){
            printf("input error\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;
    }
    return pG;
}

//返回顶点V的第一个邻接顶点的索引，失败返回-1
static  int first_vertex(Graph G,int v){
    if(v < 0 || v > (G.vexnum - 1))
        return -1;
    for(int i = 0; i < G.vexnum; i++){      //遍历顶点V的边
        if(G.matrix[v][i] == 1)
            return i;
    }
    return  -1;
}

//返回顶点V相对于w的下一个邻接顶点的索引，失败返回-1
static int next_vertix(Graph G,int v,int w){
    if(v < 0 || v > (G.vexnum - 1) || w < 0 || w > (G.vexnum - 1) )
        return -1;
    for(int i = w + 1 ; i < G.vexnum; i++){
        if(G.matrix[v][i] == 1)
            return i;
    }
    return -1;
}

//深度优先搜索遍历图的递归实现
static void DFS(Graph G,int i,int *visited)
{
    int w;

    visited[i] = 1;
    printf("%c ",G.vexs[i]);

    //遍历该顶点的所有邻接结点，没有访问过则继续往下走
    for(w = first_vertex(G,i); w >= 0; w = next_vertix(G,i,w)){         //所有的结点visvited值为1
        if(!visited[w])
            DFS(G,w,visited);
    }
}

//深度优先搜索遍历图
void DFSTraverse(Graph G){
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
void print_graph(Graph G)
{
    int i,j;

    printf("Martix Graph:\n");
    for(i = 0; i < G.vexnum; i++){
        for(j = 0; j < G.vexnum; j++){
            printf("%d",G.matrix[i][j]);
        }
        printf("\n");
    }
}
void BFS(Graph G){
    int head = 0;
    int rear = 0;
    int queue[MAX]; //辅助队列
    int visited[MAX];   //顶点访问标记
    int i,j,k;
    for(i = 0;i < G.vexnum; i++){
        visited[i] = 0;
    }
    printf("BFS: ");
    for(i = 0;i < G.vexnum;i++){
        if(!visited[i]){
            visited[i] = 1;
            printf("%c",G.vexs[i]);
            queue[rear++] = i;  //入队列
        }
        while (head != rear){
            j = queue[head++];  //出队列
            for(k  =first_vertex(G,j); k >= 0;k = next_vertix(G,j,k))   //k是访问的邻接结点
            {
                if(!visited[k]){
                    visited[k] = 1;
                    printf("%c",G.vexs[k]);
                    queue[rear++] = k;
                }
            }
        }
    }
    printf("\n");
}
int main(){
    Graph *pG;
    pG = create_graph();
    print_graph(*pG);
    DFSTraverse(*pG);
    BFS(*pG);
    return 0;
}