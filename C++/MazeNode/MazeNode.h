#ifndef MAZENODE_H
#define MAZENODE_H


//��ʾÿһ���ڵ�λ�õ��ĸ�����
const int WAY_RIGHT = 0;
const int WAY_DOWN = 1;
const int WAY_LEFT = 2;
const int WAY_UP = 3;
const int WAY_SIZE = 4;

//ÿ�������״̬
const int WAY_YES = 0;
const int WAY_NO = 1;

//�Թ�·���Ľڵ�����
class MazeNode
{
public:
	MazeNode()
	{
		for (int i = 0; i < WAY_SIZE; ++i)
		{
			_wayState[i] = WAY_NO; //�ڵ���ĸ�״̬��ʼ��Ϊ������
		}
	}
	int GetWayState(int way)//���ظýڵ��ĸ������״̬
	{
		return _wayState[way];
	}
	void SetNodeState(int way, int state)//�����ĸ������״̬
	{
		_wayState[way] = state;
	}
	void SetNode(int val, int x,int y)//ȷ���ڵ�����
	{
		_val = val;
		_x = x;
		_y = y;
	}
	int Getvalue()const
	{
		return _val;
	}
	int GetX()const
	{
		return _x;
	}
	int GetY()const
	{
		return _y;
	}
private:
	//��ʾ�ýڵ������λ��
	int _x;
	int _y;
	int _val;
	//�洢�ڵ��ĸ������״̬
	int _wayState[WAY_SIZE];
};

#endif