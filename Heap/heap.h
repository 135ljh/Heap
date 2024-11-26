#pragma once

typedef int KeyType;
typedef struct {
    KeyType key;
} RcdType;

typedef struct {
    RcdType* rcd;  // �ѻ�ַ��0�ŵ�Ԫ����
    int n;         // �ѳ���
    int size;      // ������
    int tag;       // С������󶥶ѵı�־��tag=0ΪС���ѣ�tag=1Ϊ�󶥶�
    int (*prior)(KeyType, KeyType);  // �ȽϺ���ָ��
} Heap;

typedef struct {
    RcdType* rcd;  // ˳����ַ
    int length;    // ˳�����
    int size;      // ˳�������
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







