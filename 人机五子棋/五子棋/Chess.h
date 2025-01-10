#pragma once
#include<graphics.h>//easyx图形库
#include<vector>
using namespace std;

//落子位置
struct ChessPos
{
	int row;
	int col;
	ChessPos(int r = 0,int c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();//棋盘初始化：加载图片资源，初始化相关数据
	
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos* pos, chess_kind_t kind);
	//判定坐标，确认是否有效
	void chessDown(ChessPos *pos, int val);//在棋盘的指定位置，落子
	int getGradeSize();//获取棋盘大小
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);//获取指定位置黑棋/白棋/空
	bool checkOver();//检查棋局是否结束

private:
	IMAGE chessBlackImg;//黑棋棋子
	IMAGE chessWhiteImg;//白棋棋子
	
	int gradeSize;//棋盘大小（12，15，17，19）
	int margin_x;//棋盘的左侧边界
	int margin_y;//棋盘的顶部边界
	float chessSize;//棋子大小（棋盘方格大小）
	
	vector<vector<int>> chessMap;//存储当前棋局棋子分布数据
	//chessMap[3][5]表示第三行第五列落子情况，0：空白，1：黑子，-1：白子

	void updateGameMap(ChessPos* pos);//更新落子数据

	bool playerFlag;//判断谁落子，true：黑子，false：白子

	ChessPos lastPos;

	bool checkWin();//胜负已分返回true，否则返回false

};

