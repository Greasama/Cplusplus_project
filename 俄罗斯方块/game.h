#pragma once
#include<graphics.h>
#include<vector>
#include"block.h"
using namespace std;
class game
{
public:
	//构造函数
	game(int rows, int cols, int left, int top, int blocksize);
	void init();//初始化
	void play();
private:
	void keyEvent();
	void updateWindow();
	//返回距离上一次调用该函数间隔时间
	//第一次调用，返回0
	int getDelay();
	void drop();
	void clearLine();
	void moveLeftRight(int offset);
	void rotate();
	void drawScore();//绘制当前分数

	void checkOver();//检测是否结束
	void saveScore();//保存分数
	void displayOver();//更新结束画面

private:
	int delay;
	bool update;//是否更新
	/*int map[列][行];*/
	//0:空白  5：第五种方块
	vector<vector<int>>map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	block* curblock;//当前方块
	block* nextblock;//预告方块
	block* bakblock;//当前方块降落过程中，备份上个合法位置

	int score;//当前分数
	int topScore;
	int level;//当前关卡
	int lineCount;//当前消除行
	bool gameOver;

	IMAGE imgOver;
	IMAGE imgWin;
};
