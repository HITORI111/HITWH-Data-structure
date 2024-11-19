#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define Mlength 50
#define MAX_WORD_LENGTH 10
#define MAX_FILES 10

typedef struct wordlist {
    char name[MAX_WORD_LENGTH + 1]; // 单词
    int filecnt[MAX_FILES]; // 包含该单词的文件标记，filecnt[i]为1表示该单词存在于第i个文件
} WList;

typedef struct filelist {
    char name[Mlength][MAX_WORD_LENGTH + 1]; // 每个文件最多Mlength个单词
    int wordsum; // 文件的单词数量
} Flist;

Flist file[Mlength];
WList word[Mlength * Mlength]; // 假设最多Mlength * Mlength个单词
int num = 0; // 总单词数量

// 建立单词索引表
void word_split(int N) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < file[i].wordsum; j++) {
            int flag = 0; // 判断是否为新单词
            for (k = 0; k < num; k++) {
                if (strcmp(word[k].name, file[i].name[j]) == 0) {
                    word[k].filecnt[i] = 1; // 标记该单词在文件i中存在
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) { // 新单词，添加到单词表
                strcpy(word[num].name, file[i].name[j]);
                word[num].filecnt[i] = 1;
                num++;
            }
        }
    }
}

// 计算文件相似度
void similarityCheck(int a, int b) {
    int total = 0;
    float repeat = 0;

    for (int i = 0; i < num; i++) {
        if (word[i].filecnt[a] == 1 || word[i].filecnt[b] == 1) total++;
        if (word[i].filecnt[a] == 1 && word[i].filecnt[b] == 1) repeat++;
    }

    printf("%.1f%%\n", (total > 0) ? (repeat / total * 100) : 0.0);
}

int main() {
    int N, M;
    int i, wordcnt, lettercnt;
    char ch;

    // 读取文件数量
    scanf("%d", &N);
    getchar(); // 跳过换行符

    // 读取每个文件的内容
    for (i = 0; i < N; i++) {
        wordcnt = 0;
        lettercnt = 0;

        while ((ch = getchar()) != '#') {
            if (isalpha(ch)) { // 是字母，转为小写并加入当前单词
                ch = tolower(ch);
                if (lettercnt < MAX_WORD_LENGTH) {
                    file[i].name[wordcnt][lettercnt++] = ch;
                }
            } else { // 非字母，结束当前单词
                if (lettercnt >= 3) { // 符合长度要求
                    file[i].name[wordcnt][lettercnt] = '\0';
                    wordcnt++;
                    if (wordcnt >= Mlength) break; // 单词数量达到上限
                }
                lettercnt = 0; // 重置单词字母计数
            }
        }
        file[i].wordsum = wordcnt; // 记录文件的单词总数
        getchar(); // 跳过行尾的换行符
    }

    // 建立单词索引表
    word_split(N);

    // 读取查询数量
    scanf("%d", &M);
    int a[N], b[N];

    // 处理每个查询并输出相似度
    for (i = 0; i < M; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    
    for (i = 0; i < M; i++) {
        similarityCheck(a[i] - 1, b[i] - 1); // 文件编号从1开始，转换为从0开始
    }

    return 0;
}
