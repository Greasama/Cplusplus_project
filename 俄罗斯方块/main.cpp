//block表示方块类，game表示俄罗斯方块游戏
//各个模块的主要接口
//自动下落有问题要优化

#include "game.h"
int main(void)
{
	game games(20,10,263,97,36);//像素计算得到的数字,方块位置263-97（上方多一排，可再调）
	games.play();
	return 0;
}