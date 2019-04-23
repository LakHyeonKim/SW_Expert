// SW_5648.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/* 정답 알고리즘 */

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

typedef struct ATOM {  //원자 정보(좌표, 나아가는 방향, 에너지)
	int x;
	int y;
	int direction;
	int energy;
} Atom;

typedef struct RELATION {
	int firstAtom;
	int secondAtom;
	int distenc;
} Relation;

using namespace std;

bool compare(Relation a, Relation b) {
	return a.distenc < b.distenc;
}

int main() {
	int T, N;
	scanf("%d", &T);
	for (int testCase = 0; testCase < T; testCase++) {
		scanf("%d", &N);
		Atom atomList[1000];
		int atomCT[1001] = { 0, };
		vector<Relation> relationList;
		bool check[1000] = { false, };
		int sumEnergy = 0;
		for (int i = 0; i < N; i++) {  // 입력 부분
			Atom atom;
			scanf("%d %d %d %d", &atom.x, &atom.y, &atom.direction, &atom.energy);
			atomList[i] = atom;
		}
		for (int i = 0; i < N - 1; i++) {
			for (int j = i + 1; j < N; j++) {
				Relation r;
				if (atomList[i].y == atomList[j].y && ((atomList[i].direction == 2 && atomList[j].direction == 3 && atomList[i].x > atomList[j].x) || (atomList[i].direction == 3 && atomList[j].direction == 2 && atomList[i].x < atomList[j].x))) {
					r.distenc = abs(atomList[i].x - atomList[j].x);
					r.firstAtom = i;
					r.secondAtom = j;					
					relationList.push_back(r);
				}
				else if (atomList[i].x == atomList[j].x && ((atomList[i].direction == 0 && atomList[j].direction == 1 && atomList[i].y < atomList[j].y) || (atomList[i].direction == 1 && atomList[j].direction == 0 && atomList[i].y > atomList[j].y))) {
					r.distenc = abs(atomList[i].y - atomList[j].y);
					r.firstAtom = i;
					r.secondAtom = j;					
					relationList.push_back(r);
				}
				else if (abs(atomList[i].x - atomList[j].x) == abs(atomList[i].y - atomList[j].y)) {
					if (atomList[i].direction == 0 && ((atomList[j].direction == 2 && atomList[i].x < atomList[j].x) || (atomList[j].direction == 3 && atomList[i].x > atomList[j].x)) && atomList[i].y < atomList[j].y) {
						r.distenc = abs(atomList[i].x - atomList[j].x) * 2;
						r.firstAtom = i;
						r.secondAtom = j;						
						relationList.push_back(r);
					}
					else if (atomList[i].direction == 1 && ((atomList[j].direction == 2 && atomList[i].x < atomList[j].x) || (atomList[j].direction == 3 && atomList[i].x > atomList[j].x)) && atomList[i].y > atomList[j].y) {
						r.distenc = abs(atomList[i].x - atomList[j].x) * 2;
						r.firstAtom = i;
						r.secondAtom = j;						
						relationList.push_back(r);
					}
					else if (atomList[i].direction == 2 && ((atomList[j].direction == 0 && atomList[i].y > atomList[j].y) || (atomList[j].direction == 1 && atomList[i].y < atomList[j].y)) && atomList[i].x > atomList[j].x) {
						r.distenc = abs(atomList[i].x - atomList[j].x) * 2;
						r.firstAtom = i;
						r.secondAtom = j;						
						relationList.push_back(r);
					}
					else if (atomList[i].direction == 3 && ((atomList[j].direction == 0 && atomList[i].y > atomList[j].y) || (atomList[j].direction == 1 && atomList[i].y < atomList[j].y)) && atomList[i].x < atomList[j].x) {
						r.distenc = abs(atomList[i].x - atomList[j].x) * 2;
						r.firstAtom = i;
						r.secondAtom = j;						
						relationList.push_back(r);
					}
				}
			}
		}
		sort(relationList.begin(), relationList.end(), compare);

		for (int i = 0; i < (int)relationList.size(); i++) {
			if (!check[relationList[i].firstAtom] && !check[relationList[i].secondAtom]) {
				sumEnergy += atomList[relationList[i].firstAtom].energy;
				sumEnergy += atomList[relationList[i].secondAtom].energy;
				check[relationList[i].firstAtom] = true;
				check[relationList[i].secondAtom] = true;
				atomCT[relationList[i].firstAtom] = relationList[i].distenc;
				atomCT[relationList[i].secondAtom] = relationList[i].distenc;
			}
			else if (check[relationList[i].firstAtom] && !check[relationList[i].secondAtom] && atomCT[relationList[i].firstAtom] == relationList[i].distenc) {
				sumEnergy += atomList[relationList[i].secondAtom].energy;
				check[relationList[i].secondAtom] = true;
				atomCT[relationList[i].secondAtom] = relationList[i].distenc;
			}
			else if (!check[relationList[i].firstAtom] && check[relationList[i].secondAtom] && atomCT[relationList[i].secondAtom] == relationList[i].distenc) {
				sumEnergy += atomList[relationList[i].firstAtom].energy;
				check[relationList[i].firstAtom] = true;
				atomCT[relationList[i].firstAtom] = relationList[i].distenc;
			}
		}
		printf("#%d %d\n", testCase + 1, sumEnergy);
	}
}

