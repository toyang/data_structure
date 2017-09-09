#include <iostream>
#include <cstring>


using namespace std;

//
//2017.03.13 A�� 1��
/**
 * ��һC�������ܸ��ݶ�������ݹ�������ͼG�������G���ڽӾ���G��DFS����ȣ��������У���V0��ʼ����
 * ͼ��������ʽΪn i1 j1 i2 j2 ...  im jm -1 -1�����Ƕ�����������100>n>0�������ֵ����ȥ-1����
 * >=0��<n�����У�n��ͼG�Ķ��������G�Ķ���ΪV0��V1�� ... Vn-1����������ik jk(k=1,2, ... m)��ʾ��
 * ͼG�ĴӶ���Vik������Vjk������ߣ�������-1 -1Ϊ���������ǣ�����ʾ����ߡ�
 * ��ע������Ŀ�ִ���ļ���������e1.exe����������˺Ż���debugĿ¼�£������޳ɼ���
 */

#define MAX 100
int n = 0;
int arc[MAX][MAX] = {0};

void printArc(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << arc[i][j] << " ";
        }
        cout << endl;
    }
}

void DFS(int x, int* visited){
    cout << x << " ";
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        if(visited[i] == 0 && arc[x][i] == 1){
            visited[i] = 1;
            DFS(i, visited);
        }else{
            flag = 1;
        }
    }
    if (flag){
        x++;
        if (x < n && visited[x] == 0){
            visited[x] = 1;
            DFS(x, visited);
        }
    }
}

void e1(){
    int n1, n2;
    cout << "����������ͼ��" << endl;
    cin >> n;
    if (n <= 0 || n >= 100){
        cout << "��������" << endl;
        return;
    }
    cin >> n1 >> n2;
    while (n1 != -1 && n2 != -1){
        if(n1 < 0 || n2 < 0 || n1 >= MAX || n2 >= MAX){
            cout << "��������" << endl;
            return;
        }
        arc[n1][n2] = 1;
        cin >> n1 >> n2;
    }
    cout << "G���ڽӾ���Ϊ��" << endl;
    printArc();

    cout << endl;
    cout << "DFS��������Ϊ��" << endl;
    int* visited = new int[n];
    memset(visited, 0, sizeof (int) * n);
    visited[0] = 1;

    DFS(0, visited);
}

//2017.03.13 A�� 2��
/**
 * ��һC�������ܶ������һ��������������1000������-9999Ϊ������ǣ�������ֱ�Ӳ������򣨴�С�������򣩣�
 * ����������ùؼ��ֱȽϴ�����������ʱ���������ڵ������ÿո��������
 * ��ע������Ŀ�ִ���ļ���������e2.exe����������˺Ż���debugĿ¼�£������޳ɼ���
 */
#define MAX_NUM 1000
int arr[MAX_NUM] = {0};

int inertsort(int n){
    int count = 0;
    for (int i = 1; i < n; ++i) {
        if(++count && arr[i - 1] > arr[i]){
            int temp = arr[i];
            int k = i;
            while(++count && k > 0 && arr[k - 1] > temp){
                arr[k] = arr[k - 1];
                k--;
            }
            arr[k] = temp;
        }
    }
    return count;
}

void e2(){
    cout << "������һ�����֣���-9999��β��" << endl;
    int n = 0, i;

    while ((cin >> i) && (i != -9999) && n != MAX_NUM){
        arr[n] = i;
        ++n;
    }
    int count = inertsort(n);

    for (int l = 0; l < n; ++l) {
        cout << arr[l] << " " ;
    }

    cout << endl;
    cout << "�ؼ��ֱȽϴ���Ϊ��" << count << endl;
}


//2017.03.13 B�� 1��
#define MAX_NODE 100

typedef struct Tnode
{
    char data;
    struct Tnode *lchild,*rchild;
} Tnode, * Bitree;

//ǰ������{ABHFDECKG}
//��������{HBDFAEKCG}
char pre[MAX_NODE], mid[MAX_NODE], post[MAX_NODE];

int find_index(char arr[], char to_find){
    int i = 0;
    while(arr[i] != '\0'){
        if (arr[i] == to_find)
            return i;
        ++i;

    }
    return -1;
}

