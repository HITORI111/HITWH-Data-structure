#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef int KeyType;
typedef int InfoType;

typedef struct{
    KeyType key;
    InfoType otherinfo;
}RcdType; //记录类型

typedef struct{
    RcdType r[MAXSIZE + 1];
    int length;
}SqList;

int Partition(SqList *L, int low, int high){
    KeyType pivokey;
    pivokey = L->r[low].key; //选择低位元素作为基准
    L->r[0] = L->r[low];
    while(low < high){
        while(low < high && L->r[high].key >= pivokey) --high;
        L->r[low] = L->r[high];
        while(low < high && L->r[low].key <= pivokey) ++low;
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;
}

void quickSort(SqList *L, int low, int high){
    int pivoloc;
    if(low < high){
        pivoloc = Partition(L, low, high);
        quickSort(L, pivoloc + 1, high); // 基准元素不需要再纳入排序，所以需要+1
        quickSort(L, low, pivoloc - 1); // 同理
    }
}