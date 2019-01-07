#include <stdio.h>
void SelectSort(int sort[],int length){
    for (int i = 0; i < length; ++i) {
        int index = i;  //记录点
        for (int j = i + 1; j < length; ++j) {      //从有序序列之后开始
            if(sort[j] < sort[index]){
                index = j;                          //设置记录点为无序序列最小的元素
            }
        }
        if(index == i)
            continue;
        else{
            int temp;                               //设置哨兵
            temp = sort[index];
            sort[index] = sort[i];
            sort[i] = temp;
        }
    }
}
int main(){
    int i,sort[10] = {3,5,1,8,7,2,6,4,9,0};
    SelectSort(sort,10);
    for (i = 0; i < 10; ++i) {
        printf("%d",sort[i]);
    }
    return 0;
}


