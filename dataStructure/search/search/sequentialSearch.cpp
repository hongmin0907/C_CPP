// O(N)

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 100

char **array;
int founded;

int main(){
	int n;
	char *word;
	word = (char*)malloc(sizeof(char) * LENGTH);
	scanf("%d %s", &n, word);
	array = (char**)malloc(sizeof(char)* LENGTH);
	
	for (int i = 0; i < n; i++){
		array[i] = (char*)malloc(sizeof(char)*LENGTH);
		scanf("%s", array[i]);
	}

	for (int i = 0; i < n; i++){
		if (!strcmp(array[i], word)){
			printf("%d��° �����Դϴ�. \n", i + 1);
			founded = 1;
		}
	}

	if (!founded) printf("���Ҹ� ã�� �� �����ϴ�. \n");

	return 0;
}