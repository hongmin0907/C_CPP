#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 1000


int a[SIZE];

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quickSort(int start, int end){
	if (end <= start) return;

	int key = start, i = start + 1, j = end, temp;

	while (i <= j){
		while (i <= end && a[i] <= a[key]) i++;
		while (start < j && a[key] <= a[j]) j--;
		if (j < i) swap(&a[key], &a[j]);
		else swap(&a[i], &a[j]);
	}

	quickSort(start, j - 1);
	quickSort(j + 1, end);
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	quickSort(0, n - 1);
	for (int i = 0; i < n; i++) printf("%d, ", a[i]);
	return 0;
}