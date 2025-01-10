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
	//�����������
	srand(time(NULL));
	//��������
	initgraph(938, 896);
	//���ر���ͼƬ
	loadimage(&imgBg, "res/bg2.png");

	loadimage(&imgWin, "res/win.png");
	loadimage(&imgWin, "res/win.png");

	//��ʼ����Ϸ������
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
	//��ʼ����߷�
	ifstream file(RECORDER_FILE);
	if (!file.is_open()) {
		cout << RECORDER_FILE << "��ʧ��" << endl;
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
		//�����û�����
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();//���齵��
			//��Ⱦ��Ϸ����
			update = true;
		}
		if (update)
		{
			update = false;
			//������Ϸ�Ļ���
			updateWindow();
			//������Ϸ���ݣ�������
			clearLine();
		}

		if (gameOver)
		{
			//�������
			saveScore();

			//������Ϸ��������
			displayOver();
			system("pause");
			init();//���¿���

		}
	}
}

void game::keyEvent()
{
	//update = true;(���ڿɼ��¼�)
	unsigned char ch;
	bool rotateFlag = false;
	int dx = 0;
	if (_kbhit)//�ж����ް�������
	{
		ch = _getch();
		//������·�������Զ����������ַ�����up->224 72;dowm->224 80;letf->224 75;ringht->224 77��
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
		//��ת
	}

	if (dx != 0)
	{
		moveLeftRight(dx);
		update = true;
		//ƽ��
	}
}






void game::updateWindow()
{
	putimage(0, 0, &imgBg);//���Ʊ���ͼƬ

	//����
	//block block; 
	//block.draw(leftMargin, topMargin);

	//vector����
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

	drawScore();//���Ʒ���

	EndBatchDraw();//�����˸
}

int game::getDelay()
{
	static unsigned long long lastTime = 0;

	unsigned long long currentTime = GetTickCount();
	//��һ�ε��ã���0
	//���ؾ����ϴε��ã��������ms
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
	//���ٽ��ֹͣ�½�
	block bakblock = *curblock;
	curblock->drop();
	//�½����޵��ж�
	if (!curblock->blockInMap(map)) {
		//�̶�����
		bakblock.solidify(map);
		delete curblock;
		curblock = nextblock;
		nextblock = new block;
		//�����Ϸ����
		checkOver();
	}
	delay = SPEED_NORMAL[level - 1];
}

void game::clearLine()
{
	int lines = 0;
	int k = rows - 1;//�洢��
	for (int i = rows - 1; i >= 0; i--)
	{
		//�����?
		int count = 0;
		for (int j = 0; j<cols;j++) 
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];//һ��ɨ��һ�ߴ洢
		}
		if (count < cols)//����
		{
			k--;//�ع�
		}
		else//����
		{
			lines++;
		}
	}
	if (lines > 0)
	{
		//����÷�
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		mciSendString("olay res/xiaochu1.mp3", 0, 0, 0);
		update = true;
		//����ÿ100��һ��
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
	f.lfQuality = ANTIALIASED_QUALITY;//�����
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName),_T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	outtextxy(670,727,scoreText);
	//������
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWidth * strlen(scoreText);
	outtextxy(xPos, 817, scoreText);
	//�ؿ�
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
	//�ж�ʤ��
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
