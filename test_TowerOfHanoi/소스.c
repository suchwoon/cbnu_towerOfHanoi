#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* Ÿ�� ����ü ���� */
typedef struct {
	int max;	// �ִ� ���� ����
	int ptr;	// ���� ���� ����
	int* stk;	// ù ��ҿ� ���� ������ (�迭������)
}Tower;

Tower a, b, c;	// �� Ÿ�� ����ü ������ ���������� ����
int moveCount = 0;	// �̵� Ƚ�� �������� ����

int getTowerSize(void);	// �ʱ� ���� ���� ����
void towerOfHanoi(int towerSize, Tower* from, Tower* temp, Tower* to);	// ���� ������ ���� �ϳ����� ž �ִܰ�� ����
void drawAllTowers(void);	// ���� Ÿ������ ���� �׸����� ���
void drawFloor(Tower* t, int floor);	// �ش� ���� �ش� Ÿ�� ���� �׸����� ���
void giveDelay(int time);	// ������ �� �ܼ� ȭ�� �ʱ�ȭ

int Initialize(Tower* t, int towerSize);	// Ÿ�� �ʱ�ȭ, �ִ� ���� ���� towerSize�� ����
void Push(Tower* t, int diskSize);	// Ÿ���� diskSize ���� Push
int Pop(Tower* t); // Ÿ������ ���� Pop
void Terminate(Tower* t);	// Ÿ�� ���� �޸� ����, �ʱ�ȭ

/* Ÿ�� �ʱ�ȭ */
int Initialize(Tower* t, int towerSize) {
	t->max = towerSize;	// �ִ� ���� ���� towerSize�� ����
	t->ptr = 0;	// ���� ���� ���� 0���� ����
	t->stk = (int*)calloc(t->max, sizeof(int));	// �迭�� t->max = towerSize ��ŭ�� ���� �޸� �Ҵ�

	if (t->stk == NULL) {	// �迭�����Ͱ� ������� �ʾ��� ���
		t->max = 0;	// �ִ� ���� ���� 0���� ����
		printf("Initialize ���� : �迭�����Ͱ� ������� ����\n");	// ���� �޽��� ���
		return -1;
	}
	return 0;
}

/* Ÿ���� ���� Push */
void Push(Tower* t, int diskSize) {
	if (t->ptr == 0) {	//������ ���� ���
		t->stk[t->ptr] = diskSize;	// t->ptr�� ��ҿ� diskSize ���� �Է�
		t->ptr++;	// ���� ���� +1
	}
	else if (t->ptr < t->max) {	// ������ �����ϳ� ������ �ִ밡 �ƴ� ���
		if (diskSize < t->stk[t->ptr - 1]) {	// Push�ϴ� ������ �� ���� ���Ǻ��� ���� ���
			t->stk[t->ptr] = diskSize;	// t->ptr�� ��ҿ� diskSize ���� �Է�
			t->ptr++;	// ���� ���� +1
		}
		else {
			printf("Push ���� : ������ �ʹ� ŭ\n");
		}
	}
	else {	// ���� ������ �ִ��� ���
		printf("Push ���� : ���� �� ��\n");
	}
	return;
}

/* Ÿ������ ���� Pop */
int Pop(Tower* t) {
	if (t->ptr == 0) {	// ������ ���� ���
		printf("Pop ���� : ���� ��� ����\n");
		return -1;
	}
	return t->stk[--t->ptr];	// ���� ������ ���ҽ�Ű�� �� �� ���� ��ȯ
}

/* Ÿ�� ���� �޸� ����, �ʱ�ȭ */
void Terminate(Tower* t) {
	if (t->stk != NULL) {	// �迭�����Ͱ� ����Ǿ��� ���
		free(t->stk);	// ������ ���� �޸� ����
		t->max = t->ptr = 0;	// �ִ� ���� ����, ���� ���� ���� 0���� ����
	}
	return;
}

/* �ʱ� ���� ���� ���� */
int getTowerSize(void) {
	int towerSize;	// �ִ� ���� ���� ���� ����
	printf("�ʱ� ������ ������ �Է��Ͻÿ�: ");
	scanf("%d", &towerSize);	// �ִ� ���� ���� ����
	printf("\n");
	return towerSize;	// ��ȯ
}

