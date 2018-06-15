#ifndef STACK_H
#define STACK_H



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
	void push(int val);
	//��ջ����
	void pop();
	//��ȡջ��Ԫ��
	int top();
	//�ж�ջ��
	bool empty()
	{
		return mtop == -1;
	}
	//�ж�ջ��
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