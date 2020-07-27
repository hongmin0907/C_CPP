#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10000

void radixSort(int *a, int n){
	int res[MAX], maxValue = 0;
	int exp = 1;
	
	for (int i = 0; i < n; i++){
		if (a[i] > maxValue) maxValue = a[i];
	}

	while (maxValue / exp > 0) { // 1�� �ڸ����� ���
		int bucket[10] = { 0 };
		for (int i = 0; i < n; i++) bucket[a[i] / exp % 10]++; // �ڸ��� �迭 ó��
		for (int i = 1; i < 10; i++) {
			bucket[i] += bucket[i-1]; // ���� ���
			printf("%d ", bucket[i]);
		}
		printf("\n");
		for (int i = n - 1; 0 <= i; i--){ //���� �ڸ��� ������ ������ ����

			res[--bucket[a[i] / exp % 10]] = a[i];
		}
		for (int i = 0; i < n; i++) 
			a[i] = res[i]; // �⺻ �迭 ����
		exp *= 10;
	}
}

int main(){
	int a[MAX] = {7, 84, 25, 341, 65, 30, 34};
	int n=7;
	
	//scanf("%d", &n);
	
	/*
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	*/
	radixSort(a, n);
	for (int i = 0; i < n; i++){
		printf("a[%d] = %d \n", i, a[i]);
	}
	return 0;
}