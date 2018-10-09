// 컴퓨터공학부 20151235 최동헌
// 개인 프로젝트 : 지뢰찾기

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <process.h>
using namespace std;

#define ROW 9
#define COL 9
#define MINE 44
#define FLAG 20
#define EMPTY 0
#define BOX 10
#define MINE_NUM 10

int map[ROW][COL];
int mine[ROW][COL];
int win = 0;

class Make_Map {
private:
public:
	void Print_Map() {              //기본 맵 형성
		cout << "\n\n\n*************MINESWEEPER***************\n\n" << endl;
		cout << "     1  2  3  4  5  6  7  8  9  " << endl;
		cout << "--------------------------------" << endl;

		for (int i = 0; i < ROW; i++) {
			cout << i + 1 << " l";
			for (int j = 0; j < COL; j++) {
				if (map[i][j] == BOX) {
					cout.width(2);
					cout << " ■";
				}
				else if (map[i][j] == MINE) {
					cout.width(2);
					cout << " ※";
				}
				else if (map[i][j] == FLAG) {
					cout.width(2);
					cout << " ▷";
				}
				else if (map[i][j] == EMPTY) {
					cout.width(2);
					cout << "  0";
				}
				else {
					cout.width(2);
					cout << "  " << map[i][j];
				}
			}

			cout << "\n";
		}

		cout << "---------------------------------" << endl;
	}

	void Set_Mine() {                    //지뢰 생성
		srand((unsigned)time(NULL));
		int mine_num = MINE_NUM;
		int check_num = 0;
		int r, s = 0;

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				map[i][j] = BOX;
			}
		}

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				mine[i][j] = 0;
			}
		}

		while (check_num != MINE_NUM) {         //지뢰 개수만큼 무작위 위치에 생성
			r = rand() % 9;
			s = rand() % 9;
			if (mine[r][s] != MINE) {
				mine[r][s] = MINE;
				check_num++;
			}

		}
	}
};

class Check {
private:
public:
	void Mine_Zero(int x, int y) {             //선택한 좌표 주변 지뢰가 없을 때
		int mine_num = 0;

		for (int a = x - 1; a <= x + 1; a++) {                 //선택한 좌표 주변 표시 (지뢰가 있는지 숫자로 표시)
			for (int b = y - 1; b <= y + 1; b++) {

				if (a >= 0 && b >= 0 && a < ROW && b < ROW) {

					for (int i = a - 1; i <= a + 1; i++) {
						for (int j = b - 1; j <= b + 1; j++) {

							if (i >= 0 && j >= 0 && i < ROW && j < ROW) {
								if (mine[i][j] == MINE)
									mine_num++;
							}
						}
					}
					if (map[a][b] != FLAG) {         //깃발 아닌 경우에만
						map[a][b] = mine_num;
						mine_num = 0;
					}
				}
			}
		}
	}

	void Open_Box(int x, int y) {
		int mine_num = 0;
		Check a;

		for(int i = x-1; i <= x+1; i++){              //주변 지뢰 갯수
			for (int j = y - 1; j <= y + 1; j++) {
				if (i >= 0 && j >= 0 && i < ROW && j < COL) {
					if (mine[i][j] == MINE)
						mine_num++;
				}
			}
		}
		map[x][y] = mine_num;

		if (mine_num == 0) {               //주변에 지뢰가 없을때
			a.Mine_Zero(x, y);
		}
	}

	void Flag(int x, int y) {          //깃발 설정
		if (map[x][y] == FLAG) {         //이미 깃발 있을 때 제거
			map[x][y] = BOX;
		}
		else {
			map[x][y] = FLAG;                //깃발 생성
			if (mine[x][y] == MINE)
				win++;
		} 
	}
};

class Game_Set : public Make_Map {
private:
public:
	void Game_Over(int &a, int &b) {
		int k = 0;

		for (int i = 0; i < ROW; i++) {         //지뢰 걸렸을 때 지뢰 위치 모두 표시
			for (int j = 0; j < COL; j++) {
				if (mine[i][j] == MINE)
					map[i][j] = MINE;
			}
		}

		Print_Map();
		cout << "쀍! 지뢰에 걸렸습니다! 게임 종료(0), 다시 시작(1)" << endl;
		cout << "입력 : ";
		cin >> k;

		while (k != 0 && k != 1) {
			cout << "앗! 숫자를 다시 입력해주세요!" << endl;
			cout << "입력 : ";
			cin >> k;
		}

		if (k == 0) {
			a = 1;
			b = 1;    //restart, reset 1로 만들어 종료
		}
		else if (k == 1) {
			b = 1;       //reset만 1로 만들어 다시 시작
		}

		system("cls");
	}

	void Reset(int &a) {
		a = 1; //reset
	}

	void Game_Win(int &a, int &b) {
		int k = 0;

		Print_Map();
		cout << "게임에 승리하셨습니다! 게임 종료(0), 다시 시작(1)" << endl;
		cout << "입력 : ";
		cin >> k;

		while (k != 0 && k != 1) {
			cout << "숫자를 다시 입력해주세요!" << endl;
			cout << "입력 : ";
			cin >> k;
		}

		if (k == 0) {
			a = 1;
			b = 1;    //restart, reset 1로 만들어 종료
		}
		else if (k == 1) {
			b = 1;       //reset만 1로 만들어 다시 시작
		}

		system("cls");
	}
};

int main() {

	int x, y, select = 0;
	int restart = 0;
	Make_Map Map;
	Check check;
	Game_Set Over;

	while (!restart) {
		Map.Set_Mine();
		int reset = 0;

		while (!reset) {
			Map.Print_Map();

			cout << "입력방법 : (1:OPEN 2:깃발 설치/제거 3:게임 재실행) (가로 좌표) (세로 좌표) ex) 1 3 2" << endl;
			cout << "            게임 재실행 시에는 3 1 1 입력" << endl;
			cout << "입력 : ";
			cin >> select >> x >> y;

			if (x < 1 || x>9 || y < 1 || y>9 || select < 1 || select>3)
				select = 0;

			system("cls");

			switch (select)
			{
			case 1:       
				if (map[x - 1][y - 1] == FLAG) {         //입력 좌표가 깃발인 곳일때
					cout << "＃＃＃깃발 있는 곳은 열 수 없습니다.＃＃＃" << endl;
					break;
				}
				else if(mine[x - 1][y - 1] == MINE) {       //입력 좌표가 지뢰일때
					Over.Game_Over(restart, reset);
					break;
				}
				else if (map[x - 1][y - 1] != BOX) {           //입력 좌표가 이미 열려있을 때
					cout << "＃＃＃이미 열려있습니다.＃＃＃" << endl;
					break;
				}
				check.Open_Box(x - 1, y - 1);            //입력 좌표 빈칸일 때 오픈
				if (win == MINE_NUM)                //게임 승리
					Over.Game_Win(restart, reset);
				break;
			case 2:                               //깃발 설정
				check.Flag(x - 1, y - 1);
				if (win == MINE_NUM)
					Over.Game_Win(restart, reset);
				break;
			case 3:        //리셋
				Over.Reset(reset);
				break;
			default:    
				cout << "＃＃＃잘못 입력하였습니다. 다시 입력해주세요.＃＃＃" << endl;
				break;
			}
		}
	}
}