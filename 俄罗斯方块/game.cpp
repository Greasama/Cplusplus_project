#include<iostream>
#include "game.h"
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include"block.h"
#include<fstream>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define MAX_LEVEL 5
#define RECORDER_FILE "recorder.txt"

using namespace std;

//const int SPEED_NORMAL = 500;//ms
const int SPEED_NORMAL[MAX_LEVEL] = { 200,150,120,100,80 };
const int SPEED_QUICK = 50;

game::game(int rows, int cols, int left, int top, int blocksize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blocksize;
	for (int i = 0; i < rows; i++)
	{
		vector<int>mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void game::init()
{
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	
	delay = SPEED_NORMAL[0];
	//配置随机种子
	srand(time(NULL));
	//创建窗口
	initgraph(938, 896);
	//加载背景图片
	loadimage(&imgBg, "res/bg2.png");

	loadimage(&imgWin, "res/win.png");
	loadimage(&imgWin, "res/win.png");

	//初始化游戏区数据
	char data[20][10];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}
	score = 0;
	lineCount = 0;
	level = 1;
	//初始化最高分
	ifstream file(RECORDER_FILE);
	if (!file.is_open()) {
		cout << RECORDER_FILE << "打开失败" << endl;
		topScore = 0;
	}
	else {
		file >> topScore;
	}
	file.close();
	gameOver = false;
}

void game::play()
{
	init();

	nextblock = new block;
	curblock = nextblock;
	nextblock = new block;

	int timer = 0;
	while (1)
	{
		//接收用户输入
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();//方块降落
			//渲染游戏界面
			update = true;
		}
		if (update)
		{
			update = false;
			//更新游戏的画面
			updateWindow();
			//更新游戏数据，行消除
			clearLine();
		}

		if (gameOver)
		{
			//保存分数
			saveScore();

			//更新游戏结束界面
			displayOver();
			system("pause");
			init();//重新开局

		}
	}
}

void game::keyEvent()
{
	//update = true;(后期可加事件)
	unsigned char ch;
	bool rotateFlag = false;
	int dx = 0;
	if (_kbhit)//判定有无按键输入
	{
		ch = _getch();
		//如果按下方向键，自动返回两个字符（如up->224 72;dowm->224 80;letf->224 75;ringht->224 77）
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case 72:
				rotateFlag = true;
				break;
			case 80:
				delay = SPEED_QUICK;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (rotateFlag)
	{
		rotate();
		update = true;
		//旋转
	}

	if (dx != 0)
	{
		moveLeftRight(dx);
		update = true;
		//平移
	}
}






void game::updateWindow()
{
	putimage(0, 0, &imgBg);//绘制背景图片

	//测试
	//block block; 
	//block.draw(leftMargin, topMargin);

	//vector可做
	IMAGE** imgs = block::getImages();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0) continue;
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j] - 1]);
		}
	}

	curblock->draw(leftMargin, topMargin);
	nextblock->draw(689, 150);

	drawScore();//绘制分数

	EndBatchDraw();//解决闪烁
}

int game::getDelay()
{
	static unsigned long long lastTime = 0;

	unsigned long long currentTime = GetTickCount();
	//第一次调用，置0
	//返回距离上次调用，间隔多少ms
	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}

}

void game::drop()
{
	//到临界点停止下降
	block bakblock = *curblock;
	curblock->drop();
	//下降界限的判定
	if (!curblock->blockInMap(map)) {
		//固定方块
		bakblock.solidify(map);
		delete curblock;
		curblock = nextblock;
		nextblock = new block;
		//检测游戏结束
		checkOver();
	}
	delay = SPEED_NORMAL[level - 1];
}

void game::clearLine()
{
	int lines = 0;
	int k = rows - 1;//存储行
	for (int i = rows - 1; i >= 0; i--)
	{
		//检测满?
		int count = 0;
		for (int j = 0; j<cols;j++) 
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];//一边扫描一边存储
		}
		if (count < cols)//不满
		{
			k--;//回滚
		}
		else//满行
		{
			lines++;
		}
	}
	if (lines > 0)
	{
		//计算得分
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		mciSendString("olay res/xiaochu1.mp3", 0, 0, 0);
		update = true;
		//规则：每100分一级
		level = (score + 99) / 100;
		if (level > MAX_LEVEL) {
			gameOver = true;
		}
		lineCount += lines;
	}

}

void game::moveLeftRight(int offset)
{
	block bakblock = *curblock;
	curblock->moveLR(offset);
	if (!curblock->blockInMap(map))
	{
		*curblock = bakblock;
	}
}

void game::rotate()
{
	if (curblock->getBlockType() == 7)
		return;
	block bakblock = *curblock;
	curblock->rotate();
	if (!curblock->blockInMap(map))
	{
		*curblock = bakblock;
	}
}

void game::drawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);

	setcolor(RGB(180, 180, 180));

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName),_T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	outtextxy(670,727,scoreText);
	//消除行
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWidth * strlen(scoreText);
	outtextxy(xPos, 817, scoreText);
	//关卡
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224 - 30, 727, scoreText);
}

void game::checkOver()
{
	gameOver = curblock->blockInMap(map) == false;
}

void game::saveScore()
{
	if (score > topScore)
	{
		topScore = score;
		ofstream file(RECORDER_FILE);
		file << topScore;
		file.close();
	}
}

void game::displayOver()
{
	mciSendString("stop res/bg.mp3", 0, 0, 0);
	//判定胜负
	if (level <= MAX_LEVEL){
		putimage(262, 361, &imgOver);
		mciSendString("stop res/over.mp3", 0, 0, 0);
	}
	else
	{
		putimage(262, 361, &imgWin);
		mciSendString("stop res/win.mp3", 0, 0, 0);
	}
}
