#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef int SElemType;
typedef int Status;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

// 所以在stack结构中，top指针指向的是栈顶元素下一个的空元素

Status InitStack(SqStack *S){
    S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base) exit(0);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S, SElemType e){
    if(S->top - S->base >= S->stacksize){
        S->base = (SElemType*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);
        S->top = S->base + S->stacksize; // 需要更新top指针位置
        S->stacksize += STACKINCREMENT; // 这里指向的是下一个空元素的位置
    }
    *S->top++ = e; // 将新元素入栈（先使用top指针再++）
    return OK;
}

Status Pop (SqStack *S, SElemType *e){
    if(S->top == S->base) return ERROR;
    e = S->top;
    S->top--;
    return OK;
}

int main(){
    printf("run successfully\n");
    int *ptr = (int*)malloc(sizeof(int) * 10);
    int *ptr1 = ptr;
    for(int i = 0;i < 10; i++){
        *ptr = i;
        ptr++;
    }
    printf("%d,%d",*ptr1, *(ptr1 + 10));
    return 0;
}
