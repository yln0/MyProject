#include"Queue.h"
#include<iostream>
using namespace std;

CircleQue::CircleQue(int size)
{
	msize = size;
	mfront = 0;
	mrear = 0;
	mpQue = new int[size];
}
CircleQue::~CircleQue()
{
	delete[]mpQue;
	mpQue = NULL;
}
CircleQue::CircleQue(const CircleQue &src)
{
	msize = src.msize;
	mfront = src.mfront;
	mrear = src.mrear;
	mpQue = new int[msize];
	for (int i = mfront; i < mrear; i = (i + 1) % msize)
	{
		mpQue[i] = src.mpQue[i];
	}
}
void CircleQue::operator = (const CircleQue &src)
{
	if (this == &src)
		return;
	delete[]mpQue;
	msize = src.msize;
	mfront = src.mfront;
	mrear = src.mrear;
	mpQue = new int[msize];
	for (int i = mfront; i < mrear; i = (i + 1) % msize)
	{
		mpQue[i] = src.mpQue[i];
	}
}

void CircleQue::addQue(int val)
{
	if (full())
		return;
	mpQue[mrear] = val;
	mrear = (mrear + 1) % msize;
}
void CircleQue::delQue()
{
	if (empty())
		return;
	mfront = (mfront + 1) % msize;
}
int CircleQue::front()
{
	return mpQue[mfront];
}
int CircleQue::rear()
{
	if (empty())
		return NULL;
	return mpQue[(mrear - 1)%msize];
}

void CircleQue::show()
{
	for (int i = mfront; i < mrear; i = (i + 1) % msize)
	{
		cout << mpQue[i] << " ";
	}
	cout << endl;
}
void CircleQue::modify(int data, int m)
{
	for (int i = mfront; i < mrear; i = (i + 1) % msize)
	{
		if (mpQue[i] == data)
		{
			mpQue[i] = m;
		}
	}
}