/* 틀린 부분(단순하게 터진 원자만 체크를 하는것이 아니라 해당 원자가 터지기 전까지 이동거리를 비교하여야함)*/

//		for (int i = 0; i < (int)relationList.size(); i++) { // 충돌 여부 판단
//			if (i == 0) {
//		f		sumEnergy += atomList[relationList[i].firstAtom].energy;
//				sumEnergy += atomList[relationList[i].secondAtom].energy;
//				check[relationList[i].firstAtom] = true;
//				check[relationList[i].secondAtom] = true;
//			}
//			else if (relationList[i - 1].distenc == relationList[i].distenc) {
//				if (check[relationList[i].firstAtom] && check[relationList[i].secondAtom]) continue;
//				if (check[relationList[i].firstAtom]) {
//					if (atomList[relationList[i].firstAtom].x == atomList[relationList[i].secondAtom].x || atomList[relationList[i].firstAtom].y == atomList[relationList[i].secondAtom].y)
//						continue;
//					sumEnergy += atomList[relationList[i].secondAtom].energy;
//				}
//				else if (check[relationList[i].secondAtom]) {
//					if (atomList[relationList[i].firstAtom].x == atomList[relationList[i].secondAtom].x || atomList[relationList[i].firstAtom].y == atomList[relationList[i].secondAtom].y)
//						continue;
//					sumEnergy += atomList[relationList[i].firstAtom].energy;
//				}
//				else {
//					sumEnergy += atomList[relationList[i].firstAtom].energy;
//					sumEnergy += atomList[relationList[i].secondAtom].energy;
//				}
//				check[relationList[i].firstAtom] = true;
//				check[relationList[i].secondAtom] = true;
//			}
//			else {
//				if (!check[relationList[i].firstAtom] && !check[relationList[i].secondAtom]) {
//					sumEnergy += atomList[relationList[i].firstAtom].energy;
//					sumEnergy += atomList[relationList[i].secondAtom].energy;
//					check[relationList[i].firstAtom] = true;
//					check[relationList[i].secondAtom] = true;
//				}
//			}
//			printf("%d ", relationList[i].distenc);
//		}
//		printf("#%d %d\n", testCase + 1, sumEnergy);
//	}
//}

/* 정답은 맞지만 시간초과 */

