#ifndef STACK_H
#define STACK_H


#include"MazeNode.h"

//˳��ջ
const int STACK_SIZE = 10;
class SqStack
{
public:
	SqStack(int size = 10);
	~SqStack();
	SqStack(const SqStack & src);
	void operator=(const SqStack & src);

	//��ջ����
	void push(MazeNode &val);
	//��ջ����
	void pop();
	//��ȡջ��Ԫ��
	MazeNode& top()const
	{
		return mpstack[mtop];
	}
	//�ж�ջ��
	bool empty()const
	{
		return mtop == -1;
	}
	//�ж�ջ��
	bool full()const
	{
		return mtop == msize - 1;
	}
private:
	void resize()
	{
		MazeNode *ptemp = new MazeNode[msize * 2];
		for (int i = 0; i <= mtop; ++i)
		{
			ptemp[i] = mpstack[i];
		}
		delete[]mpstack;
		msize *= 2;
		mpstack = ptemp;
	}
	MazeNode *mpstack;
	int mtop;
	int msize;
};

#endif