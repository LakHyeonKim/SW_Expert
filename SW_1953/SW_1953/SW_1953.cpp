// dfs, bfs 두 가지 방법으로 다 풀수 있는 문제...
// 중요한 부분 큐에 push할 때 level을 둬 L 시간 때 bfs로 퍼져나가는 범위 조절
// 의문?? bfs로 갈수있는 모든 방향을 탐색한 후 시작점에서 시간 때 만큼을 1시간일때 1칸 이동한 것으로 보고 시간 L 보다 작고 방문한 곳이면 카운트를 세면 안되더라...
// 왜 안될까???
#include "pch.h" 
#include <iostream>
#include <queue>
#include <cstring>
#include <math.h>

using namespace std;

int T;
int N, M, R, C, L;
int input[50][50];
int visited[50][50];
int _count;
int direction[8][4] = { {0, 0, 0, 0},
						{1, 1, 1, 1},
						{0, 1, 0, 1},
						{1, 0, 1, 0},
						{1, 0, 0, 1},
						{1, 1, 0, 0},
						{0, 1, 1, 0},
						{0, 0, 1, 1} };
int d[2][4] = { {0, 1, 0, -1},
				{1, 0, -1, 0} };

typedef struct POSITION {
	int i;
	int j;
	int type;
	int level;
} Position;

queue<Position> q;
Position p;

void reseting() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = 0;
	_count = 0;
}

//int distanc(int start_i, int start_j, int i, int j) {
//	return abs(start_i - i) + abs(start_j - j);
//}

int main()
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++)
	{
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				scanf("%d", &input[i][j]);

		p.i = R;
		p.j = C;
		p.type = input[R][C];
		p.level = 1;
		visited[R][C] = 1;
		q.push(p);

		while (!q.empty()) {
			int ii = q.front().i;
			int jj = q.front().j;
			int type = q.front().type;
			int level = q.front().level;
			q.pop();
			_count++;
			if (L <= level)
				continue;
			for (int k = 0; k < 4; k++) {
				int nextii = ii + d[0][k];
				int nextjj = jj + d[1][k];
				int nextType = input[nextii][nextjj];
				if (nextii >= 0 && nextii < N && nextjj >= 0 && nextjj < M) {
					if (direction[input[ii][jj]][k] && direction[nextType][(k + 2) % 4] && visited[nextii][nextjj] != 1) {
						visited[nextii][nextjj] = 1;
						p.i = nextii;
						p.j = nextjj;
						p.type = nextType;
						p.level = level + 1;
						q.push(p);
					}
				}
			}
		}
		/*for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				if (visited[i][j] == 1 && distanc(R, C, i, j) < L)
					_count++;
			}*/
		printf("#%d %d\n", testCase + 1, _count);
		reseting();
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
