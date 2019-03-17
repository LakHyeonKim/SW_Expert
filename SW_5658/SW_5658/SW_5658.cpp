// SW_5658.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstring>
#define MAX_SIZE 28
#define SIDE 4
#define NOTATION 16
int T, N, K;
int count = 1;
int input[MAX_SIZE];
int sort[MAX_SIZE];
int sorted[MAX_SIZE];
int numberOfSquareSides[SIDE];
char inputString[MAX_SIZE];
int digitArea[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int textArea[6] = { 10, 11, 12, 13, 14, 15 };

void merge_sort(int inputArray[], int start, int end) {
	int mid;
	int i, j, k, l;
	
	if (start < end) {
		mid = (start + end) / 2; 
		i = start; j = mid + 1; k = start;
		merge_sort(inputArray, start, mid); 
		merge_sort(inputArray, mid + 1, end); 
		while (i <= mid && j <= end) {
			if (inputArray[i] >= inputArray[j])
				sorted[k++] = inputArray[i++];
			else
				sorted[k++] = inputArray[j++];
		}
		if (i > mid) {
			for (l = j; l <= end; l++)
				sorted[k++] = inputArray[l];
		}
		else {
			for (l = i; l <= mid; l++)
				sorted[k++] = inputArray[l];
		}
		for (l = start; l <= end; l++) {
			inputArray[l] = sorted[l];
		}
	}
}

void reset(int inputArray[]) {
	for (int i = 0; i < N; i++) {
		if (inputString[i] >= '0' && inputString[i] <= '9')
			inputArray[i] = digitArea[inputString[i] % '0'];
		else
			inputArray[i] = textArea[inputString[i] % 'A'];
	}
}

void rotation(int inputArray[]) {
	int lastValue = inputArray[N - 1];
	for (int i = N - 1; i > 0; i--)
		inputArray[i] = inputArray[i - 1];
	inputArray[0] = lastValue;
}

void makeDec(int inputArray[], int numberOfSquareSidesArray[]) {
	int dec = 0;
	for (int i = 0; i < SIDE; i++) {
		for (int j = N / SIDE - 1 ; j >= 0; j--)
			dec = dec + inputArray[i * (N / SIDE) + j] * pow(NOTATION, N / SIDE - 1 - j);
		numberOfSquareSidesArray[i] = dec;
		dec = 0;
	}
}

int check(int sortArray[], int numberOfSquareSidesArray[]) {
	int flag = 0;
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < count; j++) {
			if (sortArray[j] == numberOfSquareSidesArray[i]) { flag++; break; }
			else if (j == count - 1) {
				sortArray[count - 1] = numberOfSquareSidesArray[i];
				count++;
				break;
			}
		}
	}
	if (flag == 4) return 1; else return 0;
}

void Initialize() {
	count = 1;
	memset(input, 0, sizeof(int) * MAX_SIZE);
	memset(sort, 0, sizeof(int) * MAX_SIZE);
	memset(sorted, 0, sizeof(int) * MAX_SIZE);
	memset(numberOfSquareSides, 0, sizeof(int) * MAX_SIZE);
	memset(inputString, 0, sizeof(int) * MAX_SIZE);
}

int main() 
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d %d", &N, &K);
		scanf("%s", inputString);
		reset(input);
		makeDec(input, numberOfSquareSides);
		while (check(sort, numberOfSquareSides) != 1) {
			rotation(input);
			makeDec(input, numberOfSquareSides);
		}
		
		merge_sort(sort, 0, count - 2);

		printf("#%d %d\n", testCase + 1, sort[K - 1]);
		Initialize();
	}
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
