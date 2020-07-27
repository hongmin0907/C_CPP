// AVL Tree는 균형이 갖춰진 Binary Tree
// Complete Binary Tree는 검색에 있어 O(logN)의 시간 복잡도 유지
// AVL Tree는 간단한 구현으로 Complete Binary Tree에 가까운 형태를 유지

// AVL Tree는 균형 인수(Balance Factor)라는 개념을 이용
// 균형 인수 = |왼쪽 자식 높이 - 오른쪽 자식 높이| = 1, 0, -1 인데 이때 값이 (-)2가되면 문제
// 균형 인수가 위 세가지 경우에 해당하지 않는 경우 '회전(Rotation)'을 통해 트리 재구성

/*
AVL Tree는 총 4가지 형식에 의하여 균형이 깨질 수 있다. 균형 인수가 깨지는 노드를 X라고 했을때 4가지 형식은 다음과 같다
	1. LL형식 : X의 왼쪽 자식의 왼쪽에 삽입하는 경우
	2. LR형식 : X의 왼쪽 자식의 오른쪽에 삽입하는 경우
	3. RR형식 : X의 오른쪽 자식의 오른쪽에 삽입하는 경우
	4. RL형식 : X의 오른쪽 자식의 왼쪽에 삽입하는 경우
*/

// AVL Tree의 각 노드는 균형 인수를 계산하기 위한 목적으로 자신의 '높이(height)' 값을 가집니다.



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int getMax(int a, int b){
	if (a > b) return a;
	return b;
}

typedef struct NODE {
	int data;
	int height; // 높이를 지정해야 시간 복잡도를 보장할 수 있음.
	struct NODE* leftChild;
	struct NODE* rightChild;
}Node;

int getHeight(Node* node){
	if (node == NULL) return 0;
	return node->height;
}

// 모든 노드는 회전을 수행한 이후에 높이를 다시 계산
void setHeight(Node* node){
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

int getDifference(Node* node){
	if (node == NULL) return 0;
	//Node* leftChild = node->leftChild;
	//Node* rightChild = node->rightChild;
	int leftheight = getHeight(node->leftChild);
	int rightheight = getHeight(node->rightChild);
	return  leftheight - rightheight;
}

Node* rotateLL(Node* node){
	Node* leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	setHeight(node); // 회전 이후에 높이를 다시 계산
	return leftChild; // leftChild는 이후에 setHeight() 수행
}

Node* rotateRR(Node* node){
	Node* rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	setHeight(node); // 회전 이후에 높이를 다시 계산
	return rightChild; // rightChild는 이후에 setHeight() 수행
}

Node* rotateLR(Node* node){
	Node* leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	setHeight(node); // 회전 이후에 높이를 다시 계산
	return rotateLL(node); // leftChild는 이후에 setHeight() 수행
}

Node* rotateRL(Node* node){
	Node* rightChild = node->rightChild;
	node->rightChild = rotateLL(rightChild);
	setHeight(node); // 회전 이후에 높이를 다시 계산
	return rotateRR(node); // rightChild는 이후에 setHeight() 수행
}

// AVL Tree의 균형 잡기는 각 노드가 '삽입 될 때' 마다 수행되어야 합니다. '삽입' 과정에 소요되는 시간 복잡도는 O(logN)입니다.
// 따라서 각 트리의 균형 잡기는 삽입 시에 거치는 모든 노드에 대하여 수행된다는 점에서 O(1)의 시간 복잡도를 만족해야 합니다

Node* balance(Node* node){
	int difference = getDifference(node);
	if (2 <= difference){
		if (1 <= getDifference(node->leftChild)){
			node = rotateLL(node);
		}
		else {
			node = rotateLR(node);
		}
	}
	else if (difference <= -2){
		if (getDifference(node->rightChild) <= -1){
			node = rotateRR(node);
		}
		else {
			node = rotateRL(node);
		}
	}
	setHeight(node); // 회전 이후에 높이를 다시 계산
	return node;
}

// AVL Tree의 삽입 과정은 일반적인 Binary Search Tree와 흡사합니다. 다만 삽입 시에 거치는 모든 노드에 대하여 균형 잡기를 수행해주어야 한다는 특징이 있습니다.

Node* insertNode(Node* node, int data){
	if (!node){
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftChild = node->rightChild = NULL;
	}
	else if (data < node->data){
		node->leftChild = insertNode(node->leftChild, data);
		node = balance(node);
	}
	else if (node->data < data){
		node->rightChild = insertNode(node->rightChild, data);
		node = balance(node);
	}
	else{
		printf("데이터 중복이 발생했습니다. \n");
	}
	return node;
}

// AVL Tree는 삽입되는 과정을 면밀히 살펴보는 것이 중요하므로, 트리 구조를 적절히 보여 줄 수 있는 방식으로 출력해야 합니다.
// 일반적으로 트리의 너비가 높이보다 크다는 점에서 세로 방향으로 출력하는 함수를 구현할 수 있습니다.

Node* root = NULL;

void display(Node* node, int level){
	if (node != NULL){
		display(node->rightChild, level + 1);
		printf("\n");
		if (node == root){
			printf("Root : ");
		}
		for (int i = 0; i < level && node != root; i++){
			printf("    ");
		}
		printf("%d(%d)", node->data, getHeight(node));
		display(node->leftChild, level + 1);
	}
}

int main(){
	root = insertNode(root, 7);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 6);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 5);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 3);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 1);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 9);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 8);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 12);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 16);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 18);
	display(root, 1); printf("\n");
	system("cls");
	root = insertNode(root, 23);
	root = insertNode(root, 21);
	root = insertNode(root, 14);
	root = insertNode(root, 15);
	root = insertNode(root, 19);
	root = insertNode(root, 20);
	
	display(root, 1); printf("\n");
	printf("종료\n");

	return 0;
}

// 편향 이진 트리(Skewed Binary Tree)의 경우 탐색에 있어 O(N)의 시간 복잡도를 가집니다.
// 따라서 AVL Tree를 이용하면 탐색에 있어서 O(logN)의 시간 복잡도들 유지할 수 있습니다.