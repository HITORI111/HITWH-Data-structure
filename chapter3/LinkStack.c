#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef int SElemType;
typedef int Status;

typedef struct SNode{
    SElemType data;
    struct SNode* next; // 约定链栈的next指针指向栈顶元素
}SNode, *LinkStack;

void InitStack(LinkStack *S){// 传入指针的地址,才能对指针作出修改
    *S = (SNode*)malloc(sizeof(SNode));
    if(!S) exit(OVERFLOW);
    (*S)->next = NULL;
}

Status Push(LinkStack *S, SElemType e){
    SNode* p;
    p = (SNode*)malloc(sizeof(SNode));
    if(!p) return ERROR;
    p->data = e;
    p->next = NULL;
    (*S)->next = p;
}

Status Pop(LinkStack *S, SElemType *e){
    SNode *temp;
    if((*S)->next == NULL) return ERROR; // 栈顶无元素
    temp = (*S)->next; // 指向栈顶结点
    *e = temp->data;
    (*S)->next = temp->next; // 修改头节点next指针的指向
    free(temp);
    return OK;
}