#include<iostream>
using namespace std;

#include "Stack.h"
#include"MazeNode.h"

SqStack::SqStack(int size) :msize(size), mtop(-1)
{
	mpstack = new MazeNode[msize];
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
	mpstack = new MazeNode[msize];
	for (int i = 0; i <= mtop; ++i)
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
	mpstack = new MazeNode[msize];
	for (int i = 0; i <= mtop; ++i)
	{
		mpstack[i] = src.mpstack[i];
	}
}
void SqStack::push(MazeNode &val)
{
	if (full())
		resize();
	mpstack[++mtop] = val;
}
void SqStack::pop()
{
	if (empty())
		return;
	--mtop;
}
