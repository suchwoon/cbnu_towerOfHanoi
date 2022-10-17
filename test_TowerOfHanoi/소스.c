#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* 타워 구조체 선언 */
typedef struct {
	int max;	// 최대 원판 개수
	int ptr;	// 현재 원판 개수
	int* stk;	// 첫 요소에 대한 포인터 (배열포인터)
}Tower;

Tower a, b, c;	// 각 타워 구조체 포인터 전역변수로 선언
int moveCount = 0;	// 이동 횟수 전역변수 선언

int getTowerSize(void);	// 초기 원판 개수 수집
void towerOfHanoi(int towerSize, Tower* from, Tower* temp, Tower* to);	// 원판 개수에 따른 하노이의 탑 최단경로 실행
void drawAllTowers(void);	// 현재 타워들의 상태 그림으로 출력
void drawFloor(Tower* t, int floor);	// 해당 층의 해당 타워 상태 그림으로 출력
void giveDelay(int time);	// 딜레이 후 콘솔 화면 초기화

int Initialize(Tower* t, int towerSize);	// 타워 초기화, 최대 원판 개수 towerSize로 설정
void Push(Tower* t, int diskSize);	// 타워에 diskSize 원판 Push
int Pop(Tower* t); // 타워에서 원판 Pop
void Terminate(Tower* t);	// 타워 동적 메모리 해제, 초기화

/* 타워 초기화 */
int Initialize(Tower* t, int towerSize) {
	t->max = towerSize;	// 최대 원판 개수 towerSize로 설정
	t->ptr = 0;	// 현재 원판 개수 0으로 설정
	t->stk = (int*)calloc(t->max, sizeof(int));	// 배열에 t->max = towerSize 만큼의 정수 메모리 할당

	if (t->stk == NULL) {	// 배열포인터가 선언되지 않았을 경우
		t->max = 0;	// 최대 원판 개수 0으로 설정
		printf("Initialize 오류 : 배열포인터가 선언되지 않음\n");	// 오류 메시지 출력
		return -1;
	}
	return 0;
}

/* 타워에 원판 Push */
void Push(Tower* t, int diskSize) {
	if (t->ptr == 0) {	//원판이 없을 경우
		t->stk[t->ptr] = diskSize;	// t->ptr번 요소에 diskSize 원판 입력
		t->ptr++;	// 원판 개수 +1
	}
	else if (t->ptr < t->max) {	// 원판이 존재하나 개수는 최대가 아닐 경우
		if (diskSize < t->stk[t->ptr - 1]) {	// Push하는 원판이 맨 위의 원판보다 작을 경우
			t->stk[t->ptr] = diskSize;	// t->ptr번 요소에 diskSize 원판 입력
			t->ptr++;	// 원판 개수 +1
		}
		else {
			printf("Push 오류 : 원판이 너무 큼\n");
		}
	}
	else {	// 원판 개수가 최대일 경우
		printf("Push 오류 : 원판 꽉 참\n");
	}
	return;
}

/* 타워에서 원판 Pop */
int Pop(Tower* t) {
	if (t->ptr == 0) {	// 원판이 없을 경우
		printf("Pop 오류 : 원판 비어 있음\n");
		return -1;
	}
	return t->stk[--t->ptr];	// 원판 개수를 감소시키고 맨 위 원판 반환
}

/* 타워 동적 메모리 해제, 초기화 */
void Terminate(Tower* t) {
	if (t->stk != NULL) {	// 배열포인터가 선언되었을 경우
		free(t->stk);	// 스택의 동적 메모리 해제
		t->max = t->ptr = 0;	// 최대 원판 개수, 현재 원판 개수 0으로 설정
	}
	return;
}

/* 초기 원판 개수 수집 */
int getTowerSize(void) {
	int towerSize;	// 최대 원판 개수 변수 선언
	printf("초기 원판의 개수를 입력하시오: ");
	scanf("%d", &towerSize);	// 최대 원판 개수 수집
	printf("\n");
	return towerSize;	// 반환
}

