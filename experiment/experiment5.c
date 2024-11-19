#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 学生记录结构体
typedef struct {
    char id[7];   // 学号，6位
    char name[9]; // 姓名，最多8个字符
    int score;    // 成绩，0-100
} Student;

int C; // 全局变量，用于传递排序列号

// 比较函数
int compare(const void *a, const void *b) {
    Student *student1 = (Student *)a;
    Student *student2 = (Student *)b;

    // 根据排序列进行不同的排序
    if (C == 1) {
        // 按学号排序
        return strcmp(student1->id, student2->id);
    } else if (C == 2) {
        // 按姓名排序，若姓名相同，则按学号排序
        int name_cmp = strcmp(student1->name, student2->name);
        if (name_cmp != 0) {
            return name_cmp;
        } else {
            return strcmp(student1->id, student2->id);
        }
    } else if (C == 3) {
        // 按成绩排序，若成绩相同，则按学号排序
        if (student1->score != student2->score) {
            return student1->score - student2->score;
        } else {
            return strcmp(student1->id, student2->id);
        }
    }
    return 0;
}

// 自定义快速排序函数
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序中的划分函数
int partition(Student arr[], int low, int high) {
    Student pivot = arr[high];  // 选择最后一个元素作为基准
    int i = low - 1;  // i 是较小元素的索引

    for (int j = low; j < high; j++) {
        if (compare(&arr[j], &pivot) <= 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  // 将基准元素移到正确位置
    return i + 1;  // 返回基准元素的索引
}

// 快速排序函数
void quicksort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main() {
    int N;
    scanf("%d %d", &N, &C);
    Student students[N];

    for (int i = 0; i < N; i++) {
        scanf("%s %s %d", students[i].id, students[i].name, &students[i].score);
    }

    quicksort(students, 0, N - 1);

    // 输出排序后的结果
    for (int i = 0; i < N; i++) {
        printf("%s %s %d\n", students[i].id, students[i].name, students[i].score);
    }

    return 0;
}
