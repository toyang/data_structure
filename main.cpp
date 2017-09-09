#include <iostream>
#include <cstring>


using namespace std;

//
//2017.03.13 A卷 1题
/**
 * 编一C程序，它能根据读入的数据构造有向图G，并输出G的邻接矩阵及G的DFS（深度）遍历序列（从V0开始）。
 * 图的输入形式为n i1 j1 i2 j2 ...  im jm -1 -1，它们都是整数，且100>n>0，其余的值（除去-1）都
 * >=0且<n。其中，n是图G的顶点个数（G的顶点为V0、V1、 ... Vn-1）；整数对ik jk(k=1,2, ... m)表示的
 * 图G的从顶点Vik到顶点Vjk的有向边；整数对-1 -1为输入结束标记，不表示有向边。
 * （注：程序的可执行文件名必须是e1.exe，存于你的账号或其debug目录下，否则无成绩）
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
    cout << "请输入有向图：" << endl;
    cin >> n;
    if (n <= 0 || n >= 100){
        cout << "输入有误" << endl;
        return;
    }
    cin >> n1 >> n2;
    while (n1 != -1 && n2 != -1){
        if(n1 < 0 || n2 < 0 || n1 >= MAX || n2 >= MAX){
            cout << "输入有误" << endl;
            return;
        }
        arc[n1][n2] = 1;
        cin >> n1 >> n2;
    }
    cout << "G的邻接矩阵为：" << endl;
    printArc();

    cout << endl;
    cout << "DFS遍历序列为：" << endl;
    int* visited = new int[n];
    memset(visited, 0, sizeof (int) * n);
    visited[0] = 1;

    DFS(0, visited);
}

//2017.03.13 A卷 2题
/**
 * 编一C程序，它能对输入的一串整数（不多于1000个，以-9999为结束标记），进行直接插入排序（从小到大排序），
 * 输出排序结果用关键字比较次数。（输入时，两个相邻的整数用空格隔开。）
 * （注：程序的可执行文件名必须是e2.exe，存于你的账号或其debug目录下，否则无成绩）
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
    cout << "请输入一串数字，以-9999结尾：" << endl;
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
    cout << "关键字比较次数为：" << count << endl;
}


//2017.03.13 B卷 1题
#define MAX_NODE 100

typedef struct Tnode
{
    char data;
    struct Tnode *lchild,*rchild;
} Tnode, * Bitree;

//前序序列{ABHFDECKG}
//中序序列{HBDFAEKCG}
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
    PreIndex: 前序序列字符串中子树的第一个节点在PreArray[]中的下标
    InIndex:  中序序列字符串中子树的第一个节点在InArray[]中的下标
    subTreeLen: 子树的字符串序列的长度
    PreArray： 先序序列数组
    InArray：中序序列数组
*/
void PreInCreateTree(Tnode *&T, int PreIndex, int InIndex, int subTreeLen) {
    //subTreeLen < 0 子树为空
    if (subTreeLen <= 0) {
        T = NULL;
    } else {
        T = new Tnode;
        //创建根节点
        T->data = pre[PreIndex];
        //找到该节点在中序序列中的位置
        int index = find_index(mid, pre[PreIndex]);
        //左子树结点个数
        int LenF = index - InIndex;
        //创建左子树
        PreInCreateTree(T->lchild, PreIndex + 1, InIndex, LenF);
        //右子树结点个数(总结点 - 根节点 - 左子树结点)
        int LenR = subTreeLen - 1 - LenF;
        //创建右子树
        PreInCreateTree(T->rchild, PreIndex + LenF + 1, index + 1, LenR);
    }
}

//前序序列{ABHFDECKG}
//中序序列{HBDFAEKCG}
//后序序列{HDFBKGCEA}
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
    PostIndex: 后序序列字符串中子树的最后一个节点在PostArray[]中的下标
    InIndex:  中序序列字符串中子树的第一个节点在InArray[]中的下标
    subTreeLen: 子树的字符串序列的长度
    PostArray： 后序序列数组
    InArray：中序序列数组
