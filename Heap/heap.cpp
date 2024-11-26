#define _CRT_SECURE_NO_WARNINGS
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare_min(KeyType a, KeyType b) { return a <= b; }
int compare_max(KeyType a, KeyType b) { return a >= b; }

Status InitHeap(Heap* H, int size, int tag, int (*prior)(KeyType, KeyType)) {
    H->rcd = (RcdType*)malloc((size + 1) * sizeof(RcdType));
    if (H->rcd == NULL) {
        return OVERFLOW;
    }
    H->n = 0;
    H->size = size;
    H->tag = tag;
    H->prior = prior;
    return OK;
}

void MakeHeap(Heap* H, RcdType* E, int n, int size, int tag, int (*prior)(KeyType, KeyType)) {
    H->rcd = (RcdType*)malloc((size + 1) * sizeof(RcdType));
    if (H->rcd == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    H->n = n;
    H->size = size;
    H->tag = tag;
    H->prior = prior;
    for (int i = 1; i <= n; i++) {
        H->rcd[i] = E[i - 1];
    }
    for (int i = n / 2; i >= 1; i--) {
        shift_down(H, i);
    }
}

void destroy_heap(Heap* heap) {
    free(heap->rcd);
    heap->rcd = NULL;
    heap->n = 0;
    heap->size = 0;
}

Status insert_heap(Heap* heap, RcdType record) {
    if (heap->n >= heap->size) {
       printf("Heap overflow\n");
       return OVERFLOW;
    }
    int i = ++heap->n;
    heap->rcd[i] = record;
    while (i / 2 > 0 && heap->prior(heap->rcd[i].key, heap->rcd[i / 2].key)) {
        swap_heap_elem(heap, i, i / 2);
        i /= 2;
    }
    return OK;
}

RcdType get_top(Heap* heap) {
    if (heap->n == 0) {
        printf("Heap underflow\n");
        exit(EXIT_FAILURE);
    }
    return heap->rcd[1];
}

RcdType extract_top(Heap* heap) {
    if (heap->n == 0) {
        printf("Heap underflow\n");
        exit(EXIT_FAILURE);
    }
    RcdType top = heap->rcd[1];
    heap->rcd[1] = heap->rcd[heap->n--];
    shift_down(heap, 1);
    return top;
}

int delete_pos(Heap* heap, int pos, RcdType* e) {
    if (pos <= 0 || pos > heap->n) {
        printf("Invalid position\n");
        return ERROR;
    }
    *e = heap->rcd[pos];  // ��ȡҪɾ����Ԫ��
    heap->rcd[pos] = heap->rcd[heap->n--];  // �����һ��Ԫ���Ƶ�ɾ��λ��

    // ���µ�����
    shift_down(heap, pos);

    // ���ɾ��λ�ò������һ��Ԫ�أ�����Ҫ���ϵ���
    if (pos < heap->n && heap->prior(heap->rcd[pos].key, heap->rcd[pos / 2].key)) {
        shift_up(heap, pos);
    }

    return OK;
}

int swap_heap_elem(Heap* heap, int i, int j) {
    if (i <= 0 || i > heap->n || j <= 0 || j > heap->n) {
        printf("Invalid position\n");
        return ERROR;
    }
    RcdType temp = heap->rcd[i];
    heap->rcd[i] = heap->rcd[j];
    heap->rcd[j] = temp;
    return OK;
}

void shift_down(Heap *H, int pos) {
    int i = pos;
    while (i <= H->n / 2) {
        int child = 2 * i;
        int right_child = 2 * i + 1;
        if (right_child <= H->n && H->prior(H->rcd[right_child].key, H->rcd[child].key)) {
            child = right_child;
        }
        if (H->prior(H->rcd[i].key, H->rcd[child].key)) {
            return;
        }
        swap_heap_elem(H, i, child);
        i = child;
    }
}

void shift_up(Heap* heap, int pos) {
    int i = pos;
    while (i / 2 > 0 && heap->prior(heap->rcd[i].key, heap->rcd[i / 2].key)) {
        swap_heap_elem(heap, i, i / 2);
        i /= 2;
    }
}


void heap_sort(RcdSqList* L) {
    Heap H;
    InitHeap(&H, L->length, 0, compare_min);
    for (int i = 0; i < L->length; i++) {
        insert_heap(&H, L->rcd[i]);
    }
    for (int i = 0; i < L->length; i++) {
        L->rcd[i] = extract_top(&H);
    }
    destroy_heap(&H);
}

// ��ӡ�ѵ�����
void print_heap(Heap* H) {
    printf("Heap contents: ");
    for (int i = 1; i <= H->n; i++) {
        printf("%d ", H->rcd[i].key);
    }
    printf("\n");
}

// ��ӡ˳��������
void print_list(RcdSqList* L) {
    printf("List contents: ");
    for (int i = 0; i < L->length; i++) {
        printf("%d ", L->rcd[i].key);
    }
    printf("\n");
}

// ��ȡ�û����������
void read_sequence(RcdType* elements, int* n) {
    char input[256];
    printf("������һ�����У��ÿո�ָ�����");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("��ȡ����ʧ��\n");
        exit(EXIT_FAILURE);
    }
    *n = 0;
    char* token = strtok(input, " \n");
    while (token != NULL) {
        elements[*n].key = atoi(token);
        (*n)++;
        token = strtok(NULL, " \n");
    }
}

// �û�ѡ������С���ѻ�󶥶�
int choose_tag() {
    int tag;
    printf("������tagֵ��0ΪС���ѣ�1Ϊ�󶥶ѣ���");
    if (scanf("%d", &tag) != 1 || (tag != 0 && tag != 1)) {
        printf("��Ч�����룬��������0��1\n");
        exit(EXIT_FAILURE);
    }
    return tag;
}
