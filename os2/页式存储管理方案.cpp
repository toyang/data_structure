/*ʮ�������㷨ȫʵ�֡���������ҳʽ�洢������ 
������������ �����������Կ����ߡ�05��7��5��

 

ҳʽ�洢������ 

λʾͼ 

2002�������ı�����ѧ�������ϻ����� 

�ڴ汻���ֳ�2048�飨ҳ������32λ�ֳ����ִ��λʾͼ��Ϊ0��λ��ʾ�ÿ���δ���䣬Ϊ1��λ��ʾ�ÿ��ѷ���? 
ʵϰ��飺 

1�����г����ɼ���ʦ�����ļ��������ļ��д����ڴ�Ŀǰ״����λʾͼ�����ݣ�0��1���ļ�����������Ӧ����ʾ�������Ѻã��� 
2���������Ƶĳ���Ӧ�������ݣ��������Ӧ�����ݽṹ�С� 
3����ʾ�Ѻõ��û����棬�ɼ���ʦ�����ڴ����루�ܿ������� 
4�����������λʾͼ״̬��Ϊ�û������ڴ棬������ҳ�� 
5�����λʾͼ��ҳ�� 


�����������Ҫʵ��λʾͼ�㷨,�Ƚϼ� 

VC++����ͨ�� 

(C)copyright by Neo 

��ӭ��Ҳ��� ��������Email:sony006@163.com 
*/

#include<stdio.h>
#include<iostream.h>
#include<string.h>

const int PAGES = 256; //�����ܿ��� 
const int WORD = 32; //�����ֳ� 

const int WORDNUM = PAGES / WORD; //���������� 

typedef struct node {
    char jobname[20];
    int num;
    int nums[PAGES];
    struct node *next;
} jobs;

int table[WORDNUM][WORD];
int freenum = 0;
jobs *head;

//��ʼ������ 
void initial() {
    int i, j;
    jobs *p;

//��ʼ��λʾͼ 
    for (i = 0; i < WORDNUM; i++) {
        for (j = 0; j < WORD; j++) {
            table[i][j] = 0;
        }
    }

//��ʼ����ҵ��ͷ 
    p = new jobs;
    strcpy(p->jobname, "null");
    p->num = 0;
    p->next = NULL;
    head = p;


}

//����λʾͼ��ʼ���� 
void readData() {
    int i, j;
    FILE *fp;
    char fname[20];

    cout << "�������ʼλʾͼ�����ļ���:" << endl;
    cin >> fname;

    if ((fp = fopen(fname, "r")) != NULL) {
        for (i = 0; i < WORDNUM; i++) {
            for (j = 0; j < WORD; j++) {
                fscanf(fp, "%d", &table[i][j]);
                if (table[i][j] == 1)
                    freenum++;
            }
        }
        cout << "��ʼλʾͼ" << endl;
        for (i = 0; i < WORDNUM; i++) {
            for (j = 0; j < WORD; j++) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
        cout << "�ܿ��п���:" << freenum;

    } else {
        cout << "�ļ����ܴ�" << endl;
    }

}

//�¼�����ҵ���� 
void add() {
    char jobname[20];
    int num;
    jobs *p;
    int i, j, k = 0;

    cout << "��������������ҵ��:";
    cin >> jobname;
    cout << "������ҵ����ҳ��:";
    cin >> num;

    if (num <= freenum) {
        freenum -= num;

        p = new jobs;
        strcpy(p->jobname, jobname);
        p->num = num;

        for (k = 0; k < num; k++) {
            i = 0;
            j = 0;
            while (table[i][j] == 1) {
                j = 0;
                while (table[i][j] == 1)j++;
                if (table[i][j] == 1)
                    i++;
            }
            p->nums[k] = i * WORD + j;
            table[i][j] = 1;
        }

        p->next = head->next;
        head->next = p;

    } else {
        cout << "����,��ǰʣ��ҳ��С������ҳ��,���Ժ�����:)" << endl;
    }

}

//�����ҵ���� 
void finish() {
    char jobname[20];

    jobs *p, *q;
    int n, i, j, num, k;

    cout << "��������ɵ���ҵ��:";
    cin >> jobname;

    p = head->next;
    q = head;

    while (p != NULL) {
        if (strcmp(p->jobname, jobname)) {
            q = q->next;
        }
        p = p->next;
    }

    p = q->next;

    num = p->num;
    for (k = 0; k < num; k++) {
        n = p->nums[k];
        i = n / WORD;
        j = n % WORD;
        table[i][j] = 0;
    }

    freenum += num;
    q->next = p->next;
    delete p;

}


//��ʾ��ǰλʾͼ���� 
void view_table() {
    int i, j;
    cout << "��ǰλʾͼ" << endl;
    for (i = 0; i < WORDNUM; i++) {
        for (j = 0; j < WORD; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "�ܿ��п���:" << freenum << endl;
}

//��ʾ����ҳ���� 
void view_pages() {
    jobs *p;
    int i;

    p = head->next;
    if (p == NULL)cout << "��ǰû���û���ҵ" << endl;
    else
        cout << "��ǰ���е��û���ҵҳ�����" << endl;
    while (p != NULL) {
        cout << "��ҵ��:" << p->jobname << " ���ÿ���:" << p->num << endl;
        cout << "����ҵ������������:" << endl;
        for (i = 0; i < p->num; i++) {
            cout << p->nums[i] << " ";
        }
        cout << endl;
        p = p->next;
    }
}

//��ʾ��Ȩ��Ϣ���� 
void version() {
    cout << endl << endl;

    cout << " ��������������������������������������������������" << endl;
    cout << " �������� ��ҳʽ�ڴ����ϵͳģ����� �������� ��" << endl;
    cout << " �ĩ�����������������������������������������������" << endl;
    cout << " ���� ��(c)All Right Reserved Neo������ ��������" << endl;
    cout << " ��������������sony006@163.com���� ����������������" << endl;
    cout << " ������������version 2004 build 1122��������������" << endl;
    cout << " ��������������������������������������������������" << endl;

    cout << endl << endl;
}


void main() {
    int t = 1, chioce;

    version();
    initial();

    readData();

    while (t == 1) {
        cout << endl << "===========================================" << endl;
        cout << " ҳʽ�ڴ����ϵͳģ�����" << endl;
        cout << "===========================================" << endl;
        cout << "1.��������ҵ 2.�����ҵ 3.��ʾ��ǰ�ڴ�λʾͼ 4.��ʾ������ҵҳ�� 0.�˳�" << endl;
        cout << "��ѡ��:";
        cin >> chioce;

        switch (chioce) {
            case 1:
                add();
                break;
            case 2:
                finish();
                break;
            case 3:
                view_table();
                break;
            case 4:
                view_pages();
                break;
            case 0:
                t = 0;
                break;
            default:
                cout << "ѡ�����" << endl;
        }
    }
} 

