#include <stdio.h>
#define MAX 10000 // 배열 크기 정의 

/*
    배열을 이용한 연결리스트 구현하기
    이는 나동빈님의 코드를 참조 했으며 add 부분은 예외처리 빼고 똑같고
    remove만 추가해서 올립니다
 */

int arr[MAX]; // 배열을 전역변수로 선언
int count = 0; // 지금 배열에 담겨있는 데이터 갯수

// 뒤에서 데이터 삽입하기
void addBack(int data){
    // 배열이 꽉 찼으면 리턴
    if(count == MAX){
        printf("배열이 꽉 찼습니다.");
        return;
    }
    // 배열 맨 뒤에 데이터 값 삽입 count수 올리기
    arr[count] = data;
    count++;
}

// 앞에서 데이터 삽입하기
void addFront(int data){
    // 배열이 꽉 찼으면 리턴
    if(count == MAX){
        printf("배열이 꽉 찼습니다.");
        return;
    }
    // 앞에서부터 넣어야 하기 때문에 배열의 모든 데이터는 뒤로 한칸씩 옮긴다
    for(int i = count; 0<i; i--){
        arr[i] = arr[i-1];
    }
    // 맨 앞에 데이터 삽입
    arr[0] = data;
    count ++;
}

// 뒤의 데이터 삭제하기
int removeBack(){
    // 배열이 비었을 때 리턴
    if (count == 0){
        printf("빈 배열 입니다.");
        return;
    }
    // 배열 맨 뒤에 값을 저장할 변수 선언해서 값을 넣어둠
    // 넣어 둔 뒤 맨 뒤에값 0으로 초기화 하고 
    // 배열안의 데이터 갯수 줄임
    int temp = arr[count];
    arr[count] = 0;
    count--;
    // 저장해 두었던 맨 뒤에 값 리턴
    return temp;
}

// 앞의 데이터 삭제하기
int removeFront(){
    // 배열이 비었을 때 리턴
    if (count == 0){
        printf("빈 배열 입니다.");
        return;
    }
    // 맨 앞의 데이터를 지워야 하기 때문에 맨 앞에 데이터를 변수 선언해서 저장 
    // 반복문으로 배열 안의 데이터를 하나씩 옮김
    // 배열 맨 뒤에 값을 0으로 초기화 하고 
    // 배열안의 데이터 갯수 줄임
    int temp = arr[0];
    for(int i=0; i<count; i++){
        arr[i] = arr[i+1];
    }
    arr[count] = 0;
    count--;
    // 저장해 두었던 맨 앞에 값 리턴
    return temp;
}

// 배열안의 값 출력하기
void Print(){
    // 배열이 비었을 때 리턴
    if (count == 0){
        printf("빈 배열 입니다.");
        return;
    }
    // 반복문을 활용해서 출력
    for(int i=0; i<count; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    addFront(4);
    addFront(5);
    addFront(1);
    addBack(7);
    addBack(6);
    addBack(8);
    Print();
    removeBack();
    Print();
    removeFront();
    Print();

    return 0;
}