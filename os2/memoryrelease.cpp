// memoryrelease.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAXROW 50

typedef struct tab {
    int add;
    int len;
    int flag;
} mtab;

tab freetab[MAXROW] = {0};//初始化全部为零

int index = 0;//用于记录非空记录的个数

void inittab()//先全部初始化为未分配
{
    for (int i = 0; i < MAXROW; i++) {
        freetab[i].flag = 111;
    }
}

void ReadData() {
    printf("请输入文件名：\n");
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
            printf("文件名有误，请输入文件名：\n");
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
    printf("请输入回收内存的地址，长度，以逗号隔开\n");

    scanf("%d,%d", &fadd, &flen);
}

void runrelease() {
    int i = 0;
    for (; i < index; i++) {//归还区有下临空闲区
        if (fadd + flen == freetab[i].add) {
            freetab[i].add = fadd;
            freetab[i].len += flen;
            break;
        } else if (freetab[i].add + freetab[i].len == fadd) {//归还区有上临空闲区
            freetab[i].len += flen;
            break;
        }
    }

    if (i == index) {
        freetab[index].add = fadd;
        freetab[index].len = flen;
        freetab[index].flag = 0;
    } else                            //如果释放的内存与原来的有相邻，需要检查一下，会不会发生与其它空闲区有相邻
    {
        for (int x = 0; x < index - 1; x++)//  这里-1是因为只最后一个不需要比较
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
    printf("内容空闲区内容\n");
    printf("地址      长度    标志位\n");

    for (int i = 0; i < index; i++)//为方便看可以不显示空表项，题目要求是要显示空表项的
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
        printf("请输入操作项： 1 释放内存，2，执行释放内存操作，3 显示内存空间区， 0 退出程序\n");

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
                printf("输入的是非法值\n");
        }
    }
    return 0;
}

