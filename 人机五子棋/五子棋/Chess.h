#pragma once
#include<graphics.h>//easyxͼ�ο�
#include<vector>
using namespace std;

//����λ��
struct ChessPos
{
	int row;
	int col;
	ChessPos(int r = 0,int c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();//���̳�ʼ��������ͼƬ��Դ����ʼ���������
	
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos* pos, chess_kind_t kind);
	//�ж����꣬ȷ���Ƿ���Ч
	void chessDown(ChessPos *pos, int val);//�����̵�ָ��λ�ã�����
	int getGradeSize();//��ȡ���̴�С
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);//��ȡָ��λ�ú���/����/��
	bool checkOver();//�������Ƿ����

private:
	IMAGE chessBlackImg;//��������
	IMAGE chessWhiteImg;//��������
	
	int gradeSize;//���̴�С��12��15��17��19��
	int margin_x;//���̵����߽�
	int margin_y;//���̵Ķ����߽�
	float chessSize;//���Ӵ�С�����̷����С��
	
	vector<vector<int>> chessMap;//�洢��ǰ������ӷֲ�����
	//chessMap[3][5]��ʾ�����е��������������0���հף�1�����ӣ�-1������

	void updateGameMap(ChessPos* pos);//������������

	bool playerFlag;//�ж�˭���ӣ�true�����ӣ�false������

	ChessPos lastPos;

	bool checkWin();//ʤ���ѷַ���true�����򷵻�false

};

