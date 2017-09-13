// memoryrelease.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAXROW 50

typedef struct tab {
    int add;
    int len;
    int flag;
} mtab;

tab freetab[MAXROW] = {0};//��ʼ��ȫ��Ϊ��

int index = 0;//���ڼ�¼�ǿռ�¼�ĸ���

void inittab()//��ȫ����ʼ��Ϊδ����
{
    for (int i = 0; i < MAXROW; i++) {
        freetab[i].flag = 111;
    }
}

void ReadData() {
    printf("�������ļ�����\n");
    char filename[256] = {0};
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    while (true) {
        if (fp) {
            while (!feof(fp)) {
                fscanf(fp, "%d,%d", &freetab[index].add, &freetab[index].len);
                freetab[index].flag = 0;
                index++;
            }
            break;
        } else {
            printf("�ļ��������������ļ�����\n");
            scanf("%s", filename);
        }
    }
}

void sorttab() {
    tab tb = {0};
    for (int i = 0; i < index - 1; i++) {
        for (int j = i + 1; j < index; j++) {
            if (freetab[i].add > freetab[j].add) {
                memcpy(&tb, &freetab[i], sizeof(tab));
                memcpy(&freetab[i], &freetab[j], sizeof(tab));
                memcpy(&freetab[j], &tb, sizeof(tab));
            }
        }
    }
}

int fadd = 0;
int flen = 0;

void memorymanage() {
    printf("����������ڴ�ĵ�ַ�����ȣ��Զ��Ÿ���\n");

    scanf("%d,%d", &fadd, &flen);
}

void runrelease() {
    int i = 0;
    for (; i < index; i++) {//�黹�������ٿ�����
        if (fadd + flen == freetab[i].add) {
            freetab[i].add = fadd;
            freetab[i].len += flen;
            break;
        } else if (freetab[i].add + freetab[i].len == fadd) {//�黹�������ٿ�����
            freetab[i].len += flen;
            break;
        }
    }

    if (i == index) {
        freetab[index].add = fadd;
        freetab[index].len = flen;
        freetab[index].flag = 0;
    } else                            //����ͷŵ��ڴ���ԭ���������ڣ���Ҫ���һ�£��᲻�ᷢ��������������������
    {
        for (int x = 0; x < index - 1; x++)//  ����-1����Ϊֻ���һ������Ҫ�Ƚ�
        {
            for (int y = x + 1; y < index; y++) {
                if (freetab[x].add + freetab[x].len == freetab[y].add) {
                    freetab[x].len += freetab[y].len;

                    for (int n = y + 1; n < index; n++) {
                        memcpy(&freetab[n - 1], &freetab[n], sizeof(tab));
                    }
                    index--;
                    continue;
                }
                break;
            }
        }
    }
}

void showfreetab() {
    printf("���ݿ���������\n");
    printf("��ַ      ����    ��־λ\n");

    for (int i = 0; i < index; i++)//Ϊ���㿴���Բ���ʾ�ձ����ĿҪ����Ҫ��ʾ�ձ����
        //for(int i =0 ;i<MAXROW;i++)
    {
        printf("%6d,%6d,%3d\n", freetab[i].add, freetab[i].len, freetab[i].flag);
    }

}

int _tmain(int argc, _TCHAR *argv[]) {
    inittab();
    ReadData();
    sorttab();
    showfreetab();
    int type = 0;

    while (true) {
        printf("���������� 1 �ͷ��ڴ棬2��ִ���ͷ��ڴ������3 ��ʾ�ڴ�ռ����� 0 �˳�����\n");

        scanf("%d", &type);

        switch (type) {
            case 0:
                return 0;
            case 1:
                memorymanage();
                break;
            case 2:
                runrelease();
                break;
            case 3:
                showfreetab();
                break;
            default:
                printf("������ǷǷ�ֵ\n");
        }
    }
    return 0;
}

