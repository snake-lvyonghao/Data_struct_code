#include <stdio.h>
void InsertSort(int sort[],int length){
    int i,j,temp;
    for(i = 1;i < length; i++){
        for(j = 0;j < i; j++){
            if(sort[j] > sort[i]){
                temp = sort[i];
                sort[i] = sort[j];
                sort[j] = temp;
            }
        }
    }
}
int main(){
    int i,sort[10] = {3,5,1,8,7,2,6,4,9,0};
    InsertSort(sort,10);
    for (i = 0; i < 10; ++i) {
        printf("%d",sort[i]);
    }
    return 0;
}

