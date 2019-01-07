#include <stdio.h>
void QuickSort(int sort[],int start,int end){
    if(start >= end)
        return;
    int i = start;
    int j = end;
    int baseval = sort[start];
    while(i < j){
        //从右往左找比基准数小的数
        while(i < j && sort[j] >= baseval){
            j--;
        }
        if(i < j){      //交换
            sort[i] = sort[j];
            i++;        //减少一次寻找比基准数大的数
        }
        //从左往右找比基准数大的数
        while(i < j && sort[i] < baseval){
            i++;
        }
        if(i < j){      //交换
            sort[j] = sort[i];
            j--;    //减少一次寻找比基准数小的数
        }
    }
    //把基准数放到i的位置
    sort[i] = baseval;
    //递归
    QuickSort(sort,start,i - 1);  //快速排序基准数之前的
    QuickSort(sort,i + 1,end);    //快速排序基准数之后的
}
int main(){
    int i,sort[10] = {3,5,1,8,7,2,6,4,9,0};
    QuickSort(sort,0,9);
    for (i = 0; i < 10; ++i) {
        printf("%d",sort[i]);
    }
    return 0;
}
