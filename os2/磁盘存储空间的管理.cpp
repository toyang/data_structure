/*ʮ�������㷨ȫʵ�֡������壩���̴洢�ռ�Ĺ��� 
������������ �����������Կ����ߡ�05��7��5��

 

�� ���̴洢�ռ�Ĺ��� 
��Ҫ�У� 
λʾͼ ���ڴ��λʾ��� 
���п�� �Ϳɱ��ڴ������ 
���п��� ��Ҫ��UNIX�������ӷ��������ʵ�� 

UNIXϵͳ�ļ�������������㷨˵�� 
UNIXϵͳ�ļ�������������㷨�� 

�ѿ��п�ֳ������飬��ָ��һ���и����п��ָ�뼯��һ�� 
�����ȿɷ�����ң��ֿɼ���Ϊ�޸�ָ����������̵Ĵ����� 
UNIXϵͳ�����ÿ��п�������ӵķ����� 
UNIXϵͳ��ÿ100�����п���Ϊһ�飬ÿһ��ĵ�һ�����п��еǼ���һ����п�Ŀ�źͿ��п����� 
���²���100����ǲ��ֿ��п�Ŀ�ż������Ǽ���һ��ר�ÿ��У��Ǽ����һ���ŵ��Ǹ����п����е�2����Ԫ�0���� 
��ʾ�ÿ���ָ���Ŀ�������һ��Ŀ�ţ����п������˽����� 
ϵͳ��ʼ��ʱ�Ȱ�ר�ÿ����ݶ����ڴ棬���������п�ʱ����ֱ�����ڴ��п��ҵ���Щ��ǿ��еģ�ÿ����һ���ѿ��п������ 
��Ҫ��һ���еĵ�һ�����п�����ȥ֮ǰӦ�ѵǼ��ڸÿ��е���һ��Ŀ�ż��������浽ר�ÿ��С� 
��һ����п鱻����������ٰ�ר�ÿ�����ݶ����ڴ棬ָ����һ��ɹ�����Ŀ��п顣���黹һ��ʱ�� 
ֻҪ�ѹ黹��Ŀ�ŵǼǵ���ǰ�����ҿ��п�����1�������ǰ������100�飬����ڴ��е�����д���黹���ǿ��У� 
�ù黹����Ϊ����ĵ�һ�顣�����ʼ��ʱϵͳ�Ѱ�ר�ÿ�����ڴ�L��Ԫ��ʼ�������У�����ͻ��յ��㷨���£� 
����һ�����п� 
��L��Ԫ���ݣ����п������� 
�����п���1 i ��L�����п����� 
��i��Ԫ�õ�һ���п�ţ� 
�Ѹÿ����������ߣ� 
���п�����1�� 
�����п�����1 ȡ��L��1��Ԫ���ݣ�һ��ĵ�һ���Ż�0���� 
��ֵ��0�޿��п飬�����ߵȴ� 
��������Ѹÿ����ݸ��Ƶ�ר�ÿ飻 
�ÿ����������ߣ� 
��ר�ÿ����ݶ�������L��ʼ������ 
�黹һ�� 
��L��Ԫ�Ŀ��п����� 
�����п���100 ���п�����1�� 
j ��L�����п����� 
�黹�������j��Ԫ�� 
�����п�����100 �������еǼǵ���Ϣд��黹���У� 
�ѹ黹�������L��1��Ԫ�� 
��L��Ԫ�ó�1�� 
���ó������Ӻ󣬷�����մ��̿�ʱ�����ڴ��в��Һ��޸ģ�ֻ����һ����п���������еĴ��̿鹹��һ��ʱ���������̶�д�� 
�ȵ������ӷ�ʽЧ�ʸߡ� 




6��5����������ģ��UNIX�ĳ������ӷ��������ʵ�� 

��Ҫ�����������ļ�����һ�ѿ��п�ĺ��룬Ȼ������UNIX�ĳ������ӷ��Ĺ�����������10���һ�飬 
���ҿ���ʵ������һ������N,Ȼ���N�����п�ռ�ã����ר�ÿ�Ĵ�С�����кš����ר�ÿ�Ŀռ䲻���� 
����һ����������ݿ���ר�ÿ顣�����Ҫ��д�ļ�������Ҫ��ʾ����Ļ�ϡ� 

���������:UNIX�ĳ������ӷ��������ʵ�� 

VC++����ͨ�� 

(C)copyright by Neo 

��ӭ��Ҳ��� ��������Email:sony006@163.com 
*/

#include<stdio.h>
#include<string.h>
#include<iostream.h>

const int MAXGROUP = 10;//������Ĵ�С 
const int MAXJOB = 100;//����һ����ҵ���������Ŀ��� 

//�ṹ�嶨�� 
typedef struct node {
    int quantity;
    int cell[MAXGROUP];
    struct node *next;
} group;

typedef struct node1 {
    char name[20];
    int quantity;
    int cell[MAXJOB];
    struct node1 *next;
} job;

group *head;
int total;

job *jhead;

//��ʼ���麯�� 
group *initial() {
    int i;
    group *p;

    p = new group;

    p->quantity = 0;
    p->next = NULL;

    for (i = 0; i < MAXGROUP; i++) {
        p->cell[i] = -1;
    }

    return p;
}

