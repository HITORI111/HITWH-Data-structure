#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Poly;
struct PolyNode {
    int coef;    // 系数 
    int expon;   // 指数 
    Poly link;
};

void Attach(int c, int e, Poly *L) {
    Poly p = (Poly)malloc(sizeof(struct PolyNode));
    p->coef = c;
    p->expon = e;
    p->link = NULL; // 初始化为 NULL
    (*L)->link = p;
    *L = p;
}

Poly Read() {
    Poly p = (Poly)malloc(sizeof(struct PolyNode));
    p->link = NULL; // 初始化链表头
    Poly L = p;

    int c, e;
    while (scanf("%d %d", &c, &e) == 2) {
        Attach(c, e, &L);
    }
    
    Poly result = p->link;
    free(p);
    return result;
}

Poly QiuDao(Poly p) {
    Poly head = NULL, tail = NULL;

    while (p) {
        if (p->expon != 0) {
            Poly newNode = (Poly)malloc(sizeof(struct PolyNode));
            newNode->coef = p->coef * p->expon;
            newNode->expon = p->expon - 1;
            newNode->link = NULL;
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                tail->link = newNode;
                tail = newNode;
            }
        }
        p = p->link;
    }
    
    return head; // 返回新的链表
}

void PrintPoly(Poly p) {
    if (!p) {
        printf("0 0\n");
        return;
    }

    int flag = 0;
    while (p) {
        if (flag) {
            printf(" ");
        }
        printf("%d %d", p->coef, p->expon);
        flag = 1;
        p = p->link;
    }
    printf("\n"); // 在最后添加换行
}

int main() {
    Poly P = Read();
    Poly Q = QiuDao(P);
    PrintPoly(Q);
    return 0;
}
