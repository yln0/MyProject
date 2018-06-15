#ifndef STACK_H
#define STACK_H


#include"MazeNode.h"

//Ë³ÐòÕ»
const int STACK_SIZE = 10;
class SqStack
{
public:
	SqStack(int size = 10);
	~SqStack();
	SqStack(const SqStack & src);
	void operator=(const SqStack & src);

	//ÈëÕ»²Ù×÷
	void push(MazeNode &val);
	//³öÕ»²Ù×÷
	void pop();
	//»ñÈ¡Õ»¶¥ÔªËØ
	MazeNode& top()const
	{
		return mpstack[mtop];
	}
	//ÅÐ¶ÏÕ»¿Õ
	bool empty()const
	{
		return mtop == -1;
	}
	//ÅÐ¶ÏÕ»Âú
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