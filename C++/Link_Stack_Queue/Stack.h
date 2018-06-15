#ifndef STACK_H
#define STACK_H



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
	void push(int val);
	//³öÕ»²Ù×÷
	void pop();
	//»ñÈ¡Õ»¶¥ÔªËØ
	int top();
	//ÅÐ¶ÏÕ»¿Õ
	bool empty()
	{
		return mtop == -1;
	}
	//ÅÐ¶ÏÕ»Âú
	bool full()
	{
		return mtop == msize - 1;
	}
	void modify(int data,int m);
	void show();

private:
	void resize()
	{
		int *ptemp = new int[msize * 2];
		for (int i = 0; i <= mtop; ++i)
		{
			ptemp[i] = mpstack[i];
		}
		delete[]mpstack;
		msize *= 2;
		mpstack = ptemp;
	}
	int *mpstack;
	int mtop;
	int msize;
};

#endif