/* 원판 개수에 따른 하노이의 탑 최단경로 실행 */
void towerOfHanoi(int towerSize, Tower* from, Tower* temp, Tower* to) {
	if (towerSize == 1) {	// from타워에 원판이 하나 남았을 경우
		Push(to, Pop(from));	// from타워에서 Pop한 원판을 to원판에 Push
		moveCount++;	// 이동 횟수 증가
		drawAllTowers();	// 현재 타워들의 상태 그림으로 출력
	}
	else {	// from타워에 원판이 둘 이상 있을 경우
		towerOfHanoi(towerSize - 1, from, to, temp);	// 이동 원판 개수를 감소, to와 temp를 교환해 재귀
		Push(to, Pop(from));	// from 타워에서 Pop한 원판을 to원판에 Push
		moveCount++;	// 이동 횟수 증가
		drawAllTowers();	// 현재 타워들의 상태 그림으로 출력
		towerOfHanoi(towerSize - 1, temp, from, to);	// 이동 원판 개수를 감소, from과 temp를 교환해 재귀
	}
}

/* 현재 타워들의 상태 그림으로 출력 */
void drawAllTowers(void) {
	giveDelay(1000);
	int floor;	// 출력 층 변수 선언
	for (floor = a.max; floor > 0; floor--) {	// 출력 층이 원판 최대 개수부터 1층까지 반복
		drawFloor(&a, floor);	// 각 타워에 대한 drawFloor 함수 호출
		drawFloor(&b, floor);
		drawFloor(&c, floor);	// drawAllTowers 함수 내의 pa, pb, pc는 포인터이므로 &를 붙일 필요 없음
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// 텍스트 색 흰색으로
	printf(" move %d\n", moveCount);	// 이동 횟수 출력
	printf("\n\n");
}

/* 해당 층의 해당 타워 상태 그림으로 출력 */
void drawFloor(Tower* t, int floor) {
	if (t->ptr < floor) {	// 원판 개수가 층보다 작을 경우
		for (int j = 0; j < t->max * 2; j++)	// 원판 최대 개수의 2배만큼 공백 출력
			printf(" ");
		printf("  ");	// 타워 사이 간격
	}
	else {	// 원판 개수가 층보다 크거나 같을 경우
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t->stk[floor-1]+1);	// 원판 크기에 따라 텍스트 색 설정
		int floorDiskSize = t->stk[floor - 1];
		for (int k = 0; k < t->max - floorDiskSize; k++)	// 남은 공간을 공백으로
			printf(" ");
		for (int l = 0; l < floorDiskSize * 2; l++)	// 현재 층의 diskSize의 2배만큼 별 출력
			printf("#");
		for (int m = 0; m < t->max-floorDiskSize; m++)	// 남은 공간을 공백으로
			printf(" ");
		printf("  ");	// 타워 사이 간격
	}
}

void giveDelay(int time) {
	Sleep(time);	// 딜레이
	system("cls");	// 콘솔 화면 초기화
	printf("\n");
	return;
}

/* main 함수 */
int main(void) {
	int towerSize = getTowerSize();	// 초기 원판 개수 수집

	Initialize(&a, towerSize);	// 각 타워 초기화
	Initialize(&b, towerSize);
	Initialize(&c, towerSize);

	int i;	// 반복문을 위한 매개변수 선언
	for (i = 0; i < towerSize; i++) {	// 타워 a에 모든 원판 Push
		Push(&a, towerSize - i);	// 가장 큰 원판부터 순서대로 Push
	}

	drawAllTowers(&a, &b, &c);

	towerOfHanoi(towerSize, &a, &b, &c);	// 하노이의 탑 함수 실행

	Terminate(&a);
	Terminate(&b);
	Terminate(&c);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// 텍스트 색 흰색으로

	return 0;
}