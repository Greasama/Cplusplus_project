#include "Ai.h"

void Ai::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int> row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void Ai::calculateScore()
{
	int personNum = 0;//���ַ������ж��ٸ�����
	int aiNum = 0;//AI���ж��ٸ���������
	int emptyNum = 0;//�÷���հ�λ�ĸ���

	//����������������
	for (int i = 0; i < scoreMap.size(); i++)//����
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			
			//��ÿ������м���
			if (chess->getChessData(row, col)) continue;
			for (int y = -1; y <= 0; y++) 
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0)continue;
					if (y == 0 && x != 1)continue;

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					//��������ڸ�λ������
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//�����������
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//����
					if (personNum == 1)
					{
						//����2����10��10
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2)
					{
						if (emptyNum == 1)
						{
							//����3����20��25
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2)
						{
							//����3����40��50
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3)
					{
						if (emptyNum == 1)
						{
							//����4����60��55
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2)
						{
							//����4����200��10000
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4)
					{
						//����4����20000��30000��Ӯ�壩
						scoreMap[row][col] += 20000;
					}
					emptyNum = 0;

					//��������ڸ�λ������
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//�����������
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//����
					if (aiNum == 0)
					{
						scoreMap[row][col] += 5;
					}
					if (aiNum == 1)
					{
						//����2����10��10
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2)
					{
						if (emptyNum == 1)
						{
							//����3����20��25
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2)
						{
							//����3����40��50
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1)
						{
							//����4����60��55
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2)
						{
							//����4����200��10000
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum == 4)
					{
						//����4����20000��30000��Ӯ�壩
						scoreMap[row][col] += 30000;
					}
				}
			}

		}
	}
}

ChessPos Ai::think()
{
	calculateScore();
	vector<ChessPos>maxPoints;
	int max = 0;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col) == 0)
			{
				if (scoreMap[row][col] > max)
				{
					max = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == max)
				{
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}

void Ai::go()
{
	ChessPos pos = think();
	Sleep(1200);//˼��ʱ��ģ��
	chess->chessDown(&pos, CHESS_WHITE);
}
