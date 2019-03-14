// SW_5644.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 2019.3.14


#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstring>

typedef struct POINT {
	int x;
	int y;
} Point;

typedef struct BC_IMFORMATION {
	Point point;
	int c;
	int p;
} BC_Information;

int test_Case;
int move;
int count_BC;
int d[2][5] = { {0, 0, 1, 0, -1},  // x
				{0, -1, 0, 1, 0}}; // y
int A_Move_Information[101];
int B_Move_Information[101];
BC_Information BC_list[8];
int A_BC_Check[8];
int B_BC_Check[8];
int max;
int result;

int main()
{
	Point A;
	Point B;
	
	scanf("%d", &test_Case);
	for (int t = 0; t < test_Case; t++)
	{
		scanf("%d %d", &move, &count_BC);
		for (int i = 1; i <= move; i++)
			scanf("%d", &A_Move_Information[i]);
		for (int i = 1; i <= move; i++)
			scanf("%d", &B_Move_Information[i]);
		for (int i = 0; i < count_BC; i++) {
			scanf("%d %d %d %d", &BC_list[i].point.x, &BC_list[i].point.y, &BC_list[i].c, &BC_list[i].p);
		}
			

		A.x = 1; A.y = 1;
		B.x = 10; B.y = 10;

		for (int i = 0; i <= move; i++) {
			memset(A_BC_Check, 0, sizeof(int) * 8);
			memset(B_BC_Check, 0, sizeof(int) * 8);
			A.x += d[0][A_Move_Information[i]];
			A.y += d[1][A_Move_Information[i]];
			B.x += d[0][B_Move_Information[i]];
			B.y += d[1][B_Move_Information[i]];


			for (int j = 0; j < count_BC; j++) {
				int A_abs = abs(A.x - BC_list[j].point.x) + abs(A.y - BC_list[j].point.y);
				int B_abs = abs(B.x - BC_list[j].point.x) + abs(B.y - BC_list[j].point.y);
				if (BC_list[j].c >= A_abs)
					A_BC_Check[j] = BC_list[j].p;
				if (BC_list[j].c >= B_abs)
					B_BC_Check[j] = BC_list[j].p;
			}
			
			for (int j = 0; j < count_BC; j++) {  // check!!!
				for (int k = 0; k < count_BC; k++) {
					if (j == k && A_BC_Check[j] == B_BC_Check[k] && (A_BC_Check[j] + B_BC_Check[k])) {
						if (max < A_BC_Check[j])
							max = A_BC_Check[j];
					}
					else if (max < A_BC_Check[j] + B_BC_Check[k])
						max = A_BC_Check[j] + B_BC_Check[k];
				}
			}
			/* printf("A :(%d, %d), B:(%d, %d) ", A.x, A.y, B.x, B.y);
			for (int j = 0; j < count_BC; j++) {
				if (j == 0)
					printf("A_BC_Check: ");
				printf("%d ", A_BC_Check[j]);
			}
			printf("  ");
			for (int j = 0; j < count_BC; j++) {
				if (j == 0)
					printf("B_BC_Check: ");
				printf("%d ", B_BC_Check[j]);
			}
			printf("(T = %d): max => %d \n",i ,max);*/
			result += max;
			max = 0;
		}
		printf("#%d %d\n",t+1, result);
		result = 0;
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
