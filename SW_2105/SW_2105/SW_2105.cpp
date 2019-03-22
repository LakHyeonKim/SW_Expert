// SW_2105.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 아니라고 생각한 조건은 바로바로 지우자~~!!!!!!

#include "pch.h"
#include <iostream>
#include <cstring>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define COMPARE(a,b) (((a) == (b)) ? (0) : (1))

int T, N;
int input[21][21];
char overlapCheck[101];
int start_i, start_j;
int direction[2][4] = { {1, 1, -1, -1},
				  {1, -1, -1, 1} };
int max;

void dfs(int i, int j, int previousDirection, int level, int angle) {
	if (i == start_i && j == start_j && level != 0 && angle == 4) {
		max = MAX(max, level);
		return;
	}
	if (overlapCheck[input[i][j]]) {
		return;
	}
	overlapCheck[input[i][j]] = 1;
	for (int p = previousDirection, end = 0; end < 2; p = (previousDirection + 1) % 4, end++)
	{
		int next_i = i + direction[0][p];
		int next_j = j + direction[1][p];
		if (next_i < 0 || next_i > N - 1 || next_j < 0 || next_j > N - 1)
			continue;
		dfs(next_i, next_j, p, level + 1, angle + COMPARE(p, previousDirection));
	}
	overlapCheck[input[i][j]] = 0;
}

int main()
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &input[i][j]);

		for (int i = 0; i < N - 2; i++)
			for (int j = 0; j < N; j++) {
				start_i = i; start_j = j;
				dfs(i, j, 0, 0, 1);
				memset(overlapCheck, 0, sizeof(overlapCheck));
			}
		if (max == 0) max = -1;
		printf("#%d %d\n", testCase + 1, max);
		max = 0;
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
