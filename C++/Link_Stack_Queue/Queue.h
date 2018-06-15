#ifndef QUEUE_H
#define QUEUE_H


//循环队列
class CircleQue
{
public:
	CircleQue(int size = 10);
	~CircleQue();
	CircleQue(const CircleQue &src);
	void operator=(const CircleQue &src);

	void addQue(int val);
	void delQue();
	int front();
	int rear();

	bool empty()
	{
		return mfront == mrear;
	}
	bool full()
	{
		return (mrear + 1) % msize == mfront;
	}
	void modify(int data,int m);
	void show();
private:
	int *mpQue;
	int msize;
	int mfront;
	int mrear;
};


#endif