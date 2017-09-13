/*ʮ�������㷨ȫʵ�֡������ģ�����洢��������ҳ����� 
������������ �����������Կ����ߡ�05��7��5��

 

ҳ������㷨��Ҫ�У�FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU��������㷨��OPT�� 

1�� ���룺 
ҳ�����ļ������д洢����һϵ��ҳ��ţ�ҳ�����������ʾ���ÿո���Ϊ�ָ�����������ģ��������ҳ�档 
������һ��ʾ�⣺ 
1 2 3 4 1 2 5 1 2 3 4 5 
2�� ����Ҫ�� 
��������ʱ��������ʾ��������ҳ�����ļ����ļ�������������һ���ļ����󣬳��򽫶�����ļ��е��й����ݡ� 
��ʼ��������������ҳ�򣬳�ʼʱ��Ϊ�ա� 
���ݵڶ��λ����㷨�����ݽ��д��� 
3�� ���Ҫ�� 
ÿ����һ��ҳ�棨����ÿ����һ��ҳ��ţ����ж��Ƿ���ҳ����Ҫ�����������У��ѱ�������ҳ����������Ļ�ϣ� 
��û�У������һ����*���š� 
4�� �ļ���Լ�� 
�ύ��Դ�������֣�sourceXXX.c����sourceXXX.cpp��������������ȷ���� 
�����ļ����֣������û�ָ�� 
���У�XXXΪ�˺š� 
5�� ����˵�������Խ�ʦ������׼����һ���ļ�����ʽΪ*.txt��������Ϊÿ���������ָ��һ��������Ϊ�����ļ� 
������������Ӽ�������ָ���ļ����ļ����������鿴������������ 
6�� �ڶ��λ����㷨����FIFO�㷨�����¼򵥵��޸ģ������滻ʱ���ȼ������ҳ���R�����ʣ�λ�����Ϊ0�� 
��ô��ҳ�������类����ģ����ҽ���û�б����ʣ��������̱��滻�������RλΪ1�������Rλ�����޸�����װ��ʱ�䣬 
ʹ������ձ�װ�����ҳ��һ����Ȼ������������滻������ҳ�档 
��û������ 






ҳ������㷨��Ҫ�У�FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU��������㷨��OPT�� 
�⼸���㷨�ĵ��ȶ��п����ڿ����������� 
������һ���ͣ���һ����Բο��鱾251ҳ��ʵ��ָ���� 
��2001�꿼�⣺ 
Ҫ�� 

1��ʵ�������㷨�� FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU�� 

2��ҳ�����д�ָ�����ı��ļ���TXT�ļ�����ȡ�� 

3������� 

��һ�У�ÿ����̭��ҳ��� 

�ڶ��У���ʾȱҳ���ܴ��� 


���������:FIFO���������ʹ�õ����㷨��LRU�����������õ����㷨��LFU�� �ڶ��λ����㷨 

VC++����ͨ�� 

(C)copyright by Neo 

��ӭ��Ҳ��� ��������Email:sony006@163.com 
*/


#include<stdio.h>
#include<string.h>
#include<iostream.h>

const int MAXSIZE = 1000;//�������ҳ���� 
const int MAXQUEUE = 3;//����ҳ���� 

typedef struct node {
    int loaded;
    int hit;
} page;

page pages[MAXQUEUE]; //����ҳ��� 
int queue[MAXSIZE];
int quantity;

//��ʼ���ṹ���� 
void initial() {
    int i;

    for (i = 0; i < MAXQUEUE; i++) {
        pages[i].loaded = -1;
        pages[i].hit = 0;
    }
    for (i = 0; i < MAXSIZE; i++) {
        queue[i] = -1;
    }

    quantity = 0;
}

//��ʼ��ҳ���� 
void init() {
    int i;

    for (i = 0; i < MAXQUEUE; i++) {
        pages[i].loaded = -1;
        pages[i].hit = 0;
    }
}

//����ҳ���� 
void readData() {
    FILE *fp;
    char fname[20];

    int i;

    cout << "������ҳ�����ļ���:";
    cin >> fname;

    if ((fp = fopen(fname, "r")) == NULL) {
        cout << "����,�ļ��򲻿�,�����ļ���";
    } else {
        while (!feof(fp)) {
            fscanf(fp, "%d ", &queue[quantity]);
            quantity++;
        }
    }

    cout << "�����ҳ����:";
    for (i = 0; i < quantity; i++) {
        cout << queue[i] << " ";
    }
}

//FIFO�����㷨 

void FIFO() {
    int i, j, p, flag;
    int absence = 0;

    p = 0;

    cout << endl << "----------------------------------------------------" << endl;
    cout << "FIFO�����㷨ҳ�������:";
    for (i = 0; i < quantity; i++) {
        flag = 0;
        for (j = 0; j < MAXQUEUE; j++) {
            if (pages[j].loaded == queue[i]) {//������Ҫ�����ҳ�Ƿ��Ѿ�����
                flag = 1;
            }
        }
        if (flag == 0) {//û����
            if (absence >= MAXQUEUE) {//��ʼ����MAXQUEUEҳ���ᷢ����������ʼ��ʱ�ȼ���MAXQUEUEҳ����������ָ��ָ���һҳ
                cout << pages[p].loaded << " ";
            }
            pages[p].loaded = queue[i];
            p = (p + 1) % MAXQUEUE;
            absence++;
        }
    }
    absence -= MAXQUEUE;
    cout << endl << "��ȱҳ��:" << absence << endl;

}