/*
    PreIndex: ǰ�������ַ����������ĵ�һ���ڵ���PreArray[]�е��±�
    InIndex:  ���������ַ����������ĵ�һ���ڵ���InArray[]�е��±�
    subTreeLen: �������ַ������еĳ���
    PreArray�� ������������
    InArray��������������
*/
void PreInCreateTree(Tnode *&T, int PreIndex, int InIndex, int subTreeLen) {
    //subTreeLen < 0 ����Ϊ��
    if (subTreeLen <= 0) {
        T = NULL;
    } else {
        T = new Tnode;
        //�������ڵ�
        T->data = pre[PreIndex];
        //�ҵ��ýڵ������������е�λ��
        int index = find_index(mid, pre[PreIndex]);
        //������������
        int LenF = index - InIndex;
        //����������
        PreInCreateTree(T->lchild, PreIndex + 1, InIndex, LenF);
        //������������(�ܽ�� - ���ڵ� - ���������)
        int LenR = subTreeLen - 1 - LenF;
        //����������
        PreInCreateTree(T->rchild, PreIndex + LenF + 1, index + 1, LenR);
    }
}

//ǰ������{ABHFDECKG}
//��������{HBDFAEKCG}
//��������{HDFBKGCEA}
void mkBinTree(Tnode* &t, int preIndex, int midIndex, int subTreeLen){
    if(subTreeLen <= 0){
        t = NULL;
        return;
    }else{
        t = new Tnode;
        t->data = pre[preIndex];
        int rootIndexInMid = find_index(mid, pre[preIndex]);
        int leftLen = rootIndexInMid - midIndex;

        mkBinTree(t->lchild, preIndex + 1, midIndex, leftLen);
        int rightLen = subTreeLen - 1 - leftLen;
        mkBinTree(t->rchild, preIndex + 1 + leftLen, rootIndexInMid + 1, rightLen);
    }
}

/*
    PostIndex: ���������ַ��������������һ���ڵ���PostArray[]�е��±�
    InIndex:  ���������ַ����������ĵ�һ���ڵ���InArray[]�е��±�
    subTreeLen: �������ַ������еĳ���
    PostArray�� ������������
    InArray��������������
*/
//ǰ������{ABHFDECKG}
//��������{HBDFAEKCG}
//��������{HDFBKGCEA}
void PostInCreateTree(Tnode *&T, int PostIndex, int InIndex, int subTreeLen) {
    //subTreeLen < 0 ����Ϊ��
    if (subTreeLen <= 0) {
        T = NULL;
    } else {
        T = new Tnode;
        //�������ڵ�
        cout << post[PostIndex] << endl;
        T->data = post[PostIndex];
        int index = find_index(mid, post[PostIndex]);
        int LenF = index - InIndex;
        //����������
        //PostInCreateTree(T->lchild,PostIndex - (subTreeLen - 1 - LenF) - 1,InIndex,LenF);
        PostInCreateTree(T->lchild, PostIndex - (subTreeLen - LenF), InIndex, LenF);
        //������������(�ܽ�� - ���ڵ� - ���������)
        int LenR = subTreeLen - 1 - LenF;
        //����������
        PostInCreateTree(T->rchild, PostIndex - 1, index + 1, LenR);
    }
}

//�������
void PreOrder(Tnode* &T){
    if(T != NULL){
        //���ʸ��ڵ�
        printf("%c ",T->data);
        //�������ӽ��
        PreOrder(T->lchild);
        //�������ӽ��
        PreOrder(T->rchild);
    }
}


//�������
void PostOrder(Tnode* &T){
    if(T != NULL){
        //�������ӽ��
        PostOrder(T->lchild);
        //�������ӽ��
        PostOrder(T->rchild);
        //���ʸ��ڵ�
        printf("%c",T->data);
    }
}

void e1B(){
    cout << "��������������" << endl;
    gets(mid);
    cout << "�������������" << endl;
    gets(post);
    //printf("%s\n", pre);
    //printf("%s", mid);

    Tnode* T;
    //mkBinTree(T, 0, 0, strlen(mid));
    PostInCreateTree(T, strlen(post) - 1, 0, strlen(mid));
    PreOrder(T);
}

//////////////////����ϵͳ//////////////////////
struct proc{
    char name[20];
    int id;
};

void ReadFile(){
    cout << "�������ļ���" << endl;
    char filename[20];
    cin >> filename;
    cout << filename << endl;
    FILE* file = fopen(filename,"r");
    if(file == NULL){
        cout << "�ļ���ʧ��" << endl;
        return;
    }
    proc p;
    while(!feof(file)){
        fscanf(file, "%s %d", p.name, &p.id);
    }
    fclose(file);
    cout << p.name << " " << p.id << endl;

}

/////////////���ݽṹ2016.09.13 B�� 1��///////////////

void PreOrder2(Tnode *&node){
    char c;
    cin >> c;
    if (c == '*'){
        node = NULL;
    }else{
        node = new Tnode;
        node->data = c;
        PreOrder2(node->lchild);
        PreOrder2(node->rchild);
    }
}

