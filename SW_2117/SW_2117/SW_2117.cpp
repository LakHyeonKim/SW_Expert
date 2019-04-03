// SW_2117.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cstring>

int T, N, M, home, max;
int map[22][22];
int visited[22][22];
int direction[2][4] = { {0,1,0,-1}, {1,0,-1,0} };

void makeRhombus(int i, int j, int start_i, int start_j, int k) {
	int distance = abs(start_i - i) + abs(start_j - j);
	visited[i][j] = 1;
	if (map[i][j] == 1) {
		home++;
	}
	if (distance == k - 1) {
		return;
	}
	else
	{
		for (int l = 0; l < 4; l++)
		{
			int next_i = i + direction[0][l];
			int next_j = j + direction[1][l];
			if (map[next_i][next_j] == -1 || visited[next_i][next_j])
				continue;
			makeRhombus(next_i, next_j, start_i, start_j, k);
		}
	}
}

int main()
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d %d", &N, &M);
		memset(map, -1, sizeof(map));
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf("%d", &map[i][j]);

		for (int k = 1; k <= N + 1; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					makeRhombus(i, j, i, j, k);
					if (home * M - (k * k + (k - 1) * (k - 1)) >= 0)
					{
						if (max < home)
							max = home;
					}
					memset(visited, 0, sizeof(visited));
					home = 0;
				}
			}
		}
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
