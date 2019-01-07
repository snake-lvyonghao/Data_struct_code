#include <stdio.h>
/*
	@param sort 待调整的数组
	@param i 待调整的结点的下标
	@param length 数组的长度
*/
void HeapAdjust(int sort[], int i, int length)
{
    // 调整i位置的结点
    // 先保存当前结点的下标
    int max = i;
    // 当前结点左右孩子结点的下标
    int lchild = i * 2 + 1;
    int rchild = i * 2 + 2;
    if (lchild < length && sort[lchild] > sort[max])
    {
        max = lchild;
    }
    if (rchild < length && sort[rchild] > sort[max])
    {
        max = rchild;
    }
    // 若i处的值比其左右孩子结点的值小，就将其和最大值进行交换
    if (max != i)
    {
        int temp;
        temp = sort[i];
        sort[i] = sort[max];
        sort[max] = temp;
        // 递归
        HeapAdjust(sort, max, length);
    }
}

// 堆排序
void HeapSort(int sort[], int length)
{
    // 初始化堆
    // length / 2 - 1是二叉树中最后一个非叶子结点的序号
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        HeapAdjust(sort, i, length);
    }
    // 交换堆顶元素和最后一个元素
    for (int i = length - 1; i >= 0; i--)
    {
        int temp;
        temp = sort[i];
        sort[i] = sort[0];
        sort[0] = temp;
        HeapAdjust(sort, 0, i);
    }
}

int main(){
    int i,sort[10] = {3,5,1,8,7,2,6,4,9,0};
    HeapSort(sort,10);
    for (i = 0; i < 10; ++i) {
        printf("%d",sort[i]);
    }
    return 0;
}
