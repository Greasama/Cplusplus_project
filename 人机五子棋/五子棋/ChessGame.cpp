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
		//��������
		man->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
		//AI����
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
	}
}