*/
//前序序列{ABHFDECKG}
//中序序列{HBDFAEKCG}
//后序序列{HDFBKGCEA}
void PostInCreateTree(Tnode *&T, int PostIndex, int InIndex, int subTreeLen) {
    //subTreeLen < 0 子树为空
    if (subTreeLen <= 0) {
        T = NULL;
    } else {
        T = new Tnode;
        //创建根节点
        cout << post[PostIndex] << endl;
        T->data = post[PostIndex];
        int index = find_index(mid, post[PostIndex]);
        int LenF = index - InIndex;
        //创建左子树
        //PostInCreateTree(T->lchild,PostIndex - (subTreeLen - 1 - LenF) - 1,InIndex,LenF);
        PostInCreateTree(T->lchild, PostIndex - (subTreeLen - LenF), InIndex, LenF);
        //右子树结点个数(总结点 - 根节点 - 左子树结点)
        int LenR = subTreeLen - 1 - LenF;
        //创建右子树
        PostInCreateTree(T->rchild, PostIndex - 1, index + 1, LenR);
    }
}

//先序遍历
void PreOrder(Tnode* &T){
    if(T != NULL){
        //访问根节点
        printf("%c ",T->data);
        //访问左子结点
        PreOrder(T->lchild);
        //访问右子结点
        PreOrder(T->rchild);
    }
}


//后序遍历
void PostOrder(Tnode* &T){
    if(T != NULL){
        //访问左子结点
        PostOrder(T->lchild);
        //访问右子结点
        PostOrder(T->rchild);
        //访问根节点
        printf("%c",T->data);
    }
}

void e1B(){
    cout << "请输入中序序列" << endl;
    gets(mid);
    cout << "请输入后序序列" << endl;
    gets(post);
    //printf("%s\n", pre);
    //printf("%s", mid);

    Tnode* T;
    //mkBinTree(T, 0, 0, strlen(mid));
    PostInCreateTree(T, strlen(post) - 1, 0, strlen(mid));
    PreOrder(T);
}

//////////////////操作系统//////////////////////
struct proc{
    char name[20];
    int id;
};

void ReadFile(){
    cout << "请输入文件名" << endl;
    char filename[20];
    cin >> filename;
    cout << filename << endl;
    FILE* file = fopen(filename,"r");
    if(file == NULL){
        cout << "文件打开失败" << endl;
        return;
    }
    proc p;
    while(!feof(file)){
        fscanf(file, "%s %d", p.name, &p.id);
    }
    fclose(file);
    cout << p.name << " " << p.id << endl;

}

/////////////数据结构2016.09.13 B卷 1题///////////////

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
    cout << "输入前序序列" << endl;
    PreOrder2(node);
    InOrder2(node);
}

//冒泡排序1
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

/*向二叉排序树中插入结点*/
void insertBST(int key, Node *&root) {
    Node *p = root;
    /*记录查找结点的前一个结点*/
    Node *prev = NULL;
    /*一直查找下去，直到到达满足条件的结点位置*/
    while (p != NULL) {
        prev = p;
        if (key < p->data)
            p = p->lchild;
        else if (key > p->data)
            p = p->rchild;
        else
            return;
    }
    /*prve是要安放结点的父节点，根据结点值得大小，放在相应的位置*/
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

//先序遍历
void PreOrder3(Node* &T){
    if(T != NULL){
        //访问根节点
        printf("%d ",T->data);
        //访问左子结点
        PreOrder3(T->lchild);
        //访问右子结点
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
    cout << endl << "前序序列为：" << endl;
    PreOrder3(node);
}

//1 2 3 4 5 6 7 8 9 10 -9999
void matrix_mul(){
    cout << "请输入矩阵行数：" << endl;
    int n;
    cin >> n;
    cout << "请输入上三角矩阵，" << n * (n + 1) / 2 << "个有效数字，以-9999结尾：" << endl;

    int a[1000], val = -9999, index = 0;

    while (cin >> val && val != -9999){
        a[index++] = val;
    }

    a[index] = 0;

    cout << "上三角矩阵为：" << endl;

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

    cout << "请输入下三角矩阵，" << n * (n + 1) / 2 << "个有效数字，以-9999结尾：" << endl;

    int b[1000], indexB = 0;
    val = -9999;

    while (cin >> val && val != -9999){
        b[indexB++] = val;
    }

    b[indexB] = 0;

    cout << "下三角矩阵为：" << endl;

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

    cout << "矩阵乘积" << endl;
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