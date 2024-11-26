#define _CRT_SECURE_NO_WARNINGS
#include "heap.h"
#include <stdio.h>
#include <corecrt_malloc.h>

int main() {
    RcdType elements[100];
    int n;
    read_sequence(elements, &n);

    int tag = choose_tag();

    // 初始化堆
    Heap H;
    if (InitHeap(&H, n, tag, tag == 0 ? compare_min : compare_max) != OK) {
        printf("初始化堆失败\n");
        return ERROR;
    }

    // 构建堆
    MakeHeap(&H, elements, n, n, tag, tag == 0 ? compare_min : compare_max);
    printf("调整后的堆序列：\n");
    print_heap(&H);

    // 主循环
    while (true) {
        int choice;
        printf("请选择操作：\n");
        printf("1. 获取堆顶元素\n");
        printf("2. 提取堆顶元素\n");
        printf("3. 插入元素\n");
        printf("4. 删除指定位置的元素\n");
        printf("5. 对堆进行排序\n");
        printf("6. 退出\n");
        printf("输入选项：");
        if (scanf("%d", &choice) != 1) {
            printf("无效的输入，请输入一个整数\n");
            continue;
        }

        switch (choice) {
        case 1: {
            RcdType top = get_top(&H);
            printf("堆顶元素是：%d\n", top.key);
            break;
        }
        case 2: {
            if (H.n == 0) {
                printf("堆为空，无法提取堆顶元素\n");
                break;
            }
            RcdType top = extract_top(&H);
            printf("堆顶元素%d已删除，新的堆序列是：\n", top.key);
            print_heap(&H);
            break;
        }
        case 3: {
            int key;
            printf("请输入要插入的元素：");
            if (scanf("%d", &key) != 1) {
                printf("无效的输入，请输入一个整数\n");
                continue;
            }
            RcdType record = { key };
            if (insert_heap(&H, record) != OK) {
                printf("堆溢出，无法插入元素\n");
                break;
            }
            printf("已插入元素%d，新的堆序列是：\n", key);
            print_heap(&H);
            break;
        }
        case 4: {
            int pos;
            printf("请输入要删除的位置：");
            if (scanf("%d", &pos) != 1) {
                printf("无效的输入，请输入一个整数\n");
                continue;
            }
            if (pos <= 0 || pos > H.n) {
                printf("无效的位置，必须在1到%d之间\n", H.n);
                break;
            }
            RcdType deleted;
            if (delete_pos(&H, pos, &deleted) != OK) {
                printf("删除失败\n");
                break;
            }
            printf("位置是%d的元素%d已删除，新的堆序列是：\n", pos, deleted.key);
            print_heap(&H);
            break;
        }
        case 5: {
            RcdSqList L;
            L.size = H.size;
            L.length = H.n;
            L.rcd = (RcdType*)malloc((L.size + 1) * sizeof(RcdType));  // 0号单元闲置
            for (int i = 0; i < L.length; i++) {
                L.rcd[i] = H.rcd[i + 1];
            }
            heap_sort(&L);
            printf("排好的序列是：\n");
            print_list(&L);
            free(L.rcd);
            break;
        }
        case 6:
            printf("退出程序\n");
            goto exit;
        default:
            printf("无效的选项，请重新选择\n");
        }
    }

exit:
    destroy_heap(&H);
    return 0;
}