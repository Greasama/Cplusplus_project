#include<iostream>
#include"ChessGame.h"

int main(void)
{
	Man man;
	Chess chess(13, 44, 43, 67.3);//����ͼƬ���ص�����
	Ai ai;
	ChessGame game(&man, &ai, &chess);

	//��ӳ�ʼ����

	game.play();
	return 0;
}
