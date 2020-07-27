 //������ �� ����ġ �׷���, ���� ���


/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a[1001][1001];
int n, m;

int main(void){
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		a[x][y] = 1;
		a[y][x] = 1;
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			printf("%d", a[i][j]);
		}
		printf("\n");
	}

	return 0;
}
*/


// ���� ����ġ �׷����� ���� ����Ʈ

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int index;
	int distnace;
	struct NODE* next;
}Node;

void addFront(Node *root, int index, int distance){
	Node* node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->distnace = distance;
	node->next = root->next;
	root->next = node;
}

void showAll(Node *root){
	Node* cur = root->next;
	while (cur != NULL) {
		printf("%d(�Ÿ�:%d) ", cur->index, cur->distnace);
		cur = cur->next;
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	Node** a = (Node**)malloc(sizeof(Node*)* (n + 1));

	
	for (int i = 1; i <= n; i++){
		a[i] = (Node*)malloc(sizeof(Node));
		a[i]->next = NULL;
	}

	for (int i = 0; i < m; i++){
		int x, y, distance;
		scanf("%d %d %d", &x, &y, &distance);
		addFront(a[x], y, distance);
	}
	
	for (int i = 1; i <= n; i++){
		printf("���� [%d]", i);
		showAll(a[i]);
		printf("\n");
	}
	
	printf("��");
	return 0;
}