//#include "pch.h"
//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <list>
//#include <unordered_map>
//
//using namespace std;
//
//typedef struct ATOM { //원자 정보(좌표, 나아가는 방향, 에너지)
//	int x;
//	int y;
//	int direction;
//	int energy;
//} Atom;
//
//int T, N; //T: 테스트 케이스, N: 초기 원자 개수
//int d[2][4] = { { 0, 0, -1, 1 },{ -1, 1, 0, 0 } }; // d[0]: x, d[1]: y;
//
//void convert(int *x, int *y) { //좌표변환 함수(-1000 <= x,y <= 1000 좌표를 0 <= x,y <= 4000 범위로 변환)
//	int _x = (*x), _y = (*y);
//	_x = 2 * _x + 2000;
//	_y = -2 * _y + 2000;
//	(*x) = _x; (*y) = _y;
//}
//
//int makeKey(int x, int y) { // hash_map: key 값 생성 (x,y)좌표를 겹치지 않는 1개의 값으로 변환
//	return y * 4001 + x;    // 2차원 배열을 1차월 배열로 표현하면 좌표 인덱스 값을 1개 값으로 표현가능
//}
//
//bool checkRange(int x, int y) { // 나가는 범위 체크 (범위를 나가면 아무리 시간흘러도 만날 일이 없음)
//	if (x >= 0 && x <= 4000 && y >= 0 && y <= 4000)
//		return true;
//	else
//		return false;
//}
//int main()
//{
//	scanf("%d", &T);
//	for (int testCase = 0; testCase < T; testCase++) {
//		unordered_map< int, Atom > mapAtoms;
//		unordered_map< int, Atom > tempMapAtoms;
//		int sumEnergy = 0;
//		scanf("%d", &N);
//		for (int i = 0; i < N; i++) {// 입력 부분
//			int x, y, d, e;
//			Atom atom;
//			scanf("%d %d %d %d", &x, &y, &d, &e);
//			convert(&x, &y);
//			atom.x = x;
//			atom.y = y;
//			atom.direction = d;
//			atom.energy = e;
//			mapAtoms.insert(unordered_map< int, Atom >::value_type(makeKey(atom.x, atom.y), atom));
//		}
//		while (!mapAtoms.empty()) {
//			list< unordered_map< int, Atom >::iterator > overLapIter; // 중복 되는 곳(원자소멸상황)의 iterator
//			unordered_map< int, Atom >::iterator iter;
//			for (iter = mapAtoms.begin(); iter != mapAtoms.end(); ++iter) {
//				Atom atom = iter->second;
//				atom.x += d[0][atom.direction]; /* 원자 */
//				atom.y += d[1][atom.direction]; /* 이동 */
//				if (!checkRange(atom.x, atom.y)) continue; // 좌표계 넘어 가는 경우 
//				unordered_map< int, Atom >::iterator findIter = tempMapAtoms.find(makeKey(atom.x, atom.y));
//				if (findIter == tempMapAtoms.end()) { // 중복좌표 찾지 못 한 경우
//					tempMapAtoms.insert(unordered_map< int, Atom >::value_type(makeKey(atom.x, atom.y), atom));
//				}
//				else {                                // 중복좌표 찾은 경우
//					findIter->second.energy += iter->second.energy;
//					list< unordered_map< int, Atom >::iterator >::iterator listIter = find(overLapIter.begin(), overLapIter.end(), findIter);
//					if (listIter == overLapIter.end())
//						overLapIter.push_back(findIter);
//				}
//			}
//			while (!overLapIter.empty()) { // 중복좌표 처리(소멸 에너지 합산)
//				sumEnergy += overLapIter.front()->second.energy;
//				tempMapAtoms.erase(overLapIter.front());
//				overLapIter.pop_front();
//			}
//			mapAtoms.clear();
//			mapAtoms = tempMapAtoms; // ??????? *시간초과 의심 부분* ???????
//			tempMapAtoms.clear();
//		}
//		printf("#%d %d\n", testCase + 1, sumEnergy);
//	}
//}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.





