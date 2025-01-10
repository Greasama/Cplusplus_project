#pragma once
#include<graphics.h>
#include<vector>
#include"block.h"
using namespace std;
class game
{
public:
	//���캯��
	game(int rows, int cols, int left, int top, int blocksize);
	void init();//��ʼ��
	void play();
private:
	void keyEvent();
	void updateWindow();
	//���ؾ�����һ�ε��øú������ʱ��
	//��һ�ε��ã�����0
	int getDelay();
	void drop();
	void clearLine();
	void moveLeftRight(int offset);
	void rotate();
	void drawScore();//���Ƶ�ǰ����

	void checkOver();//����Ƿ����
	void saveScore();//�������
	void displayOver();//���½�������

private:
	int delay;
	bool update;//�Ƿ����
	/*int map[��][��];*/
	//0:�հ�  5�������ַ���
	vector<vector<int>>map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	block* curblock;//��ǰ����
	block* nextblock;//Ԥ�淽��
	block* bakblock;//��ǰ���齵������У������ϸ��Ϸ�λ��

	int score;//��ǰ����
	int topScore;
	int level;//��ǰ�ؿ�
	int lineCount;//��ǰ������
	bool gameOver;

	IMAGE imgOver;
	IMAGE imgWin;
};
