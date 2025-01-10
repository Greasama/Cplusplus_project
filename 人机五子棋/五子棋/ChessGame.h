#pragma once
#include"Man.h"
#include"Ai.h"
#include"Chess.h"


class ChessGame
{
public:
	ChessGame(Man* man, Ai* ai, Chess* chess);
	void play();//启动对局

	//添加数据成员
private:
	Man* man;
	Ai* ai;
	Chess* chess;
};

