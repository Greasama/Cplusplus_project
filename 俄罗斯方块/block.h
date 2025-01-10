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
	void drop();//����
	void moveLR(int offset);//�����ƶ�
	void rotate();//��ת
	void draw(int leftMargin,int topMargin);//����߽�
	static IMAGE** getImages();
	block& operator=(const block& other);

	bool blockInMap(const vector<vector<int>>&map);
	/*Point* getSmallBlocks();*/
	void solidify(vector<vector<int>>&map);
	int getBlockType();
	

private:
	int blockType;//��������
	Point smallBlocks[4];
	IMAGE *img;//ָ���ʾָ�򷽿飨��ͬȥ�أ�

	static IMAGE* imgs[7];
	static int size;//ͼƬ��С
};

