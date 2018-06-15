#ifndef MAZENODE_H
#define MAZENODE_H


//表示每一个节点位置的四个方向
const int WAY_RIGHT = 0;
const int WAY_DOWN = 1;
const int WAY_LEFT = 2;
const int WAY_UP = 3;
const int WAY_SIZE = 4;

//每个方向的状态
const int WAY_YES = 0;
const int WAY_NO = 1;

//迷宫路径的节点类型
class MazeNode
{
public:
	MazeNode()
	{
		for (int i = 0; i < WAY_SIZE; ++i)
		{
			_wayState[i] = WAY_NO; //节点的四个状态初始化为不能走
		}
	}
	int GetWayState(int way)//返回该节点四个方向的状态
	{
		return _wayState[way];
	}
	void SetNodeState(int way, int state)//设置四个方向的状态
	{
		_wayState[way] = state;
	}
	void SetNode(int val, int x,int y)//确定节点坐标
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
	//表示该节点的坐标位置
	int _x;
	int _y;
	int _val;
	//存储节点四个方向的状态
	int _wayState[WAY_SIZE];
};

#endif