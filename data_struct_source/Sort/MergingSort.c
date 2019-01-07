#include <stdio.h>
// 归并排序
void MergingSort(int sort[], int start, int end, int *temp)
{
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    MergingSort(sort, start, mid, temp);
    MergingSort(sort, mid + 1, end, temp);

    // 合并两个有序序列
    int length = 0; // 表示辅助空间有多少个元素
    int i_start = start;
    int i_end = mid;
    int j_start = mid + 1;
    int j_end = end;
    while (i_start <= i_end && j_start <= j_end)
    {
        if (sort[i_start] < sort[j_start])      //把两个有序序列元素添加到辅助序列中
        {
            temp[length] = sort[i_start];
            length++;
            i_start++;
        }
        else
        {
            temp[length] = sort[j_start];
            length++;
            j_start++;
        }
    }
    //当一个序列为空，直接添加另一数列剩下的元素
    while (i_start <= i_end)
    {
        temp[length] = sort[i_start];
        i_start++;
        length++;
    }
    while (j_start <= j_end)
    {
        temp[length] = sort[j_start];
        length++;
        j_start++;
    }
    // 把辅助空间的数据放到原空间
    for (int i = 0; i < length; i++)
    {
        sort[start + i] = temp[i];
    }
}

int main(){
    int i,sort[10] = {3,5,1,8,7,2,6,4,9,0};
    int temp[10];   //辅助数组
    MergingSort(sort,0,9,temp);
    for (i = 0; i < 10; ++i) {
        printf("%d",sort[i]);
    }
    return 0;
}


