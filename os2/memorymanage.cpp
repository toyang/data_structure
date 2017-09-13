// memorymanage.cpp : Defines the entry point for the console application.
//

// memoryrelease.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define MAXFREEROW 50

#define MAXROW 20

typedef struct atab {
    int processname;  //表示进程名      applytab
    int len;
    int flag;        //0存在， 111表示空表项  
};

typedef struct tab {
    int add;  // 起始地址在空闲区表标地址，在分配区它表示进程名       freetab
    int len; ///长度
    int flag;        //0 表示未使用， 111表示空表项  
} ftab;


int fadd = 0;
int flen = 0;
tab freetab[MAXFREEROW] = {0};//初始化全部为零
atab applytab[MAXROW] = {0};
int index = 0;//用于记录非空记f录的个数
int aindex = 0;

void inittab()//先全部初始化为未分配
{
    for (int i = 0; i < MAXFREEROW; i++) {
        freetab[i].flag = 111;
    }

    for (int i = 0; i < MAXROW; i++) {
        applytab[i].flag = 111;
    }
}

void ReadData() {
    printf("请输入文件名：\n");
    char filename[256] = {0};
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    while (true) {
        if (fp) {
            while (!feof(fp))   //结束返回00
            {
                fscanf(fp, "%d,%d", &freetab[index].len, &freetab[index].len);
                printf("%d", freetab[index].add);
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

void runbest() {
    int value = 1000;
    int i = -1;//记录最小差值ID
    //printf("%6d",index);
    for (int x = 0; x < index; x++)//  这里-1是因为只最后一个不需要比较
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

        printf("申请内容过大，没有合适的空间,分配失败\n");
    } else {
        applytab[aindex].processname = fadd;
        applytab[aindex].len = flen;
        applytab[aindex].flag = 0;
        aindex++;

        if (freetab[i].len == flen) {//如果空闲内存刚好分配完了，则从空闲表里移除
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
    printf("请输入申请 存的进程名，长度，以逗号隔开\n");
    scanf("%d,%d", &fadd, &flen);
    runbest();//执行最优适配法
}

void showtab() {
    printf("内存空闲区内容\n");
    printf("地址     长度    标志位\n");

    for (int i = 0; i < index; i++)//为方便看可以不显示空表项，题目要求是要显示空表项的
        //for(int i =0 ;i<MAXFREEROW;i++)
    {
        printf("%6d,%6d,%3d\n", freetab[i].add, freetab[i].len, freetab[i].flag);
    }
    printf("内存分配表内容\n");
    printf("进程名    长度    标志位\n");

    //for(int i =0 ;i<MAXROW;i++)//为方便看可以不显示空表项，题目要求是要显示空表项的
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
        printf("请输入操作项： 1 申请内存，2 显示内存空间区， 0 退出程序\n");
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
                printf("输入的是非法值\n");
        }
    }
    return 0;
}