void InOrder2(Tnode *&node){
    if (node == NULL){
        cout << "*" ;
    }else{
        InOrder2(node->lchild);
        cout << node->data;
        InOrder2(node->rchild);
    }
}

void B2016(){
    Tnode *node;
    cout << "����ǰ������" << endl;
    PreOrder2(node);
    InOrder2(node);
}

//ð������1
void BubbleSort1(int a[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        bool isSwap = false;
        for (j = 1; j < n - i; j++) {
            if (a[j - 1] > a[j]) {
                int temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
                isSwap = true;
            }
        }
        if(!isSwap) break;
    }
}

struct Node{
    int data;
    struct Node *lchild, *rchild;
};

/*������������в�����*/
void insertBST(int key, Node *&root) {
    Node *p = root;
    /*��¼���ҽ���ǰһ�����*/
    Node *prev = NULL;
    /*һֱ������ȥ��ֱ���������������Ľ��λ��*/
    while (p != NULL) {
        prev = p;
        if (key < p->data)
            p = p->lchild;
        else if (key > p->data)
            p = p->rchild;
        else
            return;
    }
    /*prve��Ҫ���Ž��ĸ��ڵ㣬���ݽ��ֵ�ô�С��������Ӧ��λ��*/
    if (root == NULL) {
        root = new Node;
        root->rchild = NULL;
        root->lchild = NULL;
        root->data = key;
    } else if (key < prev->data) {
        Node *left = new Node;
        left->data = key;
        left->lchild = NULL;
        left->rchild = NULL;
        prev->lchild = left;
    } else {
        Node *right = new Node;
        right->data = key;
        right->lchild = NULL;
        right->rchild = NULL;
        prev->rchild = right;
    }
}

//�������
void PreOrder3(Node* &T){
    if(T != NULL){
        //���ʸ��ڵ�
        printf("%d ",T->data);
        //�������ӽ��
        PreOrder3(T->lchild);
        //�������ӽ��
        PreOrder3(T->rchild);
    }
}

void E2014B2(){
    int val;
    //cin >> val;
    Node *node = NULL;
    while (cin >> val && val != -9999){
        cout << val << " ";
        insertBST(val, node);
    }
    cout << endl << "ǰ������Ϊ��" << endl;
    PreOrder3(node);
}

//1 2 3 4 5 6 7 8 9 10 -9999
void matrix_mul(){
    cout << "���������������" << endl;
    int n;
    cin >> n;
    cout << "�����������Ǿ���" << n * (n + 1) / 2 << "����Ч���֣���-9999��β��" << endl;

    int a[1000], val = -9999, index = 0;

    while (cin >> val && val != -9999){
        a[index++] = val;
    }

    a[index] = 0;

    cout << "�����Ǿ���Ϊ��" << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i <= j){
                int k = i * (2 * n - i + 1) / 2 + j - i;
                printf("%3d", a[k]);
            } else {
                int k = n * (n + 1) / 2;
                printf("%3d", a[k]);
            }
        }
        cout << endl;
    }

    cout << "�����������Ǿ���" << n * (n + 1) / 2 << "����Ч���֣���-9999��β��" << endl;

    int b[1000], indexB = 0;
    val = -9999;

    while (cin >> val && val != -9999){
        b[indexB++] = val;
    }

    b[indexB] = 0;

    cout << "�����Ǿ���Ϊ��" << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i >= j){
                int k = i * (i + 1) / 2 + j;
                printf("%3d", b[k]);
            }else{
                int k = n * (n + 1) / 2;
                printf("%3d", b[k]);
            }
        }
        cout << endl;
    }

    int s = 0, m, l, c[1000], indexC = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            s = 0;
            for (int k = 0; k < n; ++k) {
                if(i <= k){
                    m = i * (2 * n - i + 1) / 2 + k -i;
                } else {
                    m = n * (n + 1) / 2;
                }

                if (k >= j){
                    l = k * (k + 1) / 2 + j;
                }else{
                    l = n * (n + 1) / 2;
                }
                s += a[m] * b[l];
            }
            if(s!=0){
                c[indexC++] = s;
            }
        }
    }

    cout << "����˻�" << endl;
    int h = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%6d", c[h++]);
        }
        cout << endl;
    }
}

int main() {
    /*int arr[] = {5,3,4,6,1,10,9,3};
    BubbleSort1(arr, 8);
    for (int i = 0; i < 8; ++i) {
        cout << arr[i] << " ";
    }*/
    //matrix_mul();
    Tnode *node = new Tnode;
    cout << (node->rchild == NULL) << endl;
    return 0;
}