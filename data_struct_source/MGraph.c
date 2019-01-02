#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define INF (~(0x1<<31))        //最大值0X7FFFFFFF
#define isLetter(a) ((((a) >= 'a') && ((a) <= 'z')) || (((a) >= 'A') && ((a) <= 'Z')))      //a - A,z - Z
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

//邻接矩阵
typedef struct _graph
{
    char vexs[MAX];             //顶点集合
    int vexnum;                 //顶点数
    int edgnum;                 //边数
    int matrix[MAX][MAX];       //邻接矩阵
}Graph,*PGraph;

//边的结构体
typedef struct _EdgeData
{
    char star;  //边的起点
    char end;   //边的终点
    int weight; //边的权重
}EData;

//返回ch 在 matrix矩阵的位置
static int get_postition(Graph g, char ch) {
    int i;
    for (i = 0; i < g.vexnum; i++) {
        if (g.vexs[i] == ch)
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
    int i,j,p1,p2,weight;
    Graph* pG;

    //输入顶点数和边数
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
    //初始化"边"的权值
    for (int i = 0; i < pG->vexnum; ++i) {
        for (j = 0; j < pG->vexnum; ++j) {
            if(i == j){
                pG->matrix[i][j] = 0;
            } else
                pG->matrix[i][j] = INF;
        }
    }
    //初始化边
    for(i = 0; i < pG->edgnum; i++){
        //读取边的起始位置和结束顶点
        printf("edge(%d):",i + 1);
        c1 = read_char();
        c2 = read_char();
        printf("weight(%d):",i + 1);
        scanf("%d",&weight);

        p1 = get_postition(*pG,c1);
        p2 = get_postition(*pG,c2);
        if(p1 == -1 || p2 == -1){
            printf("input error\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = weight;
        pG->matrix[p2][p1] = weight;
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
    for(i = 0;i < G.vexnum; i++){   //初始化访问数组
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
            for(k  = first_vertex(G,j); k >= 0;k = next_vertix(G,j,k))   //k是访问的邻接结点
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

/*
 *      prim最小生成树
 *
 *      参数说明：
 *              G -- 邻接矩阵图
 *          start -- 从图中第start个元素开始，生成最小树
 *
 */
void prim(Graph G,int start)
{
    int min,i,j,k,m,n,sum;
    int index = 0;          //prim最小生成树索引
    char prims[MAX];        //最小生成树结果
    int weights[MAX];       //顶点间边的权值

    //prim最小生成树中第一个数是图中第start个顶点，因为是从start开始的
    prims[index++] = G.vexs[start];

    //初始化"顶点的权值数组"
    //将每个顶点的权值初始化为第start个顶点到该顶点的权值
    for (int i = 0; i < G.vexnum; ++i) {
        weights[i] = G.matrix[start][i];
    }

    //将start到start设置为0
    weights[start] = 0;

    for (int i = 0; i < G.vexnum; ++i) {
        //由于从start开始，因此不需要在对第start个顶点处理。
        if(start == i){
            continue;
        }

        j = 0;
        k = 0;
        min = INF;
        //在未被加入到最小生成树的顶点中，找出权值最小的顶点
        while(j < G.vexnum){
            //若weights【j】 = 0，意味着第j个顶点已经被排序过（或者说已经加入了最小生成树）
            if (weights[j] != 0 && weights[j] < min){
                min = weights[j];
                k = j;
            }
            j++;
        }

        //经过上面的处理后，在为被加入最小生成树的顶点中，权值最小的定点是第k个顶点
        //将k个顶点加入到最小生成树的结果数组中
        prims[index++] = G.vexs[k];
        //将第k个顶点的权值标记为0，意味着第k个顶点已经排序过了
        weights[k] = 0;
        //当第k个顶点被加入到最小生成树的结果数组中之后，更新其他的顶点权值
        for (int j = 0; j < G.vexnum; ++j) {
            //当第j个结点没有被处理，并且需要实时更新
            if (weights[j] != 0 && G.matrix[k][j] < weights[j])
                weights[j] = G.matrix[k][j];
        }
    }

    //计算最小生成树的权值
    sum = 0;
    for (int i = 1; i < index; ++i) {
        min = INF;
        //获取prims[i]在G中的位置
        n = get_postition(G,prims[i]);
        //在vexs【0.。。i】中，找出到j的权值最小的顶点
        for (int j = 0; j < i; ++j) {
            m = get_postition(G,prims[j]);
            if(G.matrix[m][n] < min)
                min = G.matrix[m][n];
        }
        sum += min;
    }

    //打印最小生成树
    printf("PRIM(%c) = %d: ",G.vexs[start],sum);
    for (int i = 0; i < index; ++i) {
        printf("%c",prims[i]);
    }
    printf("\n");
}

/*
 * 获取图中的边
 */
EData* get_deges(Graph G){
    int i,j;
    int index = 0;
    EData *edges;

    edges = (EData*)malloc(G.vexnum * sizeof(EData));
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = i + 1; j < G.vexnum; ++j) {
            if(G.matrix[i][j] != INF){
                edges[index].star = G.vexs[i];
                edges[index].end = G.vexs[j];
                edges[index].weight = G.matrix[i][j];
                index++;
            }
        }
    }
    return edges;
}

/*
 * 对边按照权值大小进行排序（由小到大）
 */
void sorted_edges(EData* edges, int elen)
{
    int i,j;

    for (int i = 0; i < elen; ++i) {
        for (int j = i + 1; j < elen; ++j) {
            if (edges[i].weight > edges[j].weight){
                //交换"第i条边"和"第j条边"
                EData tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
}
/*
 * 获取i的终点
 */
int get_end(int vends[],int i){
    while(vends[i] != 0){
        i = vends[i];
    }
    return i;
}
/*
 * 克鲁斯卡尔最小生成树
 */
void kruskal(Graph G){
    int i,m,n,p1,p2;
    int lenght;
    int index = 0;          //rets数组的索引
    int vends[MAX] = {0};   //用于保存 “已有最小生成树”中每个顶点在该最小树的终点
    EData rets[MAX];        //对于结果数组保存kruskal最小生成树的1边
    EData *edges;           //图对应的所有边

    //获取图中所有边
    edges = get_deges(G);
    //按照权值从小到大排序
    sorted_edges(edges,G.edgnum);

    for (int i = 0; i < G.edgnum; ++i) {
        p1 = get_postition(G,edges[i].star);        //获取第i条边的起点序号
        p2 = get_postition(G,edges[i].end);       //获取第i条边的终点序号

        m = get_end(vends,p1);                      //获取p1在最小生成树的终点
        n = get_end(vends,p2);                      //获取p2早最小生成树的终点
        //如果m不等于n意味着边i与最小生成树的顶点没有形成环路
        if(m != n){
            vends[m] = n;                           //设置m在最小生成树的终点为n
            rets[index++] = edges[i];               //保存结果
        }
    }
    free(edges);

    //统计并打印克鲁斯卡尔最小生成树的结果
    lenght = 0;
    for (int i = 0; i < index; ++i) {
        lenght += rets[i].weight;
    }
    printf("Kruskal=%d: ",lenght);
    for (int i = 0; i < index; ++i) {
        printf("(%c%c)",rets[i].star,rets[i].end);
        printf("\n");
    }
}
int main(){
    Graph *pG;
    pG = create_graph();
//    print_graph(*pG);

//    BFS(*pG);
    prim(*pG,0);
//    kruskal(*pG);
    return 0;
}