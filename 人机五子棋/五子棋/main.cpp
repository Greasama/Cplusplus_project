#include<iostream>
#include"ChessGame.h"

int main(void)
{
	Man man;
	Chess chess(13, 44, 43, 67.3);//棋盘图片像素点运算
	Ai ai;
	ChessGame game(&man, &ai, &chess);

	//添加初始界面

	game.play();
	return 0;
}