//�������ʹ�õ����㷨��LRU�� 
void LRU() {
    int absence = 0;
    int i, j;
    int flag;


    for (i = 0; i < MAXQUEUE; i++) {
        pages[i].loaded = queue[i];
    }

    cout << endl << "----------------------------------------------------" << endl;
    cout << "�������ʹ�õ����㷨(LRU)ҳ����:";

    for (i = MAXQUEUE; i < quantity; i++) {
        flag = -1;
        for (j = 0; j < MAXQUEUE; j++) {
            if (queue[i] == pages[j].loaded) {
                flag = j;
            }
        }
        //CAUTION pages[0]�Ƕ���ͷ 
        if (flag == -1) {
            //ȱҳ���� 
            cout << pages[0].loaded << " ";
            for (j = 0; j < MAXQUEUE - 1; j++) {
                pages[j] = pages[j + 1];
            }
            pages[MAXQUEUE - 1].loaded = queue[i];
            absence++;
        } else {
            //ҳ�������� 
            pages[quantity] = pages[flag];
            for (j = flag; j < MAXQUEUE - 1; j++) {
                pages[j] = pages[j + 1];
            }
            pages[MAXQUEUE - 1] = pages[quantity];
        }
    }

    cout << endl << "��ȱҳ��:" << absence << endl;
}


//�������õ����㷨(LFU) 
void LFU() {
    int i, j, p;
    int absence = 0;
    int flag;

    for (i = 0; i < MAXQUEUE; i++) {
        pages[i].loaded = queue[i];
    }

    cout << endl << "----------------------------------------------------" << endl;
    cout << "�������õ����㷨(LFU)ҳ����:";

    for (i = MAXQUEUE; i < quantity; i++) {
        flag = -1;
        for (j = 0; j < MAXQUEUE; j++) {
            if (pages[j].loaded == queue[i]) {
                flag = 1;
                pages[j].hit++;
            }
        }
        if (flag == -1) {
			//ȱҳ�ж� 
            p = 0;
            for (j = 0; j < MAXQUEUE; j++) {
                if (pages[j].hit < pages[p].hit) {
                    p = j;
                }
            }
            cout << pages[p].loaded << " ";
            pages[p].loaded = queue[i];
            for (j = 0; j < MAXQUEUE; j++) {
                pages[j].hit = 0;
            }
            absence++;
        }
    }
    cout << endl << "��ȱҳ��:" << absence << endl;
}

//�ڶ��λ����㷨 
void second() {
    int i, j, t;
    int absence = 0;
    int flag, temp;

    for (i = 0; i < MAXQUEUE; i++) {
        pages[i].loaded = queue[i];
    }

    cout << endl << "----------------------------------------------------" << endl;
    cout << "�ڶ��λ����㷨ҳ����:";

    for (i = MAXQUEUE; i < quantity; i++) {
        flag = -1;
        for (j = 0; j < MAXQUEUE; j++) {
            if (pages[j].loaded == queue[i]) {
                flag = 1;
                pages[j].hit = 1;
            }
        }
        if (flag == -1) {
			//ȱҳ���� 
            t = 0;
            while (t == 0) {
                if (pages[0].hit == 0) {
                    cout << pages[0].loaded << " ";
                    for (j = 0; j < MAXQUEUE - 1; j++) {
                        pages[j] = pages[j + 1];
                    }
                    pages[MAXQUEUE - 1].loaded = queue[i];
                    pages[MAXQUEUE - 1].hit = 0;


                    t = 1;
                } else {
                    temp = pages[0].loaded;
                    for (j = 0; j < MAXQUEUE - 1; j++) {
                        pages[j] = pages[j + 1];
                    }
                    pages[MAXQUEUE - 1].loaded = temp;
                    pages[MAXQUEUE - 1].hit = 0;
                }
            }
            absence++;
        }
    }
    cout << endl << "��ȱҳ��:" << absence << endl;
}

//��ʾ��Ȩ��Ϣ���� 
void version() {
    cout << endl << endl;

    cout << " ��������������������������������������������������" << endl;
    cout << " �������� ������洢��������ҳ����ȡ� ���� ���� ��" << endl;
    cout << " �ĩ�����������������������������������������������" << endl;
    cout << " ���� ��(c)All Right Reserved Neo������ ��   ������" << endl;
    cout << " ��������������sony006@163.com���� ����������������" << endl;
    cout << " ������������version 2004 build 1122������ ��������" << endl;
    cout << " ��������������������������������������������������" << endl;

    cout << endl << endl;
}

void main() {
    version();
    initial();

    readData();

    FIFO();
    init();

    LRU();
    init();

    LFU();
    init();

    second();

} 

