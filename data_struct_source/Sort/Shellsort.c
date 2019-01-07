#include <stdio.h>
void Shellsort(int sort[],int length){
    int i,k;
    for(k = length/2;k > 0;k /= 2){
        for(i = k;i < length;i++){     //从数组的第增量个元素开始
            if(sort[i] < sort[i - k]){  //组内元素对比，插入排序
                int temp = sort[i];
                int j = i - k;      //j：比较的组内元素
                while (j >= 0 && sort[j] > temp){       //组内排序（直接插入排序）
                    sort[j + k] = sort[j];
                    j -= k;
                }
                sort[j + k] = temp;
            }
        }
    }
}
int main(){
    int i,sort[10] = {3,5,1,8,7,2,6,4,9,0};
    Shellsort(sort,10);
    for (i = 0; i < 10; ++i) {
        printf("%d",sort[i]);
    }
    return 0;
}
