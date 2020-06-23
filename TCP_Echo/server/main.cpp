#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

void ShowErrorMessage(string message) {
	cout << "[���� �߻�]: " << message << '\n';
	system("pause");
	exit(1);
}



int main() {
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;

	int serverPort = 9876;
	char received[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	// PF_INET�� AF_INET�� ������ ������ IPv4�� ���ڴٴ� ����, SOCKET_STERAM�� TCP�� ���ڴٴ� ��
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET; // � ü��
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // ���� �ּҷ� ������ ���ڴٴ� �� 
	serverAddress.sin_port = htons(serverPort); // ��Ʈ ��ȣ ����

	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()");
	cout << "[���� ����] bind()\n";

	if (listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");
	cout << "[���� ����] listen()\n";

	int sizeClientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
	cout << "[���� ����] accept()\n";

	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("accept()");

	while (1) {
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "[Ŭ���̾�Ʈ �޽���]: " << received << '\n';
		cout << "[�޽��� ����]: " << received << '\n';
		if (strcmp(received, "[exit]") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "[���� ����]\n";
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
	}

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	system("pause");
	return 0;
}