/* ���� ������ ���� �ϳ����� ž �ִܰ�� ���� */
void towerOfHanoi(int towerSize, Tower* from, Tower* temp, Tower* to) {
	if (towerSize == 1) {	// fromŸ���� ������ �ϳ� ������ ���
		Push(to, Pop(from));	// fromŸ������ Pop�� ������ to���ǿ� Push
		moveCount++;	// �̵� Ƚ�� ����
		drawAllTowers();	// ���� Ÿ������ ���� �׸����� ���
	}
	else {	// fromŸ���� ������ �� �̻� ���� ���
		towerOfHanoi(towerSize - 1, from, to, temp);	// �̵� ���� ������ ����, to�� temp�� ��ȯ�� ���
		Push(to, Pop(from));	// from Ÿ������ Pop�� ������ to���ǿ� Push
		moveCount++;	// �̵� Ƚ�� ����
		drawAllTowers();	// ���� Ÿ������ ���� �׸����� ���
		towerOfHanoi(towerSize - 1, temp, from, to);	// �̵� ���� ������ ����, from�� temp�� ��ȯ�� ���
	}
}

/* ���� Ÿ������ ���� �׸����� ��� */
void drawAllTowers(void) {
	giveDelay(1000);
	int floor;	// ��� �� ���� ����
	for (floor = a.max; floor > 0; floor--) {	// ��� ���� ���� �ִ� �������� 1������ �ݺ�
		drawFloor(&a, floor);	// �� Ÿ���� ���� drawFloor �Լ� ȣ��
		drawFloor(&b, floor);
		drawFloor(&c, floor);	// drawAllTowers �Լ� ���� pa, pb, pc�� �������̹Ƿ� &�� ���� �ʿ� ����
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// �ؽ�Ʈ �� �������
	printf(" move %d\n", moveCount);	// �̵� Ƚ�� ���
	printf("\n\n");
}

/* �ش� ���� �ش� Ÿ�� ���� �׸����� ��� */
void drawFloor(Tower* t, int floor) {
	if (t->ptr < floor) {	// ���� ������ ������ ���� ���
		for (int j = 0; j < t->max * 2; j++)	// ���� �ִ� ������ 2�踸ŭ ���� ���
			printf(" ");
		printf("  ");	// Ÿ�� ���� ����
	}
	else {	// ���� ������ ������ ũ�ų� ���� ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t->stk[floor-1]+1);	// ���� ũ�⿡ ���� �ؽ�Ʈ �� ����
		int floorDiskSize = t->stk[floor - 1];
		for (int k = 0; k < t->max - floorDiskSize; k++)	// ���� ������ ��������
			printf(" ");
		for (int l = 0; l < floorDiskSize * 2; l++)	// ���� ���� diskSize�� 2�踸ŭ �� ���
			printf("#");
		for (int m = 0; m < t->max-floorDiskSize; m++)	// ���� ������ ��������
			printf(" ");
		printf("  ");	// Ÿ�� ���� ����
	}
}

void giveDelay(int time) {
	Sleep(time);	// ������
	system("cls");	// �ܼ� ȭ�� �ʱ�ȭ
	printf("\n");
	return;
}

/* main �Լ� */
int main(void) {
	int towerSize = getTowerSize();	// �ʱ� ���� ���� ����

	Initialize(&a, towerSize);	// �� Ÿ�� �ʱ�ȭ
	Initialize(&b, towerSize);
	Initialize(&c, towerSize);

	int i;	// �ݺ����� ���� �Ű����� ����
	for (i = 0; i < towerSize; i++) {	// Ÿ�� a�� ��� ���� Push
		Push(&a, towerSize - i);	// ���� ū ���Ǻ��� ������� Push
	}

	drawAllTowers(&a, &b, &c);

	towerOfHanoi(towerSize, &a, &b, &c);	// �ϳ����� ž �Լ� ����

	Terminate(&a);
	Terminate(&b);
	Terminate(&c);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// �ؽ�Ʈ �� �������

	return 0;
}