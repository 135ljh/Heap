#define _CRT_SECURE_NO_WARNINGS
#include "heap.h"
#include <stdio.h>
#include <corecrt_malloc.h>

int main() {
    RcdType elements[100];
    int n;
    read_sequence(elements, &n);

    int tag = choose_tag();

    // ��ʼ����
    Heap H;
    if (InitHeap(&H, n, tag, tag == 0 ? compare_min : compare_max) != OK) {
        printf("��ʼ����ʧ��\n");
        return ERROR;
    }

    // ������
    MakeHeap(&H, elements, n, n, tag, tag == 0 ? compare_min : compare_max);
    printf("������Ķ����У�\n");
    print_heap(&H);

    // ��ѭ��
    while (true) {
        int choice;
        printf("��ѡ�������\n");
        printf("1. ��ȡ�Ѷ�Ԫ��\n");
        printf("2. ��ȡ�Ѷ�Ԫ��\n");
        printf("3. ����Ԫ��\n");
        printf("4. ɾ��ָ��λ�õ�Ԫ��\n");
        printf("5. �Զѽ�������\n");
        printf("6. �˳�\n");
        printf("����ѡ�");
        if (scanf("%d", &choice) != 1) {
            printf("��Ч�����룬������һ������\n");
            continue;
        }

        switch (choice) {
        case 1: {
            RcdType top = get_top(&H);
            printf("�Ѷ�Ԫ���ǣ�%d\n", top.key);
            break;
        }
        case 2: {
            if (H.n == 0) {
                printf("��Ϊ�գ��޷���ȡ�Ѷ�Ԫ��\n");
                break;
            }
            RcdType top = extract_top(&H);
            printf("�Ѷ�Ԫ��%d��ɾ�����µĶ������ǣ�\n", top.key);
            print_heap(&H);
            break;
        }
        case 3: {
            int key;
            printf("������Ҫ�����Ԫ�أ�");
            if (scanf("%d", &key) != 1) {
                printf("��Ч�����룬������һ������\n");
                continue;
            }
            RcdType record = { key };
            if (insert_heap(&H, record) != OK) {
                printf("��������޷�����Ԫ��\n");
                break;
            }
            printf("�Ѳ���Ԫ��%d���µĶ������ǣ�\n", key);
            print_heap(&H);
            break;
        }
        case 4: {
            int pos;
            printf("������Ҫɾ����λ�ã�");
            if (scanf("%d", &pos) != 1) {
                printf("��Ч�����룬������һ������\n");
                continue;
            }
            if (pos <= 0 || pos > H.n) {
                printf("��Ч��λ�ã�������1��%d֮��\n", H.n);
                break;
            }
            RcdType deleted;
            if (delete_pos(&H, pos, &deleted) != OK) {
                printf("ɾ��ʧ��\n");
                break;
            }
            printf("λ����%d��Ԫ��%d��ɾ�����µĶ������ǣ�\n", pos, deleted.key);
            print_heap(&H);
            break;
        }
        case 5: {
            RcdSqList L;
            L.size = H.size;
            L.length = H.n;
            L.rcd = (RcdType*)malloc((L.size + 1) * sizeof(RcdType));  // 0�ŵ�Ԫ����
            for (int i = 0; i < L.length; i++) {
                L.rcd[i] = H.rcd[i + 1];
            }
            heap_sort(&L);
            printf("�źõ������ǣ�\n");
            print_list(&L);
            free(L.rcd);
            break;
        }
        case 6:
            printf("�˳�����\n");
            goto exit;
        default:
            printf("��Ч��ѡ�������ѡ��\n");
        }
    }

exit:
    destroy_heap(&H);
    return 0;
}