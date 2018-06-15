#include<iostream>
using namespace std;

#include "MazeNode.h"
#include "Stack.h"

/*
要用OOP语言来解决一个迷宫路径的求解的问题
1.软件运行，提示如下：

输入迷宫路径的行列数(m x n): 5 5
输入迷宫路径：
0 0 0 1 0
0 0 1 0 0
0 0 0 1 0
1 0 0 1 0
1 1 0 0 0
开始寻找迷宫路径...

该迷宫不存在可通信搞的路径！
路径如下：
* * 0 1 0
0 * 1 0 0
0 * 0 1 0
1 * * 1 0
1 1 * * *

要求：0表示可通过的路径，1表示不能走的路径，从左上角入口，
找到一条可通行的路径到右下角，然后进行相应的打印，如上


*/

//迷宫类
class Maze
{
public:
	Maze(int row, int col) :_row(row), _col(col)
	{
		_pMaze = new MazeNode*[row];
		for (int i = 0; i < col; ++i)
		{
			_pMaze[i] = new MazeNode[col];
		}
	}
	void InitMaze();//输入迷宫路径
	void AnalyseMaze();//为0节点设置为能走
	//方法一。解析用户输入的迷宫路径
	void findMazePath();
	//方法二。专门用来寻找迷宫路径的
	void showMazePath();
	//方法三。用来进行打印迷宫路径的
private:
	int _row;
	int _col;
	MazeNode **_pMaze;
	SqStack  _stack;
};
void Maze::InitMaze()
{
	int data;
	cout << "输入迷宫路径：" << endl;
	for (int i = 0; i<_row; ++i)
	{
		for (int j = 0; j<_col; ++j)
		{
			cin >> data;
			_pMaze[i][j].SetNode(data, i, j);
		}
	}
	cout << "开始寻找迷宫路径..." << endl;
	cout << endl;
}
void Maze::AnalyseMaze()
{
	for (int i = 0; i<_row; ++i)
	{
		for (int j = 0; j<_col; ++j)
		{
			if (_pMaze[i][j].Getvalue() == 0)
			{
				//右
				if (j<_col - 1 && _pMaze[i][j + 1].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_RIGHT,WAY_YES);
				}
				//下
				if (i<_row - 1 && _pMaze[i + 1][j].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_DOWN, WAY_YES);
				}
				//左
				if (j>0 && _pMaze[i][j - 1].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_LEFT, WAY_YES);
				}
				//上
				if (i>0 && _pMaze[i - 1][j].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_UP, WAY_YES);
				}
			}
		}
	}
}
void Maze::findMazePath()
{
	if (_pMaze[0][0].Getvalue() == 1 || _pMaze[_row-1][_col-1].Getvalue()==1 )
	{
		cout << "该迷宫不存在可通信的路径！" << endl;
		return;
	}
	else
		_stack.push(_pMaze[0][0]);
	while (!_stack.empty())
	{
		MazeNode&node = _stack.top();
		int i = node.GetX();
		int j = node.GetY();
		if ( i == _row - 1 && j == _col - 1)
		{
			cout << "该迷宫路径如下：" << endl;
			while (!_stack.empty())
			{
				node = _stack.top();
				_pMaze[node.GetX()][node.GetY()].SetNode('*' , i, j);
				_stack.pop();
			}
			showMazePath();
			break;
		}
		//右
		if ((j <_col - 1 )&& _pMaze[i][j].GetWayState(WAY_RIGHT)==WAY_YES)
		{
			_stack.push(_pMaze[i][j + 1]);
			_pMaze[i][j].SetNodeState(WAY_RIGHT, WAY_NO);
			_pMaze[i][j+1].SetNodeState(WAY_LEFT, WAY_NO);
			continue;
		}
		//下
		if ((i <_row - 1) && _pMaze[i][j].GetWayState(WAY_DOWN) == WAY_YES)
		{
			_stack.push(_pMaze[i + 1][j]);
			_pMaze[i][j].SetNodeState(WAY_DOWN, WAY_NO);
			_pMaze[i + 1][j].SetNodeState(WAY_UP, WAY_NO);
			continue;
		}
		//左
		if ((j > 0) && _pMaze[i][j].GetWayState(WAY_LEFT) == WAY_YES)
		{
			_stack.push(_pMaze[i][j - 1]);
			_pMaze[i][j].SetNodeState(WAY_LEFT, WAY_NO);
			_pMaze[i][j - 1].SetNodeState(WAY_RIGHT, WAY_NO);
			continue;
		}
		//上
		if ((i > 0) && _pMaze[i][j].GetWayState(WAY_UP) == WAY_YES)
		{
			_stack.push(_pMaze[i -1][j]);
			_pMaze[i][j].SetNodeState(WAY_UP, WAY_NO);
			_pMaze[i - 1][j].SetNodeState(WAY_DOWN, WAY_NO);
			continue;
		}
		_stack.pop();
		if (_stack.empty())
		{
			cout << "该迷宫不存在可通信的路径！" << endl;
			return;
		}
	}
}
void Maze::showMazePath()
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			int ret = _pMaze[i][j].Getvalue();
			if (ret != 0 && ret != 1)
			{
				cout << (char)ret << " ";
			}
			else
				cout << ret << " ";
		}
		cout << endl;
	}
}
int main()
{
	int row,col;
	cout << "输入迷宫路径的行列数(m x n): ";
	cin >> row >> col;
	Maze maze(row,col);
	maze.InitMaze();
	maze.AnalyseMaze();
	maze.findMazePath();
	return 0;
}