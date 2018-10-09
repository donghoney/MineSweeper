// ��ǻ�Ͱ��к� 20151235 �ֵ���
// ���� ������Ʈ : ����ã��

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
	void Print_Map() {              //�⺻ �� ����
		cout << "\n\n\n*************MINESWEEPER***************\n\n" << endl;
		cout << "     1  2  3  4  5  6  7  8  9  " << endl;
		cout << "--------------------------------" << endl;

		for (int i = 0; i < ROW; i++) {
			cout << i + 1 << " l";
			for (int j = 0; j < COL; j++) {
				if (map[i][j] == BOX) {
					cout.width(2);
					cout << " ��";
				}
				else if (map[i][j] == MINE) {
					cout.width(2);
					cout << " ��";
				}
				else if (map[i][j] == FLAG) {
					cout.width(2);
					cout << " ��";
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

	void Set_Mine() {                    //���� ����
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

		while (check_num != MINE_NUM) {         //���� ������ŭ ������ ��ġ�� ����
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
	void Mine_Zero(int x, int y) {             //������ ��ǥ �ֺ� ���ڰ� ���� ��
		int mine_num = 0;

		for (int a = x - 1; a <= x + 1; a++) {                 //������ ��ǥ �ֺ� ǥ�� (���ڰ� �ִ��� ���ڷ� ǥ��)
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
					if (map[a][b] != FLAG) {         //��� �ƴ� ��쿡��
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

		for(int i = x-1; i <= x+1; i++){              //�ֺ� ���� ����
			for (int j = y - 1; j <= y + 1; j++) {
				if (i >= 0 && j >= 0 && i < ROW && j < COL) {
					if (mine[i][j] == MINE)
						mine_num++;
				}
			}
		}
		map[x][y] = mine_num;

		if (mine_num == 0) {               //�ֺ��� ���ڰ� ������
			a.Mine_Zero(x, y);
		}
	}

	void Flag(int x, int y) {          //��� ����
		if (map[x][y] == FLAG) {         //�̹� ��� ���� �� ����
			map[x][y] = BOX;
		}
		else {
			map[x][y] = FLAG;                //��� ����
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

		for (int i = 0; i < ROW; i++) {         //���� �ɷ��� �� ���� ��ġ ��� ǥ��
			for (int j = 0; j < COL; j++) {
				if (mine[i][j] == MINE)
					map[i][j] = MINE;
			}
		}

		Print_Map();
		cout << "��! ���ڿ� �ɷȽ��ϴ�! ���� ����(0), �ٽ� ����(1)" << endl;
		cout << "�Է� : ";
		cin >> k;

		while (k != 0 && k != 1) {
			cout << "��! ���ڸ� �ٽ� �Է����ּ���!" << endl;
			cout << "�Է� : ";
			cin >> k;
		}

		if (k == 0) {
			a = 1;
			b = 1;    //restart, reset 1�� ����� ����
		}
		else if (k == 1) {
			b = 1;       //reset�� 1�� ����� �ٽ� ����
		}

		system("cls");
	}

	void Reset(int &a) {
		a = 1; //reset
	}

	void Game_Win(int &a, int &b) {
		int k = 0;

		Print_Map();
		cout << "���ӿ� �¸��ϼ̽��ϴ�! ���� ����(0), �ٽ� ����(1)" << endl;
		cout << "�Է� : ";
		cin >> k;

		while (k != 0 && k != 1) {
			cout << "���ڸ� �ٽ� �Է����ּ���!" << endl;
			cout << "�Է� : ";
			cin >> k;
		}

		if (k == 0) {
			a = 1;
			b = 1;    //restart, reset 1�� ����� ����
		}
		else if (k == 1) {
			b = 1;       //reset�� 1�� ����� �ٽ� ����
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

			cout << "�Է¹�� : (1:OPEN 2:��� ��ġ/���� 3:���� �����) (���� ��ǥ) (���� ��ǥ) ex) 1 3 2" << endl;
			cout << "            ���� ����� �ÿ��� 3 1 1 �Է�" << endl;
			cout << "�Է� : ";
			cin >> select >> x >> y;

			if (x < 1 || x>9 || y < 1 || y>9 || select < 1 || select>3)
				select = 0;

			system("cls");

			switch (select)
			{
			case 1:       
				if (map[x - 1][y - 1] == FLAG) {         //�Է� ��ǥ�� ����� ���϶�
					cout << "��������� �ִ� ���� �� �� �����ϴ�.������" << endl;
					break;
				}
				else if(mine[x - 1][y - 1] == MINE) {       //�Է� ��ǥ�� �����϶�
					Over.Game_Over(restart, reset);
					break;
				}
				else if (map[x - 1][y - 1] != BOX) {           //�Է� ��ǥ�� �̹� �������� ��
					cout << "�������̹� �����ֽ��ϴ�.������" << endl;
					break;
				}
				check.Open_Box(x - 1, y - 1);            //�Է� ��ǥ ��ĭ�� �� ����
				if (win == MINE_NUM)                //���� �¸�
					Over.Game_Win(restart, reset);
				break;
			case 2:                               //��� ����
				check.Flag(x - 1, y - 1);
				if (win == MINE_NUM)
					Over.Game_Win(restart, reset);
				break;
			case 3:        //����
				Over.Reset(reset);
				break;
			default:    
				cout << "�������߸� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���.������" << endl;
				break;
			}
		}
	}
}