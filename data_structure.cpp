// data_structure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstddef>
#include <queue>

#define MAX 100

using namespace std;

int arc[MAX][MAX];
int n;
//6
//0 2 2 4 2 3 3 1 3 5 -1 -1
void DFS(int *visited, int x){
	cout << x << " ";

	visited[x] = 1;
	for(int i = 0; i < n; ++i){
		if(visited[i] == 0 && arc[x][i] == 1){			
			DFS(visited, i);
		}
	}
}

void DFS2(int *visited, int x){
	cout << x << " ";

	for(int i = 0; i < n; ++i){
		if(arc[x][i] == 1 && visited[i] == 0){
			DFS2(visited, i);
		}
	}
}

void bfs(int *visited, int v)
{
    queue<int> Q;
    cout << v << " ";
    visited[v] = true;
    Q.push(v);
    while(!Q.empty())
    {
        int i,j;
        i = Q.front();  //取队首顶点
        Q.pop();
        for(j=0;j<n;j++) //广度遍历
        {
            if(arc[i][j]!=0 && visited[j]==false)
            {
                cout << j << " ";
                visited[j]=true;
                Q.push(j);
            }
        }
    }
}

void bfs2(int *visited, int x){
	cout << x << " ";

	visited[x] = 1;
	queue<int> q;
	q.push(x);

	while(!q.empty()){
		int i = q.front();
		q.pop();
		for(int j = 0; j < n; ++j){
			if(arc[i][j] == 1 && visited[j] == 0){
				visited[j] = 1;
				q.push(j);
				cout << j << " ";
			}
		}
	}
}

void printArc(){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; j++){
			cout << arc[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void preInCreateTree(){
}

void E2017B2(){
	cout << "请输入顶点个数：" << endl;
	cin >> n;

	cout << "请输入整数对，以-1 -1结束：" << endl;

	int i,j;
	while(cin >> i >> j && i != -1 && j != -1){
		arc[i][j] = 1;
	}
	cout << "" << endl;
	printArc();
	int *visited = new int[n];

	memset(visited, 0, sizeof(int) * n);
	cout << endl << "深度遍历序列为：" << endl;
	DFS(visited, 0);
	cout << endl << endl;

	memset(visited, 0, sizeof(int) * n);
	cout << endl << "深度遍历序列2为：" << endl;
	DFS2(visited, 0);
	cout << endl << endl;

	memset(visited, 0, sizeof(int) * n);
	bfs(visited, 0);
	
	cout << "" << endl;
	memset(visited, 0, sizeof(int) * n);
	bfs2(visited, 0);

}

#define MAX 100

struct Node{
    char data;
    Node *lchild, *rchild;
};

char pre[MAX], mid[MAX], post[MAX];

int findIndexInArray(char arr[], char toFind){
    int index = 0;
    while(arr[index] != '\0'){
        if(arr[index] == toFind) return index;
        index++;
    }
    return -1;
}

//前序序列{ABHFDECKG}
//中序序列{HBDFAEKCG}
//后序序列{HDFBKGCEA}
void preInCreateTree(Node *&node, int preIndex, int midIndex, int subLength){
    if(subLength <= 0){
        return;
    }
    node = new Node;
	node->lchild = NULL;
	node->rchild = NULL;
    node->data = pre[preIndex];

    int index = findIndexInArray(mid, pre[preIndex]);
    int lenL = index - midIndex;
    preInCreateTree(node->lchild, preIndex + 1, midIndex, lenL);

    int lenR = subLength - lenL - 1;
    preInCreateTree(node->rchild, preIndex + lenL + 1, index + 1, lenR);

}

void preOrder(Node *&node){
    if(node != NULL){
        cout << node->data;
        preOrder(node->lchild);
        preOrder(node->rchild);
    }
}

void createTree(){
    cout << "请输入前序序列字符串" << endl;
    cin >> pre;
    cout << "请输入中序序列字符串" << endl;
    cin >> mid;

    Node *node = NULL;

    preInCreateTree(node, 0, 0, strlen(pre));
    preOrder(node);

}

int main(int argc, char* argv[])
{
	createTree();
	return 0;
}

