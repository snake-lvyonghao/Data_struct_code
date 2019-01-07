#include <stdio.h>
int main(){
    int mid,low,hight,Search[10] = {12,23,28,34,45,66,71,83,86,94},search,postion;
    search = 86;
    low = 0;
    hight = 9;
    while(low <= hight){
        mid = (low + hight) / 2;
        if(Search[mid] == search)
        {
            postion = mid;
            break;
        }
        else if(Search[mid] > search){
            hight = mid - 1;
        } else
            low = mid + 1;
    }
    printf("%d",postion);
    return 0;
}


