#include "ChessGame.h"

ChessGame::ChessGame(Man* man, Ai* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

void ChessGame::play()
{
	chess->init();
	while (1)
	{
		//棋手先行
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
		//AI后行
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
	}
}
