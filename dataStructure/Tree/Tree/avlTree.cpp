// AVL Tree�� ������ ������ Binary Tree
// Complete Binary Tree�� �˻��� �־� O(logN)�� �ð� ���⵵ ����
// AVL Tree�� ������ �������� Complete Binary Tree�� ����� ���¸� ����

// AVL Tree�� ���� �μ�(Balance Factor)��� ������ �̿�
// ���� �μ� = |���� �ڽ� ���� - ������ �ڽ� ����| = 1, 0, -1 �ε� �̶� ���� (-)2���Ǹ� ����
// ���� �μ��� �� ������ ��쿡 �ش����� �ʴ� ��� 'ȸ��(Rotation)'�� ���� Ʈ�� �籸��

/*
AVL Tree�� �� 4���� ���Ŀ� ���Ͽ� ������ ���� �� �ִ�. ���� �μ��� ������ ��带 X��� ������ 4���� ������ ������ ����
	1. LL���� : X�� ���� �ڽ��� ���ʿ� �����ϴ� ���
	2. LR���� : X�� ���� �ڽ��� �����ʿ� �����ϴ� ���
	3. RR���� : X�� ������ �ڽ��� �����ʿ� �����ϴ� ���
	4. RL���� : X�� ������ �ڽ��� ���ʿ� �����ϴ� ���
*/

// AVL Tree�� �� ���� ���� �μ��� ����ϱ� ���� �������� �ڽ��� '����(height)' ���� �����ϴ�.



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
	int height; // ���̸� �����ؾ� �ð� ���⵵�� ������ �� ����.
	struct NODE* leftChild;
	struct NODE* rightChild;
}Node;

int getHeight(Node* node){
	if (node == NULL) return 0;
	return node->height;
}

// ��� ���� ȸ���� ������ ���Ŀ� ���̸� �ٽ� ���
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
	setHeight(node); // ȸ�� ���Ŀ� ���̸� �ٽ� ���
	return leftChild; // leftChild�� ���Ŀ� setHeight() ����
}

Node* rotateRR(Node* node){
	Node* rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	setHeight(node); // ȸ�� ���Ŀ� ���̸� �ٽ� ���
	return rightChild; // rightChild�� ���Ŀ� setHeight() ����
}

Node* rotateLR(Node* node){
	Node* leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	setHeight(node); // ȸ�� ���Ŀ� ���̸� �ٽ� ���
	return rotateLL(node); // leftChild�� ���Ŀ� setHeight() ����
}

Node* rotateRL(Node* node){
	Node* rightChild = node->rightChild;
	node->rightChild = rotateLL(rightChild);
	setHeight(node); // ȸ�� ���Ŀ� ���̸� �ٽ� ���
	return rotateRR(node); // rightChild�� ���Ŀ� setHeight() ����
}

// AVL Tree�� ���� ���� �� ��尡 '���� �� ��' ���� ����Ǿ�� �մϴ�. '����' ������ �ҿ�Ǵ� �ð� ���⵵�� O(logN)�Դϴ�.
// ���� �� Ʈ���� ���� ���� ���� �ÿ� ��ġ�� ��� ��忡 ���Ͽ� ����ȴٴ� ������ O(1)�� �ð� ���⵵�� �����ؾ� �մϴ�

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
	setHeight(node); // ȸ�� ���Ŀ� ���̸� �ٽ� ���
	return node;
}

// AVL Tree�� ���� ������ �Ϲ����� Binary Search Tree�� ����մϴ�. �ٸ� ���� �ÿ� ��ġ�� ��� ��忡 ���Ͽ� ���� ��⸦ �������־�� �Ѵٴ� Ư¡�� �ֽ��ϴ�.

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
		printf("������ �ߺ��� �߻��߽��ϴ�. \n");
	}
	return node;
}

// AVL Tree�� ���ԵǴ� ������ ����� ���캸�� ���� �߿��ϹǷ�, Ʈ�� ������ ������ ���� �� �� �ִ� ������� ����ؾ� �մϴ�.
// �Ϲ������� Ʈ���� �ʺ� ���̺��� ũ�ٴ� ������ ���� �������� ����ϴ� �Լ��� ������ �� �ֽ��ϴ�.

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
	printf("����\n");

	return 0;
}

// ���� ���� Ʈ��(Skewed Binary Tree)�� ��� Ž���� �־� O(N)�� �ð� ���⵵�� �����ϴ�.
// ���� AVL Tree�� �̿��ϸ� Ž���� �־ O(logN)�� �ð� ���⵵�� ������ �� �ֽ��ϴ�.