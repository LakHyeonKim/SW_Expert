// SW_5650.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cstring>

typedef struct POINT {
	int i;
	int j;
} Point;

int T, N, max;
int map[102][102];
int direction[2][4] = { {-1,0,1,0},{0,1,0,-1} };
int block[6][4] = { {2,3,0,1}, {1,0,2,3}, {0,2,1,3}, {0,1,3,2}, {3,1,2,0}, {0,1,2,3} };
Point wormHole[2][5];

/* recursive method */
//void dfs(int i, int j, int start_i, int start_j, int preDirection, int count) {
//	if ((i == start_i && j == start_j && preDirection != -1) || map[i][j] == -1) {
//		if (max < count)
//			max = count;
//		return;
//	}
//	if (preDirection == -1) {
//		for (int outDirection = 0; outDirection < 4; outDirection++) {
//			int next_i = i + direction[0][outDirection];
//			int next_j = j + direction[1][outDirection];
//			dfs(next_i, next_j, start_i, start_j, (outDirection + 2) % 4, count);
//		}
//	}
//	else if (0 <= map[i][j] && 5 >= map[i][j]) {
//		int outDirection = block[map[i][j]][preDirection];
//		int next_i = i + direction[0][outDirection];
//		int next_j = j + direction[1][outDirection];
//		if (map[i][j] == 0)
//			dfs(next_i, next_j, start_i, start_j, (outDirection + 2) % 4, count);
//		else
//			dfs(next_i, next_j, start_i, start_j, (outDirection + 2) % 4, count + 1);
//	}
//	else if (6 <= map[i][j] && 10 >= map[i][j]) {
//		int next_i, next_j;
//		int outDirection = block[0][preDirection];
//		if (i == wormHole[0][map[i][j] - 6].i && j == wormHole[0][map[i][j] - 6].j) {
//			next_i = wormHole[1][map[i][j] - 6].i + direction[0][outDirection];
//			next_j = wormHole[1][map[i][j] - 6].j + direction[1][outDirection];
//		}
//		else {
//			next_i = wormHole[0][map[i][j] - 6].i + direction[0][outDirection];
//			next_j = wormHole[0][map[i][j] - 6].j + direction[1][outDirection];
//		}
//		dfs(next_i, next_j, start_i, start_j, (outDirection + 2) % 4, count);
//	}
//	else {
//		int outDirection = block[5][preDirection];
//		int next_i = i + direction[0][outDirection];
//		int next_j = j + direction[1][outDirection];
//		dfs(next_i, next_j, start_i, start_j, (outDirection + 2) % 4, count + 1);
//	}
//}

void work(int i, int j, int start_i, int start_j) {
	int next_i, next_j;
	int preD = -1;
	int count = 0;
	for (int outDirection = 0; outDirection < 4; outDirection++) {
		next_i = i + direction[0][outDirection];
		next_j = j + direction[1][outDirection];
		preD = (outDirection + 2) % 4;
		while (true) {
			if ((next_i == start_i && next_j == start_j) || map[next_i][next_j] == -1) {
				if (max < count)
					max = count;
				count = 0;
				break;
			}
			else if (0 <= map[next_i][next_j] && 5 >= map[next_i][next_j]) {
				int outD = block[map[next_i][next_j]][preD];
				if (map[next_i][next_j] == 0) {
					preD = (outD + 2) % 4;
				}
				else {
					preD = (outD + 2) % 4; count++;
				}
				next_i += direction[0][outD];
				next_j += direction[1][outD];
				
			}
			else if (6 <= map[next_i][next_j] && 10 >= map[next_i][next_j]) {
				int outD = block[0][preD];
				preD = (outD + 2) % 4;
				int i = next_i;
				int j = next_j;
				if (next_i == wormHole[0][map[next_i][next_j] - 6].i && next_j == wormHole[0][map[next_i][next_j] - 6].j) {
					next_i = wormHole[1][map[i][j] - 6].i + direction[0][outD];
					next_j = wormHole[1][map[i][j] - 6].j + direction[1][outD];
				}
				else {
					next_i = wormHole[0][map[i][j] - 6].i + direction[0][outD];
					next_j = wormHole[0][map[i][j] - 6].j + direction[1][outD];
				}
			}
			else {
				int outD = block[5][preD];
				preD = (outD + 2) % 4; count++;
				next_i += direction[0][outD];
				next_j += direction[1][outD];
			}
		}
			
	}

}

void init() {
	for (int i = 0; i <= N + 1; i++)
		for (int j = 0; j <= N + 1; j++)
			map[i][j] = 11;
}

int main()
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d", &N);
		init();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
				if (6 <= map[i][j] && 10 >= map[i][j]) {
					if (wormHole[0][map[i][j] - 6].i == 0 && wormHole[0][map[i][j] - 6].j == 0) {
						wormHole[0][map[i][j] - 6].i = i;
						wormHole[0][map[i][j] - 6].j = j;
					}
					else {
						wormHole[1][map[i][j] - 6].i = i;
						wormHole[1][map[i][j] - 6].j = j;
					}
				}
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if(map[i][j] == 0)
					work(i, j, i, j);
			}
		}
		printf("#%d %d\n", testCase + 1, max);
		max = 0;
		memset(wormHole, 0, sizeof(wormHole));
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
