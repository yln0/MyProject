#include "Stack.h"
#include<iostream>
using namespace std;


SqStack::SqStack(int size)
{
	mtop = -1;
	msize = size;
	mpstack = new int[msize];
}
SqStack::~SqStack()
{
	delete[]mpstack;
	mpstack = NULL;
}
SqStack::SqStack(const SqStack &src)
{
	mtop = src.mtop;
	msize = src.msize;
	mpstack = new int[msize];
	for (int i = 0; i <=mtop; ++i)
	{
		mpstack[i] = src.mpstack[i];
	}
}
void SqStack::operator=(const SqStack &src)
{
	if (this == &src)
		return;
	delete[]mpstack;
	mtop = src.mtop;
	msize = src.msize;
	mpstack = new int[msize];
	for (int i = 0; i <= mtop; ++i)
	{
		mpstack[i] = src.mpstack[i];
	}
}
//入栈操作
void SqStack::push(int val)
{
	if (full())
		resize();
	mpstack[++mtop] = val;
}
//出栈操作
void SqStack::pop()
{
	if (empty())
		return;
	--mtop;
}
//获取栈顶元素
int SqStack::top()
{
	return mpstack[mtop];
}
void SqStack::show()
{
	for (int i = mtop; i>=0; --i)
	{
		cout << mpstack[i] << " ";
	}
	cout << endl;
}

void SqStack::modify(int data,int m)
{
	for (int i = 0; i <= mtop; ++i)
	{
		if (mpstack[i] == data)
		{
			mpstack[i] = m;
		}
	}
}