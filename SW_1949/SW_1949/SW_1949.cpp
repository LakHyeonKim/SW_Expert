// SW_1949.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 2019.3.15

#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

typedef struct POINT {
	int i;
	int j;
} Point;

typedef struct MAX_VALUE_INFORMATION {
	int maxValue;
	int maxValueCount;
} MaxValue;

int T;
int N, K;
int input[10][10];
int direction[2][4] = { {0, 1, 0, -1},
						{1, 0, -1, 0} };
Point topPointArray[64];
MaxValue searchMaxValue;
int maxPathSize;
int dfsResult;

int MAX(int array[], int size) {
	int maxValue = array[0];
	for (int i = 0; i < size; i++) {
		if (maxValue < array[i])
			maxValue = array[i];
	}
	return maxValue;
}

int dfs(int i, int j) {
	int maxSearchArray[4] = {0, 0, 0, 0};
	int maxValue = 0;
	for (int k = 0; k < 4; k++) {
		if ((input[i][j] > input[i + direction[0][k]][j + direction[1][k]]) && input[i + direction[0][k]][j + direction[1][k]] != -5)
			maxSearchArray[k] = dfs(i + direction[0][k], j + direction[1][k]) + 1;
	}
	maxValue = MAX(maxSearchArray, 4);
	return maxValue;
}

MaxValue topPointValue(Point array[]) {
	MaxValue mValue;
	mValue.maxValue = input[1][1];
	mValue.maxValueCount = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++){
			if (mValue.maxValue < input[i][j])
				mValue.maxValue = input[i][j];
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (input[i][j] == mValue.maxValue) {
				array[mValue.maxValueCount].i = i;
				array[mValue.maxValueCount++].j = j;
			}
		}
	}
	return mValue;
}

void myMemset(int array[][10], int value) {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			array[i][j] = value;
}

int main()
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		myMemset(input, -5);
		scanf("%d %d", &N, &K);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf("%d", &input[i][j]);
		searchMaxValue = topPointValue(topPointArray); // Find peaks in each case
		for (int construction = 0; construction <= K; construction++) // construction
		{
			for (int v = 0; v < searchMaxValue.maxValueCount; v++) {
				for (int i = 1; i <= N; i++) {
					for (int j = 1; j <= N; j++) {
						if (i != topPointArray[v].i || j != topPointArray[v].j)
							input[i][j] -= construction; // check point
						dfsResult = dfs(topPointArray[v].i, topPointArray[v].j) + 1;
						if (maxPathSize < dfsResult)
							maxPathSize = dfsResult;
						if (i != topPointArray[v].i || j != topPointArray[v].j)
							input[i][j] += construction;
					}
				}
				
			}
		}
		
		printf("#%d %d\n", testCase + 1, maxPathSize);
		maxPathSize = 0;
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
