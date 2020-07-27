#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int data;
	int height;
	struct NODE* leftNode;
	struct NODE* rightNode;
}Node;

int getMax(int a, int b){
	if (a > b) return a;
	return b;
}

int getHeight(Node* node){
	if (node == NULL) return 0;
	return node->height;
}

void setHeight(Node* node){
	node->height = getMax(getHeight(node->leftNode), getHeight(node->rightNode)) + 1;
}

/*
void setHeight(Node* node){
	if (node->leftnode->height < node->rightnode->height)
		node->height = node->rightnode->height + 1;
	else
		node->height = node->leftnode->height + 1;
}
*/

int getDifference(Node* node){
	if (node == NULL) return 0;
	int leftlevel = getHeight(node->leftNode);
	int rightlevel = getHeight(node->rightNode);
	return  leftlevel - rightlevel;
}

Node* rotateLL(Node* node){
	Node* temp = node->leftNode;
	node->leftNode = temp->rightNode;
	temp->rightNode = node;
	setHeight(node);
	return temp;
}

Node* rotateRR(Node* node){
	Node* temp = node->rightNode;
	node->rightNode = temp->leftNode;
	temp->leftNode = node;
	setHeight(node);
	return temp;
}

Node* rotateLR(Node* node){
	Node* temp = node->leftNode;
	node->leftNode = rotateRR(temp);
	setHeight(node);
	return rotateLL(node);
}

Node* rotateRL(Node* node){
	Node* temp = node->rightNode;
	node->rightNode = rotateLL(temp);
	setHeight(node);
	return rotateRR(node);
}

Node* balance(Node* node){
	int difference = getDifference(node);
	if (2 <= difference){
		if (1 <= getDifference(node->leftNode)){
			node = rotateLL(node);
		}
		else{
			node = rotateLR(node);
		}
	}
	else if (difference <= -2){
		if (getDifference(node->rightNode) <= -1){
			node = rotateRR(node);
		}
		else{
			node = rotateRL(node);
		}
	}
	setHeight(node);
	return node;
}

Node* insert(Node* node, int data){
	if (!node){
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftNode = node->rightNode = NULL;
	}
	else if (data < node->data){
		node->leftNode = insert(node->leftNode, data);
		node = balance(node);
	}
	else if (node->data < data){
		node->rightNode = insert(node->rightNode, data);
		node = balance(node);
	}

	else{
		printf("같은 데이터가 있습니다.\n");
	}
	return node;
}

Node* root = NULL;

void display(Node* node, int level){
	if (node != NULL){
		display(node->rightNode, level + 1);
		printf("\n");
		if (node == root){
			printf("Root : ");
		}
		for (int i = 0; i < level && node != root; i++){
			printf("    ");
		}
		printf("%d(%d)", node->data, getHeight(node));
		display(node->leftNode, level + 1);
	}
}

int main(){
	root = insert(root, 7);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 6);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 5);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 3);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 1);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 9);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 8);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 12);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 16);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 18);
	display(root, 1); printf("\n");
	system("cls");
	root = insert(root, 23);
	root = insert(root, 21);
	root = insert(root, 14);
	root = insert(root, 15);
	root = insert(root, 19);
	root = insert(root, 20);

	display(root, 1); printf("\n");
	system("pause");

	return 0;
}