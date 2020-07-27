// �ؽ�(Hash)�� �����͸� �ִ��� ���� �ӵ��� �����ϵ��� �����ִ� �ڷᱸ��
// �ؽø� ����ϸ� �޸� ������ ���� �Ҹ������ �ſ� ���� �ӵ��� �����͸� ó���� �� �ֽ��ϴ�.
// ������ �����Ϳ� ������ �� �ֵ��� ������ �����ͺ��̽� ���� ����Ʈ����� Ȱ��˴ϴ�.

// key:value

// Ư���� ��(Value)�� ã���� �� ���� �� ���� Ű(Key)�� ������ �� �ֽ��ϴ�. �Ϲ������� �ؽ� �Լ��� ����(Modulo) �Ť����� ���� ������ �������� �̷���� �����Ƿ� O(1)���� ���� ������ �� �ֽ��ϴ�.

// �ؽ� ���̺��� Ű(key)�� �ߺ��Ǵ� ��� �ѵ�(Collision)�� �߻��ߴٰ� ǥ��

// �ؽ� - �ؽ� �˰����� ������ ��(Division Method)�� ���� ���� Ȱ��˴ϴ�. �Է� ���� ���̺��� ũ��� ���� ������ Ű(key)�� �̿��ϴ� ����Դϴ�. ���̺��� ũ��� �Ҽ� (prime Number)�� �A���ϴ� ���� ȿ������ �����ϴ�.

// �浹ó��
// 1) �浹�� �߻���Ű�� �׸��� �ؽ� ���̺��� �ٸ� ��ġ�� ����: ���� �����, ���� ����� ��
// 2) �ؽ� ���̺��� �ϳ��� ��Ŷ(Bucket)�� ���� ���� �׸��� ����: ü�̴�(Chaining) �� 





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

// ���� �����

/*

typedef struct STUDENT{
	int id;
	char name[20];
}Student;


// �ؽ� ���̺��� �ʱ�ȭ �մϴ�.
void init(Student** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		hashtable[i] = NULL;
	}
}

// �ؽ� ���̺��� �޸𸮸� ��ȯ�մϴ�.
void destructor(Student** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashtable[i] != NULL){
			free(hashtable[i]);
		}
	}
}

// �ؽ� ���̺� �� �� ������ ���� Ž������ ã���ϴ�.
int findEmpty(Student** hashtable, int id){
	int i = id % TABLE_SIZE;
	while (1){
		if (hashtable[i % TABLE_SIZE] == NULL){
			return i % TABLE_SIZE;
		}
		i++;
	}
}

// Ư���� ID ���� ��Ī�Ǵ� �����͸� �ؽ� ���̺� ������ ã���ϴ�.
int search(Student** hashtable, int id){
	int i = id % TABLE_SIZE;
	while (1){
		if (hashtable[i % TABLE_SIZE] == NULL) return -1;
		else if (hashtable[i % TABLE_SIZE]->id == id) return i;
		i++;
	}
}

// Ư���� Ű �ε����� �����͸� �����մϴ�.
void add(Student** hashtable, Student* input, int key){
	hashtable[key] = input;
}

Student* getValue(Student** hashtable, int key){
	return hashtable[key];
}

void show(Student** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		if (hashtable[i] != NULL){
			printf("Ű : [%d] �̸�: [%s]\n", i, hashtable[i]->name);
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
		sprintf(student->name, "���%d", student->id);
		if (search(hashtable, student->id) == -1){ // �ߺ��Ǵ� ID�� �������� �ʵ��� ��.
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

// ü�̴�

typedef struct STUDENT{
	int id;
	char name[20];
}Student;

typedef struct BUCKET{
	Student* data;
	struct BUCKET* next;
}Bucket;

// �ؽ� ���̺� �ʱ�ȭ
void init(Bucket** hashtable){
	for (int i = 0; i < TABLE_SIZE; i++){
		hashtable[i] = NULL;
	}
}

// �ؽ� ���̺��� �޸𸮸� ��ȯ�մϴ�.
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
				printf("Ű: [%d] �̸�: [%s]\n", i, cur->data->name);
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
		sprintf(student->name, "���%d", student->id);
		if (!isExist(hashtable, student->id)){ // �ߺ��Ǵ� ID�� �������� �ʵ��� ��.
			add(hashtable, student);
		}
	}

	show(hashtable);
	destructor(hashtable);
	system("pause");
	return 0;
}

// �ؽô� �����ͺ��̽� �ε��� �� �������� ���� ��� ��� ������ �پ��ϰ� ���ǰ� �ִ�.