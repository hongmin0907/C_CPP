/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001 // ����� �����̹Ƿ� 300,000��

typedef struct {
	int cost;
	int node;
} Edge;

void swap(Edge *a, Edge *b) {
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}

typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
} priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	// �� ���Ҹ� ������ ���Ŀ� ��������� ���� �����մϴ�.
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

Edge* pop(priorityQueue *pq) {
	if (pq->count <= 0) return NULL;
	Edge *res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now;
	// �� ���Ҹ� ������ ���Ŀ� ��������� ���� �����մϴ�.
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break; // �� �̻� �������� �ʾƵ� �� �� ����
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
	}
	return res;
}

typedef struct Node {
	Edge *data;
	struct Node *next;
} Node;

Node** adj;
int ans[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = edge;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = edge;
		node->next = target[index];
		target[index] = node;
	}
}

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	adj = (Node**)malloc(sizeof(Node*)* (n + 1));
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		ans[i] = INT_MAX;
	}
	
	priorityQueue *pq;
	pq = (priorityQueue*)malloc(sizeof(priorityQueue));
	pq->count = 0;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		Edge *edge = (Edge*)malloc(sizeof(Edge));
		edge->node = b;
		edge->cost = c;
		addNode(adj, a, edge);
	}

	// ���ͽ�Ʈ�� �˰����� �����մϴ�.
	ans[k] = 0;
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = k; push(pq, start);
	
	while (1) {
		Edge* now = pop(pq);
		if (now == NULL) break;
		int curNode = now->node;
		int curCost = now->cost;
		if (ans[curNode] < curCost) continue;
		Node* cur = adj[curNode];
		while (cur != NULL) {
			Edge* temp = cur->data;
			temp->cost += curCost;
			if (temp->cost < ans[temp->node]) { ans[temp->node] = temp->cost; push(pq, temp); }
			cur = cur->next;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (ans[i] == INT_MAX) printf("INF\n");
		else printf("%d\n", ans[i]);
	}

	system("pause");
}
*/

#define _WINSOCK_DEPRECATED_NOP_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

void ShowErrorMessage(string message){
	cout << "[���� �߻�]:" << message << '\n';
	system("pause");
	exit(1);
}

int main(){
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;

	int serverPort = 9876;
	char received[256];
	string sent;

	//Winsock �ʱ�ȭ 
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");

	// TCP ���� ����
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	// ���ڿ� IP�� ��Ʈ��ũ ����Ʈ ��������
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	// 2����Ʈ ���� ��Ʈ��ũ ����Ʈ ��������
	serverAddress.sin_port = htons(serverPort);

	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()");

	//�ݺ������� ������ �޽����� �����ϰ� ���� �޼����� ���� �޽��ϴ�.
	while (1){
		cout << "[�޼��� ����]: ";
		getline(cin, sent);

		if (sent == "") continue;

		send(clientSocket, sent.c_str(), sent.length(), 0);

		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = '\0';

		if (strcmp(received, "[exit]") == 0){
			cout << "[���� ����]\n";
			break;
		}
		cout << "[���� �޽���]: " << received << '\n';
	}

	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}