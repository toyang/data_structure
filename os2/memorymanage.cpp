// memorymanage.cpp : Defines the entry point for the console application.
//

// memoryrelease.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define MAXFREEROW 50

#define MAXROW 20

typedef struct atab {
    int processname;  //��ʾ������      applytab
    int len;
    int flag;        //0���ڣ� 111��ʾ�ձ���  
};

typedef struct tab {
    int add;  // ��ʼ��ַ�ڿ���������ַ���ڷ���������ʾ������       freetab
    int len; ///����
    int flag;        //0 ��ʾδʹ�ã� 111��ʾ�ձ���  
} ftab;


int fadd = 0;
int flen = 0;
tab freetab[MAXFREEROW] = {0};//��ʼ��ȫ��Ϊ��
atab applytab[MAXROW] = {0};
int index = 0;//���ڼ�¼�ǿռ�f¼�ĸ���
int aindex = 0;

void inittab()//��ȫ����ʼ��Ϊδ����
{
    for (int i = 0; i < MAXFREEROW; i++) {
        freetab[i].flag = 111;
    }

    for (int i = 0; i < MAXROW; i++) {
        applytab[i].flag = 111;
    }
}

void ReadData() {
    printf("�������ļ�����\n");
    char filename[256] = {0};
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    while (true) {
        if (fp) {
            while (!feof(fp))   //��������00
            {
                fscanf(fp, "%d,%d", &freetab[index].len, &freetab[index].len);
                printf("%d", freetab[index].add);
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

void runbest() {
    int value = 1000;
    int i = -1;//��¼��С��ֵID
    //printf("%6d",index);
    for (int x = 0; x < index; x++)//  ����-1����Ϊֻ���һ������Ҫ�Ƚ�
    {
        printf("%6d", freetab[x].len);
        if (freetab[x].len >= flen) {
            //	printf(freetab[x].len+"fff");
            if (value > freetab[x].len - flen) {
                value = freetab[x].len - flen;
                i = x;
            }
        }
    }
    //printf("%d",i);
    if (i == -1) {

        printf("�������ݹ���û�к��ʵĿռ�,����ʧ��\n");
    } else {
        applytab[aindex].processname = fadd;
        applytab[aindex].len = flen;
        applytab[aindex].flag = 0;
        aindex++;

        if (freetab[i].len == flen) {//��������ڴ�պ÷������ˣ���ӿ��б����Ƴ�
            for (int n = i + 1; n < index; n++) {
                memcpy(&freetab[n - 1], &freetab[n], sizeof(tab));
            }
            index--;
        } else {
            freetab[i].len -= flen;
        }
    }
}

void applymemory() {
    fadd = 0;
    flen = 0;
    printf("���������� ��Ľ����������ȣ��Զ��Ÿ���\n");
    scanf("%d,%d", &fadd, &flen);
    runbest();//ִ���������䷨
}

void showtab() {
    printf("�ڴ����������\n");
    printf("��ַ     ����    ��־λ\n");

    for (int i = 0; i < index; i++)//Ϊ���㿴���Բ���ʾ�ձ����ĿҪ����Ҫ��ʾ�ձ����
        //for(int i =0 ;i<MAXFREEROW;i++)
    {
        printf("%6d,%6d,%3d\n", freetab[i].add, freetab[i].len, freetab[i].flag);
    }
    printf("�ڴ���������\n");
    printf("������    ����    ��־λ\n");

    //for(int i =0 ;i<MAXROW;i++)//Ϊ���㿴���Բ���ʾ�ձ����ĿҪ����Ҫ��ʾ�ձ����
    for (int i = 0; i < aindex; i++) {
        printf("%6d,%6d,%3d\n", applytab[i].processname, applytab[i].len, applytab[i].flag);
    }
}

int _tmain(int argc, _TCHAR *argv[]) {
    inittab();
    ReadData();
    showtab();

    int type = 0;

    while (true) {
        printf("���������� 1 �����ڴ棬2 ��ʾ�ڴ�ռ����� 0 �˳�����\n");
        scanf("%d", &type);
        switch (type) {
            case 0:
                return 0;
            case 1:
                applymemory();
                break;
            case 2:
                showtab();
                break;
            default:
                printf("������ǷǷ�ֵ\n");
        }
    }
    return 0;
}