//��ʼ����ҵ���� 
job *initial_job() {
    int i;
    job *p;

    p = new job;

    strcpy(p->name, "");
    p->quantity = 0;
    p->next = NULL;

    for (i = 0; i < MAXGROUP; i++) {
        p->cell[i] = -1;
    }

    return p;
}

//������п����ļ� 
void readData() {
    FILE *fp;
    char fname[20];
    int temp;
    group *p;

    cout << "�������ʼ���п������ļ���:";

    cin >> fname;

    if ((fp = fopen("5unix.txt", "r")) == NULL) {
        cout << "����,�ļ��򲻿�,�����ļ���:)" << endl;
    } else {
        cout << "==================================================" << endl;
        cout << "����ĳ�ʼ���п��:";
        while (!feof(fp)) {
            fscanf(fp, "%d ", &temp);
            if (head->quantity < MAXGROUP) {
                head->cell[head->quantity] = temp;
                head->quantity++;
            } else {
                p = initial();
                p->next = head;
                head = p;
                p->cell[p->quantity] = temp;
                p->quantity++;
            }
            total++;
//�����ʼ���� 
            cout << temp << " ";
        }

        cout << endl << "�ܿ��п���:" << total << endl;
    }
}

//�鿴ר�ÿ麯�� 
void view() {
    int i;

    cout << endl << "ר�ÿ���������:" << endl;
    cout << "-------------------------------" << endl;
    cout << "���洢�Ŀ��п��:";
    for (i = 0; i < head->quantity; i++) {
        cout << head->cell[i] << " ";
    }
    cout << endl << "ר�ÿ���п���Ϊ:" << head->quantity;
    cout << endl << "�ܿ��п���:" << total << endl;
}


//�����뺯�� 
void bid() {
    char jobname[20];
    int number;
    int i;
    job *p;

    cout << "----------------------------------" << endl;
    cout << "��������רҵ��:";
    cin >> jobname;
    cout << "�����ڴ����:";
    cin >> number;

    if (number > total) {
        cout << "�����ڴ�������ڵ�ǰ���п���,���Ժ�����:)" << endl;
    } else {
        p = initial_job();
        strcpy(p->name, jobname);
        p->next = jhead->next;
        jhead->next = p;
        p->quantity = number;
        cout << "�����뵽�Ŀ��п����:";
        for (i = 0; i < number; i++) {
            if (head->quantity > 1) {
                cout << head->cell[head->quantity - 1] << " ";
                head->quantity--;
                p->cell[i] = head->cell[head->quantity - 1];
            } else {
                cout << head->cell[0] << " ";
                p->cell[i] = head->cell[head->quantity - 1];
                head->quantity--;
                if (head->next != NULL) {
                    head = head->next;
                }
            }
            total--;
        }
    }
    cout << endl;
}

//������ҵ 
void finish() {
    char jobname[20];
    int i;
    job *p, *q;
    group *r;

    cout << "������Ҫ��������ҵ��:";
    cin >> jobname;

    q = jhead;
    p = jhead->next;
    while ((p != NULL) && (strcmp(p->name, jobname))) {
        q = q->next;
        p = p->next;
    }

    if (p == NULL) {
        cout << "Sorry,û�и���ҵ" << endl;
    } else {
        for (i = 0; i < p->quantity; i++) {
            if (head->quantity < MAXGROUP) {
                head->cell[head->quantity] = p->cell[i];
                head->quantity++;
            } else {
                r = initial();
                r->next = head;
                head = r;
                r->cell[r->quantity] = p->cell[i];
                r->quantity++;
            }
        }
        total += p->quantity;

        q->next = p->next;
        delete p;
    }
}

//��ʾ��Ȩ��Ϣ���� 
void version() {
    cout << endl << endl;

    cout << " ��������������������������������������������������" << endl;
    cout << " �������� ��ģ��UNIX�ĳ������ӷ� �� �������� ��" << endl;
    cout << " �ĩ�����������������������������������������������" << endl;
    cout << " ���� ��(c)All Right Reserved Neo������ ��������" << endl;
    cout << " ��������������sony006@163.com���� ����������������" << endl;
    cout << " ������������version 2004 build 1122��������������" << endl;
    cout << " ��������������������������������������������������" << endl;

    cout << endl << endl;
}


void main() {
    int f = 1;
    int chioce;

    version();
    head = initial();
    total = 0;
    jhead = initial_job();

    readData();

    while (f == 1) {
        cout << "====================================================" << endl;
        cout << " ģ��UNIX�ĳ������ӷ� " << endl;
        cout << "====================================================" << endl;
        cout << "1.������п� 2.������ҵ 3.�鿴ר�ÿ� 0.�˳�" << endl;
        cout << "��ѡ��:";
        cin >> chioce;

        switch (chioce) {
            case 1:
                bid();
                break;
            case 2:
                finish();
                break;
            case 3:
                view();
                break;
            case 0:
                f = 0;
                break;
            default:
                cout << "ѡ�����!" << endl;
        }
    }

} 

