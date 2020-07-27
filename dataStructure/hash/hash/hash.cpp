// 해시(Hash)는 데이터를 최대한 빠른 속도로 관리하도록 도와주는 자료구조
// 해시를 사용하면 메모리 공간이 많이 소모되지만 매우 빠른 속도로 데이터를 처리할 수 있습니다.
// 빠르게 데이터에 접근할 수 있따는 점에서 데이터베이스 등의 소프트웨어에서 활용됩니다.

// key:value

// 특정한 값(Value)을 찾고자 할 때는 그 값의 키(Key)로 접근할 수 있습니다. 일반적으로 해시 함수는 모듈로(Modulo) ㅕㅇㄴ산 등의 수학적 연산으로 이루어져 있으므로 O(1)만에 값에 전근할 수 있습니다.

// 해시 테이블에서 키(key)가 중복되는 경우 총돌(Collision)이 발생했다고 표현

// 해싱 - 해싱 알고리즘은 나눗셈 법(Division Method)이 가장 많이 활용됩니다. 입력 값을 테이블의 크기로 나눈 나머지 키(key)를 이용하는 방식입니다. 테이블의 크기는 소수 (prime Number)로 섲렁하는 것이 효율성이 높습니다.

// 충돌처리
// 1) 충돌을 발생시키는 항목을 해시 테이블의 다른 위치에 저장: 선형 조사법, 이차 조사법 등
// 2) 해시 테이블의 하나의 버킷(Bucket)에 여러 개의 항목을 저장: 체이닝(Chaining) 등 





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

// 선형 조사법

/*

typedef struct STUDENT{
	int id;
	char name[20];
}Student;


// 해시 테이블을 초기화 합니다.
void init(Student** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		hashtable[i] = NULL;
	}
}

// 해시 테이블의 메모리를 반환합니다.
void destructor(Student** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashtable[i] != NULL){
			free(hashtable[i]);
		}
	}
}

// 해시 테이블 내 빈 공간을 선형 탐색으로 찾습니다.
int findEmpty(Student** hashtable, int id){
	int i = id % TABLE_SIZE;
	while (1){
		if (hashtable[i % TABLE_SIZE] == NULL){
			return i % TABLE_SIZE;
		}
		i++;
	}
}

// 특정한 ID 값에 매칭되는 데이터를 해시 테이블 내에서 찾습니다.
int search(Student** hashtable, int id){
	int i = id % TABLE_SIZE;
	while (1){
		if (hashtable[i % TABLE_SIZE] == NULL) return -1;
		else if (hashtable[i % TABLE_SIZE]->id == id) return i;
		i++;
	}
}

// 특정한 키 인덱스에 데이터를 삽입합니다.
void add(Student** hashtable, Student* input, int key){
	hashtable[key] = input;
}

Student* getValue(Student** hashtable, int key){
	return hashtable[key];
}

void show(Student** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashtable[i] != NULL){
			printf("키 : [%d] 이름: [%s]\n", i, hashtable[i]->name);
		}
	}
}

int main(){
	Student** hashtable;
	hashtable = (Student**)malloc(sizeof(Student)* TABLE_SIZE);
	init(hashtable);

	for (int i = 0; i < INPUT_SIZE; i++){
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 1000000;
		sprintf(student->name, "사람%d", student->id);
		if (search(hashtable, student->id) == -1){ // 중복되는 ID는 존재하지 않도록 함.
			int index = findEmpty(hashtable, student->id);
			add(hashtable, student, index);
		}
	}

	show(hashtable);
	destructor(hashtable);
	system("pause");
	return 0;
}

*/

// 체이닝

typedef struct STUDENT{
	int id;
	char name[20];
}Student;

typedef struct BUCKET{
	Student* data;
	struct BUCKET* next;
}Bucket;

// 해시 테이블 초기화
void init(Bucket** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		hashtable[i] = NULL;
	}
}

// 해시 테이블의 메모리를 반환합니다.
void destructor(Bucket** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashtable[i] != NULL){
			free(hashtable[i]);
		}
	}
}

int isExist(Bucket** hashtable, int id) {
	int i = id % TABLE_SIZE;
	if (hashtable[i] == NULL) return 0;
	else{
		Bucket *cur = hashtable[i];
		while (cur != NULL) {
			if (cur->data->id == id) return 1;
			cur = cur->next;
		}
	}
	return 0;
}

void add(Bucket** hashtable, Student* input){
	int i = input->id % TABLE_SIZE;
	if (hashtable[i] == NULL){
		hashtable[i] = (Bucket*)malloc(sizeof(Bucket));
		hashtable[i]->data = input;
		hashtable[i]->next = NULL;
	}
	else{
		Bucket *cur = (Bucket*)malloc(sizeof(Bucket));
		cur->data = input;
		cur->next = hashtable[i];
		hashtable[i] = cur;
	}
}

void show(Bucket** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashtable[i] != NULL){
			Bucket *cur = hashtable[i];
			while (cur != NULL){
				printf("키: [%d] 이름: [%s]\n", i, cur->data->name);
				cur = cur->next;
			}
		}
	}
}

int main(){
	Bucket** hashtable;
	hashtable = (Bucket**)malloc(sizeof(Bucket)* TABLE_SIZE);
	init(hashtable);

	for (int i = 0; i < INPUT_SIZE; i++){
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 1000000;
		sprintf(student->name, "사람%d", student->id);
		if (!isExist(hashtable, student->id)){ // 중복되는 ID는 존재하지 않도록 함.
			add(hashtable, student);
		}
	}

	show(hashtable);
	destructor(hashtable);
	system("pause");
	return 0;
}

// 해시는 데이터베이스 인덱싱 및 정보보안 관련 모듈 등에서 굉장히 다양하게 사용되고 있다.