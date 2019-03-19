// SW_5656.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

int T;
int N, W, H;
int input[17][14];
int copyInput[17][14];
int selected[12];
int direction[2][4] = { {0, 1, 0, -1},
                        {1, 0, -1, 0} };
int disappeared = 0;
int max = 0;
int box = 0;


void dfs(int i, int j) {
	int currentLocation = input[i][j];
	int ii, jj;
	input[i][j] = 0;
	disappeared++;
	for (int k = 0; k < 4; k++) {
		for (int l = 1; l < currentLocation; l++) {
			ii = i + (l * direction[0][k]);
			jj = j + (l * direction[1][k]);
			if (ii >= 0 && ii <= H && jj >= 0 && jj <= W) {
				if (input[ii][jj] > 0) {
					dfs(ii, jj);
				}
			}
		}
	}
}

void reset()
{
	for (int j = 1, count = H; j <= W; j++, count = H) {
		for (int i = H; i >= 1; i--) {
			if (input[i][j] > 0) {
				input[count][j] = input[i][j];
				if(count != i)
					input[i][j] = 0;
				count--;
			}
		}
	}
}

void inputReset() 
{
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
			input[i][j] = copyInput[i][j];
}

void fullSearch(int depth) {
	if (N == depth) {
		for (int i = 0; i < N; i++) {
			for (int top = 1; top <= H; top++)
			{
				if (input[top][selected[i]] != 0) {
					dfs(top, selected[i]);
					reset();
					break;
				}
			}
		}
		inputReset();
		if (max < disappeared) max = disappeared;
		disappeared = 0;
		return;
	}
	for (int i = 1; i <= W; i++) {
		selected[depth] = i;
		fullSearch(depth + 1);
	}
}

int main()
{
	scanf("%d", &T);
	for(int testCase = 0; testCase < T; testCase++)
	{
		scanf("%d %d %d", &N, &W, &H);
		for (int i = 1; i <= H; i++)
			for (int j = 1; j <= W; j++) {
				scanf("%d", &input[i][j]);
				copyInput[i][j] = input[i][j];
				if (input[i][j] > 0)
					++box;
			}
		fullSearch(0);
		printf("#%d %d\n", testCase + 1, box - max);
		box = 0;
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
