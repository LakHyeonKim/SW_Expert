// SW_4014.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <math.h>

int T, N, X, result;
int input[21][21];
int wOverlapCheck[21];
int hOverlapCheck[21];

int main() {
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d %d", &N, &X);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf("%d", &input[i][j]);

		for (int i = 1, wRight = 0, wLeft = 0, hRight = 0, hLeft = 0; i <= N; i++, wRight = 0, wLeft = 0, hRight = 0, hLeft = 0) {
			for (int j = 1; j < N; j++) {
				int width = input[i][j] - input[i][j + 1];
				int height = input[j][i] - input[j + 1][i];
				int wRightFlag = 0, wLeftFlag = 0, hRightFlag = 0, hLeftFlag = 0;
				if (width == 1) {
					for (int k = 1, firstValue = 0; k <= X; k++) {
						if (j + k > N) { wRightFlag = 1; break; }
						if (k == 1) { firstValue = input[i][j + k]; }
						else if (firstValue != input[i][j + k]) { wRightFlag = 1; }
					}
					if (wRightFlag == 0) {
						for (int k = 1; k <= X; k++)
							wOverlapCheck[j + k] = 1;
						wRight += 1;
					}
					else wRight = -1234;
				}
				else if (width == -1) {
					for (int k = 0, firstValue = 0; k < X; k++) {
						if (j - k < 1) { wLeftFlag = 1; break; }
						if (k == 0) { firstValue = input[i][j - k]; }
						else if (firstValue != input[i][j - k] || wOverlapCheck[j - k]) { wLeftFlag = 1; }
					}
					if (wLeftFlag == 0) wLeft += 1;
					else wLeft = -1234;
				}
				else if (abs(width) > 1) {
					wRight = -1234; wLeft = -1234;
				} 

				if (height == 1) {
					for (int k = 1, firstValue = 0; k <= X; k++) {
						if (j + k > N) { hRightFlag = 1; break; }
						if (k == 1) { firstValue = input[j + k][i]; }
						else if (firstValue != input[j + k][i]) { hRightFlag = 1; }
					}
					if (hRightFlag == 0) {
						for (int k = 1; k <= X; k++)
							hOverlapCheck[j + k] = 1;
						hRight += 1;
					}
					else hRight = -1234;
				}
				else if (height == -1) {
					for (int k = 0, firstValue = 0; k < X; k++) {
						if (j - k < 1) { hLeftFlag = 1; break; }
						if (k == 0) { firstValue = input[j - k][i]; }
						else if (firstValue != input[j - k][i] || hOverlapCheck[j - k]) { hLeftFlag = 1; }
					}
					if (hLeftFlag == 0) hLeft += 1;
					else hLeft = -1234;
				}
				else if (abs(height) > 1) {
					hRight = -1234; hLeft = -1234;
				}
			}
			memset(wOverlapCheck, 0, sizeof(wOverlapCheck));
			memset(hOverlapCheck, 0, sizeof(hOverlapCheck));
			if (wRight >= 0 && wLeft >= 0) result++;
			if (hRight >= 0 && hLeft >= 0) result++;
		}

		printf("#%d %d\n", testCase + 1, result);
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
