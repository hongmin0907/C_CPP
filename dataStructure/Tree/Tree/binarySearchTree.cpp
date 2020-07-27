// 이진 탐색 트리
// 완전 이진 탐색 트리인 경우 O(logN)의 시간 복잡도를 가짐
// 이진 탐색 트리의 성능을 최대로 끌어내기 위해서는 이진 탐색 트리가 완전 이진 트리에 가까워 질 수 있도록 설계해야 한다.



#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node *leftChild;
	struct _node *rightChild;
}Node;

Node* insertNode(Node* root, int data){
	if (root == NULL){
		root = (Node*)malloc(sizeof(Node));
		root->leftChild = root->rightChild = NULL;
		root->data = data;
		return root;
	}
	else{
		if (root->data > data){
			root->leftChild = insertNode(root->leftChild, data);
		}
		else{
			root->rightChild = insertNode(root->rightChild, data);
		}
	}
	
	return root;
}

Node* searchNode(Node* root, int data){
	if (root == NULL) return NULL;

	if (root->data == data) return root;
	else if (root->data > data) return searchNode(root->leftChild, data);
	else return searchNode(root->rightChild, data);

}

Node* findMinNode(Node* root){
	Node* node = root;
	while (node->leftChild != NULL){
		node = node->leftChild;
	}
	return node;
}

Node* deleteNode(Node* root, int data) {
	Node* node = NULL;
	
	if (root == NULL) return NULL;
	
	if (root->data > data) root->leftChild = deleteNode(root->leftChild, data);
	else if (root->data < data) root->rightChild = deleteNode(root->rightChild, data);
	else{
		if (root->leftChild != NULL && root->rightChild != NULL){
			node = findMinNode(root->rightChild);
			root->data = node->data;
			root->rightChild = deleteNode(root->rightChild, node->data);
		}
		else{
			node = (root->leftChild != NULL) ? root->leftChild : root->rightChild;
			free(root);
			return node;
		}
	}

	return root;
}	

void preorder(Node* root){
	if (root == NULL) return;
	
	printf("%d ", root->data);
	preorder(root->leftChild);
	preorder(root->rightChild);
}

int main(){
	Node* root = NULL;
	root = insertNode(root, 30);
	root = insertNode(root, 17);
	root = insertNode(root, 48);
	root = insertNode(root, 5);
	root = insertNode(root, 23);
	root = insertNode(root, 37);
	root = insertNode(root, 50);
	root = deleteNode(root, 30);

	preorder(root);
	printf("pause");

	return 0;
}