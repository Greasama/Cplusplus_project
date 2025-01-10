#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;

}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (1)
	{
		msg = GetMouseMsg();//获取鼠标点击对象
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))//通过chess对象，来调用判断落子是否有效以及落子功能
		{
			break;
		}
	}
	printf("%d,%d\n", pos.row, pos.col);
	chess->chessDown(&pos, CHESS_BLACK);//落子
}
