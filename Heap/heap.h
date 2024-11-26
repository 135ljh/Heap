#pragma once

typedef int KeyType;
typedef struct {
    KeyType key;
} RcdType;

typedef struct {
    RcdType* rcd;  // 堆基址，0号单元闲置
    int n;         // 堆长度
    int size;      // 堆容量
    int tag;       // 小顶堆与大顶堆的标志：tag=0为小顶堆，tag=1为大顶堆
    int (*prior)(KeyType, KeyType);  // 比较函数指针
} Heap;

typedef struct {
    RcdType* rcd;  // 顺序表基址
    int length;    // 顺序表长度
    int size;      // 顺序表容量
} RcdSqList;

typedef enum { OK, ERROR, OVERFLOW, UNDERFLOW } Status;

int compare_min(KeyType a, KeyType b);
int compare_max(KeyType a, KeyType b);

Status InitHeap(Heap* H, int size, int tag, int (*prior)(KeyType, KeyType));
void MakeHeap(Heap* H, RcdType* E, int n, int size, int tag, int (*prior)(KeyType, KeyType));
void destroy_heap(Heap* heap);
Status insert_heap(Heap* heap, RcdType record);
RcdType get_top(Heap* heap);
RcdType extract_top(Heap* heap);
int delete_pos(Heap* heap, int pos, RcdType* e);
int swap_heap_elem(Heap* heap, int i, int j);
void shift_down(Heap* heap, int pos);
void shift_up(Heap* heap, int pos);
void heap_sort(RcdSqList *L);

void print_heap(Heap* H);

void print_list(RcdSqList* L);

void read_sequence(RcdType* elements, int* n);

int choose_tag();







