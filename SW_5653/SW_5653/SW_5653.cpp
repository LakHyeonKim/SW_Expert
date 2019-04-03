// SW_5653.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef struct CELL {
	int i;
	int j;
	int vitality;
	int activation;
	int Inactive;
	bool death;
} Cell;

int T, N, M, K;
int map[1001][1001];
int direction[2][4] = { {0, 1, 0, -1}, {1, 0, -1, 0} };


int main()
{
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase) {
		scanf("%d %d %d", &N, &M, &K);
		vector<Cell> inact;
		vector<Cell> act;
		int hStart = 500 - (N / 2), hEnd = 500 + (N / 2) + (N % 2);
		int wStart = 500 - (M / 2), wEnd = 500 + (M / 2) + (M % 2);
		for (int i = hStart; i < hEnd; i++) {
			for (int j = wStart; j < wEnd; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] != 0) {
					Cell c;
					c.i = i; c.j = j;
					c.vitality = map[i][j];
					c.activation = c.vitality;
					c.Inactive = c.vitality;
					c.death = false;
					inact.push_back(c);
				}
			}
		}		
		for (int time = 0; time < K; time++) {
			for (int i = 0; i < inact.size(); i++) // 비활성상태 -> 활성상태로 바뀌는 녀석들 확인
			{
				inact.at(i).Inactive--;
				if (inact.at(i).Inactive == 0) {
					vector<Cell>::iterator iter = inact.begin();
					act.push_back(inact.at(i));
					inact.erase(iter + i);
				}
			}
			for (int i = 0; i < act.size(); i++) {
				Cell c;
				act.at(i).activation--;
				if (act.at(i).activation == 0) {

				}
			}




		}
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
