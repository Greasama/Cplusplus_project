#include "block.h"
#include<stdlib.h>
#include<vector>

IMAGE* block::imgs[7] = { NULL, };
int block::size = 36;

block::block()
{
	if (imgs[0] == NULL)
	{
		//�и�ͼƬ���÷�
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage();//�ָ�������
	}
	int block[7][4] =
	{
		1,3,5,7,//I��
		2,4,5,7,//Z1��
		3,5,4,6,//Z2��
		3,5,4,7,//T��
		2,3,5,7,//L��
		3,5,7,6,//J��
		2,3,4,5,//����
	};
	blockType = 1 + rand() % 7;//1->7������
	//��ʼ��smallBlocks�ṹ����
	for (int i = 0; i < 4; i++)
	{
		int value = block[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];//�����·���
}

void block::drop()
{
	/*for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].row++;
	}*/
	for (auto& block : smallBlocks)
	{
		block.row++;
	}//c++���º���д��
}

void block::moveLR(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].col += offset;
	}
}

void block::rotate()//��ת
{
	Point p = smallBlocks[1];
	for (int i = 0; i < 4; i++)
	{
		Point tmp = smallBlocks[i];
		smallBlocks[i].col = p.col - tmp.row + p.row;//��ת��ʽ�Ƶ�����
		smallBlocks[i].row = p.row + tmp.col - p.col;
	}
}

void block::draw(int leftMargin, int topMargin)
{
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + smallBlocks[i].col * size;
		int y = topMargin + smallBlocks[i].row * size;
		putimage(x, y, img);
	}
}

IMAGE** block::getImages()
{

	return imgs;
}

block& block::operator=(const block& other)
{
	if (this == &other) return *this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) {
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;
}

bool block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++) {
		if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols ||
			smallBlocks[i].row < 0 || smallBlocks[i].row >= rows ||
			map[smallBlocks[i].row][smallBlocks[i].col]){
			return false;
		}
	}
	return true;
}

void block::solidify(vector<vector<int>>&map)
{
	for (int i = 0; i < 4; i++) {
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;//���ñ�ǹ̻�λ��
	}
}

int block::getBlockType()
{
	return blockType;
}
