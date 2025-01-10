#pragma once
#include<vector>
#include<graphics.h>//easyX
using namespace std;

struct Point
{
	int row;
	int col;
};

class block
{
public:
	block();
	void drop();//下落
	void moveLR(int offset);//左右移动
	void rotate();//旋转
	void draw(int leftMargin,int topMargin);//方块边界
	static IMAGE** getImages();
	block& operator=(const block& other);

	bool blockInMap(const vector<vector<int>>&map);
	/*Point* getSmallBlocks();*/
	void solidify(vector<vector<int>>&map);
	int getBlockType();
	

private:
	int blockType;//方块类型
	Point smallBlocks[4];
	IMAGE *img;//指针表示指向方块（相同去重）

	static IMAGE* imgs[7];
	static int size;//图片大小
};

