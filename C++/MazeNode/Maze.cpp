#include<iostream>
using namespace std;

#include "MazeNode.h"
#include "Stack.h"

/*
Ҫ��OOP���������һ���Թ�·������������
1.������У���ʾ���£�

�����Թ�·����������(m x n): 5 5
�����Թ�·����
0 0 0 1 0
0 0 1 0 0
0 0 0 1 0
1 0 0 1 0
1 1 0 0 0
��ʼѰ���Թ�·��...

���Թ������ڿ�ͨ�Ÿ��·����
·�����£�
* * 0 1 0
0 * 1 0 0
0 * 0 1 0
1 * * 1 0
1 1 * * *

Ҫ��0��ʾ��ͨ����·����1��ʾ�����ߵ�·���������Ͻ���ڣ�
�ҵ�һ����ͨ�е�·�������½ǣ�Ȼ�������Ӧ�Ĵ�ӡ������


*/

//�Թ���
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
	void InitMaze();//�����Թ�·��
	void AnalyseMaze();//Ϊ0�ڵ�����Ϊ����
	//����һ�������û�������Թ�·��
	void findMazePath();
	//��������ר������Ѱ���Թ�·����
	void showMazePath();
	//���������������д�ӡ�Թ�·����
private:
	int _row;
	int _col;
	MazeNode **_pMaze;
	SqStack  _stack;
};
void Maze::InitMaze()
{
	int data;
	cout << "�����Թ�·����" << endl;
	for (int i = 0; i<_row; ++i)
	{
		for (int j = 0; j<_col; ++j)
		{
			cin >> data;
			_pMaze[i][j].SetNode(data, i, j);
		}
	}
	cout << "��ʼѰ���Թ�·��..." << endl;
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
				//��
				if (j<_col - 1 && _pMaze[i][j + 1].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_RIGHT,WAY_YES);
				}
				//��
				if (i<_row - 1 && _pMaze[i + 1][j].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_DOWN, WAY_YES);
				}
				//��
				if (j>0 && _pMaze[i][j - 1].Getvalue() == 0)
				{
					_pMaze[i][j].SetNodeState(WAY_LEFT, WAY_YES);
				}
				//��
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
		cout << "���Թ������ڿ�ͨ�ŵ�·����" << endl;
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
			cout << "���Թ�·�����£�" << endl;
			while (!_stack.empty())
			{
				node = _stack.top();
				_pMaze[node.GetX()][node.GetY()].SetNode('*' , i, j);
				_stack.pop();
			}
			showMazePath();
			break;
		}
		//��
		if ((j <_col - 1 )&& _pMaze[i][j].GetWayState(WAY_RIGHT)==WAY_YES)
		{
			_stack.push(_pMaze[i][j + 1]);
			_pMaze[i][j].SetNodeState(WAY_RIGHT, WAY_NO);
			_pMaze[i][j+1].SetNodeState(WAY_LEFT, WAY_NO);
			continue;
		}
		//��
		if ((i <_row - 1) && _pMaze[i][j].GetWayState(WAY_DOWN) == WAY_YES)
		{
			_stack.push(_pMaze[i + 1][j]);
			_pMaze[i][j].SetNodeState(WAY_DOWN, WAY_NO);
			_pMaze[i + 1][j].SetNodeState(WAY_UP, WAY_NO);
			continue;
		}
		//��
		if ((j > 0) && _pMaze[i][j].GetWayState(WAY_LEFT) == WAY_YES)
		{
			_stack.push(_pMaze[i][j - 1]);
			_pMaze[i][j].SetNodeState(WAY_LEFT, WAY_NO);
			_pMaze[i][j - 1].SetNodeState(WAY_RIGHT, WAY_NO);
			continue;
		}
		//��
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
			cout << "���Թ������ڿ�ͨ�ŵ�·����" << endl;
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
	cout << "�����Թ�·����������(m x n): ";
	cin >> row >> col;
	Maze maze(row,col);
	maze.InitMaze();
	maze.AnalyseMaze();
	maze.findMazePath();
	return 0;
}