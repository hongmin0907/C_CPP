#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

void radix(int* a, int n){
	int res[MAX], maxValue = 0;
	int exp = 1;
	int number = 1;

	for (int i = 0; i < n; i++){
		if (maxValue < a[i]){
			maxValue = a[i];
		}
	}
	
	while (0 < maxValue / exp){
		int numbering[10] = { 0 };
		
		
		for (int i = 0; i < n; i++){
			numbering[a[i] / exp % 10]++;
		}

		for (int i = 1; i < 10; i++){
			numbering[i] += numbering[i - 1];
		}
		
		printf("%d 자리\n", number);
		for (int i = n - 1; 0 <= i; i--){
			//printf("--한 경우(%d번째) =  %d \n", i, --(numbering[a[i] / exp % 10]));
			//printf("1한 경우(%d번째) = %d \n", i, (numbering[a[i] / exp % 10]) );
			//int t = --numbering[a[i] / exp % 10];
			printf("%d ", numbering[a[i] / exp % 10]);
			res[--numbering[a[i] / exp % 10]] = a[i];
		}
		printf("\n");

		for (int i = 0; i < n; i++){
			a[i] = res[i];
		}
		exp *= 10;
		number *= 10;
	}

}

int main(){
	int a[MAX] = { 7, 84, 25, 341, 65, 30, 34 };
	int n = 7;

	radix(a, n);

	for (int i = 0; i < n; i++){
		printf("a[%d] = %d \n", i, a[i]);
	}

	return 0;
}